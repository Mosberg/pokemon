// POKE-CONFLUENCE: Surfing Pikachu Beach Minigame Subsystem (pokeyellow)
#include "global.h"
#include "malloc.h"
#include "task.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "scanline_effect.h"
#include "sound.h"
#include "text.h"
#include "window.h"
#include "palette.h"
#include "bg.h"
#include "gpu_regs.h"
#include "overworld.h"
#include "pokemon.h"
#include "battle.h"
#include "script.h"
#include "text_window.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "trig.h"
#include "string_util.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/moves.h"
#include "constants/flags.h"
#include "constants/vars.h"
#include "constants/game_stat.h"
#include "constants/rgb.h"
#include "constants/event_objects.h"
#include "field_specials.h"
#include "surfing_pikachu.h"

#define SURF_COURSE_MAX_DISTANCE 2400
#define SURF_BASE_WATER_Y 88

enum SurfingMinigameState
{
    SURF_STATE_INIT = 0,
    SURF_STATE_COUNTDOWN,
    SURF_STATE_SURFING,
    SURF_STATE_AIRBORNE,
    SURF_STATE_WIPEOUT,
    SURF_STATE_COURSE_COMPLETE,
    SURF_STATE_RESULTS,
    SURF_STATE_EXIT
};

struct SurfingPikachuData
{
    MainCallback savedCallback;
    u8 state;
    u8 substate;
    u16 timer;
    u16 hp;
    u16 distance;
    u16 speed;
    s16 pikaX;
    s16 pikaY;
    s16 yVel;
    s16 rotAngle;
    s32 airRotDegrees;
    u8 flipsInJump;
    u32 radness;
    u32 totalScore;
    u16 wavePhase;
    u8 pikaSpriteId;
    u8 hudWindowId;
    u8 resultsWindowId;
    bool8 isNewHighScore;
};

static EWRAM_DATA struct SurfingPikachuData *sSurfingData = NULL;

static void SurfingPikachu_MainCallback(void);
static void SurfingPikachu_VblankHandler(void);
static void SurfingPikachu_SetupBgAndWindows(void);
static void SurfingPikachu_UpdateHud(void);
static void SurfingPikachu_DrawResults(void);
static void SurfingPikachu_Task(u8 taskId);
static void SurfingPikachu_FreeAndExit(u8 taskId);

static const struct BgTemplate sSurfingBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0,
    },
    {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0,
    },
};

static const struct WindowTemplate sSurfingWindowTemplates[] =
{
    {
        .bg = 0,
        .tilemapLeft = 1,
        .tilemapTop = 1,
        .width = 28,
        .height = 3,
        .paletteNum = 15,
        .baseBlock = 0x010,
    },
    {
        .bg = 0,
        .tilemapLeft = 3,
        .tilemapTop = 5,
        .width = 24,
        .height = 13,
        .paletteNum = 15,
        .baseBlock = 0x080,
    },
    DUMMY_WIN_TEMPLATE,
};

bool32 HasSurfingPikachuInParty(void)
{
    u32 i, j;

    for (i = 0; i < gPartiesCount[B_TRAINER_PLAYER]; i++)
    {
        struct Pokemon *mon = &gParties[B_TRAINER_PLAYER][i];

        if (GetMonData(mon, MON_DATA_IS_EGG))
            continue;

        if (GetMonData(mon, MON_DATA_SPECIES) == SPECIES_PIKACHU)
        {
            for (j = 0; j < MAX_MON_MOVES; j++)
            {
                if (GetMonData(mon, MON_DATA_MOVE1 + j) == MOVE_SURF)
                    return TRUE;
            }
        }
    }
    return FALSE;
}

void CheckSurfingPikachuInParty(void)
{
    gSpecialVar_Result = HasSurfingPikachuInParty();
}

void GetSurfingPikachuScores(void)
{
    u16 highScore = VarGet(VAR_SURFING_PIKACHU_HIGH_SCORE);
    u16 radness = VarGet(VAR_SURFING_PIKACHU_RADNESS);

    gSpecialVar_0x8004 = highScore;
    gSpecialVar_0x8005 = radness;
    gSpecialVar_Result = (highScore > 0);
}

void StartSurfingPikachuMinigameSpecial(void)
{
    LockPlayerFieldControls();
    StartSurfingPikachuMinigame(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}

void StartSurfingPikachuMinigame(MainCallback exitCallback)
{
    sSurfingData = AllocZeroed(sizeof(struct SurfingPikachuData));
    sSurfingData->savedCallback = exitCallback;
    sSurfingData->state = SURF_STATE_INIT;
    sSurfingData->hp = 999;
    sSurfingData->distance = 0;
    sSurfingData->speed = 2;
    sSurfingData->pikaX = 64;
    sSurfingData->pikaY = SURF_BASE_WATER_Y;
    sSurfingData->yVel = 0;
    sSurfingData->rotAngle = 0;
    sSurfingData->airRotDegrees = 0;
    sSurfingData->flipsInJump = 0;
    sSurfingData->radness = 0;
    sSurfingData->totalScore = 0;
    sSurfingData->wavePhase = 0;
    sSurfingData->isNewHighScore = FALSE;

    SetMainCallback2(SurfingPikachu_MainCallback);
}

static void SurfingPikachu_MainCallback(void)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        SurfingPikachu_SetupBgAndWindows();
        gMain.state++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() == TRUE)
            return;
        CreateTask(SurfingPikachu_Task, 0);
        PlayNewMapMusic(MUS_RG_SURF);
        BlendPalettes(PALETTES_ALL, 0x10, 0);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0x10, 0, 0);
        SetVBlankCallback(SurfingPikachu_VblankHandler);
        SetMainCallback2(SurfingPikachu_MainCallback);
        gMain.state++;
        break;
    case 2:
        RunTasks();
        AnimateSprites();
        BuildOamBuffer();
        DoScheduledBgTilemapCopiesToVram();
        UpdatePaletteFade();
        break;
    }
}

static void SurfingPikachu_VblankHandler(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void SurfingPikachu_SetupBgAndWindows(void)
{
    ResetAllBgsCoordinates();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sSurfingBgTemplates, ARRAY_COUNT(sSurfingBgTemplates));
    InitWindows(sSurfingWindowTemplates);
    DeactivateAllTextPrinters();

    LoadPalette(GetTextWindowPalette(0), BG_PLTT_ID(15), PLTT_SIZE_4BPP);
    ShowBg(0);
    ShowBg(1);

    // Create Pikachu sprite
    sSurfingData->pikaSpriteId = CreateObjectGraphicsSprite(OBJ_EVENT_GFX_PIKACHU, SpriteCallbackDummy, sSurfingData->pikaX, sSurfingData->pikaY, 0);
    gSprites[sSurfingData->pikaSpriteId].oam.priority = 1;

    SurfingPikachu_UpdateHud();
}

static void SurfingPikachu_UpdateHud(void)
{
    u8 strBuf[64];
    u8 tempBuf[16];

    FillWindowPixelBuffer(0, PIXEL_FILL(1));
    PutWindowTilemap(0);

    StringCopy(strBuf, COMPOUND_STRING("RAD: "));
    ConvertIntToDecimalStringN(tempBuf, sSurfingData->radness, STR_CONV_MODE_RIGHT_ALIGN, 5);
    StringAppend(strBuf, tempBuf);

    StringAppend(strBuf, COMPOUND_STRING("  TIME: "));
    ConvertIntToDecimalStringN(tempBuf, sSurfingData->hp, STR_CONV_MODE_RIGHT_ALIGN, 3);
    StringAppend(strBuf, tempBuf);

    StringAppend(strBuf, COMPOUND_STRING("  DIST: "));
    ConvertIntToDecimalStringN(tempBuf, sSurfingData->distance / 100, STR_CONV_MODE_RIGHT_ALIGN, 2);
    StringAppend(strBuf, tempBuf);
    StringAppend(strBuf, COMPOUND_STRING("/24"));

    AddTextPrinterParameterized(0, FONT_SMALL, strBuf, 4, 4, 0, NULL);
    CopyWindowToVram(0, COPYWIN_FULL);
}

static void SurfingPikachu_DrawResults(void)
{
    u8 textBuf[64];
    u8 numBuf[16];
    u16 yOffset = 8;

    FillWindowPixelBuffer(1, PIXEL_FILL(1));
    PutWindowTilemap(1);

    AddTextPrinterParameterized(1, FONT_NORMAL, COMPOUND_STRING("--- SURFING RESULTS ---"), 12, yOffset, 0, NULL);
    yOffset += 18;

    StringCopy(textBuf, COMPOUND_STRING("TIME BONUS: "));
    ConvertIntToDecimalStringN(numBuf, sSurfingData->hp * 5, STR_CONV_MODE_RIGHT_ALIGN, 5);
    StringAppend(textBuf, numBuf);
    StringAppend(textBuf, COMPOUND_STRING(" PTS"));
    AddTextPrinterParameterized(1, FONT_NORMAL, textBuf, 8, yOffset, 0, NULL);
    yOffset += 16;

    StringCopy(textBuf, COMPOUND_STRING("RADNESS:    "));
    ConvertIntToDecimalStringN(numBuf, sSurfingData->radness, STR_CONV_MODE_RIGHT_ALIGN, 5);
    StringAppend(textBuf, numBuf);
    StringAppend(textBuf, COMPOUND_STRING(" PTS"));
    AddTextPrinterParameterized(1, FONT_NORMAL, textBuf, 8, yOffset, 0, NULL);
    yOffset += 16;

    StringCopy(textBuf, COMPOUND_STRING("TOTAL:      "));
    ConvertIntToDecimalStringN(numBuf, sSurfingData->totalScore, STR_CONV_MODE_RIGHT_ALIGN, 5);
    StringAppend(textBuf, numBuf);
    StringAppend(textBuf, COMPOUND_STRING(" PTS"));
    AddTextPrinterParameterized(1, FONT_NORMAL, textBuf, 8, yOffset, 0, NULL);
    yOffset += 18;

    if (sSurfingData->isNewHighScore)
    {
        AddTextPrinterParameterized(1, FONT_BOLD, COMPOUND_STRING("RADICAL! NEW HI-SCORE!"), 8, yOffset, 0, NULL);
        yOffset += 16;
    }

    AddTextPrinterParameterized(1, FONT_SMALL, COMPOUND_STRING("Press A to Return"), 32, yOffset, 0, NULL);
    CopyWindowToVram(1, COPYWIN_FULL);
}

static void SurfingPikachu_Task(u8 taskId)
{
    s16 waterY;
    s16 angleDiff;
    u16 oldHighScore;

    if (gPaletteFade.active)
        return;

    switch (sSurfingData->state)
    {
    case SURF_STATE_INIT:
        sSurfingData->timer = 60;
        sSurfingData->state = SURF_STATE_COUNTDOWN;
        break;

    case SURF_STATE_COUNTDOWN:
        if (--sSurfingData->timer == 0)
        {
            PlaySE(SE_PIN);
            sSurfingData->state = SURF_STATE_SURFING;
        }
        break;

    case SURF_STATE_SURFING:
        sSurfingData->wavePhase = (sSurfingData->wavePhase + (sSurfingData->speed * 3)) & 0xFF;
        waterY = SURF_BASE_WATER_Y + (Sin(sSurfingData->wavePhase, 20) >> 1);

        sSurfingData->pikaY = waterY;
        sSurfingData->distance += sSurfingData->speed;
        if (sSurfingData->hp > 0)
            sSurfingData->hp--;

        // Controls on water
        if (JOY_HELD(DPAD_RIGHT) && sSurfingData->speed < 5)
            sSurfingData->speed++;
        else if (JOY_HELD(DPAD_LEFT) && sSurfingData->speed > 1)
            sSurfingData->speed--;

        // Jump off wave crest
        if (JOY_NEW(A_BUTTON | B_BUTTON))
        {
            sSurfingData->yVel = -7 - (sSurfingData->speed / 2);
            sSurfingData->airRotDegrees = 0;
            sSurfingData->flipsInJump = 0;
            sSurfingData->rotAngle = 0;
            sSurfingData->state = SURF_STATE_AIRBORNE;
            PlaySE(SE_BALL_BOUNCE_1);
        }

        // Check course completion or timeout
        if (sSurfingData->distance >= SURF_COURSE_MAX_DISTANCE || sSurfingData->hp == 0)
        {
            sSurfingData->state = SURF_STATE_COURSE_COMPLETE;
        }
        break;

    case SURF_STATE_AIRBORNE:
        sSurfingData->pikaY += sSurfingData->yVel;
        sSurfingData->yVel += 1; // gravity
        sSurfingData->distance += sSurfingData->speed;
        if (sSurfingData->hp > 0)
            sSurfingData->hp--;

        // Flips in the air
        if (JOY_NEW(DPAD_LEFT) || JOY_HELD(DPAD_LEFT))
        {
            sSurfingData->rotAngle = (sSurfingData->rotAngle + 315) % 360;
            sSurfingData->airRotDegrees += 45;
        }
        else if (JOY_NEW(DPAD_RIGHT) || JOY_HELD(DPAD_RIGHT))
        {
            sSurfingData->rotAngle = (sSurfingData->rotAngle + 45) % 360;
            sSurfingData->airRotDegrees += 45;
        }

        // Award trick flip bonus every 360 degrees
        if (sSurfingData->airRotDegrees >= 360)
        {
            sSurfingData->airRotDegrees -= 360;
            sSurfingData->flipsInJump++;
            sSurfingData->radness += 100 * sSurfingData->flipsInJump;
            PlaySE(SE_EXP);
        }

        // Landing check
        sSurfingData->wavePhase = (sSurfingData->wavePhase + (sSurfingData->speed * 3)) & 0xFF;
        waterY = SURF_BASE_WATER_Y + (Sin(sSurfingData->wavePhase, 20) >> 1);

        if (sSurfingData->pikaY >= waterY)
        {
            sSurfingData->pikaY = waterY;
            angleDiff = sSurfingData->rotAngle % 360;
            if (angleDiff > 180)
                angleDiff = 360 - angleDiff;

            if (angleDiff <= 30)
            {
                // Clean landing
                sSurfingData->radness += 500;
                if (sSurfingData->speed < 5)
                    sSurfingData->speed++;
                PlaySE(SE_SUCCESS);
                sSurfingData->state = SURF_STATE_SURFING;
            }
            else if (angleDiff <= 60)
            {
                // Rough landing
                sSurfingData->radness += 100;
                PlaySE(SE_SHIP);
                sSurfingData->state = SURF_STATE_SURFING;
            }
            else if (angleDiff <= 90)
            {
                // Hard landing
                if (sSurfingData->speed > 1)
                    sSurfingData->speed--;
                PlaySE(SE_PIN);
                sSurfingData->state = SURF_STATE_SURFING;
            }
            else
            {
                // Wipeout
                sSurfingData->hp = (sSurfingData->hp > 100) ? sSurfingData->hp - 100 : 0;
                sSurfingData->speed = 1;
                sSurfingData->timer = 30;
                PlaySE(SE_BANG);
                sSurfingData->state = SURF_STATE_WIPEOUT;
            }
        }

        if (sSurfingData->distance >= SURF_COURSE_MAX_DISTANCE || sSurfingData->hp == 0)
        {
            sSurfingData->state = SURF_STATE_COURSE_COMPLETE;
        }
        break;

    case SURF_STATE_WIPEOUT:
        if (--sSurfingData->timer == 0)
        {
            sSurfingData->rotAngle = 0;
            sSurfingData->state = SURF_STATE_SURFING;
        }
        break;

    case SURF_STATE_COURSE_COMPLETE:
        sSurfingData->totalScore = (sSurfingData->hp * 5) + sSurfingData->radness;
        oldHighScore = VarGet(VAR_SURFING_PIKACHU_HIGH_SCORE);

        if (sSurfingData->totalScore > oldHighScore)
        {
            sSurfingData->isNewHighScore = TRUE;
            VarSet(VAR_SURFING_PIKACHU_HIGH_SCORE, sSurfingData->totalScore);
            VarSet(VAR_SURFING_PIKACHU_RADNESS, sSurfingData->radness);
            IncrementGameStat(GAME_STAT_SURFING_PIKACHU_HIGH_SCORE);
            PlaySE(SE_RG_CARD_FLIP);
        }
        else
        {
            PlaySE(SE_SUCCESS);
        }

        SurfingPikachu_DrawResults();
        sSurfingData->state = SURF_STATE_RESULTS;
        break;

    case SURF_STATE_RESULTS:
        if (JOY_NEW(A_BUTTON | B_BUTTON))
        {
            PlaySE(SE_SELECT);
            BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 0x10, 0);
            sSurfingData->state = SURF_STATE_EXIT;
        }
        break;

    case SURF_STATE_EXIT:
        SurfingPikachu_FreeAndExit(taskId);
        break;
    }

    // Update sprite coordinate
    gSprites[sSurfingData->pikaSpriteId].x = sSurfingData->pikaX;
    gSprites[sSurfingData->pikaSpriteId].y = sSurfingData->pikaY;

    if (sSurfingData->state != SURF_STATE_RESULTS && sSurfingData->state != SURF_STATE_EXIT)
        SurfingPikachu_UpdateHud();
}

static void SurfingPikachu_FreeAndExit(u8 taskId)
{
    MainCallback callback = sSurfingData->savedCallback;

    FreeAllWindowBuffers();
    if (sSurfingData != NULL)
    {
        Free(sSurfingData);
        sSurfingData = NULL;
    }
    DestroyTask(taskId);
    SetMainCallback2(callback);
}
