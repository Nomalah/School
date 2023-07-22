#pragma once
#include <vector>
#include <algorithm>

enum RP_rank {
    Ten,
    Jack,
    Queen,
    King,
    Ace,
    None
};

enum RP_suit {
    Spade,
    Diamond,
    Club,
    Heart,
    None
};

struct RP_card{
    RP_rank rank;
    RP_suit suit;
    bool operator==(const RP_card& other) const {
        return rank == other.rank && suit == other.suit;
    }

    operator int() const {return (int)rank * 10 + (int)suit;}
};

struct RP_deck{
    std::vector<RP_card> cards;
    decltype(cards.rbegin()) deck_pos;

    RP_deck(RP_card hole[2]){
        for(int r = Ten; r <= Ace; r++){
            for(int s = Spade; s <= Heart; s++){
                RP_card add_to_deck = {(RP_rank)r, (RP_suit)s};
                if(add_to_deck == hole[0] && add_to_deck == hole[1])
                    cards.push_back(add_to_deck);
            }
        }
        deck_pos = cards.rbegin();
    }

    void next_shuffle(){
        next_permutation(cards.begin(), cards.end());
        deck_pos = cards.rbegin();
    }

    RP_card deal_card(){
        return *(deck_pos++);
    }
};