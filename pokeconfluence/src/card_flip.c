#include "global.h"
#include "coins.h"
#include "event_data.h"
#include "item.h"
#include "random.h"
#include "string_util.h"
#include "strings.h"
#include "card_flip.h"
#include "constants/items.h"

// POKE-CONFLUENCE: Authentic GBC Crystal Goldenrod & Celadon Game Corner Card Flip Minigame
// Reference: games/gbc/pokecrystal/engine/games/card_flip.asm

static const u8 sSuitPikachu[]    = _("PIKACHU");
static const u8 sSuitJigglypuff[] = _("JIGGLYPUFF");
static const u8 sSuitPoliwag[]    = _("POLIWAG");
static const u8 sSuitOddish[]     = _("ODDISH");
static const u8 sText_Space[]     = _(" ");

static const u8 *const sCardFlipSuitNames[CARDFLIP_NUM_SUITS] = {
    sSuitPikachu,
    sSuitJigglypuff,
    sSuitPoliwag,
    sSuitOddish,
};

static EWRAM_DATA struct CardFlipState sCardFlip = {0};

void CardFlip_InitDeck(void)
{
    u32 i;

    for (i = 0; i < CARDFLIP_DECK_SIZE; i++)
    {
        sCardFlip.deck[i] = i;
        sCardFlip.discarded[i] = FALSE;
    }

    sCardFlip.cardsPlayed = 0;
    sCardFlip.dealtCard1 = 0;
    sCardFlip.dealtCard2 = 0;
    sCardFlip.chosenCard = 0;
    sCardFlip.betType = 0;
    sCardFlip.betParam1 = 0;
    sCardFlip.betParam2 = 0;
    sCardFlip.lastPayout = 0;

    CardFlip_ShuffleDeck();
}

void CardFlip_ShuffleDeck(void)
{
    u32 i;

    for (i = 0; i < CARDFLIP_DECK_SIZE; i++)
    {
        sCardFlip.deck[i] = i;
        sCardFlip.discarded[i] = FALSE;
    }

    // Fisher-Yates shuffle
    for (i = CARDFLIP_DECK_SIZE - 1; i > 0; i--)
    {
        u32 j = Random() % (i + 1);
        u8 temp = sCardFlip.deck[i];
        sCardFlip.deck[i] = sCardFlip.deck[j];
        sCardFlip.deck[j] = temp;
    }

    sCardFlip.cardsPlayed = 0;
}

void CardFlip_DealTwoCards(void)
{
    if (sCardFlip.cardsPlayed + 2 > CARDFLIP_DECK_SIZE)
        CardFlip_ShuffleDeck();

    sCardFlip.dealtCard1 = sCardFlip.deck[sCardFlip.cardsPlayed];
    sCardFlip.dealtCard2 = sCardFlip.deck[sCardFlip.cardsPlayed + 1];
    sCardFlip.chosenCard = sCardFlip.dealtCard1;
    sCardFlip.cardsPlayed += 2;
}

void CardFlip_ChooseCard(u8 which)
{
    if (which == 2)
        sCardFlip.chosenCard = sCardFlip.dealtCard2;
    else
        sCardFlip.chosenCard = sCardFlip.dealtCard1;
}

void CardFlip_SetBet(u8 betType, u8 param1, u8 param2)
{
    sCardFlip.betType = betType;
    sCardFlip.betParam1 = param1;
    sCardFlip.betParam2 = param2;
}

u8 CardFlip_GetCardSuit(u8 card)
{
    return card % CARDFLIP_NUM_SUITS;
}

u8 CardFlip_GetCardRank(u8 card)
{
    return (card / CARDFLIP_NUM_SUITS) + 1;
}

const u8 *CardFlip_GetSuitName(u8 suit)
{
    if (suit >= CARDFLIP_NUM_SUITS)
        return sCardFlipSuitNames[0];
    return sCardFlipSuitNames[suit];
}

bool8 CardFlip_EvaluateBet(void)
{
    u8 card = sCardFlip.chosenCard;
    u8 suit = CardFlip_GetCardSuit(card);
    u8 rank = CardFlip_GetCardRank(card);
    bool8 won = FALSE;
    u16 payout = 0;

    switch (sCardFlip.betType)
    {
    case CARDFLIP_BET_SINGLE_CARD:
        // betParam1 = suit (0..3), betParam2 = rank (1..6)
        if (suit == sCardFlip.betParam1 && rank == sCardFlip.betParam2)
        {
            won = TRUE;
            payout = 72; // 24x
        }
        break;

    case CARDFLIP_BET_RANK:
        // betParam1 = rank (1..6)
        if (rank == sCardFlip.betParam1)
        {
            won = TRUE;
            payout = 18; // 6x
        }
        break;

    case CARDFLIP_BET_SUIT:
        // betParam1 = suit (0..3)
        if (suit == sCardFlip.betParam1)
        {
            won = TRUE;
            payout = 12; // 4x
        }
        break;

    case CARDFLIP_BET_RANK_PAIR:
        // betParam1: 0 -> 1 & 2, 1 -> 3 & 4, 2 -> 5 & 6
        if (sCardFlip.betParam1 == 0 && (rank == 1 || rank == 2))
        {
            won = TRUE;
            payout = 9; // 3x
        }
        else if (sCardFlip.betParam1 == 1 && (rank == 3 || rank == 4))
        {
            won = TRUE;
            payout = 9;
        }
        else if (sCardFlip.betParam1 == 2 && (rank == 5 || rank == 6))
        {
            won = TRUE;
            payout = 9;
        }
        break;

    case CARDFLIP_BET_SUIT_PAIR:
        // betParam1: 0 -> Pikachu & Jigglypuff, 1 -> Poliwag & Oddish
        if (sCardFlip.betParam1 == 0 && (suit == CARDFLIP_SUIT_PIKACHU || suit == CARDFLIP_SUIT_JIGGLYPUFF))
        {
            won = TRUE;
            payout = 6; // 2x
        }
        else if (sCardFlip.betParam1 == 1 && (suit == CARDFLIP_SUIT_POLIWAG || suit == CARDFLIP_SUIT_ODDISH))
        {
            won = TRUE;
            payout = 6;
        }
        break;
    }

    sCardFlip.lastPayout = payout;
    sCardFlip.discarded[card] = TRUE;

    if (won)
        AddCoins(payout);

    return won;
}

u16 CardFlip_GetLastPayout(void)
{
    return sCardFlip.lastPayout;
}

u8 CardFlip_GetCardsRemaining(void)
{
    if (sCardFlip.cardsPlayed >= CARDFLIP_DECK_SIZE)
        return 0;
    return CARDFLIP_DECK_SIZE - sCardFlip.cardsPlayed;
}

u8 CardFlip_GetChosenCard(void)
{
    return sCardFlip.chosenCard;
}

// Script Specials

void Special_CardFlipInit(void)
{
    if (!CheckBagHasItem(ITEM_COIN_CASE, 1))
    {
        gSpecialVar_Result = 0; // No Coin Case
        return;
    }

    if (GetCoins() < CARDFLIP_BET_COST)
    {
        gSpecialVar_Result = 1; // Not enough coins
        return;
    }

    CardFlip_InitDeck();
    gSpecialVar_Result = 2; // Ready
}

void Special_CardFlipDeal(void)
{
    if (GetCoins() < CARDFLIP_BET_COST)
    {
        gSpecialVar_Result = 2; // Not enough coins
        return;
    }

    RemoveCoins(CARDFLIP_BET_COST);

    if (sCardFlip.cardsPlayed >= CARDFLIP_DECK_SIZE)
        gSpecialVar_Result = 1; // Reshuffled
    else
        gSpecialVar_Result = 0; // Normal deal

    CardFlip_DealTwoCards();
}

void Special_CardFlipSelectCard(void)
{
    CardFlip_ChooseCard(gSpecialVar_0x8004);
}

void Special_CardFlipSetBet(void)
{
    CardFlip_SetBet(gSpecialVar_0x8004, gSpecialVar_0x8005, gSpecialVar_0x8006);
}

void Special_CardFlipEvaluate(void)
{
    bool8 won = CardFlip_EvaluateBet();
    gSpecialVar_Result = won;
    gSpecialVar_0x8005 = sCardFlip.lastPayout;
}

void Special_CardFlipBufferResult(void)
{
    u8 card = sCardFlip.chosenCard;
    u8 suit = CardFlip_GetCardSuit(card);
    u8 rank = CardFlip_GetCardRank(card);

    StringCopy(gStringVar1, CardFlip_GetSuitName(suit));
    ConvertIntToDecimalStringN(gStringVar2, rank, STR_CONV_MODE_LEFT_ALIGN, 1);

    StringCopy(gStringVar3, gStringVar1);
    StringAppend(gStringVar3, sText_Space);
    StringAppend(gStringVar3, gStringVar2);
}

void Special_CardFlipShowCoins(void)
{
    ShowCoinsWindow(GetCoins(), 20, 0);
}

void Special_CardFlipHideCoins(void)
{
    HideCoinsWindow();
}
