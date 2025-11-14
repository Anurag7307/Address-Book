#include "contact.h"

int main(){

	int choice;

        AddressBook addrBook;
        memset(&addrBook, 0, sizeof(addrBook));

	//load form csv or start empty
	loadContacts(&addrBook);

        //initialize(ptr);
	
	do{

	printf("\nAddressBook menu: \n");
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save & Exit\n");

        printf("\nEnter a choice: ");
        scanf("%d", &choice);
        getchar();
        printf("\n");

        switch(choice){
                case 1: printf("1. Selected create contact\n");
                        createContact(&addrBook);
                        break;
                case 2: printf("2. Selected search contact\n");
                        searchContact(&addrBook);
                        break;
                case 3: printf("3. Selected edit contact\n");
                        editContact(&addrBook);
                        break;
                case 4: printf("4. Selected Delete contact\n");
			deleteContact(&addrBook);
                        break;
                case 5: printf("5. Selected list all contacts\n");
                        listContacts(&addrBook);
                        break;
                case 6: printf("6. Save & Exit\n");
			saveContact(&addrBook);
			return 0;
                        break;
                default: printf("Invalid input");
                        break;
            }
	}while(choice != 6);
	
	return 0;
}

