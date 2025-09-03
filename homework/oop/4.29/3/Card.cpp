

#include<bits/stdc++.h>

class Card{
    public:
        Card(int id){
            mBackPic=0;
            width=50;
            height=70;
            x=0;
            y=0;
            mSuit=static_cast<Suit>(id%13);
            mRank=static_cast<Rank>(id/4);
        };
        Card(const Card& other){
            mBackPic=other.mBackPic;
            width=other.width;
            height=other.height;
            x=other.x;
            y=other.y;
            mSuit=other.mSuit;
            mRank=other.mRank;
        }
        int getBackPic(Card& card){
            return card.mBackPic;
        }
        int CompareRank(Card& card){
            if(mRank>card.mRank) return 1;
            else if(mRank<card.mRank) return -1;
            else return 0;
        }
        bool CompareSuit(Card& card){
            if(mSuit==card.mSuit) return true;
            else return false;
        }
    private:
    enum Suit { SPADE, HEART, DIAMOND, CLUB };
    enum Rank { ACE=0, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK=10, QUEEN=11, KING=12 };
    int mBackPic;
    double width;
    double height;
    int x;
    int y;
    Suit mSuit;
    Rank mRank;
};

int main(){
    Card card1(5);
    Card card2(card1);
    printf("%d\n",card1.CompareRank(card2));
    printf("%d\n",card1.CompareSuit(card2));
    return 0;
}