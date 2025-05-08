#include<bits/stdc++.h>
#include<windows.h>
#include"TRandom.h"
using namespace std;

class Crypter{
    public:
        Crypter(unsigned long seed=0){
            mSeed=(seed?seed: GetTickCount());
        }
        void Seed(unsigned long seed=0){
            mSeed=(seed?seed: GetTickCount());
        }
        void Encoder(unsigned char data[],int len,  unsigned long key);
        void Decoder(unsigned char data[], int len, unsigned long key);
    private:
        unsigned long mSeed;
};

void Crypter::Encoder(unsigned char data[],int len,  unsigned long key){
    TRandom rand(key);

    for(int i=0;i<len;i++){
        unsigned char randByte = rand.Integer()&0xff;
        data[i]^=randByte;
    }
    return;
}

void Crypter::Decoder(unsigned char data[],int len, unsigned long key){
    TRandom rand(key);

    for(int i=0;i<len;i++){
        unsigned char randByte = rand.Integer()&0xff;
        data[i]^=randByte;
    }
    return;
}

int main(){
    unsigned char data[100];
    printf("原始数据:\n");
    for(int i=0;i<100;i++){
        data[i]=i;
        printf("%02x ",data[i]);
    }
    unsigned long seed=0x12345678;
    Crypter crypter(seed);
    crypter.Encoder(data,100,seed);
    printf("\n加密后\n");
    for(int i=0;i<100;i++){
        printf("%02x ",data[i]);
    }
    printf("\n解密后\n");
    crypter.Decoder(data,100,seed);
    for(int i=0;i<100;i++){
        printf("%02x ",data[i]);
    }
    return 0;
}