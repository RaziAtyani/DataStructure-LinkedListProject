#include <stdio.h>
#include <string.h>
#include <malloc.h>
typedef  struct node{// define the linked list struct and what it contains
    char TeamName[10];// the team name
    char code[5];// the team code
    int numberOfWins;// the wins of the that team
    int numberOfDraws;// the draws of that team
    int numberOfLoses;//the loses of that team
    int GoalDiff;// the goal difference
    int points ;// the points
    struct node* Next;// pointer to the next node on the linked list
} Teams ;// type definition of that struct
typedef struct node1{// define the linked list of the first 11 player of team
    char nameOfPlayer[15];// the name of the player
    struct node1* next;// the pointer to the next player of that team
} Player;//type definition of the struct
struct Q{//define the first queue players struct
    char SparePlayers [20];//the name of each them
    struct Q* next;//pointer to the next player
};
struct Q2{// define the second queue players
    char SparePlayers2 [20];//the name of the players
    struct Q2* next;//pointer to the next player
};
typedef struct Q *spareQueue1;//type definition of the struct queue1
typedef struct Q2 *spareQueue2;//type definition of the struct queue2
spareQueue1 first, last;// define two global pointers for the first queue
spareQueue2 first2, last2;// define two global pointers for the second  queue
int clubs =4;//number of teams in the file
Teams* insertTeams(char teamName [], char Code [], int wins, int Draws, int Loses, int GoalDifference, Teams * L, Teams *P)
{//insert function the team linked list
    Teams *temp;// pointer on the linked list
    temp = (Teams*)malloc(sizeof(Teams));//memory allocate for add on the linked list
    strcpy(temp->TeamName, teamName);// the name
    strcpy(temp->code, Code);// the code
    temp->numberOfWins = wins;// the wins
    temp->numberOfLoses = Loses;// the loses
    temp->numberOfDraws = Draws;//the draws
    temp->GoalDiff = GoalDifference;// the goal difference
    temp->points = 3 * wins + 1 * Draws;// adding the points and calculating it
    temp->Next = P->Next;//pointer to null
    P->Next = temp;//pointer the new node
    return temp;// return it for insert at last
}
int isLastTeam(Teams * s)
{// method at last
    return s->Next == NULL;// for knowing if it is at last or not
}
int isLastPlayer(Player * d)
{// method at last
    return d->next == NULL;// for knowing if it is at last or not
}
int isEmptyTeam(Teams *b)
{//method to know if it is empty or not
    return b->Next==NULL;
}
spareQueue1 createFirstQueue(spareQueue1 q)
{// for creating the queue for the spare players
    q = (spareQueue1)malloc(sizeof(struct Q));// allocate memory for it
    first = last = NULL;// front and rear
    return q;// return a pointer
}
void enQueueSpare(spareQueue1 temp, char NamesPlayers[])
{//to insert new player in the first queue
    spareQueue1 t;// define pointer
    t = (spareQueue1) malloc(sizeof(struct Q));// allocate memory for the node
    strcpy(t->SparePlayers, NamesPlayers);// the contents
    t->next = NULL;//insert  at last
    temp = t;// equal to the allocate pointer
    if (last == NULL)//reach at last pointer
    {
        first = last = temp;//insertion at last
        return;
    }
    last->next = temp;//pointer to temp
    last = temp;// at last
}
void DisplayQueue1(spareQueue1 m)
{// to print the queue elements

    m = first;//pointer to first element
    if ((first == NULL) && (last == NULL))// if it is Empty the queue
    {
        printf(" The Queue for the first team is Empty \n");
        return;
    }
    printf("The Queue Elements  for the First Team are : \n");
    while (m != NULL)// if it is not Null
    {
        printf("%s ", m->SparePlayers);// the Players Name
        m = m->next;// next player
    }
    printf("\n");
}
spareQueue2 createQueue2(spareQueue2 q)
{
    q = (spareQueue2)malloc(sizeof(struct Q2));
    first2 = last2 = NULL;
    return q;
}
void EnQueueSpare2(spareQueue2 temp, char NamePlayers2[])
{//to insert new player in the Second queue
    spareQueue2 e = (spareQueue2)malloc(sizeof(struct Q2));// allocate memory for the node
    strcpy(e->SparePlayers2, NamePlayers2);// the contents
    e->next = NULL;//insert  at last
    temp=e;// define pointer
    if (last2 == NULL)//reach at last pointer
    {
        first2 = last2 = temp;//insertion at last
        return;
    }
    last2->next = temp;//pointer to temp
    last2 = temp;// at last
}
void DisplayQueue2(spareQueue2 m)
{// to print the queue elements
    m = first2;//pointer to first element
    if ((first2 == NULL) && (last2 == NULL))// if it is Empty the queue
    {
        printf("The Queue for the Second team is Empty\n");
        return;
    }
    printf("The Queue Elements  for the Second Team are :\n");
    while (m != NULL)// if it is not Null
    {
        printf("%s ", m->SparePlayers2);// the Players Name
        m = m->next;// next player
    }
    printf("\n");
}
void PrintListTeams(Teams * L)
{// for printing the linked list
    Teams *P = L;// define pointer
    if(isEmptyTeam(L))// to know if it is Empty or not
        printf(" Empty List\n ");
    else// the second case
    {
        while(!isLastTeam(P)){//the last or not
            P=P->Next;// next POINTER
            // printing the elements
            printf("%s %s %d %d %d %d %d \n", P->TeamName, P->code, P->numberOfWins, P->numberOfDraws, P->numberOfLoses, P->GoalDiff,P->points);
        }

    }
}
void ReadFileOfTeams(Teams *L)
{// for reading the file of teams
    Teams *p;//pointer on the linked list of teams
    p=L;// at first
    FILE*Teams=fopen("teams.txt","r");//open file
    if (!Teams )// if it is not Exist
    {
        printf("File does not Exist \n");
    }
    // defining the contents
    char TeamData[30];
    char code[30];
    int numberOfWins;
    int NumberOfDraws;
    int numberOfLoses;
    int GoalDiff;
    // while for reaching the End of File
    while(!feof(Teams))
    {
        // scan the data
        fscanf(Teams, "\n%[^,],%[^,],%d,%d,%d,%d", TeamData, code, &numberOfWins, &NumberOfDraws,&numberOfLoses,&GoalDiff);
        //inserting it
        p= insertTeams(TeamData, code, numberOfWins, NumberOfDraws, numberOfLoses, GoalDiff, p, p);

    }
    // close the file
    fclose(Teams);
}
Teams * MakeEmptyForTheTeams(Teams* L)
{ // for making the head
    L = (Teams *)malloc(sizeof(Teams));// allocating memory node
    if(L == NULL)//if it  is pointer to Null
        printf("not in memory\n");
    L->Next = NULL;// else
    return L;
}
Player * MakeEmptyForThePlayers(Player * a)
{ //for making the head
    a = (Player *)malloc(sizeof(Player));// allocating memory node
    if(a == NULL)//if it is  pointer to Null
        printf("out of memory\n");
    a->next = NULL;// else
    return a;
}
Player* Insert11Players(char Players[], Player*P)
{// for adding the players
    Player* e;// pointer
    e = (Player*)malloc(sizeof(Player));//allocating memory
    strcpy(e->nameOfPlayer, Players);// the contents
    e->next = P->next;// to null
    P->next = e;// to e
    return e;// return it
}
void ReadFileOfPlayers(Player*  Players[])
{// making array of linked list for reading the players
    for(int j=0; j < clubs; j++)
    {// making the head on every linked list
        Players[j]= MakeEmptyForThePlayers(Players[j]);
    }// reading  the file
    FILE* fplayers = fopen("players.txt", "r");
    char players[20];
    // file is Exist or not
    if (!fplayers)
    {
        printf("File not Exist\n");
    }
    int i=0;
    // untill the end of file
    while (!feof(fplayers))
    {   // scan the file
        int counter =0;
        fscanf(fplayers, "%s", players);
        // if new team inserted
        if(strstr(players, "*"))
        {
            // removing the * by the method memmove
            memmove(players, players + 1, strlen(players));
            //reading the 11 players
            while(i < clubs)
            {     // insert in the linked list
                Insert11Players(players, Players[i]);
                // scan
                fscanf(fplayers, "%s", players);
                counter++;
                // after 11
                if(counter == 12)
                {
                    i++;
                    break;
                }
            }
        }
    }
    // close the file
    fclose(fplayers);
}
void PrintListPlayers(Player * L)
{// for printing the linked list
    Player *P = L;// define pointer
    printf("The First 11 players :\n");
    while (!isLastPlayer(P)){//the last or not
        P=P->next;// next POINTER
        // printing the elements
        printf("%s ", P->nameOfPlayer);
    }
    printf("\n");
}
Teams* FindPreviousTeams(char Code[], Teams* L)
{// function to find previous
    Teams * P;//pointer
    P = L;// at head
    while(P->Next != NULL && strcmp(P->Next->code, Code) != 0)// while not found
    {
        P= P->Next;
    }
    return P;//return it
}
Player * FindPreviousPlayers(char Code[], Player * L)
{// function to find previous
    Player * i;//pointer
    i = L;// at head
    while(i->next != NULL && strcmp(i->next->nameOfPlayer, Code) != 0)// while not found
    {
        i= i->next;
    }

    return i;//return it
}
void DeleteTeams(char code [], Teams * L)
{// for deleting  teams
    Teams * P, *temp;// pointers
    P = FindPreviousTeams(code, L);// previous node
    if( !isLastTeam(P) )// last or not
    {
        temp = P->Next;// determine previous
        P->Next = temp->Next; //bypass delete cell
        free(temp);// free it
    }
}
void DeletePlayers(char Code [], Player * L)
{// for deleting  players
    Player *P, *temp;// pointers
    P = FindPreviousPlayers(Code, L);// previous node
    if (!isLastPlayer(P))// last or not
    {
        temp = P->next;// determine previous
        P->next = temp->next;//bypass delete cell
        free(temp);// free it

    }
}
spareQueue1 SpareTeam(spareQueue1 SubFirstTeam, char FirstTeam[])
{ // to read from file the spare Players
    char SpareNames[20];// to scan
    FILE*file = fopen("players.txt", "r");
    if (!file)//file not found
    {
        printf("File not Exist\n");
    }
    while(!feof(file))//found untill end of file
    {
        int counter =0;//counter
        fscanf(file, "%s", SpareNames);//scan
        memmove(SpareNames, SpareNames + 1, strlen(SpareNames));
        if(strcmp(SpareNames, FirstTeam) == 0)// if found the team
        {
            while (!feof(file))// read to finish it
            {
                fscanf(file, "%s", SpareNames);
                if(strstr(SpareNames, "*"))//un till the second team
                {
                    break;
                }
                counter++;
                if (counter >= 12)
                {
                    enQueueSpare(SubFirstTeam, SpareNames);// insert in queue
                }
            }
        }
        if(counter > 12)
        {
            break;
        }
    }
    return SubFirstTeam;
}
spareQueue2 SpareTeam2(spareQueue2 SubSecondTeam, char SecondTeam[])
{// to read from file the spare Players
    char SpareNames[20];// to scan
    FILE*file = fopen("players.txt", "r");
    if (!file)//file not found
    {
        printf("File not Found\n");
    }
    while(!feof(file))//found untill end of file
    {
        int counter =0; //counter

        fscanf(file, "%s", SpareNames);//scan
        memmove(SpareNames, SpareNames + 1, strlen(SpareNames));
        if(strcmp(SpareNames, SecondTeam) == 0)// if found the team
        {
            while (!feof(file))// read to finish it
            {
                fscanf(file, "%s", SpareNames);
                if(strstr(SpareNames, "*"))//un till the second team
                {
                    break;
                }
                counter++;
                if (counter >= 12)// insert in queue
                {
                    EnQueueSpare2(SubSecondTeam, SpareNames);
                }
            }
        }
        if(counter > 12)
        {
            break;
        }
    }
    return SubSecondTeam;
}
void addingTeam(Teams * Group)
{// for inserting a new team as the user want
    char name[20];//team name
    char code [4];// team code
    int w, d, l, goalDifference;// info
    printf("\n Enter the team name and all the information like code, w, d, l and Goal Difference\n");
    scanf("%s %s %d %d %d %d", name, code, &w, &d, &l, &goalDifference);//scan
    insertTeams(name, code, w, d, l, goalDifference, Group, Group);//inserting
}
Teams *PrintOnTheFile(Teams *r, FILE *teamsSorted)
{//printing teams
    while (!isLastTeam(r)) {//the end of the linked list

        r = r->Next;//pointer
// info printing
        fprintf(teamsSorted, "%s %s %d %d %d %d %d\n", r->TeamName, r->code, r->numberOfWins, r->numberOfDraws,
                r->numberOfLoses, r->GoalDiff, r->points);
    }


    return r;
}
Player * Lineups(Player * Players[], char Team[])
{ // this to find where the team in the array of linked list
    int l;//lopp to find the team
    for (l = 0; l < clubs; l++)
    {
        Player * team = Players[l];
        while (!isLastPlayer(team)){//to compare with the first element
            team = team->next;
            if (strcmp(team->nameOfPlayer, Team) == 0)//to leave the first loop
            {
                break;
            }
        }
        if (strcmp(team->nameOfPlayer, Team) == 0)// to leave the second loop
        {
            break;
        }
    }
    Player * P = Players[l];//the players array
    DeletePlayers(Team, P);//this is for deleting the code
    return P;
}
void modify(Teams * Group)
{// modify team
    char Code[5];//the code
    int number, w, l, d, gd;// the info
    Teams *P ;//pointer
    while(P->Next == NULL){//to find the same code
        printf("Enter the team code\n");
        scanf("%s", Code);
        P = FindPreviousTeams(Code, Group);
        if(P->Next==NULL)// not found
        {
            printf("The team you chose does not in the linked list ,try again\n");
        }
    }
    P=P->Next;//the same team
    printf("choose the info you want to modify\n1-GD 2-Loses 3-Draws 4-Wins");//what to modify
    scanf("%d",&number);
    switch (number)
    {
        case 1://gd
            printf("Enter the new GoalDifference number\n");
            scanf("%d", &gd);
            P->GoalDiff = gd;
            break;
        case 2:// l
            printf("Enter the new Loses for this team\n");
            scanf("%d", &l);
            P->numberOfLoses = l;
            P->points=(P->numberOfWins *3)+ (P->numberOfDraws);
            break;
        case 3://d
            printf("Enter the new Draws for this team\n");
            scanf("%d", &d);
            P->numberOfDraws = d;
            P->points=(P->numberOfWins *3)+ (P->numberOfDraws);
            break;
        case 4:// w
            printf("Enter the new Wins for this team\n");
            scanf("%d", &w);
            P->numberOfWins = w;
            P->points=(P->numberOfWins *3)+ (P->numberOfDraws);
            break;
//and again to calculate the points
    }
}
void DeleteFromList(Teams* L)
{// for delete elements from the linked list
    Teams *P, *temp;// pointer
    P = L->Next;
    L->Next = NULL;
    while(P != NULL)// finding the element
    {
        temp = P->Next;
        free(P);// free it
        P=temp;
    }
}
void swappingNodes(Teams *P, Teams *P2)
{// to swap nodes by goal difference
    // goalDifference
    int temp =P->GoalDiff;
    P->GoalDiff=P2->GoalDiff;
    P2->GoalDiff=temp;
    // numberOfWins
    int temp2 =P->numberOfWins;
    P->numberOfWins=P2->numberOfWins;
    P2->numberOfWins=temp2;
    // numberOfDraws
    int temp3 =P->numberOfDraws;
    P->numberOfDraws=P2->numberOfDraws;
    P2->numberOfDraws =temp3;
    // numberOfLoses
    int temp4 =P->numberOfLoses;
    P->numberOfLoses=P2->numberOfLoses;
    P2->numberOfLoses=temp4;
    // code
    char array[3];
    strcpy(array,P->code);
    strcpy(P->code,P2->code);
    strcpy(P2->code,array);
    // teamName
    char array2[10];
    strcpy(array2,P->TeamName);
    strcpy(P->TeamName,P2->TeamName);
    strcpy(P2->TeamName,array2);
}
Teams * RadixSort(Teams *Group)
{// sorting by using the Radixsort
    Teams *p = Group;//pointer
    int maxPoints;// max point
    int counterPoints = 0;// numberOf points
    do // to calculate number of points
    {
        p = p->Next;
        counterPoints++;
    }
    while (!isLastTeam(p));
    // to calculate max point
    Teams *l = Group;
    maxPoints = 0;
    int counter = counterPoints;
    do
    {
        l = l->Next;
        if (l->points > maxPoints)
        {
            maxPoints = l->points;
        }
    }
    while (!isLastTeam(l));
    // max digit of the max point
    int maxDigit = 0;
    while (maxPoints > 0)
    {
        maxDigit++;
        maxPoints = maxPoints / 10;
    }
    // array of linked list
    Teams *link[10];
    for (int q = 0; q <= 9; q++)
    {// making head
        link[q] = MakeEmptyForTheTeams(link[q]);
    }
    int c = 10;
    int N = 1;
    int s=0;
    Teams *P = NULL;
    P = MakeEmptyForTheTeams(P);
    counter = counterPoints;
    // sorting on the big digit
    while(maxDigit >0)
    { // first we take from the original linked list
        if (N == 1)
        {
            p = Group->Next;
        }
        //now from the new linked list
        else
        {
            p = P->Next;
        }
        for (int j = 0; j < counter; j++)
        {   // the equation and inserting in array of linked list
            int ListNumber = (p->points % c) / N;
            insertTeams(p->TeamName, p->code, p->numberOfWins, p->numberOfDraws, p->numberOfLoses, p->GoalDiff,
                        link[ListNumber], link[ListNumber]);
            p = p->Next;
            // the new linked list
            if (j == counter - 1)
            {// to delete th elements on the linked list
                if (s>=1)
                {
                    DeleteFromList(P);
                }
                // inserting into the linked list
                for (int i = 0; i <= 9; i++)
                {
                    if (link[i]->Next == NULL)
                    {
                        continue;
                    }
                    do
                    {
                        // insert it
                        link[i] = link[i]->Next;
                        insertTeams(link[i]->TeamName, link[i]->code, link[i]->numberOfWins, link[i]->numberOfDraws,
                                    link[i]->numberOfLoses, link[i]->GoalDiff,
                                    P, P);
                    }
                    while (!isLastTeam(link[i]));
                }
                s++;
            }
        }
        // the second Digit
        maxDigit = maxDigit - 1;
        c = c * 10;
        N = N * 10;
    } // free the linked list
    for(int q = 0; q <= 9; q++)
    {
        free(link[q]);
    }
    // now the swap by Goal Difference
    Teams *temp1, *temp2;
    temp1 =P->Next;
    temp2 =P->Next->Next;
    do
    {
        if(temp1->points == temp2->points)
        {// in case the first smaller than second
            if(temp1->GoalDiff<temp2->GoalDiff)
            {
                swappingNodes(temp1,temp2);
            }
        } // we make the first pointer as a point to refernce it
        temp2 = temp2->Next;
        if(temp2->Next == NULL)
        {
            temp2 =temp1->Next->Next;
            temp1 = temp1->Next;
        }
    }
    while(!isLastTeam(temp1->Next));
    PrintListTeams(P);// the new sorted linked list
    return P;
}
void sub(Player * FirstTeamLineUp, Player *SecondTeamLineUp, spareQueue1 subTeamOne, spareQueue2 subTeamTwo, char Players[])
{// sub player
    // define two pointers
    Player *P1 = FirstTeamLineUp;
    Player *P2 = SecondTeamLineUp;
    char t [20];//name
    do
    {
        // find name
        P1 = P1->next;
        if (strcmp(P1->nameOfPlayer, Players) == 0)
        {
            // find the team and the subbed
            strcpy(t, Players);
            strcpy(P1->nameOfPlayer,first->SparePlayers);
            enQueueSpare(subTeamOne, t);
            //print that subbed
            printf("%s subbed\n",Players);
            free(first);
            first = first->next;
            // print it
            PrintListPlayers(FirstTeamLineUp);
            DisplayQueue1(subTeamOne);
            break;
        }
    }
    while (!isLastPlayer(P1));
    // subbed for the second team
    if (strcmp(t, Players) != 0)
    {
        do
        {
            // find name
            P2 = P2->next;
            if (strcmp(P2->nameOfPlayer, Players) == 0)
            {
                // find the team and the subbed
                strcpy(t, Players);
                strcpy(P2->nameOfPlayer, first2->SparePlayers2);
                EnQueueSpare2(subTeamTwo, t);
                //print that subbed
                printf("%s has been subbed\n", Players);
                free(first2);
                first2=first2->next;
                //print it
                PrintListPlayers(SecondTeamLineUp);
                DisplayQueue2(subTeamTwo);
                break;
            }
        }
        while (!isLastPlayer(P2));
    }
    //if neither there
    if(strcmp(P1->nameOfPlayer, Players ) != 0 && strcmp(t, Players) != 0)
    {
        printf("%s does not play for these teams\n", Players);
    }
}
void playersFile(Player * FirstTeamLineUp, Player *SecondTeamLineUp)
{ //players info file
    FILE *InfoPlayer = fopen("playersInfo.txt", "w");// open file
    Player *u = FirstTeamLineUp;
    Player *u2 = SecondTeamLineUp;
    spareQueue1 temp = first;
    spareQueue2 temp2 = first2;
    // print
    do{
        u = u->next;
        fprintf(InfoPlayer, "%s\n", u->nameOfPlayer);
    }
    while (!isLastPlayer(u));
    fprintf(InfoPlayer, "spareQueue1 elements are: \n");
    // print
    while (temp != NULL)
    {
        fprintf(InfoPlayer, "%s  ", temp->SparePlayers);
        temp = temp->next;
    }
    fprintf(InfoPlayer, "\n");
    // print
    do
    {
        u2 = u2->next;
        fprintf(InfoPlayer, "%s\n", u2->nameOfPlayer);
    }
    while (!isLastPlayer(u2));
    // print
    fprintf(InfoPlayer, "spareQueue1 elements are: \n");
    while (temp2 != NULL)
    {
        fprintf(InfoPlayer, "%s  ", temp2->SparePlayers2);
        temp2 = temp2->next;
    }
    fprintf(InfoPlayer, "\n");

}
void DeletePlayer(char Names [], Player * FirstTeamLineUp, Player * SecondTeamLineUp)
{// delete player
    Player *P1 = FirstTeamLineUp;
    Player *P2 = SecondTeamLineUp;
    while (!isLastPlayer(P1)){
        P1 = P1->next;
        if (strcmp(P1->nameOfPlayer, Names) == 0)
        {
            // to give a red card
            DeletePlayers(Names, FirstTeamLineUp);
            printf("%s has been given a red card!\n", Names);
            PrintListPlayers(FirstTeamLineUp);
            break;
        }
    }
    //if from the second team
    if (strcmp(P1->nameOfPlayer, Names) != 0)
    {
        while (!isLastPlayer(P2)){
            P2 = P2->next;
            if (strcmp(P2->nameOfPlayer, Names) == 0)
            {
                DeletePlayers(Names, SecondTeamLineUp);
                printf("%s has been given a red card!\n", Names);
                PrintListPlayers(SecondTeamLineUp);
                break;
            }
        }
    }
    //if neither
    if(strcmp(P1->nameOfPlayer, Names) != 0 && strcmp(P2->nameOfPlayer, Names) != 0)
    {
        printf("%s does not play for either teams\n", Names);
    }
}
void Menu2(Player * FirstLineUp, Player *SecondLineUp, spareQueue1 subTeamOne, spareQueue2 subTeamTwo)
{ // menue 2
    int op;
    char Deleted[20], Subbed[20];

    while(1)
    { // switch cases
        printf("Welcome!\n1- lineups 2-red card to a player 3-Sub a player 4-End");
        scanf("%d",&op);
        switch (op)
        {
            default:
                printf("please try again");
                continue;
            case 1:
                PrintListPlayers(FirstLineUp);
                DisplayQueue1(subTeamOne);
                PrintListPlayers(SecondLineUp);
                DisplayQueue2(subTeamTwo);
                continue;
            case 2:
                printf("Please enter player \n");
                scanf("%s", Deleted);
                DeletePlayer(Deleted, FirstLineUp, SecondLineUp);
                continue;
            case 3:
                printf("Enter the player \n");
                scanf("%s", Subbed);
                sub(FirstLineUp, SecondLineUp, subTeamOne, subTeamTwo, Subbed);
                continue;
            case 4:
                playersFile(FirstLineUp, SecondLineUp);
                break;
        }
        break;
    }
}
void Menu1 (Teams *Group, spareQueue1 subOne, spareQueue2 subTwo, Teams *P1, Teams  *P2 , Player *Players[])
{ //menu1
    int op;
    printf("\nWelcome\n\n1-add team \n2-modify a team \n3-delete a team "
           "\n4-Print the list \n5-Click to save the teams info (you can find it in a file named teamsInfo.txt)\n6-Create a match\n7-Exit\n");
    scanf("%d",&op);
    // switch cases
    switch(op)
    {
        case 1:
            addingTeam(Group);
            clubs++;
            RadixSort(Group);
            Menu1(Group, subOne, subTwo, P1, P2, Players);
            break;
        case 2:
            modify(Group);
            RadixSort(Group);
            Menu1(Group, subOne, subTwo, P1, P2, Players);
            break;
        case 3:
            printf("\nPlease enter the team code to delete the said team\n");
            char code[20];
            scanf("%s", code);
            DeleteTeams(code, Group);
            RadixSort(Group);
            Menu1(Group, subOne, subTwo, P1, P2, Players);
            break;
        case 4:
            RadixSort(Group);
            Menu1(Group, subOne, subTwo, P1, P2, Players);
            break;
        case 5:
            printf(" this is what you will find in the file\n ");
            Teams *f =NULL;
            f = RadixSort(Group);
            FILE  *out;
            out=fopen("teamsInfo.txt","w");
            PrintOnTheFile(f, out);
            printf("the teams info are there ");
            Menu1(Group, subOne, subTwo, P1, P2, Players);
            break;
        case 6:
            printf ("Welcome to the match\n");
            char TeamOne[10], TeamTwo[10];
            do
            {
                printf("enter the first team\n");
                scanf("%s", TeamOne);
                P1 = FindPreviousTeams(TeamOne, Group);
                printf("enter the second team\n");
                scanf("%s", TeamTwo);
                P2 = FindPreviousTeams(TeamTwo, Group);
                if(P1->Next==NULL || P2->Next == NULL)
                {
                    printf("One of the teams you chose does not exist, please try again\n");
                }
            }
           while(P1->Next==NULL || P2->Next == NULL);
            ReadFileOfPlayers(Players);
            subOne = SpareTeam(subOne, TeamOne);
            subTwo= SpareTeam2(subTwo, TeamTwo);
            Player * FirstTeamLineUp = Lineups(Players, TeamOne);
            Player * SecondTeamLineUp = Lineups(Players, TeamTwo);
            Menu2(FirstTeamLineUp, SecondTeamLineUp, subOne, subTwo);
            break;
        case 7:
            exit(0);
    }
}
int main()
{  //linked list of teams
    Teams *Group = NULL;
    Group = MakeEmptyForTheTeams(Group);
    //linked list of player
    Player *Players [clubs];
    // queue 1
    spareQueue1 SpareOne = NULL;
    SpareOne = createFirstQueue(SpareOne);
    //queue 2
    spareQueue2 SpareTwo = NULL;
    SpareTwo = createQueue2(SpareTwo);
    //pointers
    Teams  *P1 = NULL, *P2=NULL;
    ReadFileOfTeams( Group);
    Menu1(Group, SpareOne, SpareTwo, P1, P2, Players);
    for(int i=0; i < clubs; i++)
    {
        free(Players[i]);
    }
    free(Group);
    return 0;
}