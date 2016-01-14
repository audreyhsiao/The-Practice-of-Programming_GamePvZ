#include"Zombie.h"
#include"Plant.h"
#include"Player.h"
#include"Land.h"
#include"Map.h"
#include<cstdlib>
#include<time.h>

using namespace std;
int main()
{
    srand(time(0));
    constexpr int COUNT = 5;
    int lands = 0;
    cout << "Number of lands on the map.";
    cin >> lands;
    cout << "Number of zombies.";
    cin >> Zombie::TotalNum;

    Map map(lands);
    Player p;
    Zombie * z = new Zombie[Zombie::TotalNum];

    /*Set pos*/
    p.Move(rand()%lands);
    for(int i=0;i<Zombie::TotalNum;i++)
        z[i].Move(rand()%lands);

    /*Display*/
    if(map.IsNonPlant())
    {
        cout << "The map is so clear!" << endl;
    }
    map.Display(p,z);
    /*Plainting*/
    HealPlant x("HealPlant",50,50,10);
    for(int i=0;i<COUNT;i++)
    {
        if(p.Money()>0)
        {
            if(map.GetLand(p.Pos())->IsEmpty())
            {
                cout << "p's money:" << p.Money() << endl;
                map.GetLand(p.Pos())->Planting(p,x);
                cout << "p plant a plant." << x.Name() << endl;
            }
        }

        for(int j=0;j<Zombie::TotalNum;j++)
        {
            if( z[j].isAlive() )
                cout << "z[" << j << "] move to " << map.Rand(z[j]) << endl;
            if( map.GetLand( z[j].Pos() )->IsEmpty() == false )
            {
                Plant * tmp = map.GetLand(z[j].Pos())->GetPlant();
                if( tmp -> Type() == 'S' || tmp -> Type() == 'B')
                {
                    int attack = ( tmp -> Type() == 'S' )?( tmp->Attack() ):( tmp->Hp() );
                    z[j].Damage( attack ) ;
                    cout << tmp -> Name() << "gives" << attack << "damages to the Zombie!" << endl;
                }
                tmp->Damage( z[j].Attack() );
                cout << "Zombie eats Plant " << tmp->Name() << " and causes damage" << z[j].Attack() << endl;
                if( !z[j].isAlive() )
                    cout << "Zombie is killed!" << endl;
                if(!tmp->isAlive())
                    cout << "Plant " << tmp->Name() << " is killed" << endl;
                system("pause");

            }
        }
        int position = map.Rand(p);
        cout << "p move to " << position << endl<< endl;
        Land *l = map.GetLand(position);
        if(!l->IsEmpty())
        {
            Plant *p = l->GetPlant();
            if(p->HpBack())
            {
                cout << "oh no?" << endl;
                map.Healing(p->HpBack());
                cout << "All your plants have recovered "<< p->HpBack() << " HP!" << endl;
            }
        }
        system("pause");
        map.Display(p,z);
        system("pause");
        system("cls");
    }
    delete []z;
    return 0;
}
