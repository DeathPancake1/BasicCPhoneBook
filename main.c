#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    unsigned int day,month,year;
}Birth;

typedef struct{
    char lastName[20],firstName[20],address[41],phone[12],emailAddress[41];
    Birth birthDate;
}Entry;


FILE *f;
Entry *content;
char fileName[20];
int numRecords=0;
int end=0;

int makeDigit(char *s){
    int i, j, l,n;
    char *t;
    l = strlen(s);
    t = malloc(l+1);
    for (i = 0, j = 0; i < l; i++) {
        if (isdigit(s[i]))
            t[j++] = s[i];
    }
    t[j] = '\0';
    n=atoi(t);
    return n;
}

int validateDate(int day,int month,int year){
    if((day>31||day<1)||(month>12||month<1)||(year<0)){
        return 0;
    }
    return 1;
}

int validatePhone(char s[]){
    int i, l,f=0;
    l = strlen(s);
    for (i = 0; i < l; i++) {
        if (!isdigit(s[i]))
            f=1;
    }
    if(f==0){
        return 1;
    }
    return 0;
}

int validateEmail(char s[]){
    int i, l,f1=0,f2=0;
    l = strlen(s);
    for (i = 0; i < l; i++) {
        if (s[i]=='@')
            f1=1;
        if (s[i]=='.')
            f2=1;
    }
    if(f1==1&&f2==1){
        return 1;
    }
    return 0;
}

int compare(Birth a, Birth b){
    if (a.year > b.year)
        return 1;
    if (a.year == b.year && a.month > b.month)
        return 1;
    if (a.year == b.year && a.month == b.month && a.day > b.day)
        return 1;

    return 0;
}

void LOAD(){
    char *l;
    printf("Enter the name of the file you want to load.\n");
    scanf("%s",fileName);
    f=fopen(fileName,"r");
    if(!f){
        printf("Unable to load the file\n");
        LOAD();
    }
    char buffer[100];
    while(fgets(buffer,sizeof(buffer),f)){
        numRecords++;
    }
    content=(Entry *)calloc(numRecords,sizeof(Entry));
    fseek(f,0l,SEEK_SET);
    for(int i=0;i<numRecords;i++){
        fgets(buffer,sizeof(buffer),f);
        char *tok=strtok(buffer,",");
        strcpy(content[i].lastName,tok);
        for(int j=0;j<7;j++){
            tok=strtok(NULL,",");
            switch(j){
            case 0:
                strcpy(content[i].firstName,tok);
                break;
            case 1:
                strcpy(content[i].phone,tok);
                break;
            case 2:
                strcpy(content[i].address,tok);
                break;
            case 3:
                content[i].birthDate.day=makeDigit(tok);
                break;
            case 4:
                content[i].birthDate.month=makeDigit(tok);
                break;
            case 5:
                content[i].birthDate.year=makeDigit(tok);
                break;
            case 6:
                for(int i=0;i<numRecords;i++){
                    l=strlen(tok);
                    for(int j=0;j<l-1;j++){
                        content[i].emailAddress[j]=tok[j];
                    }
                }
                break;
            }
        }
    }
    fclose(f);
}

void ADD(){
    char lastName[20],firstName[20],address[41],phone[12],emailAddress[41];
    unsigned int day,month,year;
    printf("Enter last name: ");
    scanf("%s",lastName);
    printf("Enter first name: ");
    scanf("%s",firstName);
    printf("Enter phone number: ");
    scanf("%s",phone);
    if(!validatePhone(phone)){
        printf("Phone number is not correct.\n");
        return;
    }
    printf("Enter address: ");
    scanf("%s",address);
    printf("Enter day,month and year of birth: ");
    scanf("%d %d %d",&day,&month,&year);
    if(!validateDate(day,month,year)){
        printf("Date is not correct.\n");
        return;
    }
    printf("Enter email address: ");
    scanf("%s",emailAddress);
    if(!validateEmail(emailAddress)){
        printf("Email Address is not correct.\n");
        return;
    }
    numRecords++;
    content=(Entry *)realloc(content,numRecords*sizeof(Entry));
    strcpy(content[numRecords-1].lastName,lastName);
    strcpy(content[numRecords-1].firstName,firstName);
    strcpy(content[numRecords-1].phone,phone);
    strcpy(content[numRecords-1].address,address);
    content[numRecords-1].birthDate.day=day;
    content[numRecords-1].birthDate.month=month;
    content[numRecords-1].birthDate.year=year;
    strcpy(content[numRecords-1].emailAddress,emailAddress);
}

void QUERY(){
    char query[21],lowerQuery[21],lowerLname[21];
    int f=0,lengthQ,lengthLN;
    printf("The last name of the person: ");
    scanf("%s",query);
    lengthQ=strlen(query);
    strcpy(lowerQuery,query);
    for(int j=0;j<lengthQ;j++){
        lowerQuery[j]=tolower(lowerQuery[j]);
    }
    for(int i=0;i<numRecords;i++){
        lengthLN=strlen(content[i].lastName);
        strcpy(lowerLname,content[i].lastName);
        for(int j=0;j<lengthLN;j++){
            lowerLname[j]=tolower(lowerLname[j]);
        }
        if(strcmp(lowerLname,lowerQuery)==0){
            printf("%s %s %s %s %d %d %d %s\n",content[i].lastName,content[i].firstName,content[i].phone,content[i].address,content[i].birthDate.day,content[i].birthDate.month,content[i].birthDate.year,content[i].emailAddress);
            f=1;
        }
    }
    if(f==0){
        printf("Unable to find %s in the file.\n",query);
    }
}

void sortByLname(){
    Entry temp;
    for(int j=0;j<numRecords;j++){
        for(int i=0;i<numRecords-1;i++){
            if(strcmp(content[i].lastName,content[i+1].lastName)>0){
                temp=content[i];
                content[i]=content[i+1];
                content[i+1]=temp;
            }
        }
    }
    for(int i=0;i<numRecords;i++){
        printf("%s %s %s %s %d %d %d %s\n",content[i].lastName,content[i].firstName,content[i].phone,content[i].address,content[i].birthDate.day,content[i].birthDate.month,content[i].birthDate.year,content[i].emailAddress);
    }
}

void sortByDOB(){
    Entry temp;
    for(int j=0;j<numRecords;j++){
        for(int i=0;i<numRecords-1;i++){
            if(compare(content[i].birthDate,content[i+1].birthDate)){
                temp=content[i];
                content[i]=content[i+1];
                content[i+1]=temp;
            }
        }
    }
    for(int i=0;i<numRecords;i++){
        printf("%s %s %s %s %d %d %d %s\n",content[i].lastName,content[i].firstName,content[i].phone,content[i].address,content[i].birthDate.day,content[i].birthDate.month,content[i].birthDate.year,content[i].emailAddress);
    }
}
void PRINT(){
    int choice;
    printf("In what order do you want to print?\n1)Names\n2)Birth Date\n");
    scanf("%d",&choice);
    switch(choice){
        case 1:
            sortByLname();
            break;
        case 2:
            sortByDOB();
            break;
    }
}
void MODIFY(){
    char query[21],lowerQuery[21],lowerLname[21];
    int f=0,lengthQ,lengthLN,index;
    printf("The last name of the person you want to modify: ");
    scanf("%s",query);
    lengthQ=strlen(query);
    strcpy(lowerQuery,query);
    for(int j=0;j<lengthQ;j++){
        lowerQuery[j]=tolower(lowerQuery[j]);
    }
    for(int i=0;i<numRecords;i++){
        lengthLN=strlen(content[i].lastName);
        strcpy(lowerLname,content[i].lastName);
        for(int j=0;j<lengthLN;j++){
            lowerLname[j]=tolower(lowerLname[j]);
        }
        if(strcmp(lowerLname,lowerQuery)==0){
            index=i;
            f=1;
        }
    }
    if(f==0){
        printf("Unable to find %s in the file.\n",query);
        return;
    }
    char lastName[20],firstName[20],address[41],phone[12],emailAddress[41];
    unsigned int day,month,year;
    printf("Enter last name: ");
    scanf("%s",lastName);
    printf("Enter first name: ");
    scanf("%s",firstName);
    printf("Enter phone number: ");
    scanf("%s",phone);
    if(!validatePhone(phone)){
        printf("Phone number is not correct.\n");
        return;
    }
    printf("Enter address: ");
    scanf("%s",address);
    printf("Enter day,month and year of birth: ");
    scanf("%d %d %d",&day,&month,&year);
    if(!validateDate(day,month,year)){
        printf("Date is not correct.\n");
        return;
    }
    printf("Enter email address: ");
    scanf("%s",emailAddress);
    if(!validateEmail(emailAddress)){
        printf("Email Address is not correct.\n");
        return;
    }
    strcpy(content[index].lastName,lastName);
    strcpy(content[index].firstName,firstName);
    strcpy(content[index].phone,phone);
    strcpy(content[index].address,address);
    content[index].birthDate.day=day;
    content[index].birthDate.month=month;
    content[index].birthDate.year=year;
    strcpy(content[index].emailAddress,emailAddress);
}

void DELETE(){
    char query[21],lowerQuery[21],lowerLname[21];
    int f=0,lengthQ,lengthLN,index;
    printf("The last name of the person you want to delete: ");
    scanf("%s",query);
    lengthQ=strlen(query);
    strcpy(lowerQuery,query);
    for(int j=0;j<lengthQ;j++){
        lowerQuery[j]=tolower(lowerQuery[j]);
    }
    for(int i=0;i<numRecords;i++){
        lengthLN=strlen(content[i].lastName);
        strcpy(lowerLname,content[i].lastName);
        for(int j=0;j<lengthLN;j++){
            lowerLname[j]=tolower(lowerLname[j]);
        }
        if(strcmp(lowerLname,lowerQuery)==0){
            index=i;
            f=1;
        }
    }
    if(f==0){
        printf("Cannot find %s in the file.\n",query);
        return;
    }
    else{
        for(int i=0,j=0;i<numRecords;i++){
            if(i!=index){
                content[j]=content[i];
                j++;
            }
        }
        numRecords=numRecords-1;
        content=(Entry *)realloc(content,numRecords*sizeof(Entry));
    }
}

void SAVE(){
    f=fopen(fileName,"w");
    char buffer[100];
    for(int i=0;i<numRecords;i++){
        sprintf(buffer,"%s,%s,%s,%s,%d,%d,%d,%s\n",content[i].lastName,content[i].firstName,content[i].phone,content[i].address,content[i].birthDate.day,content[i].birthDate.month,content[i].birthDate.year,content[i].emailAddress);
        fputs(buffer,f);
    }
    fclose(f);
    return;
}

void QUIT(){
    int choice;
    printf("Are you sure you want to quit? any unsaved data will be lost.\n1)Quit\n2)Go to menu\n");
    scanf("%d",&choice);
    switch(choice){
        default:
            printf("Enter a valid choice.\n");
            QUIT();
            break;
        case 1:
            end=1;
            return;
            break;

        case 2:
            break;
    }
}

void MENU(){
    LOAD();
    int choice;
    while(end!=1){
        printf("------------------------------------------What to you want to do?------------------------------------------\n");
        printf("1)Search the file.\n2)Add an entry.\n3)Delete an entry.\n4)Modify an existing entry.\n5)Print and sort the phone book.\n6)Save\n7)Exit without saving.\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                QUERY();
                break;
            case 2:
                ADD();
                break;
            case 3:
                DELETE();
                break;
            case 4:
                MODIFY();
                break;
            case 5:
                PRINT();
                break;
            case 6:
                SAVE();
                break;
            case 7:
                QUIT();
                break;
            default:
                printf("Enter a valid choice");
        }
    }
}

int main()
{
    printf("------------------------------------------Phone Book application------------------------------------------\n");
    MENU();
    return 0;
}
