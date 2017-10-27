/*HARI   OM!!!
Account captcha
Author:-
Version:
*/
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
#include<stdbool.h>
#define MIN_DEBIT_BALANCE 5000
#define MIN_BALANCE 1000
#define NAMELENGTH 15
#define TRUE 1
#define FALSE 0
#define ADMINPASSWORD 007
struct account_details
{
     int id;
    char fname[ NAMELENGTH];
    char lname[NAMELENGTH];
//   struct name name;
    int acc_num;
    int pin;
    float balance;
    char account_type;
    //struct dob dob;
};
struct node{
    struct account_details account;
    struct node *next;
};
typedef struct node *NODEPTR;
NODEPTR load_all();
NODEPTR getnode();
int set_pin();
void signup();
void transfer(NODEPTR sender,NODEPTR receiver);
NODEPTR load_details(int accnum);
int generate_account_number();
void printdetails(NODEPTR p);
void write_to_file(struct account_details ac);
void deposit(NODEPTR p);
void withdraw(NODEPTR p);
void apply_debit_card(NODEPTR p);
NODEPTR search_account(NODEPTR base,int accountno,int accountpin);
void signin(NODEPTR list);
void do_transactions(NODEPTR p,NODEPTR list);
void admin_access();
int generate_debit_pin();
NODEPTR searchByAccountnum(NODEPTR list,int accnum);
void file_update(NODEPTR list);
int main()
{
    NODEPTR p=NULL;
    int choice,signinchoice;
    printf("Welcome to Gringott's Bank\n");
    printf("Enter 1 to sign up\n");
    printf("Enter 2 to sign in\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
                signup();
                break;
        case 2:
                printf("Enter \n1-> to login as admin\n2->to login as customer\n");
                scanf("%d",&signinchoice);
                switch(signinchoice)
                {
                    case 1:
                        admin_access();
                        break;
                    case 2:
                        p=load_all();
                        signin(p);
                                                                                                 //To pass p it should have been loaded all the accounts here it is not done so segmentation fault occurs
                       break;
                    default:
                        printf("Invalid Entry \n");
                        exit(1);

                }
                break;
            default:
                printf("Invalid choice\n");
                printf("Please enter valid choice\n");
    }


    printf("Now we will print the updaTED \n");
    NODEPTR temp=p;
    while(temp!=NULL)
    {
        printdetails(temp);
        temp=temp->next;
    }
    file_update(p);
    return 0;
}
NODEPTR load_all()
{

    FILE *fptr;
    int s;
    NODEPTR temp=NULL, base;
    struct account_details accountt;
    fptr=fopen("documentary.dat","r");
    if (temp==NULL)
    {
    	fread(&accountt,sizeof(struct account_details),1,fptr);
    	temp=getnode();
    	base=temp;
    	//temp->account.account_type=account.account_type;
    	temp->account.acc_num=accountt.acc_num;
    	temp->account.balance=accountt.balance;
    	strcpy(temp->account.fname,accountt.fname);
    	//temp->account.id=account.id;
    	strcpy(temp->account.lname,accountt.lname);
    	temp->account.pin=accountt.pin;
    }
    while(fread(&accountt,sizeof(accountt),1,fptr))
    {
        temp->next=getnode();
        temp=temp->next;
        //temp->account.account_type=account.account_type;
        temp->account.acc_num=accountt.acc_num;
        temp->account.balance=accountt.balance;
        strcpy(temp->account.fname,accountt.fname);
        //temp->account.id=account.id;
        strcpy(temp->account.lname,accountt.lname);
        temp->account.pin=accountt.pin;
    }
    temp->next=NULL;
    fclose(fptr);
    return (base);
}
NODEPTR getnode()
{
    NODEPTR p;
    p=(NODEPTR)malloc(sizeof(struct node));
    if(p==NULL)
    {
        printf("Insufficient Heap Memory Available\n");
        exit(1);
    }
    p->next=NULL;
    return p;
}
int generate_account_number()
{
    int number;
    //initialize random seed:
    srand ( time(NULL) );
    //generate a random number: 		                                                                    ///Show to all
    number = rand() % 1000 + 1;
    printf("%d ", number);                                                                         //Substitute to generate random numbers without repetition (uses time.h)
    return (number);
}
int set_pin()
{
    int teddy=0;
    int temp;
    while(teddy==0)
    {
    printf("Enter a pin\nIt will be set as your password\n");

    if(scanf("%d",&temp)!=1)
    {
        printf("Enter a valid password\n");
        teddy=0;
    }
    teddy=1;
    }
    return temp;
}
void signup()
{
    NODEPTR p;
    int x;
    float bal;
    p=getnode();
    printf("Enter details\n");
    printf("Enter your first name\n");
    scanf("%s",p->account.fname);
    printf("Enter your last name\n");
    scanf("%s",p->account.lname);
    p->account.pin=set_pin();
    printf("To create this account we need a minimum balance of Rs%d/-\nPlease deposit initial Balance\n",MIN_BALANCE);
         scanf("%f",&bal);
         if(bal>=MIN_BALANCE)
                p->account.balance=bal;
        else
        {
            printf("Insufficient funds\n");
            exit(1);
        }
        x=generate_account_number();
        p->account.acc_num=x;
        printf("Your account number is %d\n",x);
        p->next=NULL;
        printf("Your details entered are\n");
        printdetails(p);
        write_to_file(p->account);

}
void write_to_file(struct account_details ac)
{
    FILE *fp=fopen("documentary.dat","a");
    fwrite(&ac,sizeof(ac),1,fp);
    printf("Successfully written\n");
    fclose(fp);
}
void printdetails(NODEPTR p)
{
    printf("Name:%s %s\n",p->account.fname,p->account.lname);
    printf("Balance: %f\n",p->account.balance);
    printf("Acc Num:%d\n",p->account.acc_num);
}
void deposit(NODEPTR p)
{
        float amt;
        printf("Enter the amount to be deposited\n");
        scanf("%f",&amt);
        p->account.balance+=amt;
        /*Displaying modified account details_display()*/
        //q.front--;
}
void withdraw(NODEPTR p)
{
    float amt;
    printf("Enter amount to be withdrawn\n");
    scanf("%f",&amt);
    p->account.balance-=amt;

    /*Display updated account*/
}
void apply_debit_card(NODEPTR p)
{
    int dpin;
    if(p->account.balance>=MIN_DEBIT_BALANCE)
    {
        printf("You are eligible to apply for debit card\n");
        dpin=generate_account_number();
        printf("Your debit card pin is %d\n",dpin);
        printf("This is confidential\n");
        printf("Please, do not disclose your pin to anyone\n");
    }
    else{
            printf("Since your balance is below Rs 5000, you are ineligible to apply for debit card\n");
            }
}
int generate_debit_pin()
{
        int flag;
        flag=rand()%1000 +10;
        return flag;
}
void pay_interest (NODEPTR p)
{
        struct account_details account;
        float interest;
        interest=6;
        p->account.balance=p->account.balance+(p->account.balance*interest);
}
NODEPTR search_account(NODEPTR base,int accountno,int accountpin)////good while administrator
{
    NODEPTR temp=NULL;
    temp=base;
    while(temp!=NULL)
    {
        if(temp->account.acc_num==accountno&&temp->account.pin==accountpin)
            return(temp);
        else
            temp=temp->next;
    }
    return NULL;
}
void signin(NODEPTR list)
{
    int accountnumber;
    int accountpin;
    int ted=0;
    int ch;
    NODEPTR p;
    while(ted==0)
    {
        printf("\nEnter your account number:");
        scanf("%d",&accountnumber);
        printf("\nEnter pin:");
        scanf("%d",&accountpin);
        p=search_account(list,accountnumber,accountpin);
        if(p==NULL)
        {
            printf("Account Number or the password does not match\n");
            ted=0;
        }
      else
        ted=1;
    }
    do
        {
            do_transactions(p,list);
            printdetails(p);
            printf("\n Enter 1 to continue the transactions :-");
            scanf("%d",&ch);
        }while(ch==1);
}
void do_transactions(NODEPTR p,NODEPTR list)
{
    NODEPTR q;
        int choice;
        int bear=0;
        int option;
    printf("Enter 1->withdraw\n\n");
    printf("Enter 2->deposit\n\n");
    printf("Enter 3->apply for debit\n\n");
    printf("Enter 4->transfer amount\n\n");
    scanf("%d",&choice);
    int accnum;
    switch(choice)
    {
    case 1:
                withdraw(p);
                break;
    case 2:
                deposit(p);
                break;
    case 3:
                apply_debit_card(p);
                break;
    case 4:
                while(bear==0)
                {
                    printf("Enter the account number to whom you want to send\n");
                    scanf("%d",&accnum);
                    q=searchByAccountnum(list,accnum);
                    if(q==NULL)
                    {
                        bear=0;
                        continue;
                    }
                    printf("Did you mean by the person\n%s %s\nwhose account number is%d\nif yes press 1\nelse press anything other than 1\n",q->account.fname,q->account.lname,q->account.acc_num);

                    scanf("%d",&option);
                    if(option==1)
                        break;
                    else
                        bear=1;
                    printf("Please try again\n\nEnter a valid account number\n\n");
                }
                        transfer(p,q);
                        break;
    default:
                 printf("Invalid option entry\n");
    }
}
NODEPTR searchByAccountnum(NODEPTR list,int accnum)
{

 NODEPTR temp=NULL;
    temp=list;
    while(temp!=NULL)
    {
        if(temp->account.acc_num==accnum)
            return(temp);
        else
            temp=temp->next;
    }
    return NULL;
}
void transfer(NODEPTR sender,NODEPTR receiver)
{
    int amt;
    printf("Enter the amount you want to transfer\n\n");
    scanf("%d",&amt);
    sender->account.balance-=amt;
    receiver->account.balance+=amt;
}
void admin_access()
{
    int entered_password;
    int ted=0;
    NODEPTR p;
    while(ted==0)
    {
        printf("Enter the password\n\n");
        scanf("%d",&entered_password);
        if(entered_password!=007)
        {
            printf("Incorrect password\n");
            printf("Please Try Again!\n");
            ted=0;
        }
        else
            ted=1;
    }
    p=load_all();
    NODEPTR q;
    q=p;
    while(q!=NULL)
    {
        printdetails(q);
        q=q->next;
    }
}
void file_update(NODEPTR list)
{
    struct account_details ac;
	FILE *fptr=fopen("documentary.dat","w");
	while(list!=NULL)
    {
        fwrite(&ac,sizeof(ac),1,fptr);
        list=list->next;
    }
    fclose(fptr);
}
void update_details(NODEPTR p)
{
        char localfname[20];
        char locallname[20];
        int  localpin;
        int flag;
        struct account_details account;
        printf("1-> To change only first name\n");
        printf("2-> To change only last name\n");
        printf("3->To change only pin\n");
        scanf("%d",&flag);
        printf("Enter account number whose details need to be changed");
        search_account(p,account.acc_num,localpin);
        switch(flag)
        {
            case 1:
                printf("Enter name to be updated/modified\n");
                gets(localfname);
                strcpy(p->account.fname,localfname);
                break;
            case 2:
                printf("Enter last name to be updated/modified\n");
                gets(locallname);
                strcpy(locallname,p->account.lname);
                break;
            case 3:
                printf("Enter pin to be changed\n");
                scanf("%d",&localpin);
                p->account.pin=localpin;
                break;
            default:
                    printf("Invalid choice\n");
        }

}
