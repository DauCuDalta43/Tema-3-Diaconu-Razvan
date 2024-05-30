#ifndef A_H_INCLUDED
#define A_H_INCLUDED
#include <bits/stdc++.h>

using namespace std;

int myrandom (int i) { return std::rand()%i;}

class Player;
class Enemy;
class Hand;



class Exceptie : public std::exception {
    char * msg;

    public:
    Exceptie(char * msg) : msg(msg) {}
    char * what () {
        return msg;
    }
};


class Data
{
    static vector<string>CardName,CardDesc;
    static vector<int>CardCost;
    public:
    void ReadData()
    {
        ifstream fin("data.txt");
        string s;
        int x;
        for(int i=1;i<=20;i++)
        {
            getline(fin,s);
            CardName.push_back(s);
        }
        for(int i=1;i<=20;i++)
        {
            getline(fin,s);
            CardDesc.push_back(s);
        }
        for(int i=1;i<=20;i++)
        {
            fin>>x;
            CardCost.push_back(x);
        }
    }
    static string GetName(int i)
    {
        return CardName[i];
    }
    static string GetDesc(int i)
    {
        return CardDesc[i];
    }
    static int GetCost(int i)
    {
        return CardCost[i];
    }
};

class Card:Data
{
    private:
    int id,cost;
    string name,desc;
    public:
    Card()
    {

    }

    Card(int x):id(x)
    {
        name=Data::GetName(x);
        desc=Data::GetDesc(x);
        cost=Data::GetCost(x);
    }

    int get_Id()
    {
        return id;
    }

    int get_Cost()
    {
        return cost;
    }
    friend ostream & operator << (ostream &out, const Card &c);

};

ostream & operator << (ostream &out, const Card &c)
{
    cout<<c.name<<"("<<c.cost<<"):"<<c.desc<<"\n";
}

class classDeck
{
    private:
    vector<Card>deck;

    public:
    classDeck()
    {
        Card a(0);
        for(int i=1;i<=5;i++)
            deck.push_back(a);
        a=Card(1);
        for(int i=1;i<=5;i++)
            deck.push_back(a);
        deck.push_back(Card(2));
    }

    vector<Card> get_deck()
    {
        return deck;
    }

    void AddDeck(Card c)
    {
        deck.push_back(c);
    }


};


class OffHand
{
    private:
    classDeck d;
    vector<Card>draw;
    vector<Card>discard;
    public:
    OffHand()
    {
        ///cout<<"c\n";
    }
    OffHand(classDeck x):d(x)
    {
        //cout<<"c\n";
        discard.clear();
        draw=d.get_deck();
        std::random_shuffle(draw.begin(),draw.end(),myrandom);
        ///cout<<draw.size()<<" "<<discard.size()<<"\n";
//        for(int i=0;i<draw.size();i++)
//            cout<<draw[i].id<<" ";
    }

    void Reshuffle()
    {
        std::random_shuffle(discard.begin(),discard.end());
        draw=discard;
        discard.clear();
        ///cout<<draw.size()<<" "<<discard.size()<<"\n";
    }

    Card Draw()
    {
        if(draw.empty())
            Reshuffle();
        Card a;
        a=draw.back();
        draw.pop_back();
        ////cout<<draw.size()<<" "<<discard.size()<<"\n";
        return a;
    }

    vector<Card> get_draw()
    {
        return draw;
    }

    vector<Card> get_discard()
    {
        return discard;
    }
    friend ostream & operator << (ostream &out, const OffHand &oh);

    void Discard(Card c)
    {
        discard.push_back(c);
    }

    void TempCard(Card c)
    {
        draw.push_back(c);
    }



};

ostream & operator << (ostream &out, const OffHand &oh)
{
    cout<<"Draw:"<<oh.draw.size()<<"   Discard:"<<oh.discard.size()<<"\n";
}

class Hand
{
    private:
    OffHand& deck;
    Player& p;
    Enemy& e;
    int Energy;
    vector<Card>hand;
    public:

    Hand(OffHand& x, Player& y, Enemy& z):deck(x),p(y),e(z)
    {
        ///cout<<this<<"\n";
        for(int i=1;i<=5;i++)
            hand.push_back(deck.Draw());
    }

    void Draw(int n)
    {
        for(int i=1;i<=n;i++)
            hand.push_back(deck.Draw());
    }

    void Endturn()
    {
        while(!hand.empty())
        {
            deck.Discard(hand.back());
            hand.pop_back();
        }
    }
    friend ostream & operator << (ostream &out, const Hand &h);

    Player& get_Player()
    {
        return p;
    }
    OffHand& get_OH()
    {
        return deck;
    }
    Enemy& get_Enemy()
    {
        return e;
    }
    void set_Energy(int x)
    {
        Energy+=x;
    }
    vector<Card> get_Hand()
    {
        return hand;
    }
    int get_Energy()
    {
        return Energy;
    }
    void DiscardN(int nr)
    {
        Card c=hand[nr];
        hand.erase(hand.begin()+nr);
        if(c.get_Id()!=19)deck.Discard(c);
    }
    void turnEnergy(int x)
    {
        Energy=x;
    }
    void AddtoHand(Card c)
    {
        hand.push_back(c);
    }

};

ostream & operator << (ostream &out, const Hand &h)
{
    cout<<"\nEnergy:"<<h.Energy<<"\n";;
    for(int i=1;i<=h.hand.size();i++)
        cout<<i<<": "<<h.hand[i-1];
    cout<<"e: End turn.\n";
}

void AfisReward(Card x, Card y, Card z)
{
    for(int i=1;i<=100;i++)
        cout<<"\n";
    cout<<"Choose card:\n";
    cout<<"1: "<<x;
    cout<<"2: "<<y;
    cout<<"3: "<<z;
    cout<<"s: Skip\n";
}

void AfisBonus()
{
    for(int i=1;i<=100;i++)
        cout<<"\n";
    cout<<"Choose reward:\n";
    cout<<"1: +1 Energy\n";
    cout<<"2: +2 Strenght\n";
    cout<<"3: +2 Dexterity\n";
}



void CardReward(classDeck& p)
{

    int x,y,z;
    x=rand()%8+2;
    y=rand()%17+2;
    z=rand()%14+2;
    Card xc(x);
    Card yc(y);
    Card zc(z);
    char ch;
    AfisReward(xc,yc,zc);
    while(cin>>ch)
    {
        AfisReward(xc,yc,zc);
        if((ch<'1'||ch>'3')&&ch!='s')continue;
        if(ch=='1')p.AddDeck(xc);
        else if(ch=='2')p.AddDeck(yc);
        else if(ch=='3')p.AddDeck(zc);
        for(int i=1;i<=100;i++)
            cout<<"\n";
        return;
    }

}

class Player
{


    int Hp,Energy;
    int block;
    int weak,frail,vulnerable;
    int str,dex;
    int strBoost,dexBoost;
    classDeck deck;
    OffHand oh;

    static Player* p;
    Player()
        {
            Hp=50;
            Energy=3;
            block=str=dex=weak=vulnerable=frail=strBoost=dexBoost=0;
            deck=classDeck();
            oh=OffHand(deck);
            ///hand=Hand(oh);

        }
    public:




    static Player* getPlayer()
    {
        if(p==NULL)
            p=new Player();
        else return p;
    }

    classDeck get_deck()
    {
        return deck;
    }
    OffHand& get_oh()
    {
        return oh;
    }
    int get_value(string s)
    {
        if(s=="Hp")
            return Hp;
        if(s=="Energy")
            return Energy;
        if(s=="block")
            return block;
        if(s=="weak")
            return weak;
        if(s=="frail")
            return frail;
        if(s=="vulnerable")
            return vulnerable;
        if(s=="str")
            return str;
        if(s=="dex")
            return dex;
        if(s=="strBoost")
            return strBoost;
        if(s=="dexBoost")
            return dexBoost;
    }

    void set_value(string s,int x)
    {
        if(s=="Hp")
            Hp+=x;
        if(s=="Energy")
            Energy+=x;
        if(s=="block")
            block+=x;
        if(s=="weak")
            weak+=x;
        if(s=="frail")
            frail+=x;
        if(s=="vulnerable")
            vulnerable+=x;
        if(s=="str")
            str+=x;
        if(s=="dex")
            dex+=x;
        if(s=="strBoost")
            strBoost+=x;
        if(s=="dexBoost")
            dexBoost+=x;
    }

    void Debuff(int type)
    {
        switch(type)
        {
        case 0:
            vulnerable+=2;
            break;
        case 1:
            weak+=2;
            break;
        case 2:
            frail+=2;
        case 3:
            Card c(19);
            oh.TempCard(c);
        }
    }

    void TakeDamage(int dmg)
    {
        if(vulnerable)dmg*=1.5;
        if(dmg<block)block-=dmg;
        else
        {
            dmg-=block;
            block=0;
            Hp-=dmg;
        }
    }

    void Endturn()
    {
        block=0;
        if(weak)weak--;
        if(frail)frail--;
        if(vulnerable)vulnerable--;
    }

    void EndCombat()
    {
        CardReward(deck);
        weak=frail=strBoost=vulnerable=dexBoost=block=0;
        Hp+=10;
        oh=OffHand(deck);
    }


};

void Bonus(Player& p)
{
    char ch;
    AfisBonus();
    while(cin>>ch)
    {
        AfisBonus();
        if(ch<'1'||ch>'3')continue;
        if(ch=='1')p.set_value("Energy",1);
        else if(ch=='2')p.set_value("str",2);
        else if(ch=='3')p.set_value("dex",2);
        return;
    }
}

ostream & operator << (ostream &out, Player &p)
{
    cout<<"Health:"<<p.get_value("Hp")<<"   Block:"<<p.get_value("block")<<"\n";
    if(p.get_value("dex")+p.get_value("dexBoost"))cout<<"Dexterity:"<<p.get_value("dex")+p.get_value("dexBoost")<<"  ";
    if(p.get_value("str")+p.get_value("strBoost"))cout<<"Strenght:"<<p.get_value("str")+p.get_value("strBoost")<<"  ";
    if(p.get_value("weak"))cout<<"Weak:"<<p.get_value("weak")<<"  ";
    if(p.get_value("frail"))cout<<"Frail:"<<p.get_value("frail")<<"  ";
    if(p.get_value("vulnerable"))cout<<"Vulnerable:"<<p.get_value("vulnerable")<<"  ";
    cout<<"\n\n";
    cout<<p.get_oh();
}




class Enemy
{
    protected:
    string name,special;
    int Hp,dmg;
    int weak, vulnerable;
    int poison;
    int str;
    int stage,intent,type;
    void Intent()
    {
        intent=rand()%2;
    }

    public:

    string get_name()
    {
        return name;
    }
    string get_special()
    {
        return special;
    }
    int get_value(string s)
    {
        if(s=="Hp")
            return Hp;
        if(s=="dmg")
            return dmg;
        if(s=="weak")
            return weak;
        if(s=="vulnerable")
            return vulnerable;
        if(s=="poison")
            return poison;
        if(s=="str")
            return str;
        if(s=="stage")
            return stage;
        if(s=="intent")
            return intent;
        if(s=="type")
            return type;
    }

    void set_value(string s, int x)
    {
        if(s=="Hp")
            Hp+=x;
        if(s=="dmg")
            dmg+=x;
        if(s=="weak")
            weak+=x;
        if(s=="vulnerable")
            vulnerable+=x;
        if(s=="poison")
            poison+=x;
        if(s=="str")
            str+=x;
    }
    void set_name(string s)
    {
        name=s;
    }
    Enemy()
    {
        weak=vulnerable=str=poison=0;
        Intent();
    }
    virtual ~Enemy()
    {

    }


    virtual void Endturn(Player& p)
    {

    }
};
class Assasin : public Enemy
{

    public:
    static int enemycount;
    Assasin(int stage):Enemy()
    {
        type=0;
        name="Assasin";
        special="Inflicts 2 Vulnerable.";
        Hp=30*(1.0+0.05*(stage-1));
        dmg=4*(1.0+0.05*(stage-1));
    }

    virtual void Attack(Player& p)
    {
        int dmgVar=dmg;
        if(weak)dmgVar*=0.75;
        p.TakeDamage(dmgVar);
        if(!intent)p.Debuff(type);
        else p.TakeDamage(dmgVar);
    }

    void Endturn(Player& p)
    {
        if(poison)
        {
            Hp-=poison;
            poison--;
        }
        Attack(p);
        if(weak)weak--;
        if(vulnerable)vulnerable--;
        Intent();
    }
    static void IncCounter()
    {
        enemycount++;
    }
    static int ShowCounter()
    {
        return enemycount;
    }

    ~Assasin()
    {
        enemycount++;
    }

};

class Slaver : public Enemy
{
    static int enemycount;
    public:
    Slaver(int stage):Enemy()
    {
        type=1;
        name="Slaver";
        special="Inflicts 2 Weak.";
        Hp=45*(1.0+0.05*(stage-1));
        dmg=4*(1.0+0.05*(stage-1));
        weak=vulnerable=poison=str=0;
    }

    void Attack(Player& p)
    {
        int dmgVar=dmg;
        if(weak)dmgVar*=0.75;
        p.TakeDamage(dmgVar);
        if(!intent)p.Debuff(type);
        else p.TakeDamage(dmgVar);
    }

    void Endturn(Player& p)
    {
        if(poison)
        {
            Hp-=poison;
            poison--;
        }
        Attack(p);
        if(weak)weak--;
        if(vulnerable)vulnerable--;
        Intent();
    }

    static void IncCounter()
    {
        enemycount++;
    }
    static int ShowCounter()
    {
        return enemycount;
    }
    ~Slaver()
    {
        enemycount++;
    }
};

class Bruiser : public Enemy
{
    static int enemycount;
    void Attack(Player& p)
    {
        int dmgVar=dmg;
        if(weak)dmgVar*=0.75;
        p.TakeDamage(dmgVar);
        if(!intent)p.Debuff(type);
        else p.TakeDamage(dmgVar);
    }

public:

    Bruiser(int stage):Enemy()
    {
        type=2;
        name="Bruiser";
        special="Inflicts 2 Frail.";
        Hp=40*(1.0+0.05*(stage-1));
        dmg=4*(1.0+0.05*(stage-1));
        weak=vulnerable=poison=str=0;
    }



    void Endturn(Player& p)
    {
        if(poison)
        {
            Hp-=poison;
            poison--;
        }
        Attack(p);
        if(weak)weak--;
        if(vulnerable)vulnerable--;
        Intent();
    }

    static void IncCounter()
    {
        enemycount++;
    }
    static int ShowCounter()
    {
        return enemycount;
    }
    ~Bruiser()
    {
        enemycount++;
    }
};

class Rammer : public Enemy
{
    static int enemycount;
    void Attack(Player& p)
    {
        int dmgVar=dmg;
        if(weak)dmgVar*=0.75;
        p.TakeDamage(dmgVar);
        if(!intent)p.Debuff(type);
        else p.TakeDamage(dmgVar);
    }

public:

    Rammer(int stage):Enemy()
    {
        type=3;
        name="Rammer";
        special="Inflicts 2 Dazed.";
        Hp=40*(1.0+0.05*(stage-1));
        dmg=3*(1.0+0.05*(stage-1));
        weak=vulnerable=poison=str=0;
    }



    void Endturn(Player& p)
    {
        if(poison)
        {
            Hp-=poison;
            poison--;
        }
        int dmgVar=dmg;
        Attack(p);
        if(weak)weak--;
        if(vulnerable)vulnerable--;
        Intent();
    }

    static void IncCounter()
    {
        enemycount++;
    }
    static int ShowCounter()
    {
        return enemycount;
    }
    ~Rammer()
    {
        enemycount++;
    }
};

/*class Cultist : public Enemy
{
    static int enemycount;
    virtual void Attack(Player& p)
    {
        int dmgVar=dmg+str;
        if(weak)dmgVar*=0.75;
        p.TakeDamage(dmgVar);
        str+=4;
    }

public:

    Cultist(int stage):Enemy()
    {
        type=4;
        name="Cultist";
        special="Gains 4 Strenght.";
        Hp=30*(1.0+0.05*(stage-1));
        dmg=4*(1.0+0.05*(stage-1));
        weak=vulnerable=poison=str=0;
    }



    void Endturn(Player& p)
    {
        if(poison)
        {
            Hp-=poison;
            poison--;
        }
        Attack(p);
        if(weak)weak--;
        if(vulnerable)vulnerable--;
        Intent();
    }

    static void IncCounter()
    {-
        enemycount++;
    }
    static void ShowCounter()
    {
        cout<<enemycount<<" "<<"Cultist";
        if(enemycount!=1)cout<<"s";
        cout<<"\n";
    }
};*/

template<class T> void MakeElite(T& base, int stage)
{
    base->set_value("Hp",stage*10);
    base->set_value("dmg",stage);
    base->set_name("Elite "+base->get_name());
};

ostream & operator << (ostream &out, Enemy &e)
{
    int dmgVar=e.get_value("dmg")+e.get_value("str");
    if(e.get_value("weak"))dmgVar*=0.75;
    cout<<e.get_name()<<"\n";
    cout<<"Health:"<<e.get_value("Hp")<<"\n";
    cout<<"Deals "<<dmgVar+dmgVar*e.get_value("intent")<<" Damage. ";
    if(!e.get_value("intent")||e.get_value("type")==4)cout<<e.get_special();
    cout<<"\n";
    if(e.get_value("str"))cout<<"Strenght:"<<e.get_value("str")<<"   ";
    if(e.get_value("weak"))cout<<"Weak:"<<e.get_value("weak")<<"   ";
    if(e.get_value("vulnerable"))cout<<"Vulnerable:"<<e.get_value("vulnerable")<<"   ";
    if(e.get_value("poison"))cout<<"Poison:"<<e.get_value("poison")<<"   ";
    return out;
}


///Cards

int CalcDmg(Hand& h, int base, int mult=1)
{
    float dmg=base+(h.get_Player().get_value("str")+h.get_Player().get_value("strBoost"))*mult;
    if(h.get_Enemy().get_value("vulnerable"))dmg*=1.5;
    if(h.get_Player().get_value("weak"))dmg*=0.75;
    return (int)dmg;
}

int CalcBlock(Hand& h, int base)
{
    float block=base+h.get_Player().get_value("dex")+h.get_Player().get_value("dexBoost");
    if(h.get_Player().get_value("frail"))block*=0.75;
    return (int)block;
}

void Strike(Hand& h)
{
    h.get_Enemy().set_value("Hp",-CalcDmg(h,6));
}

void Defend(Hand& h)
{
    h.get_Player().set_value("block",CalcBlock(h,5));
}

void Bash(Hand& h)
{
    h.get_Enemy().set_value("Hp",-CalcDmg(h,8));
    h.get_Enemy().set_value("vulnerable",2);
}

void HeavyBlade(Hand& h)
{
    h.get_Enemy().set_value("Hp",-CalcDmg(h,14,3));
}

void PommelStrike(Hand& h)
{
    h.get_Enemy().set_value("Hp",-CalcDmg(h,8));
    h.Draw(1);

}

void ShruggOff(Hand& h)
{
    h.get_Player().set_value("block",CalcBlock(h,8));
    h.Draw(1);
}

void IronWave(Hand& h)
{
    h.get_Player().set_value("block",CalcBlock(h,5));
    h.get_Enemy().set_value("Hp",-CalcDmg(h,5));
}

void PowerThrough(Hand& h)
{
    h.get_Player().set_value("block",CalcBlock(h,15));
    Card c(19);
    h.AddtoHand(c);
}

void SeeingRed(Hand& h)
{
    h.set_Energy(2);
}

void Neutralize(Hand& h)
{
    h.get_Enemy().set_value("Hp",-CalcDmg(h,3));
    h.get_Enemy().set_value("weak",1);
}

void Deflect(Hand& h)
{
    h.get_Player().set_value("block",CalcBlock(h,4));
}

void DeadlyPoison(Hand& h)
{
    h.get_Enemy().set_value("poison",5);
}

void PoisonedStab(Hand& h)
{
    h.get_Enemy().set_value("poison",3);
    h.get_Enemy().set_value("Hp",-CalcDmg(h,6));
}

void Catalyst(Hand& h)
{
    h.get_Enemy().set_value("poison",h.get_Enemy().get_value("poison"));
}

void Footwork(Hand& h)
{
    h.get_Player().set_value("dexBoost",2);
}

void LegSweep(Hand& h)
{
    h.get_Enemy().set_value("weak",2);
    h.get_Player().set_value("block",CalcBlock(h,11));
}

void Adrenaline(Hand& h)
{
    h.set_Energy(1);
    h.Draw(2);
}

void Offering(Hand& h)
{
    h.set_Energy(2);
    h.Draw(3);
    h.get_Player().set_value("Hp",-3);
}

void LimitBreak(Hand& h)
{
    h.get_Player().set_value("strBoost",h.get_Player().get_value("str")+h.get_Player().get_value("strBoost"));
}

void Reaper(Hand& h)
{
    h.get_Enemy().set_value("Hp",-CalcDmg(h,4));
    h.get_Player().set_value("Hp",CalcDmg(h,4));
}




void PlayCard(Hand& h,int nr)
{
    if(nr>=h.get_Hand().size())
    {
        return;
    }
    Card c=h.get_Hand()[nr];

    try
    {
        for(int i=1;i<=100;i++)
            cout<<"\n";
        if(h.get_Energy()<c.get_Cost())
        {
            throw(Exceptie("Missing Energy"));
        }
        h.set_Energy(-c.get_Cost());
        h.DiscardN(nr);
        switch(c.get_Id()+1)
        {
        case 1:
            Strike(h);
            break;
        case 2:
            Defend(h);
            break;
        case 3:
            Bash(h);
            break;
        case 4:
            HeavyBlade(h);
            break;
        case 5:
            PommelStrike(h);
            break;
        case 6:
            ShruggOff(h);
            break;
        case 7:
            IronWave(h);
            break;
        case 8:
            PowerThrough(h);
            break;
        case 9:
            Neutralize(h);
            break;
        case 10:
            DeadlyPoison(h);
            break;
        case 11:
            Deflect(h);
            break;
        case 12:
            PoisonedStab(h);
            break;
        case 13:
            Catalyst(h);
            break;
        case 14:
            Footwork(h);
            break;
        case 15:
            LegSweep(h);
            break;
        case 16:
            Adrenaline(h);
            break;
        case 17:
            Offering(h);
            break;
        case 18:
            LimitBreak(h);
            break;
        case 19:
            Reaper(h);
            break;
        }
    }
    catch(Exceptie a)
    {
        cout<<a.what();
    }

}

class Potion
{
protected:
    int cnt;
    string text;
public:
    virtual void UsePotion(Player& p)=0;
    virtual void UsePotion(Enemy& e)=0;
    void AfisPotion()
    {
        if(cnt!=0)
            cout<<text<<cnt<<"\n";
    }
    void GetPotion()
    {
        cnt++;
    }

};

class StrPotion: public Potion
{
public:

    StrPotion()
    {
        cnt=0;
        text="Strength Potion. Use on self to gain 2 strength. Use on enemy to reduce 2 strength. x";
    }

    void UsePotion(Player& p)
    {
        try
        {
            for(int i=1;i<=100;i++)
                cout<<"\n";
            if(cnt<=0)
            {
                throw(Exceptie("Missing Strength Potion"));
            }
            p.set_value("strBoost",2);
            cnt--;
        }
        catch(Exceptie a)
        {
            cout<<a.what();
        }


    }
    void UsePotion(Enemy& e)
    {
        try
        {
            for(int i=1;i<=100;i++)
                cout<<"\n";
            if(cnt<=0)
            {
                throw(Exceptie("Missing Strength Potion"));
            }
            e.set_value("str",-2);
            cnt--;
        }
        catch(Exceptie a)
        {
            cout<<a.what();
        }


    }
};

class DexPotion: public Potion
{
public:

    DexPotion()
    {
        cnt=0;
        text="Dexterity Potion. Use on self to gain 2 dexterity. Use on enemy to inflict 2 weak. x";
    }

    void UsePotion(Player& p)
    {
        try
        {
            for(int i=1;i<=100;i++)
                cout<<"\n";
            if(cnt<=0)
            {
                throw(Exceptie("Missing Strength Potion"));
            }
            p.set_value("dexBoost",2);
            cnt--;
        }
        catch(Exceptie a)
        {
            cout<<a.what();
        }

    }
    void UsePotion(Enemy& e)
    {
        try
        {
            for(int i=1;i<=100;i++)
                cout<<"\n";
            if(cnt<=0)
            {
                throw(Exceptie("Missing Strength Potion"));
            }
            e.set_value("weak",2);
            cnt--;
        }
        catch(Exceptie a)
        {
            cout<<a.what();
        }

    }
};

class FirePotion: public Potion
{
public:

    FirePotion()
    {
        cnt=0;
        text="Fire Potion. Use on self to gain 10 health. Use on enemy to deal 10 damage. x";
    }

    void UsePotion(Player& p)
    {
        try
        {
            for(int i=1;i<=100;i++)
                cout<<"\n";
            if(cnt<=0)
            {
                throw(Exceptie("Missing Strength Potion"));
            }
            p.set_value("Hp",10);
            cnt--;
        }
        catch(Exceptie a)
        {
            cout<<a.what();
        }
    }
    void UsePotion(Enemy& e)
    {
        try
        {
            for(int i=1;i<=100;i++)
                cout<<"\n";
            if(cnt<=0)
            {
                throw(Exceptie("Missing Strength Potion"));
            }
            e.set_value("Hp",-10);
            cnt--;
        }
        catch(Exceptie a)
        {
            cout<<a.what();
        }
    }
};

class PotionBelt
{
    unique_ptr<StrPotion> sp;
    unique_ptr<DexPotion> dp;
    unique_ptr<FirePotion> fp;
    public:
    void PlayPotion(Player& p,Enemy& e)
    {
        char ch;
        cin>>ch;
        if(ch=='1')
        {
            cin>>ch;
            if(ch=='s')
                sp->UsePotion(p);
            if(ch=='d')
                dp->UsePotion(p);
            if(ch=='f')
                fp->UsePotion(p);
        }
        if(ch=='2')
        {
            cin>>ch;
            if(ch=='s')
                sp->UsePotion(e);
            if(ch=='d')
                dp->UsePotion(e);
            if(ch=='f')
                fp->UsePotion(e);
        }
    }
    void GainPotion()
    {
        int r=rand()%60;
        if(r<10)sp->GetPotion();
        else if(r<20)dp->GetPotion();
        else if(r<30)fp->GetPotion();
    }
    void AfisPotion()
    {
        sp->AfisPotion();
        dp->AfisPotion();
        fp->AfisPotion();
    }

    PotionBelt()
    {
        sp=make_unique<StrPotion>();
        dp=make_unique<DexPotion>();
        fp=make_unique<FirePotion>();
    }
};

ostream & operator << (ostream &out, PotionBelt &pot)
{
    pot.AfisPotion();
    cout<<"\n\n";
    return out;
}


void Afisare(Player& p, Enemy& e, Hand& h,PotionBelt& pot)
{
    for(int i=1;i<=5;i++)
        cout<<"\n";
    cout<<e;
    cout<<"\n\n\n";
    cout<<pot;
    cout<<p;
    cout<<h;

}

void Turn(Player& p, Enemy& e,PotionBelt& pot)
{
    char ch;
    Hand h(p.get_oh(),p,e);
    h.turnEnergy(p.get_value("Energy"));
    Afisare(p,e,h,pot);
    while(cin>>ch)
    {
        if(e.get_value("Hp")<=0)return;

        if(ch=='e')
        {
            h.Endturn();
            p.Endturn();
            e.Endturn(p);

            for(int i=1;i<=100;i++)
                cout<<"\n";
            return;
        }
        if(ch=='p')
        {
            pot.PlayPotion(p,e);
        }
        if(ch<='9'&&ch>='1')
        {
            //cout<<ch;
            PlayCard(h,int(ch-'1'));
        }
        if(e.get_value("Hp")<=0)return;
        Afisare(p,e,h,pot);
    }

}

void GameOver(int stage)
{
    for(int i=1;i<=100;i++)
        cout<<"\n";
    cout<<"Game Over. You reached stage "<<stage<<"!\n";
    cout<<"You defeated:\n";
    array<pair<int,string>,4>a{{{-Assasin::ShowCounter(),"Assasins:"},
                                {-Bruiser::ShowCounter(),"Bruisers:"},
                                {-Rammer::ShowCounter(),"Rammers:"},
                                {-Slaver::ShowCounter(),"Slavers:"}}};
    sort(a.begin(),a.end());
    for(int i=0;i<=3;i++)
        cout<<a[i].second<<" "<<-a[i].first<<"\n";
    ///Cultist::ShowCounter();
}

Enemy* GetEnemy(int stage)
{
    int enemyvar=rand()%4;
    if(enemyvar==0)
    {
        Assasin *e = new Assasin(stage);
        if(stage%3==0)MakeElite(e,stage);
        return e;
    }
    if(enemyvar==1)
    {
        Bruiser *e = new Bruiser(stage);
        if(stage%3==0)MakeElite(e,stage);
        return e;
    }
    if(enemyvar==2)
    {
        Slaver *e = new Slaver(stage);
        if(stage%3==0)MakeElite(e,stage);
        return e;
    }
    if(enemyvar==3)
    {
        Rammer *e = new Rammer(stage);
        if(stage%3==0)MakeElite(e,stage);
        return e;
    }
    /*if(enemyvar==4)
    {
        Cultist *e = new Cultist(stage);
        if(stage%3==0)MakeElite(e,stage);
        return e;
    }*/
}

int Combat(int stage, shared_ptr<PotionBelt> pot)
{
    Player* p=Player::getPlayer();

    Enemy *e=GetEnemy(stage);
    while(p->get_value("Hp")>0&&e->get_value("Hp")>0)
        Turn(*p,*e,*pot);

    if(p->get_value("Hp")>0)
    {
        delete e;
        p->EndCombat();
        pot->GainPotion();
        return 1;
    }
    GameOver(stage);
    return 0;
}


#endif // A_H_INCLUDED
