#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook)
{
    int i;
    FILE *fptr=fopen("contacts.csv","w");
    fprintf(fptr,"%d\n",addressBook->contactCount);
    for(i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
    
}

void loadContactsFromFile(AddressBook *addressBook)
{
    int i;
    FILE *fptr=fopen("contacts.csv","r");
    if(fptr==NULL)
    return;
fscanf(fptr,"%d\n",&addressBook->contactCount);
printf("loaded contacts=%d\n",addressBook->contactCount);
for(i=0;i<addressBook->contactCount;i++)
{
    fscanf(fptr,"%[^,],%[^,],%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
}
fclose(fptr);
    
}
