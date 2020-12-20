//ROLL NO 20PT14
//HANGMAN

//unknown is the string that the player has to fill up.
//wordFind is the string that is produced by computer to be found by player.
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>
#define lives 5
int Fill(char guess,char word[],char wordFind[])//function to fill unknown  with letter which was found right. 
{
    int i,matches=0;
    for(i=0;word[i]!='\0';i++)
    if(guess==word[i])//if letter guessed is a part of wordFind
    {
        wordFind[i]=guess;//the letter is filled in unknown( unknown and wordFind of same length)
        matches++;
    }
return matches;//if 0 one life is lost, if non-zero the string is displayed, no change in life
}

int check(char word[],char guessWord[])//to check if the word is found yet.
{
    if(strcmp(word,guessWord)==0)
    {
        printf("\033[0;32m""\n%s\nWORD FOUND!\n""\033[0m",guessWord);
        return 0;//returns 0 if found (for condition checking in main() )
    }
}

void Assign(char wordFind[],int *n)
{srand(time(NULL));
 *n=rand()%31;
 
char words[][80]={"INDIA\0","PAKISTAN\0","CHINA\0","AMERICA\0","AFRICA\0","BHUTAN\0","DUBAI\0","MEXICO\0","AUSTRALIA\0",\
"BULGARIA\0","COMBODIA\0","CANADA\0","CUBA\0","KOREA\0","DENMARK\0","EGYPY\0","FRANCE\0","GERMANY\0","GEORGIA\0","HUNGARY\0",\
"IRAQ\0","JAMAICA\0","IRELAND\0","KENYA\0","LUXEMBOURG\0","MYANMAR\0","NEPAL\0","SINGAPORE\0","TAJIKISTAN\0","UAE\0","ZIMBABWE\0"};
 strcpy(wordFind,words[*n]);
}


int game()
{int ifWin=0;
 char unknown[80];
 int WrongGuesses=0;
 char wordFind[80];
 int n;
 Assign(wordFind,&n); 
 
 for(int i=0;wordFind[i]!='\0';i++)
 unknown[i]='*';//assigning '*' for unknown letters that has to guessed by player.
 
 printf("\033[0;33m""\nWelecome to hangman!\n""\033[0;34m""Guess a country name %s\n""\033[0;36m""You have 5 maximum tries\n\n" "\033[0m",unknown);

 while(WrongGuesses<lives && check(wordFind,unknown)!=0)//game terminates if wrong guesses made is >5 or when player wins.
 {  char letter;
     printf( "%s""\033[0;35m""\nGuess a letter""\033[0m",unknown);
     again:
     scanf("%c",&letter);
     if(isalpha(letter)==0)
     goto again;//to avoid input errors.
     letter=toupper(letter);
     if(Fill(letter,wordFind,unknown)==0)//if letter guessed was not right
     { 
         printf("\033[0;31m" "\nOops!! Letter not found" "\033[0m");
         WrongGuesses++;//one life lost;
     }
     else
     printf("\033[0;32m""\nyou found a letter\n""\033[0m");
     printf("\033[0;36m""\nYou have %d number of guesses left\n" "\033[0m",5-WrongGuesses);
     if(WrongGuesses==lives)
     {
       printf("\033[0;31m" "\nyou lose!! Better luck next time!\n" "\033[0m");
       printf("The word is:\n%s\n",wordFind);
       ifWin=1;//flag variable passed to main()
     }
 }
return ifWin;//returns 0 if won,returns 1 if lost
}

void main()
{
int c,score=0;
char ch,name[100];
printf("Player name:");
scanf("%s",name);
do
{
c=game();

if(c==0)
score++;

printf("\ndo you want to play another game?\n");
lb:
scanf("%c",&ch);
if(ch==' '||ch=='\n')
goto lb;
}while(ch=='y'||ch=='Y');

FILE *fp;
fp=fopen("ScoreBoard.txt","a");
fprintf(fp,"%s\t\t%d\n",name,score);
fclose(fp);

printf("\n\t\t LEADERBOARD\n\t\t ***********\nPlayer name\tgames won\n");

char readc;
fp=fopen("ScoreBoard.txt","r");
while(!feof(fp))
{readc=getc(fp);
printf("%c",readc);
}
fclose(fp);
}

