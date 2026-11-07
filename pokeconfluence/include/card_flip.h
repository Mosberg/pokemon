#ifndef GUARD_CARD_FLIP_H
#define GUARD_CARD_FLIP_H

#include "global.h"

// POKE-CONFLUENCE: Authentic GBC Crystal Goldenrod & Celadon Game Corner Card Flip Minigame
// Reference: games/gbc/pokecrystal/engine/games/card_flip.asm

#define CARDFLIP_DECK_SIZE 24
#define CARDFLIP_NUM_SUITS 4
#define CARDFLIP_NUM_RANKS 6
#define CARDFLIP_BET_COST  3

enum CardFlipSuit
{
    CARDFLIP_SUIT_PIKACHU = 0,
    CARDFLIP_SUIT_JIGGLYPUFF = 1,
    CARDFLIP_SUIT_POLIWAG = 2,
    CARDFLIP_SUIT_ODDISH = 3,
};

enum CardFlipBetType
{
    CARDFLIP_BET_SINGLE_CARD = 0, // 24x -> 72 coins
    CARDFLIP_BET_RANK = 1,        // 6x  -> 18 coins
    CARDFLIP_BET_SUIT = 2,        // 4x  -> 12 coins
    CARDFLIP_BET_RANK_PAIR = 3,   // 3x  -> 9 coins
    CARDFLIP_BET_SUIT_PAIR = 4,   // 2x  -> 6 coins
};

struct CardFlipState
{
    u8 deck[CARDFLIP_DECK_SIZE];
    bool8 discarded[CARDFLIP_DECK_SIZE];
    u8 cardsPlayed;
    u8 dealtCard1;
    u8 dealtCard2;
    u8 chosenCard;
    u8 betType;
    u8 betParam1;
    u8 betParam2;
    u16 lastPayout;
};

// Core Engine API
void CardFlip_InitDeck(void);
void CardFlip_ShuffleDeck(void);
void CardFlip_DealTwoCards(void);
void CardFlip_ChooseCard(u8 which); // 1 = Card 1, 2 = Card 2
void CardFlip_SetBet(u8 betType, u8 param1, u8 param2);
bool8 CardFlip_EvaluateBet(void);
u16 CardFlip_GetLastPayout(void);
u8 CardFlip_GetCardsRemaining(void);
u8 CardFlip_GetChosenCard(void);
u8 CardFlip_GetCardSuit(u8 card);
u8 CardFlip_GetCardRank(u8 card);
const u8 *CardFlip_GetSuitName(u8 suit);

// Script specials
void Special_CardFlipInit(void);
void Special_CardFlipDeal(void);
void Special_CardFlipSelectCard(void);
void Special_CardFlipSetBet(void);
void Special_CardFlipEvaluate(void);
void Special_CardFlipBufferResult(void);
void Special_CardFlipShowCoins(void);
void Special_CardFlipHideCoins(void);

#endif // GUARD_CARD_FLIP_H
