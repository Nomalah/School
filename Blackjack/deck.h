#include <random>
#include <algorithm>
#include <vector>
#include <chrono>

enum Suit{
    Club,
    Diamond,
    Spade,
    Heart
};
const char* const SuitNames[] = {"Club", "Diamond", "Spade", "Heart"};
const char* const SSuitNames[] = {"C", "D", "S", "H"};
Suit operator++(Suit& ID){
    ID = (Suit)((int)ID + 1);
    return ID;
}

enum Rank{
    Ace,
    Two, Three, Four, Five, Six, Seven, Eight, Nine, Ten,
    Jack, Queen, King
};
const char* const RankNames[] = {"Ace", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
const char* const SRankNames[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "T", "J", "Q", "K"};
Rank operator++(Rank& ID){
    ID = (Rank)((int)ID + 1);
    return ID;
}

struct Card{
    Suit m_Suit;
    Rank m_Rank;
};

std::ostream& operator<<(std::ostream& out, Card card){
    out << RankNames[card.m_Rank] << " of " << SuitNames[card.m_Suit] << "s";
    return out;
}

struct Deck{
    std::vector<Card> m_Deck;
    Deck(){
        m_Deck.reserve(52);
        for(Suit S = Suit::Club; S <= Suit::Heart; ++S){
            for(Rank R = Rank::Ace; R <= Rank::King; ++R){
                m_Deck.push_back({S, R});
            }
        }
    }
};

Deck RandomDeck(){
    Deck TempOut;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(TempOut.m_Deck.begin(), TempOut.m_Deck.end(), std::default_random_engine(seed));
    return TempOut;
}