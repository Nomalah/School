#include <iostream>
#include <fstream>
#include <iomanip>
#include "deck.h"

size_t CalculateHand(const std::vector<Card>& hand){
    size_t NumOfAces = 0;
    size_t HandScore = 0;
    for(Card i : hand){
        switch(i.m_Rank){
            case Rank::Ace:
                NumOfAces++;
                HandScore += 11;
                break;
            case Rank::Two ... Rank::Nine:
                HandScore += i.m_Rank + 1; // +1 is because enums start at 0
                break;
            default:
                HandScore += 10;
                break;
        }
    }

    while(NumOfAces > 0 && HandScore > 21){
        NumOfAces--;
        HandScore -= 10;
    }

    return HandScore;
}

void Hit(std::vector<Card>& hand, Deck& deck){
    hand.push_back(deck.m_Deck.back());
    deck.m_Deck.pop_back();
}

struct Result{
    bool PlayerWon;
    bool Push;
};

struct Cards{
    Card P1;
    Card P2;
    Card D;
};

class BlackJackGame{
    private:
        Deck m_Deck;
        std::vector<Card> m_DealerHand;
        std::vector<Card> m_PlayerHand;
    public:
        BlackJackGame(){
            m_Deck = RandomDeck();
            Hit(m_PlayerHand, m_Deck);
            Hit(m_DealerHand, m_Deck);
            Hit(m_PlayerHand, m_Deck);
        }

        void Display(){
            std::cout << "Dealer's Hand: " << CalculateHand(m_DealerHand) << std::endl;
            for(Card i : m_DealerHand)
                std::cout << '\t' << i << std::endl;
            std::cout << "Player's Hand: " << CalculateHand(m_PlayerHand) << std::endl;
            for(Card i : m_PlayerHand)
                std::cout << '\t' << i << std::endl;
        }

        void PlayerHit(){
            Hit(m_PlayerHand, m_Deck);
        }

        Result DealerTurn(){
            if(CalculateHand(m_PlayerHand) > 21){
                return {false, false};
            }

            while(CalculateHand(m_DealerHand) < 17){
                Hit(m_DealerHand, m_Deck);
            }

            //std::cout << CalculateHand(m_DealerHand) << " (";
            //for(Card i : m_DealerHand)
            //    std::cout << SRankNames[i.m_Rank] << ", ";
            //std::cout << ") vs " << CalculateHand(m_PlayerHand) << "("
            //    << SRankNames[m_PlayerHand[0].m_Rank] << ", " << SRankNames[m_PlayerHand[1].m_Rank] << ")" << std::endl;
            
            if(CalculateHand(m_DealerHand) > 21){
                return {true, false};
            }

            if(CalculateHand(m_DealerHand) == CalculateHand(m_PlayerHand)){
                return {false, true};
            }
            return {CalculateHand(m_DealerHand) < CalculateHand(m_PlayerHand), false};
        }

        Cards StartCards(){
            return {m_PlayerHand[0], m_PlayerHand[1], m_DealerHand[0]};
        }
};

struct Percent{
    int Win = 0;
    int Total = 0;
};

std::ostream& operator<<(std::ostream& out, Percent p){
    out << std::fixed << std::setprecision(4) << (float)p.Win/((float)p.Total == 0.0f ? 1.0f : (float)p.Total);
    return out;
}

void DumpPercents(Percent Stats[13][13][13], const char* FileName){
    std::ofstream File(FileName);
    
    
    for(size_t x = 0; x <= Rank::King; x++){
        File << "\t";
        for(size_t y = 0; y <= Rank::King; y++){
            File << std::setw(7) << SRankNames[y];
        }
        for(size_t y = 0; y <= Rank::King; y++){
            File << std::endl << SRankNames[x] << ", " << SRankNames[y];
            for(size_t i = 0; i <= Rank::King; i++){
                File << std::setw(7) << Stats[x][y][i];
            }
        }
        File << "\n";
    }
    File.close();
}

int main(){
    

    // First 2 dimentions are Player's starting hand, 3rd is the dealers
    Percent StandWinStats[13][13][13]{};
    DumpPercents(StandWinStats, "StandStats.txt");

    for(size_t i = 0; i < 1000000; i++){
        BlackJackGame MainGame;
        Result r = MainGame.DealerTurn();
        Cards c = MainGame.StartCards();
        StandWinStats[c.P1.m_Rank][c.P2.m_Rank][c.D.m_Rank].Total++;
        if(r.PlayerWon)
            StandWinStats[c.P1.m_Rank][c.P2.m_Rank][c.D.m_Rank].Win++;
    }

    DumpPercents(StandWinStats, "StandStats.txt");

    Percent HitWinStats[13][13][13]{};
    DumpPercents(HitWinStats, "HitWinStats.txt");

    for(size_t i = 0; i < 1000000; i++){
        BlackJackGame MainGame;
        MainGame.PlayerHit();
        Result r = MainGame.DealerTurn();
        Cards c = MainGame.StartCards();
        HitWinStats[c.P1.m_Rank][c.P2.m_Rank][c.D.m_Rank].Total++;
        if(r.PlayerWon)
            HitWinStats[c.P1.m_Rank][c.P2.m_Rank][c.D.m_Rank].Win++;
    }

    DumpPercents(HitWinStats, "HitWinStats.txt");

    Percent HitHitWinStats[13][13][13]{};
    DumpPercents(HitHitWinStats, "HitHitWinStats.txt");

    for(size_t i = 0; i < 1000000; i++){
        BlackJackGame MainGame;
        MainGame.PlayerHit();
        MainGame.PlayerHit();
        Result r = MainGame.DealerTurn();
        Cards c = MainGame.StartCards();
        HitHitWinStats[c.P1.m_Rank][c.P2.m_Rank][c.D.m_Rank].Total++;
        if(r.PlayerWon)
            HitHitWinStats[c.P1.m_Rank][c.P2.m_Rank][c.D.m_Rank].Win++;
    }

    DumpPercents(HitHitWinStats, "HitHitWinStats.txt");
/*
    Percent HitHitHitWinStats[13][13][13]{};
    DumpPercents(HitHitHitWinStats, "HitHitHitWinStats.txt");

    for(size_t i = 0; i < 1000000; i++){
        BlackJackGame MainGame;
        MainGame.PlayerHit();
        MainGame.PlayerHit();
        Result r = MainGame.DealerTurn();
        Cards c = MainGame.StartCards();
        HitHitHitWinStats[c.P1.m_Rank][c.P2.m_Rank][c.D.m_Rank].Total++;
        if(r.PlayerWon)
            HitHitHitWinStats[c.P1.m_Rank][c.P2.m_Rank][c.D.m_Rank].Win++;
    }

    DumpPercents(HitHitHitWinStats, "HitHitHitWinStats.txt");

    Percent HitHitHitHitWinStats[13][13][13]{};
    DumpPercents(HitHitHitHitWinStats, "HitHitHitHitWinStats.txt");

    for(size_t i = 0; i < 1000000; i++){
        BlackJackGame MainGame;
        MainGame.PlayerHit();
        MainGame.PlayerHit();
        Result r = MainGame.DealerTurn();
        Cards c = MainGame.StartCards();
        HitHitHitHitWinStats[c.P1.m_Rank][c.P2.m_Rank][c.D.m_Rank].Total++;
        if(r.PlayerWon)
            HitHitHitHitWinStats[c.P1.m_Rank][c.P2.m_Rank][c.D.m_Rank].Win++;
    }

    DumpPercents(HitHitHitHitWinStats, "HitHitHitHitWinStats.txt");
*/
    /*if(CalculateHand(PlayerHand) == 21){
        std::cout << "BlackJack!";
    }else{
        while(CalculateHand(PlayerHand) <= 21){
            std::cout << "Dealer's Hand: " << CalculateHand(DealerHand) << std::endl;
            std::cout << '\t' << DealerHand[0] << std::endl;
            std::cout << "Player's Hand: " << CalculateHand(PlayerHand) << std::endl;
            for(Card i : PlayerHand)
                std::cout << '\t' << i << std::endl;
            

            char HitOrStand;
            std::cout << "Hit(H) or Stand(S)?: ";
            std::cin >> HitOrStand;
            if(HitOrStand == 'H') {
                Hit(PlayerHand, MainDeck);
                std::cout << "\033[2JYou were dealt the " << PlayerHand.back() << std::endl;
            }else break;
        }

        if(CalculateHand(PlayerHand) > 21){ 
            std::cout << "Player's Hand: " << CalculateHand(PlayerHand) << std::endl;
            for(Card i : PlayerHand)
                std::cout << '\t' << i << std::endl;
            std::cout << "BUST! - " << CalculateHand(PlayerHand) << std::endl;
        }
    }*/
    
    return 0;
}