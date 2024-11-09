# include <bits/stdc++.h>

using namespace std;
int nrcladiri=0;
int trees=1000;
double treeModifier;
struct building{string name;int pollution;int cost;short productionType;int gain;}cladiri[1000];
struct event{string name; string type; int cost;}evenimente[100];
struct resource{string name; int gain; int val;}food,population,money,pollution,happiness;
void fbuild(building optiuniCladiri[][3],int answer,int &trees,int &schimb,int x)
{
    if(money.val>=optiuniCladiri[x][answer].cost)
        {
            int p;
            cout<<" # You successfully bought a "<<optiuniCladiri[x][answer].name<<'\n';
            char repl='Y';
            if(trees)
            {
                cout<<" # Do you want to replace an already existing building? This wont refund the destroyed building's cost.(Y/N) \n > ";
                cin>>repl;
            }
            if(repl=='Y')
            {
                cout<<" # What's the number of the building you want to replace? \n > ";
                int n;
                while(true)
                {
                    cin>>n;
                    n--;
                    if(n>=0 && n<nrcladiri)
                    {
                        p=n;
                        switch(cladiri[p].productionType)
                        {
                            case 1:
                            {
                                food.gain-=cladiri[p].gain;
                                break;
                            }
                            case 2:
                            {
                                money.gain-=cladiri[p].gain;
                                break;
                            }
                            case 3:
                            {
                                happiness.gain-=cladiri[p].gain;
                                happiness.val-=cladiri[p].gain*5;
                                break;
                            }
                        }
                        pollution.gain-=cladiri[p].pollution;
                        break;
                    }
                    else
                    {
                        cout<<" # Has to be a number between 1 and "<<nrcladiri<<"\n > ";
                    }
                }

            }
            else
            {
                p=nrcladiri;
                nrcladiri++;
            }
            cladiri[p]=optiuniCladiri[x][answer];
            schimb+=optiuniCladiri[x][answer].gain;
        }
    else
        cout<<"You don't have enough money"<<'\n';
}
void asighn(building v[],string nume[],int productionT, int gain[3])
{
    int spoll=300,scost=200;
    for(int i=0;i<3;i++)
    {
        v[i].cost=scost;
        v[i].name=nume[i];
        v[i].pollution=spoll;
        v[i].productionType=productionT;
        v[i].gain=gain[i];
        scost+=200;
        spoll-=150;
    }

}
void introductie()
{
    cout<<" - Your goal is to create a fully sustainable city \n - each citizen consumes 1 food per year, if there isn't enough food for everyone the people without food will leave town, people move in every year based on the overall happiness \n";
    cout<<" - People will constantly loose happiness, if their happiness is too low some of them will leave town, people become more unhappy during disasters \n";
    cout<<" - Occasionally random events will appear, those are mostly negative things that make the game harder, there are 3 types of random events\n 1. Normal Events: They won't straight up loose you the game if left unattended and are easy to resolve \n 2. Natural Disasters: Will loose you the game if left unattended \n     - Require you to allocate large amounts of resources to guarantee they are resolved \n     - You may spend less money in order to have a random chance of resolving them \n 3. Extreme Events: Events that will loose you the game if not resolved immediately \n     - Take an absurd amount of resources to guarantee they are fixed \n     - You could pay less for a chance at completing them but you will also receive a permanent negative side effect \n";
    cout<<" - Pollution constantly increases over time, your city is in a forest so the trees will absorb some of the pollution, building structures removes 50 trees \n";
    cout<<" - You loose if the population reaches 0 or if the pollution reaches a value greater than 500 \n";
    cout<<" - You aren't in charge of housing \n";
    cout<<" - You win when you make a fully sustainable city that has over 1500 people and over 500 happiness \n";
}
void status()
{
    cout<<" # remaining food:"<<food.val<<", food gain:"<<food.gain;
    cout<<"\n # remaining population:"<<population.val<<", population gain:"<<happiness.val/5;
    cout<<"\n # remaining money:"<<money.val<<", money gain:"<<money.gain;
    cout<<"\n # pollution is at:"<<pollution.val<<", pollution gain:"<<pollution.gain-trees/2*treeModifier;
    cout<<"\n # overall happiness is at:"<<happiness.val<<", happiness gain:"<<happiness.gain;
}
void construire(int &trees)
{
    if(nrcladiri==0)
        cout<<" # You haven't built anything yet \n ";
    else
    {
        cout<<" # Your current buildings are: \n ";
        for(int i=0;i<nrcladiri;i++)
            cout<<i+1<<". "<<cladiri[i].name<<"\n ";
    }
    building optiuniCladiri[3][3];
    string ferme[3],powerPlants[3],entertainment[3];
    ferme[0]="livestock farm";
    ferme[1]="fruit and vegetable farm";
    ferme[2]="regenerative fruit and vegetable farm";
    powerPlants[0]="fossil fuel based power plant";
    powerPlants[1]="biomass based power plant";
    powerPlants[2]="wind/solar based power plant";
    entertainment[0]="stadium";
    entertainment[1]="eco-friendly stadium";
    entertainment[2]="theater";
    int vferme[3]={100,100,100},vgen[3]={500,300,400},vent[3]={50,50,40};
    asighn(optiuniCladiri[0],ferme,1,vferme);
    asighn(optiuniCladiri[1],powerPlants,2,vgen);
    asighn(optiuniCladiri[2],entertainment,3,vent);
    string tip[3];
    tip[0]="farms(generate food)";
    tip[1]="power plants(generate money)";
    tip[2]="entertainment(generate happiness, happiness spikes when they are built, drastically lowers when destroyed)";
    bool construction=1;
    while(construction)
    {
        cout<<" # What do you want to build? \n 1. Farm \n 2. Power plant \n 3. Entertainment building\n > ";
        int type;
        cin>>type;
        type--;
        if(type<0 || type>2)
        {
            cout<<" # Has to be a number from 1 to 3, try again \n > ";
        }
        else
        {
            cout<<" # What type of "<<tip[type]<<" do you want to build? \n ";
            for(int i=0;i<3;i++)
                cout<<i+1<<". "<<optiuniCladiri[type][i].name<<"(pollution:"<<optiuniCladiri[type][i].pollution<<", earnings per year:"<<optiuniCladiri[type][i].gain<<", cost:"<<optiuniCladiri[type][i].cost<<") \n ";
            cout<<"4. None of the above \n > ";
            int answer=0;
            while(!answer)
            {
                cin>>answer;
                if(answer<1||answer>4)
                {
                    cout<<" # Has to be a number between 1 to 4, try again \n > ";
                }
                else if(answer!=4)
                {
                    answer--;
                    switch(answer)
                    {
                        case 0:
                        {
                            fbuild(optiuniCladiri,answer,trees,food.gain,type);
                            break;
                        }
                        case 1:
                        {
                            fbuild(optiuniCladiri,answer,trees,money.gain,type);
                            break;
                        }
                        case 2:
                        {
                            fbuild(optiuniCladiri,answer,trees,happiness.gain,type);
                            happiness.val+=cladiri[nrcladiri-1].gain*10;
                            break;
                        }

                    }
                    break;
                }
            }
        }
        cout<<" # Do you want to build anything else?(Y/N) \n >";
        char repeat;
        cin>>repeat;
        if(repeat=='N')
            construction=0;

    }

}
void joc(int diff)
{
    food.name="food";
    food.val=1500;
    population.val=500;
    money.val=1000;
    population.name="population";
    money.name="money";
    pollution.name="pollution";
    happiness.name="happiness";
    happiness.val=1000;
    happiness.gain=-200;
    if(diff<=2)
    {
        treeModifier=1.5;
        money.gain=200;
        if(diff<2)
        {
            pollution.gain=-100;
        }
    }
    else if(diff>3)
    {
        happiness.gain=-300;
        treeModifier=0.5;
        money.gain=-200;
    }
    char tutorial;
    cout<<"# Do you wanna read the tutorial?(Y/N) \n > ";
    cin>>tutorial;
    if(tutorial=='Y')
        introductie();
    bool continuing=1;
    for(int year=1;continuing;year++)
    {
        cout<<"# Year "<<year<<": \n";
        status();
        cout<<"\n # Do you want to build anything?(Y/N) \n > ";
        char answer;
        cin>>answer;
        if(answer == 'Y')
        {
            construire(trees);
        }
        food.val+=food.gain;
        population.val+=happiness.val/5;
        if(happiness.val<200)
            population.val-=200-happiness.val;
        money.val+=money.gain;
        pollution.val+=pollution.gain-trees*treeModifier/2;
        happiness.val+=happiness.gain;
        food.val -= population.val;
        if(population.val<=0 || money.val<200 && money.gain<1 || pollution.val>500)
        {
            cout<<"YOU LOST"<<'\n';
            return;
        }
        if(population.val>1500 && food.gain>population.val && happiness.val>=500 && pollution.gain<=0 )
        {
            cout<<"YOU WON"<<'\n';
            return;
        }
        if(pollution<0)
            pollution=0;
        if(food<0)
        {
            population+=food;
            food=0;
        }
    }
}
int main()
{
    short diff;
    cout<<" # Choose a difficulty \n 1.Trivial \n - Trees decrease pollution faster \n - Citizens are immortal and can't leave town \n - Pollution decreases automatically over time \n - You get free money from the government \n - No random events \n - For the weak \n";
    cout<<"2. Easy \n - Trees decrease pollution faster \n - Citizens only leave if their life is in danger \n - No natural disasters \n - Citizens require less food \n - No extreme random events \n - recommended if u don't know what your doing \n";
    cout<<"3. Medium \n - The game as intended \n - No extreme random events \n";
    cout<<"4. Hard \n - Trees decrease pollution slower \n - Citizens are unhappier \n - More random events \n - The government steals money from you \n - Riots appear that greatly reduce happiness \n - For those looking for a challenge \n";
    cout<<"5. Extreme \n - Pollution can't decrease \n - Citizens are way unhappier \n - More extreme events \n - The Government steals money from you \n - Lots of riots \n - For experts at resource managment \n > ";
    bool ok=1;
    while(ok)
    {
        cin>>diff;
        string dificulties[5]={"Trivial","Easy","Medium","Hard","Extreme"};
        if(diff<6 && diff>0)
           {
               cout<<" # Difficulty set to "<<dificulties[diff- 1]<<"\n ";
               ok=0;
           }
        else
            cout<<" # Difficulty has to be a number from 1 to 5, try again \n > ";
    }
    while(true)
    {
        joc(diff);
        cout<<" # Play again?(Y/N)? \n > ";
        char tryAgian;
        cin>>tryAgian;
        if(tryAgian=='N')
        {
            cout<<" # Thank you for playing! \n # Game made by Sebastian Balan for Unihack 2024";
        }
    }
    return 0;
}
