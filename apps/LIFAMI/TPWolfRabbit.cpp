// apps/LIFAMI/TPWolfRabbit.cpp
#include <Grapic.h>
#include <math.h>
#include <iostream>

using namespace grapic;
using namespace std;


const int DIMW=1000;
const int TYPE_HERBE = 0;
const int TYPE_PROIE = 1;
const int TYPE_PREDATEUR = 2;
const int MAXTAB=100;
const int DUREE_VIE_PROIE=10;
const int DUREE_VIE_PREDATEUR=10;
const int MAX_JEUNE_PROIE=10;
const int MAX_JEUNE_PREDAYEUR=10;

//proie(t+1)-proie(t)=alpha*proie(t)-beta*proie(t)*predateur(t)
//predateur(t+1)-predateur(t)=-omega*predateur(t)+deta*predateur(t)*proie(t)

struct Ecosysteme
{
    float nbproies;
    float nbpredateurs;
    float a,b,c,d;
};

void evolution_pop(struct Ecosysteme & e)
{
    float nbp = e.nbproies;
    e.nbproies = e.nbproies*(1+e.a-e.b*e.nbpredateurs);
    e.nbpredateurs = -e.nbpredateurs*(-1-e.d*nbp+e.c);
}

void initEco(struct Ecosysteme & e)
{
    e.nbproies=120.0;
    e.nbpredateurs=40.0;
    e.a=0.045;
    e.b=0.001;
    e.c=0.025;
    e.d=0.0002;
}

void drawGraph (Ecosysteme e,Plot &p,int x)
{
    plot_add(p, x, e.nbproies);
    plot_add(p, x, e.nbpredateurs,1);
    plot_draw(p,200,200,800,800,false);

}

///////////////////////////////////////////////////////////////////////////////////////JEU//////////////////////////////////////////////////////////////////////
struct Individu
{
    int type;
    int age;
    int duree_jeune;
};

struct Ecosysteme2
{
    Individu grille[MAXTAB][MAXTAB];
    int dx, dy;
    int nbproies;
    int nbpredateurs;
    Image imgHerbe;
    Image imgProie;
    Image imgPredateur;
};

void initEco2(struct Ecosysteme2 & e)
{
    e.dx=10;
    e.dy=10;
    e.nbproies = 40;
    e.nbpredateurs = 10;
    e.imgHerbe = image("../data/lifami_WolfRabbit/herbe.jpg");
    e.imgProie = image("../data/lifami_WolfRabbit/mouton.jpg");
    e.imgPredateur = image("../data/lifami_WolfRabbit/loup.jpg");
    for(int y=0;y<e.dy;y++)
    {
        for(int x=0;x<e.dx;x++)
        {
            e.grille[y][x].type=TYPE_HERBE;
        }
    }
    int i,j,x,y;
    for(i=0;i<e.nbproies;i++)               //PLACE MOUTONS ALEATOIRE
    {
        do{
            x=rand()%(e.dx-2)+1;
            y=rand()%(e.dy-2)+1;
        }while(e.grille[y][x].type!=TYPE_HERBE);
        e.grille[y][x].type=TYPE_PROIE;
    }
    for(j=0;j<e.nbpredateurs;j++)               //PLACE LOUPS ALEATOIRE
    {
        do{
            x=rand()%(e.dx-2)+1;
            y=rand()%(e.dy-2)+1;
        }while(e.grille[y][x].type!=TYPE_HERBE);
        e.grille[y][x].type=TYPE_PREDATEUR;
    }
}

void voisinnage(struct Ecosysteme2 e, int x, int y, int & nbproie , int & nbpredateur)
{
    nbproie = 0;
    nbpredateur = 0;
    for(int j=-1; j<=1;j++)
    {
        for(int i=-1;i<=1;i++)
        {
            if((i!=0)&&(j!=0))
            {
                if(e.grille[y+j][x+i].type==TYPE_PROIE)
                    nbproie++;
                else if(e.grille[y+j][x+i].type==TYPE_PREDATEUR)
                    nbpredateur++;
                //switch(e.grille[y+j][x+i].type)
                //{
                //    case TYPE_PROIE : nbproie++ ; break;
                //    case TYPE_PREDATEUR : nbpredateur++ ; break;
                //}
            }
        }
    }
}

void evolution(struct Ecosysteme2 & e)
{
    struct Ecosysteme2 et=e;     //et = temps t     e = temps+1
    for(int y=1;y<=e.dy-2;y++)
    {
        for(int x=1;x<e.dx-2;x++)
        {
            int nbproies, nbpredateurs;
            voisinnage(et,x,y,nbproies,nbpredateurs);
            switch(et.grille[y][x].type)
            {
                case TYPE_PROIE : if((nbproies>0)&&(nbpredateurs==0))
                {
                }
                else if(et.grille[y][x].age>100)
                {
                    e.grille[y][x].type=TYPE_HERBE;
                }break;
                case TYPE_PREDATEUR : if((nbpredateurs>0)&&(et.grille[y][x].duree_jeune<DUREE_VIE_PREDATEUR))
                {
                }
                else if (nbproies>0)
                {
                    e.grille[y][x].duree_jeune=1;
                }
            }
        }
    }
}

int caseVersEcran(const Ecosysteme2& e, int x)                               //1 PIXEL = 1 CASE
{
    return int(x*DIMW /e.dx);
}

int drawEco(struct Ecosysteme2 e)
{
    int i,j;
    backgroundColor( 255, 255, 255, 255 );

    color(100, 100, 100);                               //couleur traits grille
    grid(0, 0, DIMW-1, DIMW-1, e.dx, e.dy);

    color(0, 0, 0);
    fontSize(15);

    for(i=0;i<e.dx+1;i++)
    {
        for(j=0;j<e.dy+1;j++)
        {
                if(e.grille[i][j].type==TYPE_HERBE)
                {
                    image_draw( e.imgHerbe, caseVersEcran(e,i) + 5, caseVersEcran(e,j) + 5, DIMW/e.dx - 10, DIMW/e.dy -10);              //si herbe alors image
                }
                else if(e.grille[i][j].type==TYPE_PROIE)
                {
                    image_draw( e.imgProie, caseVersEcran(e,i) + 5, caseVersEcran(e,j) + 5, DIMW/e.dx - 10, DIMW/e.dy -10);              //si mouton alors image
                }
                else if(e.grille[i][j].type==TYPE_PREDATEUR)
                {
                    image_draw( e.imgPredateur, caseVersEcran(e,i) + 5, caseVersEcran(e,j) + 5, DIMW/e.dx - 10, DIMW/e.dy -10);              //si loup alors image
                }
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////MAIN/////////////////////////////////////////////////////////////////

int main(int argc, char**argv)
{
    bool stop=false;
    winInit("LOUP MOUTON",DIMW,DIMW);

    Menu men;
    menu_add(men,"GRAPH");
    menu_add(men,"JEU");


    int i=0;                //le temps
    Ecosysteme eco;
    initEco(eco);
    Plot plot;
    plot_setSize(plot, 1000);

    Ecosysteme2 eco2;
    initEco2(eco2);
    while(!stop)
    {
        winClear();
        menu_draw(men,5,10,100,100);
        switch(menu_select(men))
        {
            case 0 : i++; evolution_pop(eco); drawGraph(eco,plot,i); break;
            case 1 : i++; evolution(eco2); drawEco(eco2); break;
            default: i++; evolution_pop(eco); drawGraph(eco,plot,i); break;
        }
        switch(menu_select(men))
        {
            case 0 : backgroundColor(150,150,150); break;
            case 1 : backgroundColor(220,220,220); break;
            default: backgroundColor(150,150,150); break;
        }
        stop=winDisplay();
    }
    winQuit();
    return 0;
}



