#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
//#include "populate.h"


void listContacts(AddressBook *addressBook)
{
        int i,j;
        Contact temp;
        for(i=0;i<addressBook->contactCount-1;i++)
        {
            for(j=0;j<addressBook->contactCount-1-i;j++)
            {
                if((strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0))
                {
                temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j+1];
                addressBook->contacts[j+1]=temp;
                }
            }
        }
    for(i=0;i<addressBook->contactCount;i++)
    {
        printf("%s\t|\t%s\t|\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
}


void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
   // populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    //loadContactsFromFile(addressBook);
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook);  
}

int validate_name(char *name)
{
    int i=0;
    while(name[i])
    {
        if(!((name[i]>='A' && name[i]<='Z')||(name[i]>='a' && name[i]<='z')||name[i]=='.'||name[i]==' '))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int validate_phone(char *phone,AddressBook *addressBook)
{
    int i=0,j;
    while(phone[i])
    {
        if(!(phone[i]>='0' && phone[i]<='9'))
        {
            return 0;
        }
        i++;
    }
    if(i==10)
    {
        for(j=0;j<addressBook->contactCount;j++)
        {
            if(strcmp(addressBook->contacts[j].phone,phone)==0)
            {
                return 0;
            }
        }
        return 1;
    }
    else
    {
    return 0;
    }
}


int validate_email(char *email,AddressBook *addressBook)
{
    int i=0,j;
    while(email[i]>='a' && email[i]<='z')
    {
        i++;
    }
    if(email[i]!='@')
    {
        return 0;
    }
    i++;
    if(!(email[i]>='a' && email[i]<='z'))
    {
        return 0;
    }
    while(email[i]>='a'&&email[i]<='z')
    {
        i++;
    }
    if(email[i]=='.'&&email[i+1]=='c' && email[i+2]=='o' && email[i+3]=='m' && email[i+4]=='\0')
    {
        for(j=0;j<addressBook->contactCount;j++)
        {
            if(strcmp(addressBook->contacts[j].email,email)==0)
            {
                return 0;
            }
        }
        return 1;
    }
}

void createContact(AddressBook *addressBook)
{
    char name[20];
    int valid1;
    while(1)
    {
        printf("Enter the name : ");
        scanf(" %[^\n]", name);
        valid1= validate_name(name);
        if(valid1 == 1)
        {
            break;
        }
        else
        {
            printf("It is not valid,enter the name again\n");
        }
    }

char phone[20];
int valid2;
while(1)
{
    printf("eter mobile number:");
    scanf(" %[^\n]",phone);
    valid2=validate_phone(phone,addressBook);
    if(valid2==1)
    {
       break;
    }
     else
    {
    printf("It is not a valid number,try again:\n");
    }
}

char email[30];
int valid3;
while(1)
{
    printf("Enter the mail:");
    scanf(" %[^\n]",email);
    valid3=validate_email(email,addressBook);
    if(valid3==1)
    {
        break;
    }
    else
    {
        printf("It is not valid mail,try again:\n");
    }
}
     strcpy(addressBook->contacts[addressBook->contactCount].name,name);
     strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);
     strcpy(addressBook->contacts[addressBook->contactCount].email,email);

     addressBook->contactCount++;
     printf("\ncontact added successfully\n");
}

int search_by_name(AddressBook *addressBook)
{
    char str[50];
    int i;
    int count=0,ind;
    //Enter the name
    printf("Enter the name:");
    //Get the name
    scanf(" %[^\n]",str);

    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(str, addressBook->contacts[i].name) == 0)
        {
            //print the contact with a s.no
            printf("%d\t%s\t%s\t%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            ind = i;
            count++;
        }
    }

    // count ==> 0 ==> No match ==> return -1;
    if(count==0)
    return -1;
   // count ==> 1 ==> return ind
    if(count==1)
    return ind;
  // count > 1 ==> return search_by_phone(addressBook);
  if(count > 1)
  {
    search_by_phone(addressBook);
  }
  //return search_by_phone(addressBook);

}

int search_by_phone(AddressBook *addressBook)
{
    char str[11];
    int i;
    //Enter the phone
    printf("Enter the phone number:");
    //Get the phone
    scanf(" %[^\n]",str);

    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(str, addressBook->contacts[i].phone) == 0)
        {
            //print the contact
            printf("%s\t|\t%s\t|\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            return i;
        }
    }

    // Not found
    printf("Not found\n");
    return -1;
}

int search_by_email(AddressBook *addressBook)
{
    char str[20];
    int i;
    printf("Enter the email:");
    scanf(" %[^\n]",str);

    for(i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(str, addressBook->contacts[i].email) == 0)
        {
            //print the contact
            printf("%s\t|\t%s\t|\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            return i;
        }
    }

    // Not found
    printf("not found\n");
    return -1;
}

void searchContact(AddressBook *addressBook) 
{
    int choice;
    //promt (printf)
    printf("search contact by:\n");
    printf("1. Name\n");
    printf("2. Phone Number\n");
    printf("3. Email\n");
    printf("Enter your choice:");
    //get a choise from user (scanf)
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
            search_by_name(addressBook);
            break;
        case 2: 
            search_by_phone(addressBook);
            break;
        case 3: 
            search_by_email(addressBook);
            break;
        default:
            printf("Invalid input\n");
            
    }
} 

void edit_name(AddressBook *addressBook,int res)
{
    // get the name
    int valid1;
    char name[20];
    while(1)
    {
        printf("Enter the name : ");
        scanf(" %[^\n]", name);
        valid1= validate_name(name);
        if(valid1 == 1)// valid
          break;
    else
        printf("Invalid number,please enter a valid number\n");
   }
   strcpy(addressBook->contacts[res].name, name);

}

void edit_phone(AddressBook *addressBook,int res)
{
    char phone[20];
    int valid2;
    while(1)
    {
        printf("Enter mobile number:");
        scanf(" %[^\n]",phone);
        valid2=validate_phone(phone,addressBook);
        if(valid2==1)
        break;
    else
    printf("Invalid number,please enter a valid number\n");
    }
    strcpy(addressBook->contacts[res].phone,phone);
}

void edit_email(AddressBook *addressBook,int res)
{
    char email[50];
    int valid3;
    while(1)
    {
        printf("Enter mail id:");
        scanf(" %[^\n]",email);
        valid3=validate_email(email,addressBook);
        if(valid3==1)
        break;
    else
    printf("Invalid mail,please enter a valid mail\n");
    }
    strcpy(addressBook->contacts[res].email,email);
}

void editContact(AddressBook *addressBook)
{
    int res;
    int choice;
    do
    {
        printf("search by name\n");
        printf("search by phone\n");
        printf("search by email\n");
        printf("enter your choice:");
        scanf("%d",&choice);
        switch(choice)
    {
        case 1:
            res=search_by_name(addressBook);
            break;
        case 2: 
            res=search_by_phone(addressBook);
            break;
        case 3: 
            res=search_by_email(addressBook);
            break;
        default:
            printf("Invalid input\n");
    }
    if(res != -1)
    {
        break;
    }
    printf("contact not found\n");
}
while(choice != 3);
if(res != -1)
{ 
    printf("Edit name\n");
    printf("Edit phone\n");
    printf("Edit mail\n");
    printf("Enter the choice:");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
            edit_name(addressBook, res);
            break;
        case 2:
            edit_phone(addressBook, res);
            break;
        case 3: 
            edit_email(addressBook, res);
            break;
        default:
            printf("Invalid input\n");
            break;
    }   
}
}

void delete_name(AddressBook *addressBook,int res)
{
    int valid1;
    char name[20];
    while(1)
    {
        printf("Enter the name:");
        scanf(" %[^\n]",name);
        valid1=validate_name(name);
        if(valid1==1)
        break;
    }
}

void delete_phone(AddressBook *addressBook,int res)
{
    int valid2;
    char phone[20];
    while(1)
    {
        printf("Enter the phone:");
        scanf(" %[^\n]",phone);
        valid2=validate_phone(phone,addressBook);
        if(valid2==1)
        break;
    else
    printf("Invalid number,please enter a valid number\n");
    }
}

void delete_email(AddressBook *addressBook,int res)
{
    int valid3;
    char email[50];
    while(1)
    {
        printf("Enter the email:");
        scanf(" %[^\n]",email);
        valid3=validate_email(email,addressBook);
        if(valid3==1)
        break;
    else
    printf("Invalid mail,please enter a valid mail\n");
    }
}

void deleteContact(AddressBook *addressBook)
{
    int i,res,choice;
    do
    {
        printf("search contact by:\n");
        printf("1.search by name\n");
        printf("2.search by phone\n");
        printf("3.search by email\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            res=search_by_name(addressBook);
            break;
            case 2:
            res=search_by_phone(addressBook);
            break;
            case 3:
            res=search_by_email(addressBook);
            break;
            default:
            printf("invalid input\n");
        }
        if(res != -1)
        {
            break;
        }
        printf("contact not found\n");
     }
     while(choice != 3);

     if(res != -1)
     {
        printf("delete contact by:\n");
        printf("1.delete name\n");
        printf("2.delete phone\n");
        printf("3.delete email\n");
        printf("Enter the choice:");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1:
            delete_name(addressBook,res);
            break;
            case 2:
            delete_phone(addressBook,res);
            break;
            case 3:
            delete_email(addressBook,res);
            break;
            default:
            printf("Invalid input\n");
            break;
        }
     }
     for(i=res;i<addressBook->contactCount;i++)
     {
        addressBook->contacts[i]=addressBook->contacts[i+1];
     }
     addressBook->contactCount--;
     printf("contact deleted successfully\n");
}
