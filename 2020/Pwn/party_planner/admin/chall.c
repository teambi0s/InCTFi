#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<time.h>

typedef struct Person{
    char  name[32];
    char * details;
    unsigned int in_house;
    unsigned int id;
}Person;

typedef struct House{
    char name[32];
    Person ** person_array;
    char * description;
}House;


House * houses[2];
Person * houseOnePeople[10];
Person * houseTwoPeople[10];
Person * person[20];
Person * curPerson;

char *arr[] = {"\x1B[31m%s\x1B[0m","\x1B[32m%s\x1B[0m","\x1B[33m%s\x1B[0m","\x1B[34m%s\x1B[0m","\x1B[35m%s\x1B[0m","\x1B[36m%s\x1B[0m","\x1B[37m%s\x1B[0m"};
void Exit(char* s){
    printf(arr[0],s);
    exit(0);
}

unsigned int getInp(char* ptr,unsigned int size){
    int ret = read(0,ptr,size);
    if(ret <=0){
        Exit("Read error");
    }
    ptr[ret-1]='\0';
    return ret;
}

unsigned int getInt(){
    char buf[32];
    getInp(buf,32);
    return atoi(buf);
}

void initialize(){
    setvbuf(stdin,NULL,_IONBF,0);
    setvbuf(stdout,NULL,_IONBF,0);
    setvbuf(stderr,NULL,_IONBF,0);
    alarm(120);
}

void createHouse(){
    unsigned int i;
    for(i=0;i<2;i++){
        if(!houses[i])
            break;
    }
    if(i>=2)
        Exit("You are not rich enough to have more than two houses");
    houses[i] = (House *)malloc(sizeof(House));
    printf("Name for your House : ");
    getInp(houses[i]->name,32);
    if(i==0)
        houses[i]->person_array=houseOnePeople;
    else
        houses[i]->person_array=houseTwoPeople;
    printf("Enter the size for description of House : ");
    unsigned int size = getInt();
    if(size > 0x500)
        Exit("Size too large");
    char * desc= (char *)malloc(size);
    printf("Enter the description : ");
    getInp(desc,size);
    houses[i]->description=desc;
    return;
}


void createPerson(){
    unsigned int i;
    for(i =0;i<20;i++){
        if(!person[i])
            break;
    }
    if(i>19)
        Exit("Maximum person number reached");
    curPerson = (Person *)malloc(sizeof(Person));
    printf("Enter the name of the Person : ");
    getInp(curPerson->name,32);
    printf("Enter the size for details of Person : ");
    unsigned int size = getInt();
    if(size > 0x500)
        Exit("Size too large");
    char * deta = (char *)malloc(size);
    printf("Enter the details : ");
    getInp(deta,size);
    curPerson->details=deta;
    curPerson->in_house=0;
    curPerson->id=0;
    person[i]=curPerson;
    curPerson=NULL;
    return;

}

void addPersonToHouse(){
    printf("Enter the Person number : ");
    unsigned int i=getInt();
    if(!person[i])
        Exit("No such Person");
    if(person[i]->in_house)
        Exit("Person is already in a House");
    printf("Which House (0 or 1) ? : ");
    unsigned int idx = getInt();
    if(!houses[idx] || idx>1)
        Exit("House doesn't exist");
    unsigned int j;
    for(j=0;j<10;j++){
        if(idx==0){
            if(!houseOnePeople[j])
                break;
        }
        else{
            if(!houseTwoPeople[j])
                break;
        }
    }
    if(j>9)
        Exit("Space is over in the House you requested");
    if(idx==0){
        houseOnePeople[j]=person[i];
        houseOnePeople[j]->in_house=1;
        houseOnePeople[j]->id=j;
    }
    else{
        houseTwoPeople[j]=person[i];
        houseTwoPeople[j]->in_house=1;
        houseTwoPeople[j]->id=j;
    }
    person[i]=NULL;
    return;
}

void viewHouse(){
    char string [] ="             _______________________\n"
        "            /                       \\\n"
        "           /                         \\\n"
        "          /                           \\\n"
        "         /   ______          ______    \\\n"
        "        /   |      |        |      |    \\\n"
        "       /    |      |        |      |     \\\n"
        "      /     |______|        |______|      \\\n"
        "     /                                     \\\n"
        "    /                                       \\\n"
        "    |---------------------------------------|\n"
        "    |                                       |\n"
        "    |                                       |\n"
        "    |                                       |\n"
        "    |                                       |\n"
        "    |                                       |\n"
        "    | ";



    char string2 [] = "    |_______________________________________|\n";

    printf("Which House (0 or 1) ? : ");
    unsigned int idx = getInt();
    if(!houses[idx] || idx>1)
        Exit("House doesn't exist");
    printf("%s",string);
    unsigned int count=0;
    if(idx==0){
        for(int i=0;i<10;i++){
            if(houseOnePeople[i]){
                count++;
                char c = (char)(i+48);
                printf("%c",c);
                if(i<9)
                    printf("%s","   ");
            }
            else{
                printf("%s","_");
                if(i<9)
                    printf("%s","   ");
            }
        }
        printf("%s"," |\n");
    }
    else{
        for(int i=0;i<10;i++){
            if(houseTwoPeople[i]){
                count++;
                char c = (char)(i+48);
                printf("%c",c);
                if(i<9)
                    printf("%s","   ");
            }
            else{
                printf("%s","_");
                if(i<9)
                    printf("%s","   ");
            }
        }
        printf("%s"," |\n");
    }
    printf("%s\n\n",string2);
    printf("House name : %s\n",houses[idx]->name);
    printf("House description : %s\n",houses[idx]->description);
    printf("Number of People in the House : %d\n",count);
    if(idx==0){
        for(int i=0;i<10;i++){
            if(houseOnePeople[i]){
                printf("Person %d  %s with details  %s\n",houseOnePeople[i]->id,houseOnePeople[i]->name,houseOnePeople[i]->details);
            }
        }
    }
    else{
        for(int i=0;i<10;i++){
            if(houseTwoPeople[i]){
                printf("Person %d  %s with details  %s\n",houseTwoPeople[i]->id,houseTwoPeople[i]->name,houseTwoPeople[i]->details);
            }
        }
    }
    return;
}

void destroyHouse(){
    printf("Which House (0 or 1) ? : ");
    unsigned int idx = getInt();
    if(!houses[idx] || idx>1)
        Exit("House doesn't exist");
    if(idx==0){
        for(int i=0;i<10;i++){
            if(houseOnePeople[i])
                Exit("You can't destroy a House with people in it");
        }
    }
    else{
        for(int i=0;i<10;i++){
            if(houseTwoPeople[i])
                Exit("You can't destroy a House with people in it");
        }
    }
    free(houses[idx]->description);
    free(houses[idx]);
    houses[idx]=NULL;
    return;
}

void Party(){
    printf("Which House (0 or 1) ? : ");
    unsigned int idx = getInt();
    if(!houses[idx] || idx>1)
        Exit("House doesn't exist");

    for(int i=0;i<7;i++){
        printf(arr[i],
                "             _______________________\n"
                "            /                       \\\n"
                "           /                         \\\n"
                "          /                           \\\n"
                "         /   ______          ______    \\\n"
                "        /   |      |        |      |    \\\n"
                "       /    |      |        |      |     \\\n"
                "      /     |______|        |______|      \\\n"
                "     /                                     \\\n"
                "    /                                       \\\n"
                "    |---------------------------------------|\n"
                "    |                                       |\n"
                "    |                                       |\n"
                "    |                                       |\n"
                "    |                                       |\n"
                "    |                                       |\n"
                "    |                                       |\n"
                "    |_______________________________________|\n");
        usleep(200000);
        if(i<6){
            for(int j=0;j<18;j++){
                printf("\033[A\r");
                fflush(stdout);
            }
        }
    }
    if(idx==0){
        for(int i=0;i<10;i++){
            if(houseOnePeople[i]){
                free(houseOnePeople[i]->details);
                free(houseOnePeople[i]);
                houseOnePeople[i]=NULL;
            }
        }
    }
    else{
        for(int i=0;i<10;i++){
            if(houseTwoPeople[i]){
                free(houseTwoPeople[i]->details);
                free(houseTwoPeople[i]);
                houseTwoPeople[i]=NULL;
            }
        }
    }
    printf("\n\nParty is over\nAll people have left\n\n");
    return;
}

void removePersonFromHouse(){
    unsigned int idx;
    printf("Which House (0 or 1) ? : ");
    idx=getInt();
    if(!houses[idx] || idx>1)
        Exit("No such House");
    unsigned int i;
    printf("Enter the Person number : ");
    i=getInt();
    if(!curPerson){
        if(idx==0){
            if(!houseOnePeople[i])
                Exit("No such Person");
            curPerson=houseOnePeople[i];
        }
        else{
            if(!houseTwoPeople[i])
                Exit("No such Person");
            curPerson=houseTwoPeople[i];
        }
    }
    if(idx==0){
        if(!curPerson->in_house)
            Exit("Something went wrong");
        curPerson->in_house=0;
        free(curPerson->details);
        free(curPerson);
        houseOnePeople[i]=NULL;

    }
    else{
        if(!curPerson->in_house)
            Exit("Something went wrong");
        curPerson->in_house=0;
        free(curPerson->details);
        free(curPerson);
        houseTwoPeople[i]=NULL;
    }
    curPerson=NULL;
    return;
}

void viewPerson(){
    unsigned int idx;
    printf("Which House (0 or 1) ? : ");
    idx=getInt();
    if(!houses[idx] || idx>1)
        Exit("No such House");
    printf("Enter the Person number : ");
    unsigned int i=getInt();
    if(idx==0){
        if(!houseOnePeople[i])
            Exit("No such Person");
        curPerson=houseOnePeople[i];
    }
    else{
        if(!houseTwoPeople[i])
            Exit("No such Person");
        curPerson=houseTwoPeople[i];
    }
    printf("Name of Person %d is %s\n",curPerson->id,curPerson->name);
    return;
}


unsigned int menu(){
    printf(
            " _______________________________\n"
            "|                               |\n"
            "|      House Party Planner      |\n"
            "|_______________________________|\n"
            "|                               |\n"
            "| 1. Create a House             |\n"
            "| 2. Create a Person            |\n"
            "| 3. Add Person to House        |\n"
            "| 4. Remove Person from House   |\n"
            "| 5. View the House             |\n"
            "| 6. View a Person              |\n"
            "| 7. Party                      |\n"
            "| 8. Destroy House              |\n"
            "| 9. Give Up                    |\n"
            "|_______________________________|\n"
            "Choice >> ");
    return getInt();
}

int main(){
    initialize();
    while(1){
        switch(menu()){
            case 1:createHouse();
                   break;
            case 2: createPerson();
                    break;
            case 3: addPersonToHouse();
                    break;
            case 4: removePersonFromHouse();
                    break;
            case 5: viewHouse();
                    break;
            case 6: viewPerson();
                    break;
            case 7: Party();
                    break;
            case 8: destroyHouse();
                    break;
            case 9: Exit("Bye");
                    break;
            default : puts("Invalid Option");
        }
    }
    return 0;
}
