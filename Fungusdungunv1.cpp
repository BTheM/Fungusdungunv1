#include <iostream>
#include <cmath>
#include <string>
#include <limits>
#include <random>
#include <ctime>

using namespace std;

//enums section
enum enJob { Warrior = 1, Wizard = 2, Thief = 3 };
enum enEnemy { Minshroom = 1, Fungi = 2, Shroomguard = 3, SporespreaderFungus = 4, BigMushroomMan = 5 };
//enum enSpecialEnemy { FungusGoblino = 1, BombaFungus = 2, Gnome = 3 };
//enum enBossEnemy { MushroomTree = 1 };

//functions section
struct stStats
{
    string jobname;
    int hp;
    int def;
    int atk;
    int mp;
    int crit;
};

struct stEnemyStats
{
    string enemyName;
    int hp;
    int def;
    int atk;
    int mp;
};

void JobStats(enJob job, stStats& stat)
{
    switch (job)
    {
    case Warrior:
        stat.jobname = "Warrior";
        stat.hp = 100;
        stat.def = 15;
        stat.atk = 20;
        stat.mp = 0;
        stat.crit = 1;
        break;
    case Wizard:
        stat.jobname = "Wizard";
        stat.hp = 100;
        stat.def = 5;
        stat.atk = 10;
        stat.mp = 40;
        stat.crit = 1;
        break;
    case Thief:
        stat.jobname = "Thief";
        stat.hp = 100;
        stat.def = 10;
        stat.atk = 18;
        stat.mp = 10;
        stat.crit = 90;
        break;
    }
}

void EnemyStats(enEnemy enemy, stEnemyStats& stat)
{
    switch (enemy)
    {
    case Minshroom:

        stat.enemyName = "Minshroom";
        stat.hp = 10;
        stat.def = 0;
        stat.atk = 20;
        stat.mp = 0;
        break;
    case Fungi:

        stat.enemyName = "Fungi";
        stat.hp = 20;
        stat.def = 5;
        stat.atk = 20;
        stat.mp = 0;
        break;
    case Shroomguard:

        stat.enemyName = "Shroom Guard";
        stat.hp = 20;
        stat.def = 10;
        stat.atk = 20;
        stat.mp = 0;
        break;
    case SporespreaderFungus:

        stat.enemyName = "Spore Spreader Fungus";
        stat.hp = 20;
        stat.def = 0;
        stat.atk = 10;
        stat.mp = 20;
        break;
    case BigMushroomMan:

        stat.enemyName = "Big Mushroom Man";
        stat.hp = 50;
        stat.def = 10;
        stat.atk = 30;
        stat.mp = 0;
        break;
    }
}

string Readstring(string message)
{
    string name;
    cout << message << endl;
    getline(cin >> ws, name);

    return name;
}

int ReadNumberInRange(string Message, int From, int To)
{
    int Number = 0;

    do
    {
        Number = 0;
        cout << Message << endl;
        cin >> Number;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\033[31m\nInvalid input! Please enter a number from between \033[0m" << From << "\033[31m to \033[0m" << To << endl;
            continue;
        }

    } while (Number < From || Number > To);
    return Number;
}

int Randomcrit(int& atk, int crit, mt19937& rng)
{
    uniform_int_distribution<int> dist(1, 100);

    if (dist(rng) <= crit)
    {
        atk *= 2;
        cout << "\nCRITICAL HIT!!!\n " << atk << endl;
    }

    return atk;
}

void Calculateatk(int atk, int crit ,int def, int& hp, mt19937 rng)
{
    int afterdef = 0;
    Randomcrit(atk, crit, rng);

    if (atk > def)
    {
        
        afterdef = atk - def;
         hp -= afterdef;
    }
    else
    {
        cout << "\nNo damage was dealt!\n";
    }
}

void CalculateSpell(int mp, int& hp, int choosingspell)
{
    switch (choosingspell)
    {
        case 1:
        {
            cout << "\nFIREBALL!\n";
            hp -= mp;
            break;
        }
        case 2:
        {
            cout << "\nA cold storm!\n";
            mp = mp / 2;
            hp -= mp;
            break;
        }
    }
}

stEnemyStats RandomEnemy(enEnemy& enemy, mt19937& rng)
{
    uniform_int_distribution<int> dist(1, 5);

    enemy = static_cast<enEnemy>(dist(rng));

    stEnemyStats stats;
    EnemyStats(enemy, stats);

    cout << "\033[93m" << "\nA Fungus have spawned!\n" << "\033[0m";
    cout << "\033[93m" << stats.enemyName << "!" << "\033[0m" << endl;

    return stats;
}

bool YesnoChoice(const string& Message)
{
    while (true)
    {
        int YesnoSelect;

        cout << Message << " (1 = Yes/ 0 = No): " << endl;
        cin >> YesnoSelect;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\033[31m\nERROR! INVALID INPUT! Please enter 1 as Yes or 0 as No\n\033[0m" << endl;
            continue;
        }

        if (YesnoSelect == 1)
        {
            cout << YesnoSelect << endl;
            return true;
        }
        else if (YesnoSelect == 0)
        {
            cout << YesnoSelect << endl;
            return false;
        }
        else
        {
            cout << "\033[31m\nERROR! Please enter 1 for Yes or 0 for No.\n\033[0m" << endl;
        }
    }
}

void Printstats(stStats stat, string name)
{
    cout << "\nYour name: " << name << endl;
    cout << "Job: " << stat.jobname << endl;
    cout << "hp: " << stat.hp << endl;
    cout << "def: " << stat.def << endl;
    cout << "atk: " << stat.atk << endl;
    cout << "mp: " << stat.mp << endl;
    cout << "crit: " << stat.crit << endl;
}

void Printenemystats(stEnemyStats stat, string name)
{
    cout << "\nEnemy name: " << name << endl;
    cout << "hp: " << stat.hp << endl;
    cout << "def: " << stat.def << endl;
    cout << "atk: " << stat.atk << endl;
    cout << "mp: " << stat.mp << endl;
}

void Library()
{
    int Choosenum;
    cout << "\n===================\n";
    cout << "\nGreetings scholar and welcome to the fungus library.\n";
    cout << "\nOnly those of high intelligence may enter the library.\n";
    cout << "\nWhat do you wish to learn today?\n";
    cout << "\n===================\n";

    do
    {
        cout << "\n===================\n";
        Choosenum = ReadNumberInRange("\n1. Job stat\n2. Enemy stat\n3. stats explained\n4. spells\n5. leave the library", 1, 5);
        cout << "\n===================\n";
        switch (Choosenum)
        {
        case 1:
        {
            stStats stat;
            enJob job;
            int choosejobstat;
            do
            {
                cout << "\n===================\n";
                choosejobstat = ReadNumberInRange("\n1. Warrior\n2. Wizard\n3. Thief\n4. leave this menu", 1, 4);
                job = (enJob)choosejobstat;

                JobStats(job, stat);

                string Jobname[] = { "Warrior", "Wizard", "Thief" };
                if (choosejobstat >= 1 && choosejobstat <= 3)
                {
                    Printstats(stat, Jobname[choosejobstat - 1]);
                }
            } while (choosejobstat != 4);
            cout << "\n===================\n";
            break;
        }
        case 2:
        {
            stEnemyStats enemystat;
            enEnemy enemy;
            int chooseenemystat;
            do
            {
                cout << "\n===================\n";
                chooseenemystat = ReadNumberInRange("\n1. Minshroom\n2. Fungi\n3. Shroomguard\n4. Spore Spreader Fungus\n5. Big Mushroom man\n6. leave this menu", 1, 6);
                enemy = (enEnemy)chooseenemystat;

                EnemyStats(enemy, enemystat);

                string Enemyname[] = { "Minshroom", "Fungi", "Shroomguard", "Spore Spreader Fungus", "Big Mushroom man" };
                if (chooseenemystat >= 1 && chooseenemystat <= 5)
                {
                    Printenemystats(enemystat, Enemyname[chooseenemystat - 1]);
                }
            } while (chooseenemystat != 6);
            cout << "\n===================\n";
            break;
        }
        case 3:
        {
            cout << "\n===================\n";
            cout << "hp stands for health points. If a person hp reaches 0, they die." << endl << endl;
            cout << "def stands for defensive. when a person takes an attack, that attack would be reduced by the amount of def they have." << endl << endl;
            cout << "atk stands for attack. When attacking with a weapon, the target would take that amount of damage to their health points." << endl << endl;
            cout << "mp stands for magic power. the more magic power you have, the stronger your spells will be." << endl << endl;
            cout << "crit stands for critical strike. It increases the chance to double the damage when attacking. the more crit you have the higher your chance to crit. (Only the player can have this stat)" << endl << endl;
            cout << "\n===================\n";
            break;
        }
        case 4:
        {
            cout << "\n===================\n";
            cout << "Fireball - a ball of fire that deals 100% of your magic power to a single target." << endl << endl;
            cout << "Icestorm - summon a storm around you that deals 50% of your magic power to all enemies." << endl << endl;
            //cout << "Heal - Heal the player for 50% of magic power." << endl << endl;
            cout << "\n===================\n";
            break;
        }
        }
    } while (Choosenum >= 1 && Choosenum <= 4);
    cout << "\nGoodbye\n" << endl;
}

void Combat(stStats& stats, stEnemyStats& enemystats, mt19937& rng)
{
    while (stats.hp > 0 && enemystats.hp > 0)
    {
            int Choosenum = 0;
            if (stats.jobname == "Wizard")
            {
                cout << "\033[92m" << "\nYour health : " << stats.hp << "\033[0m";
                cout << "\033[91m" << "\nEnemy health: " << enemystats.hp << "\033[0m" << endl;
                cout << "\n===========================\n";
                cout << "\nWhats your next action?";
                cout << "\033[90m" << "\n1. Attack" << "\033[0m";
                cout << "\033[94m" << "\n2. Defend" << "\033[0m";
                cout << "\033[96m" << "\n3. Spell" << "\033[0m";
                cout << "\n===========================\n";
                Choosenum = ReadNumberInRange("", 1, 3);


                    switch (Choosenum)
                    {
                        case 1:
                        {
                            //player attack enemy
                            Calculateatk(stats.atk, stats.crit, enemystats.def, enemystats.hp, rng);
                            //enemy attack player
                            if (enemystats.hp > 0)
                            {
                                Calculateatk(enemystats.atk, 0, stats.def, stats.hp, rng);
                            }
                            break;
                        }
                        case 2:
                        {
                            stats.def += 10;
                            //enemy attack player
                            Calculateatk(enemystats.atk, 0, stats.def, stats.hp, rng);
                            stats.def -= 10;
                            break;
                        }
                        case 3:
                        {
                            int Choosespell = 0;
                            cout << "\n===========================\n";
                            cout << "\n1. Fireball";
                            cout << "\033[94m" << "\n2. Icestorm" << "\033[0m";
                            cout << "\n===========================\n";
                            Choosespell = ReadNumberInRange("", 1, 2);

                            CalculateSpell(stats.mp, enemystats.hp, Choosespell);
                            if (enemystats.hp > 0)
                            {
                                Calculateatk(enemystats.atk, 0, stats.def, stats.hp, rng);
                            }
                            break;
                        }
                    }
            }
            else
            {
                cout << "\033[92m" << "\nYour health : " << stats.hp << "\033[0m";
                cout << "\033[91m" << "\nEnemy health: " << enemystats.hp << "\033[0m" << endl;
                cout << "\n===========================\n";
                cout << "\nWhats your next action?";
                cout << "\033[90m" << "\n1. Attack" << "\033[0m";
                cout << "\033[94m" << "\n2. Defend" << "\033[0m";
                cout << "\n===========================\n";
                Choosenum = ReadNumberInRange("", 1, 2);


                    switch (Choosenum)
                    {
                        case 1:
                        {
                            //player attack enemy
                            Calculateatk(stats.atk, stats.crit, enemystats.def, enemystats.hp, rng);
                            //enemy attack player
                            Calculateatk(enemystats.atk, 0, stats.def, stats.hp, rng);
                            break;
                        }
                        case 2:
                        {
                            stats.def += 10;
                            //enemy attack player
                            Calculateatk(enemystats.atk, 0, stats.def, stats.hp, rng);
                            stats.def -= 10;
                            break;
                        }
                    }
            }

    }
    if (stats.hp <= 0)
    {
        cout << "\033[31m" << "\n===========================\n" << "\033[0m";
        cout << "\033[31m" << "\nYou Died.\n" << "\033[0m";
        cout << "\033[31m" << "You died to " << enemystats.enemyName << "\033[0m";
        cout << "\033[31m" << "\n===========================\n" << "\033[0m";
        exit(0);
    }
    else
    {
        cout << "\033[35m" << "\n===========================\n" << "\033[0m";
        cout << "\033[35m" << "\nYou have slain the enemy!" << "\033[0m";
        cout << "\033[35m" << "\nYou killed " << enemystats.enemyName << "\033[0m";
        cout << "\033[35m" << "\n===========================\n" << "\033[0m";
    }
}

//finish this after combat function is done
void BattleLoop(stStats& stats, stEnemyStats& enemystat,enEnemy& enemy, mt19937 rng)
{
    int enemyDefeated = 0;
    while (enemyDefeated < 10 && stats.hp > 0)
    {
        enemystat = RandomEnemy(enemy, rng);
        Combat(stats, enemystat, rng);

        if (stats.hp > 0)
        {
            enemyDefeated++;
        }
    }

    if (enemyDefeated == 10)
    {
        cout << "\033[93m" << "\nYou have destroyed all the mushrooms within the dungeon!!\n" << "\033[0m";
    }
}

//main section
int main()
{
    random_device rd;
    mt19937 rng(rd());
    stStats stat;
    stEnemyStats enemystat;
    enEnemy enemy;
    int Choosejob = ReadNumberInRange("\nWhat is thy craft? (Warrior = 1, Wizard = 2, Thief = 3)\n", 1, 3);
    enJob job = (enJob)Choosejob;
    string name = Readstring("\nAnd what shall we call you?\n");
    bool libraryVisit;

    JobStats(job, stat);

    Printstats(stat, name);

    libraryVisit = YesnoChoice("\nDo you wish to visit the library?\n");

    if (libraryVisit)
    {
        Library();
    }

    cout << "\033[93m" << "\nYou may enter the dungon now.\nYour mission is to destroy the fungus tree.\nKeep destroying mushrooms and you will eventually find it.\nGood luck, " << stat.jobname << '.' << "\033[0m" << endl;

    BattleLoop(stat, enemystat, enemy, rng);

    switch (job)
    {
        case Warrior:
        {
            cout << "\033[93m" << "\nBrave warrior! You have destroyed all of the mushrooms and saved THE ENTIRE WORLD from the mushrooms that totally didn't harm anyone! as a reward you will recive a star sticker! We thank you again brave warrior!" << "\033[0m" << endl;
            cout << "\033[93m" << R"(
                    .
                   ,O,
                  ,OOO,
            'oooooOOOOOooooo'
              `OOOOOOOOOOO`
                `OOOOOOO`
                OOOO'OOOO
               OOO'   'OOO
              O'         'O
            )" << "\033[0m" << endl;

            break;
        }
        case Wizard:
        {
            cout << "\033[93m" << "\nWise wizard! with your knowlege and power you have made the mushrooms perish before you! as a reward we grant you access to the library for as long as you wish!" << "\033[0m" << endl;
            libraryVisit = YesnoChoice("\nDo you wish to visit the library? (no there is nothing new. we don't buy new books...)\n");

            if (libraryVisit)
            {
                Library();
            }
            break;
        }
        case Thief:
        {
            cout << "\033[93m" << "\nThief? THIEF! Guards! Guards! there is a thief in the Fungus halls!" << "\033[0m" << endl;
            break;
        }
    }


    cout << "\033[35m" << R"(
   _____  _____ 
  / ____|/ ____|
 | |  __| |  __ 
 | | |_ | | |_ |
 | |__| | |__| |
  \_____|\_____|
                
)" << "\033[0m" << endl;

    return 0;
}