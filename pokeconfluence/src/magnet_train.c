#include "global.h"
#include "bg.h"
#include "decompress.h"
#include "event_data.h"
#include "field_specials.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "constants/event_objects.h"
#include "constants/johto_flags.h"
#include "constants/maps.h"
#include "constants/rgb.h"
#include "constants/songs.h"

// POKE-CONFLUENCE: Magnet Train Goldenrod <-> Saffron Pass Subsystem

enum
{
    TAG_MAGNET_TRAIN = 0x8840,
};

struct MagnetTrainCutscene
{
    u8 bgTaskId;
    u8 state;
    u8 direction; // 0 = Eastbound (Goldenrod -> Saffron), 1 = Westbound (Saffron -> Goldenrod)
    u16 timer;
    u16 bg0Offset;
    u16 bg1Offset;
    u16 bg2Offset;
    u8 trainSpriteId;
    u16 *groundTilemap;
    u16 *treesTilemap;
    u16 *bgMountainsTilemap;
    u8 bgTilemapBuffers[4][BG_SCREEN_SIZE];
};

static EWRAM_DATA struct MagnetTrainCutscene *sMagnetTrain = NULL;

static void CB2_LoadMagnetTrain(void);
static void CB2_MagnetTrain(void);
static void CB2_EndMagnetTrain(void);
static void VBlankCB_MagnetTrain(void);
static void Task_MagnetTrain(u8 taskId);
static void Task_LoadMagnetTrain(u8 taskId);
static void SetBgRegs(bool8 active);

static const struct BgTemplate sMagnetTrainBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 28,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    },
    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 29,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
    {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0
    },
};

static const u16 sGround_Tilemap[] = INCBIN_U16("graphics/cable_car/ground.bin.smolTM");
static const u16 sTrees_Tilemap[] = INCBIN_U16("graphics/cable_car/trees.bin.smolTM");
static const u16 sBgMountains_Tilemap[] = INCBIN_U16("graphics/cable_car/bg_mountains.bin.smolTM");

static const struct CompressedSpriteSheet sMagnetTrainSpriteSheets[] = {
    { gCableCar_Gfx, 0x800, TAG_MAGNET_TRAIN },
    { }
};

static const struct SpritePalette sMagnetTrainSpritePalettes[] = {
    { gCableCar_Pal, TAG_MAGNET_TRAIN },
    { }
};

static const struct OamData sOam_MagnetTrain =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = FALSE,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(64x64),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0
};

static void SpriteCB_MagnetTrain(struct Sprite *sprite)
{
    if (sMagnetTrain != NULL)
    {
        // Subtle vertical vibration on the magnetic rail
        sprite->y2 = ((sMagnetTrain->timer % 4) < 2) ? 0 : 1;
    }
}

static const struct SpriteTemplate sSpriteTemplate_MagnetTrain =
{
    .tileTag = TAG_MAGNET_TRAIN,
    .paletteTag = TAG_MAGNET_TRAIN,
    .oam = &sOam_MagnetTrain,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_MagnetTrain,
};

// POKE-CONFLUENCE: Pre-warp destination configuration & scene management
void MagnetTrainWarp(void)
{
    if (gSpecialVar_0x8004 == 0) // Eastbound: Goldenrod -> Saffron
    {
        SetWarpDestination(MAP_GROUP(MAP_JOHTO_SAFFRON_MAGNET_TRAIN_STATION),
                           MAP_NUM(MAP_JOHTO_SAFFRON_MAGNET_TRAIN_STATION),
                           WARP_ID_NONE, 11, 5);
        VarSet(VAR_JOHTO_SCENE_SAFFRON_MAGNET_TRAIN_STATION, 1);
    }
    else // Westbound: Saffron -> Goldenrod
    {
        SetWarpDestination(MAP_GROUP(MAP_JOHTO_GOLDENROD_MAGNET_TRAIN_STATION),
                           MAP_NUM(MAP_JOHTO_GOLDENROD_MAGNET_TRAIN_STATION),
                           WARP_ID_NONE, 11, 5);
        VarSet(VAR_JOHTO_SCENE_GOLDENROD_MAGNET_TRAIN_STATION, 1);
    }
}

// POKE-CONFLUENCE: Initiates high-speed Magnet Train transit cutscene
void MagnetTrain(void)
{
    LockPlayerFieldControls();
    CreateTask(Task_LoadMagnetTrain, 1);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
}

static void Task_LoadMagnetTrain(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(CB2_LoadMagnetTrain);
        DestroyTask(taskId);
    }
}

static void CB2_LoadMagnetTrain(void)
{
    u32 sizeOut = 0;

    switch (gMain.state)
    {
    case 0:
    default:
        SetVBlankCallback(NULL);
        SetBgRegs(FALSE);
        DmaFillLarge16(3, 0, (void *)VRAM, VRAM_SIZE, 0x1000);
        DmaFill32Defvars(3, 0, (void *)OAM, OAM_SIZE);
        DmaFill16Defvars(3, 0, (void *)PLTT, PLTT_SIZE);
        sMagnetTrain = AllocZeroed(sizeof(*sMagnetTrain));
        if (sMagnetTrain != NULL)
            sMagnetTrain->direction = gSpecialVar_0x8004;
        gMain.state++;
        break;

    case 1:
        ResetSpriteData();
        ResetTasks();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetTempTileDataBuffers();

        InitMapMusic();
        ResetMapMusic();
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sMagnetTrainBgTemplates, ARRAY_COUNT(sMagnetTrainBgTemplates));
        SetBgTilemapBuffer(0, sMagnetTrain->bgTilemapBuffers[0]);
        SetBgTilemapBuffer(1, sMagnetTrain->bgTilemapBuffers[1]);
        SetBgTilemapBuffer(2, sMagnetTrain->bgTilemapBuffers[2]);
        gSpriteCoordOffsetX = gSpriteCoordOffsetY = 0;
        gMain.state++;
        break;

    case 2:
        LoadCompressedSpriteSheet(&sMagnetTrainSpriteSheets[0]);
        LoadSpritePalettes(sMagnetTrainSpritePalettes);
        sMagnetTrain->groundTilemap = malloc_and_decompress(sGround_Tilemap, &sizeOut);
        sMagnetTrain->treesTilemap = malloc_and_decompress(sTrees_Tilemap, &sizeOut);
        sMagnetTrain->bgMountainsTilemap = malloc_and_decompress(sBgMountains_Tilemap, &sizeOut);
        DecompressAndCopyTileDataToVram(0, gCableCarBg_Gfx, 0, 0, 0);
        gMain.state++;
        break;

    case 3:
        if (!FreeTempTileDataBuffersIfPossible())
        {
            LoadPalette(gCableCarBg_Pal, BG_PLTT_ID(0), 4 * PLTT_SIZE_4BPP);
            gMain.state++;
        }
        break;

    case 4:
        sMagnetTrain->trainSpriteId = CreateSprite(&sSpriteTemplate_MagnetTrain, 120, 84, 0);
        gMain.state++;
        break;

    case 5:
        // Populate background tilemap buffers
        CopyToBgTilemapBufferRect_ChangePalette(2, sMagnetTrain->bgMountainsTilemap, 0, 0, 30, 20, 17);
        CopyToBgTilemapBufferRect_ChangePalette(1, sMagnetTrain->treesTilemap, 0, 10, 32, 10, 17);
        CopyToBgTilemapBufferRect_ChangePalette(0, sMagnetTrain->groundTilemap, 0, 14, 32, 6, 17);
        gMain.state++;
        break;

    case 6:
        BeginNormalPaletteFade(PALETTES_ALL, 3, 16, 0, RGB_BLACK);
        FadeInNewBGM(MUS_CABLE_CAR, 1);
        SetBgRegs(TRUE);
        gMain.state++;
        break;

    case 7:
        IntrEnable(INTR_FLAG_VBLANK);
        SetVBlankCallback(VBlankCB_MagnetTrain);
        SetMainCallback2(CB2_MagnetTrain);
        CreateTask(Task_MagnetTrain, 0);
        break;
    }
}

static void CB2_MagnetTrain(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
    MapMusicMain();
}

static void VBlankCB_MagnetTrain(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Task_MagnetTrain(u8 taskId)
{
    if (sMagnetTrain == NULL)
        return;

    sMagnetTrain->timer++;

    switch (sMagnetTrain->state)
    {
    case 0: // Departure whoosh & sound effects
        PlaySE(SE_WARP_IN);
        sMagnetTrain->state = 1;
        break;

    case 1: // Acceleration phase (timer 0..50)
        if (sMagnetTrain->timer % 25 == 0)
            PlaySE(SE_TRUCK_MOVE);
        if (sMagnetTrain->timer >= 50)
            sMagnetTrain->state = 2;
        break;

    case 2: // High-speed cruising across the Kanto/Johto magnetic railway
        if (sMagnetTrain->timer % 30 == 0)
            PlaySE(SE_TRUCK_MOVE);
        if (sMagnetTrain->timer >= 180)
        {
            PlaySE(SE_DING_DONG);
            sMagnetTrain->state = 3;
        }
        break;

    case 3: // Deceleration & arrival fade
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        sMagnetTrain->state = 4;
        break;

    case 4: // Wait for palette fade before warping into destination station
        if (!gPaletteFade.active)
        {
            SetMainCallback2(CB2_EndMagnetTrain);
            DestroyTask(taskId);
        }
        break;
    }

    // High-speed parallax background scrolling
    if (sMagnetTrain->state >= 1 && sMagnetTrain->state <= 3)
    {
        if (sMagnetTrain->direction == 0) // Eastbound (Johto -> Kanto)
        {
            sMagnetTrain->bg0Offset += 6;
            sMagnetTrain->bg1Offset += 3;
            sMagnetTrain->bg2Offset += 1;
        }
        else // Westbound (Kanto -> Johto)
        {
            sMagnetTrain->bg0Offset -= 6;
            sMagnetTrain->bg1Offset -= 3;
            sMagnetTrain->bg2Offset -= 1;
        }

        SetGpuReg(REG_OFFSET_BG0HOFS, sMagnetTrain->bg0Offset);
        SetGpuReg(REG_OFFSET_BG1HOFS, sMagnetTrain->bg1Offset);
        SetGpuReg(REG_OFFSET_BG2HOFS, sMagnetTrain->bg2Offset);
    }
}

static void CB2_EndMagnetTrain(void)
{
    HideBg(0);
    HideBg(1);
    HideBg(2);
    SetBgRegs(FALSE);
    gSpriteCoordOffsetX = 0;

    ResetTasks();
    ResetSpriteData();
    ResetPaletteFade();
    UnsetBgTilemapBuffer(0);
    UnsetBgTilemapBuffer(1);
    UnsetBgTilemapBuffer(2);
    ResetBgsAndClearDma3BusyFlags(0);

    FREE_AND_SET_NULL(sMagnetTrain->bgMountainsTilemap);
    FREE_AND_SET_NULL(sMagnetTrain->treesTilemap);
    FREE_AND_SET_NULL(sMagnetTrain->groundTilemap);
    FREE_AND_SET_NULL(sMagnetTrain);

    DmaFillLarge16(3, 0, (void *)VRAM, VRAM_SIZE, 0x1000);
    DmaFill32Defvars(3, 0, (void *)OAM, OAM_SIZE);
    DmaFill16Defvars(3, 0, (void *)PLTT, PLTT_SIZE);

    WarpIntoMap();
    gFieldCallback = NULL;
    SetMainCallback2(CB2_LoadMap);
}

static void SetBgRegs(bool8 active)
{
    switch (active)
    {
    case FALSE:
    default:
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN1H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WIN1V, 0);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        SetGpuReg(REG_OFFSET_BG3CNT, 0);
        SetGpuReg(REG_OFFSET_BG2CNT, 0);
        SetGpuReg(REG_OFFSET_BG1CNT, 0);
        SetGpuReg(REG_OFFSET_BG0CNT, 0);
        SetGpuReg(REG_OFFSET_BG3HOFS, 0);
        SetGpuReg(REG_OFFSET_BG3VOFS, 0);
        SetGpuReg(REG_OFFSET_BG2HOFS, 0);
        SetGpuReg(REG_OFFSET_BG2VOFS, 0);
        SetGpuReg(REG_OFFSET_BG1HOFS, 0);
        SetGpuReg(REG_OFFSET_BG1VOFS, 0);
        SetGpuReg(REG_OFFSET_BG0HOFS, 0);
        SetGpuReg(REG_OFFSET_BG0VOFS, 0);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        break;
    case TRUE:
        SetGpuReg(REG_OFFSET_WININ, 0);
        SetGpuReg(REG_OFFSET_WINOUT, 0);
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN1H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WIN1V, 0);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_BG0_ON | DISPCNT_BG1_ON | DISPCNT_BG2_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        ShowBg(2);
        break;
    }
}
