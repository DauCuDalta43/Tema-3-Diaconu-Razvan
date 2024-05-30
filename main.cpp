#include "a.h"
#include <bits/stdc++.h>
using namespace std;




void StartGame()
{
    char ch;
    for(int i=1;i<=100;i++)
        cout<<"\n";
    cout<<"Enter any key to start game\n";
    cin>>ch;
    for(int i=1;i<=100;i++)
        cout<<"\n";
}

int Assasin::enemycount;
int Slaver::enemycount;
int Bruiser::enemycount;
int Rammer::enemycount;
Player* Player::p=NULL;
///int Cultist::enemycount;
vector<string> Data::CardName;
vector<string> Data::CardDesc;
vector<int> Data::CardCost;

int main()
{


    srand(time(NULL));
    int stage=1;
    Data d;
    d.ReadData();
    Player::getPlayer();
    std::shared_ptr<PotionBelt> pot=std::make_shared<PotionBelt>();
    StartGame();
    while(Combat(stage,pot))
    {
        //if(stage%3==0)
          //  Bonus(*Player::getPlayer());
        stage++;
    }

    return 0;
}
