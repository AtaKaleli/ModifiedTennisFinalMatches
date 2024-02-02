#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void menu();
void MatchResult(int[4],int[4]);
void TheVictor(int[4],int[4]);
int randomNumberGenerator();



int main(){

srand(time(NULL));
int Spain[4]={0,0,0,0},Russia[4]={0,0,0,0};
/*
Array elements are as follows:
1)Number of match victory
2)Number of set victory
3)Number of set victory for the best
player of the team
4)The best player
By default, I set these values to zero
*/



int op;
menu();
scanf("%d",&op);

while(op!=1 && op!=2){
    fflush(stdin);
    printf("Please enter option either 1 or 2!\n");
    printf("Option: ");
    scanf("%d",&op);
}

if(op==1){
    MatchResult(Russia,Spain);
}
else{
    printf("Quit!\n");
}







return 0;
}

void menu(){
    printf("Tennis Final Matches Simulator\n\n");
    printf("1. Press 1 to start the simulation\n");
    printf("2. Press 2 to quit\n");
    printf("Option: ");
}

int randomNumberGenerator(){
    return rand()%4;
}

void MatchResult(int Spain[4],int Russia[4]){

int i,j;
int spainMatchScores[4][4],russianMatchScores[4][4];
printf("\nSimulation starts..\n\n");

for(i=0;i<4;i++){
    for(j=1;j<=4;j++){
        printf("Match %d\n",i*4+j);
        printf("-----------------------------\n");
        printf("Player %d (Spain) Vs. Player %d (Russia)\n",i+1,j);
        spainMatchScores[i][j-1]=randomNumberGenerator();
        russianMatchScores[i][j-1]=randomNumberGenerator();
        int validMatch=0;//valid match == 1 if possible result occured.

        while(!validMatch){
            if((russianMatchScores[i][j-1]==3 || spainMatchScores[i][j-1]==3) && (spainMatchScores[i][j-1]!=russianMatchScores[i][j-1]))
                validMatch=1;
            else{
                spainMatchScores[i][j-1]=randomNumberGenerator();
                russianMatchScores[i][j-1]=randomNumberGenerator();
            }
        }
        printf("Result: Spain %d - %d Russia\n\n\n",spainMatchScores[i][j-1],russianMatchScores[i][j-1]);
    }
}

int spainTotalMatchWin[4]={0,0,0,0},russiaTotalMatchWin[4]={0,0,0,0};//these arrays hold the number of match wins for each player
int spainTotalSetWin[4]={0,0,0,0},russiaTotalSetWin[4]={0,0,0,0};//these arrays hold the number of set wins for each player

for(i=0;i<4;i++){
    for(j=0;j<4;j++){
        if(spainMatchScores[i][j]==3){
           spainTotalMatchWin[i]++;
       }
        if(russianMatchScores[i][j]==3){
           russiaTotalMatchWin[i]++;
       }
    }
}

for(i=0;i<4;i++){
    for(j=0;j<4;j++){
        spainTotalSetWin[i]+=spainMatchScores[i][j];
        russiaTotalSetWin[i]+=russianMatchScores[j][i];
    }
}

int spainBestPlayerSet=0,russiaBestPlayerSet=0;//these are the #of sets won by players

//now I have the best sets for both countries.
for(i=0;i<4;i++){//if two players have same #of sets won, I chose the smaller id player
    if(spainBestPlayerSet<spainTotalSetWin[i]){
        spainBestPlayerSet=spainTotalSetWin[i];
    }
}

for(i=0;i<4;i++){
    if(russiaBestPlayerSet<russiaTotalSetWin[i]){
        russiaBestPlayerSet=russiaTotalSetWin[i];
    }
}

//now I will find the indexes of best players using the bestSet variable

int spainBestindex;
int russiaBestindex;

for(i=0;i<4;i++){
    if(spainBestPlayerSet==spainTotalSetWin[i]){
        spainBestindex=i;
    }
}


for(i=0;i<4;i++){
    Spain[0]+=spainTotalMatchWin[i];
    Spain[1]+=spainTotalSetWin[i];
}

Spain[2]=spainBestPlayerSet;
Spain[3]=spainBestindex+1;




for(i=0;i<4;i++){
    if(russiaBestPlayerSet==russiaTotalSetWin[i]){
        russiaBestindex=i;
    }
}


for(i=0;i<4;i++){
    Russia[0]+=russiaTotalMatchWin[i];
    Russia[1]+=russiaTotalSetWin[i];
}

Russia[2]=russiaBestPlayerSet;
Russia[3]=russiaBestindex+1;

TheVictor(Spain,Russia);





}

void TheVictor(int Spain[4],int Russia[4]){

printf("\n\n\nTable of Statistics\n");
printf("--------------------------------------\n");

printf("Spain\n");
printf("Number of match victory: %d\n",Spain[0]);
printf("Number of set victory: %d\n",Spain[1]);
printf("Number of set victory of the best player: %d\n",Spain[2]);
printf("Best Player: %d\n\n\n",Spain[3]);

printf("Russia\n");
printf("Number of match victory: %d\n",Russia[0]);
printf("Number of set victory: %d\n",Russia[1]);
printf("Number of set victory of the best player: %d\n",Russia[2]);
printf("Best Player: %d\n\n\n\n",Russia[3]);


int spainWin=0,russiaWin=0;

while(spainWin!=1 || russiaWin!=1){

    printf("Announcing the champion:\n");
    printf("--------------------------------------\n");
    printf("Number of match victory: Spain %d vs %d Russia\n",Spain[0],Russia[0]);
    if(Spain[0]>Russia[0]){
        spainWin=1;
        break;
    }
    else if(Spain[0]<Russia[0]){
        russiaWin=1;
        break;
    }
    else{
        printf("Draw! We should compare the set victory of each team:\n");
        printf("Number of set victory: Spain %d vs %d Russia\n",Spain[1],Russia[1]);
        if(Spain[1]>Russia[1]){
            spainWin=1;
            break;
        }
        else if(Spain[1]<Russia[1]){
            russiaWin=1;
            break;
        }
        else{
            printf("Draw! We should compare the set victory of the best players of each team:\n");
            printf("Number of set victory of the best players : Spain %d vs %d Russia\n",Spain[2],Russia[2]);
            if(Spain[2]>Russia[2]){
                spainWin=1;
                break;
            }
            else if(Spain[2]<Russia[2]){
                russiaWin=1;
                break;
            }
            else{
                printf("Draw! Final match between the best players of each team should decide the best team:\n");
                int spainTieBreakScore=randomNumberGenerator();
                int russiaTieBreakScore=randomNumberGenerator();
                int validMatch=0;//valid match == 1 if possible result occured.

                while(!validMatch){
                    if((spainTieBreakScore==3 || russiaTieBreakScore==3) && (spainTieBreakScore!=russiaTieBreakScore))
                        validMatch=1;
                    else{
                        spainTieBreakScore=randomNumberGenerator();
                        russiaTieBreakScore=randomNumberGenerator();
                    }
                }
                printf("Player %d of Spain  %d  vs  %d  Player %d of Russia \n",Spain[3],spainTieBreakScore,russiaTieBreakScore,Russia[3]);
                if(spainTieBreakScore>russiaTieBreakScore){
                    spainWin=1;
                    break;
                }
                else{
                    russiaWin=1;
                    break;
                }

            }
        }
    }

}

printf("The champion of 2047 tennis champion league is: \n");

if(spainWin)
    printf("Spain\n\n");
else
    printf("Russia\n\n");

printf("We wish all the players the best for the next tennis champion league.\n");
printf("See you in 2048.");


}












