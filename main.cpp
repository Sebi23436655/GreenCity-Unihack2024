# include <bits/stdc++.h>

using namespace std;
int nrcladiri=0;
int trees=1000;
double treeModifier=1;
struct building{string name;int pollution;int cost;short productionType;int gain;}cladiri[1000];
struct event{int type; string problem; string outcome;  int cost;}evenimente[100];
struct resource{string name; int gain; int val;}food,population,money,pollution,happiness;
void currentBuildings()
{
    if(nrcladiri)
    {
        cout<<" # Your buildings are: \n ";
        for(int i=0;i<nrcladiri;i++)
            cout<<1+i<<". "<<cladiri[i].name<<"\n ";
    }
}
void events(int diff)
{
    srand(unsigned(time(0)));
    int p=rand()%16+1;
    string eventType[3];
    eventType[0]=" !EVENT! \n";
    eventType[1]=" !!DISASTER!! \n";
    eventType[2]=" !!!EXTREME EVENT!!! \n";
    bool problem=0;
    if(p<5)
    {
        cout<<" # Everything is going as usual \n";
    }
    else
    {
        p-=4;
        if(diff<3)
            p=1+(p%10);
        cout<<eventType[evenimente[p].type];
        cout<<" # "<<evenimente[p].problem<<"(costs "<<evenimente[p].cost<<" to guarantee it's resolved) \n # If not resolved "<<evenimente[p].outcome;
        if(evenimente[p].type==0)
        {
            cout<<"\n # Do you wish to resolve it?(Y/N) \n > ";
            char resolve;
            cin>>resolve;
            resolve=toupper(resolve);
            if(resolve == 'Y' && money.val>evenimente[p].cost)
            {
                money.val-=evenimente[p].cost;
            }
            else
            {
                problem=1;
            }
        }
        else if(evenimente[p].type==1)
        {
            int cost=1+(rand()%evenimente[p].cost);
            cout<<"\ # How much do you want to pay to resolve this event(success rate is proportional to money payed)?(Y/N) \n > ";
            int pay=-1;
            while(true)
            {
                cin>>pay;
                if(pay<money.val)
                    cout<<" # Not enough money \n > ";
                else
                {
                    money.val-=pay;
                    if(pay<cost)
                    {
                        problem=1;
                    }
                    break;
                }
            }
            if(problem)
            {
                cout<<" # Issue wasn't resolved \n";
                switch(p)
                {
                    case 1:
                    {
                        p++;
                    }
                    case 2:
                    {
                        money.gain-=200;
                        break;
                    }
                    case 3:
                    {
                        p++;
                    }
                    case 4:
                    {
                        food.val=0;
                        break;
                    }
                    case 5:
                    {
                        p++;
                    }
                    case 6:
                    {
                        population.val-=500;
                        happiness.val-=300;
                        break;
                    }
                    case 7:
                    {
                        p++;
                    }
                    case 8:
                    {
                        pollution.gain+=150;
                        break;
                    }
                    case 9:
                    {
                        p++;
                    }
                    case 10:
                    {
                        happiness.val-=600;
                        happiness.gain-=50;
                        break;
                    }
                    case 11:
                    {
                        population.val-=300;
                        trees=0;
                        happiness.val-=500;
                        break;
                    }
                    case 12:
                    {
                        population.val*=0.3;
                        population.gain-=300;
                        happiness.val-=800;
                        break;
                    }
                    case 13:
                    {
                        money.val=0;
                        money.gain*=0.3;
                        break;
                    }
                }
            }
            else
                cout<<"Issue resolved successfully \n";
        }
    }
}
void fbuild(building optiuniCladiri[][3],int answer,int &schimb,int x)
{
    if(money.val>=optiuniCladiri[x][answer].cost)
        {
            int p;
            cout<<" # You successfully bought a "<<optiuniCladiri[x][answer].name<<'\n';
            char repl='Y';

            if(!nrcladiri)
            {
                repl='N';
            }
            else if(trees)
            {
                cout<<" # Do you want to replace an already existing building? This wont refund the destroyed building's cost.(Y/N) \n > ";
                cin>>repl;
                toupper(repl);
            }
            if(repl=='Y')
            {
                cout<<" # What's the number of the building you want to replace? \n";
                int n;
                currentBuildings();
                cout<<"< ";
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
                trees-=50;
            }
            cladiri[p]=optiuniCladiri[x][answer];
            schimb+=optiuniCladiri[x][answer].gain;
        }
    else
        cout<<"You don't have enough money"<<'\n';
}
void asighn(building v[],string nume[],int productionT, int gain[3],int cost[],int pol[])
{
    for(int i=0;i<3;i++)
    {
        v[i].cost=cost[i];
        v[i].name=nume[i];
        v[i].pollution=pol[i];
        v[i].productionType=productionT;
        v[i].gain=gain[i];
    }

}
void introductie()
{
    cout<<" - Your goal is to create a fully sustainable city \n - each citizen consumes 1 food per year, if there isn't enough food for everyone the people without food will leave town, people move in every year based on the overall happiness \n";
    cout<<" - People will constantly loose happiness, if their happiness is too low some of them will leave town, people become more unhappy during disasters \n";
    cout<<" - Occasionally random events will appear, those are mostly negative things that make the game harder, there are 3 types of random events\n 1. Normal Events: They won't straight up loose you the game if left unattended and are easy to resolve \n 2. Disasters: Will loose you the game if left unattended \n     - Require you to allocate large amounts of resources to guarantee they are resolved \n     - You may spend less money in order to have a random chance of resolving them \n 3. Extreme Events: Events that will loose you the game if not resolved immediately \n     - Take an absurd amount of resources to guarantee they are fixed \n     - You could pay less for a chance at completing them but you will also receive a permanent negative side effect \n";
    cout<<" - Pollution constantly increases over time, your city is in a forest so the trees will absorb some of the pollution, building structures removes 50 trees \n";
    cout<<" - You loose if the population reaches 0 or if the pollution reaches a value greater than 500 \n";
    cout<<" - You aren't in charge of housing \n";
    cout<<" - You win when you make a fully sustainable city that has over 1500 people and over 500 happiness \n";
}
void status()
{
    cout<<" # remaining food:"<<food.val<<", food gain:"<<food.gain-population.val;
    cout<<"\n # remaining population:"<<population.val<<", population gain:"<<happiness.val/5+population.gain;
    cout<<"\n # remaining money:"<<money.val<<", money gain:"<<money.gain;
    cout<<"\n # pollution is at:"<<pollution.val<<", pollution gain:"<<pollution.gain-trees/2*treeModifier;
    cout<<"\n # overall happiness is at:"<<happiness.val<<", happiness gain:"<<happiness.gain;
    cout<<"\n # the number of trees is:"<<trees<<'\n';

}
void construire()
{
    currentBuildings();
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
    int vferme[3]={400,400,400},vgen[3]={500,200,400},vent[3]={50,50,40},cstandard[3]={200,400,600},pstandard[3]={300,150,0},cpowerplant[3]={200,150,600},ppowerplant[3]={300,50,0};
    asighn(optiuniCladiri[0],ferme,1,vferme,cstandard,pstandard);
    asighn(optiuniCladiri[1],powerPlants,2,vgen,cpowerplant,ppowerplant);
    asighn(optiuniCladiri[2],entertainment,3,vent,cstandard,pstandard);
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
                    switch(type)
                    {
                        case 0:
                        {
                            fbuild(optiuniCladiri,answer,food.gain,type);
                            break;
                        }
                        case 1:
                        {
                            fbuild(optiuniCladiri,answer,money.gain,type);
                            break;
                        }
                        case 2:
                        {
                            fbuild(optiuniCladiri,answer,happiness.gain,type);
                            happiness.val+=optiuniCladiri[type][answer].gain*10;
                            break;
                        }

                    }
                    pollution.gain+=optiuniCladiri[type][answer].pollution;
                    money.val-=optiuniCladiri[type][answer].cost;
                    break;
                }
            }
        }
        cout<<" # Remaining money:" <<money.val<<'\n';
        cout<<" # Do you want to build anything else?(Y/N) \n > ";
        char repeat;
        cin>>repeat;
        toupper(repeat);
        if(repeat=='N')
            construction=0;

    }

}
void joc(int diff)
{
    if(true)
    {
        /// if pt a ascunde initializarile
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
        evenimente[1].type=0;
        evenimente[1].problem="Due to a bank being close to going bankrupt there there will be an economic crisis";
        evenimente[1].outcome="You will gain 200 less money";
        evenimente[1].cost=500;
        evenimente[2]=evenimente[1];
        evenimente[3].type=0;
        evenimente[3].problem="Due to a spike in the rat population the city's food reserves are at risk";
        evenimente[3].cost=400;
        evenimente[3].outcome="Food will be set to 0(you will still gain food before you loose population)";
        evenimente[4]=evenimente[3];
        evenimente[5].type=0;
        evenimente[5].problem="Due to some problems with the sewage the streets have started to stink, if you don't fix it people will move out and happiness will decrease";
        evenimente[5].outcome="Population will decrease by 500 and happiness by 300";
        evenimente[5].cost=600;
        evenimente[6]=evenimente[5];
        evenimente[7].type=0;
        evenimente[7].problem="Due to how outdated some of the citizen's cars are they are polluting the atmosfere";
        evenimente[7].outcome="Pollution gain will increase by 150";
        evenimente[7].cost=400;
        evenimente[8]=evenimente[7];
        evenimente[9].problem="Due to the increase of technology that require 5G people will become way unhappier if you do not implement more 5G towers";
        evenimente[9].cost=400;
        evenimente[9].outcome="Happiness will decrease by 600 and happiness gain will be lowered by 50";
        evenimente[10]=evenimente[9];
        evenimente[11].problem="A massive forest fire was detected";
        evenimente[11].cost=1000;
        evenimente[11].outcome="All the trees will be gone and no more buildings will be able to be built in that area(You can still replace old buildings)\n #The casualties will sit at 300 and happiness will be lowered by 500";
        evenimente[11].type=1;
        evenimente[12].type=1;
        evenimente[12].problem="Toxic substances were detected in the water supply";
        evenimente[12].outcome="70% of the population will die, 300 less people will move in each year and happiness will be lowered by 800";
        evenimente[12].cost=1000;
        evenimente[13].type=1;
        evenimente[13].problem="Multiple major banks in the city are going bankrupt";
        evenimente[13].outcome="You will loose all your money reserves and 70% of the money you are currently";
    }

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
    tutorial=toupper(tutorial);
    if(tutorial=='Y')
        introductie();
    for(int year=1;true;year++)
    {
        cout<<"# Year "<<year<<": \n";
        status();
        if(year>2)
        {
            events(diff);
        }
        int random=rand()%1;
        cout<<" # Do you want to build anything?(Y/N) \n > ";
        char answer;
        cin>>answer;
        answer=toupper(answer);
        if(answer == 'Y')
        {
            construire();
        }
        food.val+=food.gain;
        if(happiness.val<200)
            population.val-=200-happiness.val;
        money.val+=money.gain;
        pollution.val+=pollution.gain-trees*treeModifier/2;
        happiness.val+=happiness.gain;
        food.val -= population.val;
        if(population.val<=0 || money.val<200 && money.gain<1 || pollution.val>500)
        {
            cout<<"YOU LOST \n"<<'\n';
            return;
        }
        population.val+=happiness.val/5+population.gain;
        if(population.val>1500 && food.gain>population.val && happiness.val>=500 && pollution.gain-trees*treeModifier/2<=0 )
        {
            cout<<"YOU WON \n"<<'\n';
            return;
        }
        if(pollution.val<0)
            pollution.val=0;
        if(food.val<0)
        {
            population.val+=food.val;
            food.val=0;
        }

    }
}
int main()
{
    short diff;
    cout<<" # Choose a difficulty \n 1.Trivial \n - Trees decrease pollution faster \n - Pollution decreases automatically over time \n - You get free money from the government \n - No random events \n - For the weak \n";
    cout<<"2. Easy \n - Trees decrease pollution faster \n - No natural disasters \n - No extreme random events \n - recommended if u don't know what your doing \n";
    cout<<"3. Medium \n - The game as intended \n - No extreme random events \n";
    cout<<"4. Hard \n - Trees decrease pollution slower \n - Citizens are unhappier \n - More random events \n - The government steals money from you \n - For those looking for a challenge \n";
    cout<<"5. Extreme \n - Pollution can't decrease \n - Citizens are way unhappier \n - More extreme events \n - The Government steals money from you \n - For experts at resource managment \n > ";
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
        toupper(tryAgian);
        cin>>tryAgian;
        if(tryAgian=='N')
        {
            cout<<" # Thank you for playing! \n # Game made by Sebastian Balan for Unihack 2024";
        }
    }
    return 0;
}
