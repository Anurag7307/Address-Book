#include "contact.h"

int findContactIndex(AddressBook *addressBook){
	if(addressBook->contactCount == 0){
                printf("No contacts available to edit.\n");
                return -1;  //nothing to search
        }

	int searchChoice;
	char searchInput[50];

	/*Ask the user how they want to search
	 * Loops untill a valid input(0-3)*/
	do{
		
            printf("Search a contact: \n");

            printf("0. Back\n1. Name\n2. Phone number\n3. Email-Id\n");
            printf("Please select an option for search: ");
            scanf(" %d", &searchChoice);
            getchar(); //clear newline
	    //fflush(stdin);  //clear the buffer        
           
	    if(searchChoice < 0 || searchChoice > 3){
		   printf("Invalid Input! Please try again\n");
	   }

	}while(searchChoice < 0 || searchChoice > 3);


	/*Get search input from user*/
        switch(searchChoice){
                case 0:
                        printf("Back");
                        return -2;
                case 1:
                        printf("Enter Name: ");
                        scanf(" %49[^\n]", searchInput);
                        break;
                case 2:
                        printf("Phone number: ");
                        scanf(" %49[^\n]", searchInput);
                        break;
                case 3:
                        printf("Email-Id: ");
                        scanf(" %49[^\n]", searchInput);
                        break;
        }

	/*Search for the contact*/
        for(int i = 0; i<addressBook->contactCount; i++){
		Contact *c = &addressBook->contacts[i];
                if((searchChoice == 1 && strcmp(c->name, searchInput) == 0)||
                (searchChoice == 2 && strcmp(c->phone, searchInput) == 0)||
                (searchChoice == 3 && strcmp(c->email, searchInput) == 0)){
                        return i;
                }

        }

	return -1; //if no match found
}

//verifying the phone number 
int isValidPhone(const char *phone){
	//check the max characters to be 10
	if(strlen(phone)!=10)
		return 0;
	for(int i = 0; phone[i]!='\0'; i++){            //going to each character
		if(!isdigit((unsigned char)phone[i]))    //check wheather its number or not							 
		            return 0;
	}
	return 1;
}

//verifying email
int isValidEmail(const char *email){
       const char *at = strchr(email, '@'); 
       if(!at || at == email)
	       return 0;

       const char *dot = strchr(at, '.');
       if(!dot || dot<(at+2))
                return 0;
       if(*(dot+1) == '\0')
                return 0;

       return 1;	

}




void listContacts(AddressBook *addressBook) 
{
        /* print list of all contacts from AddressBook */
	printf("Contact details\n");

	for(int i = 0; i< addressBook->contactCount; i++){
		printf("%s\t%s\t%s\n", addressBook->contacts[i].name,
				addressBook->contacts[i].phone,
				addressBook->contacts[i].email);

	}

}

/*
void initialize(AddressBook *addressBook) 
{
	if(!loadContacts(addressBook)){
	     printf("No contact found, start with an empty Address Book");
	}
	addressBook->contactCount = 0;
	//No dummy data now, let the user add manually

	//for populating the Adderessbook with dummy contacts
	populateContact(addressBook);

    
}
*/

void createContact(AddressBook *addressBook) 
{
	/*read string from the user from countContact position
	 * increment countContact*/

	if(addressBook->contactCount >= MAX_CONTACTS){
		printf("AddressBook is full! Cannot add more contacts.\n");
	}

	Contact tempContact;

	printf("Enter name: ");
	scanf(" %[^\n]", tempContact.name);

	//validation for phone number
	do{

	   printf("Enter phone number(10 digits): ");
 	   scanf(" %[^\n]", tempContact.phone);

	   if(!isValidPhone(tempContact.phone)){
		printf("Invalid phone number. It must be exactly 10 digits!\n");
	   } 

	}while(!isValidPhone(tempContact.phone));

	//validation for email id
	do{
		
	   printf("Enter email: ");
	   scanf(" %[^\n]", tempContact.email);

	     if(!isValidEmail(tempContact.email)){
		   printf("Invalid Email ID. Format 'user@mail.com'\n");
	     }
	     
	  }while(!isValidEmail(tempContact.email));

	//check for duplicates
	for(int i = 0; i<addressBook->contactCount; i++){
		Contact *existing = &addressBook->contacts[i];

		if((strcmp(existing->name, tempContact.name) == 0) ||
				(strcmp(existing->phone, tempContact.phone) == 0) ||
				(strcmp(existing->email, tempContact.email) == 0)){

			printf("Contact with the same name, phone number or email-id already exists \n");
			return;
		}

	}
	

	        
		/*Add new contact to the contacts array*/
                addressBook->contacts[addressBook->contactCount] = tempContact;

                addressBook->contactCount++;   //incrementing the contactCount
	        saveContact(addressBook);  //contact saving after reading

		printf("Contact added successfully!\n");

}

void searchContact(AddressBook *addressBook) 
{
	if(addressBook->contactCount == 0){
		printf("Address Book is empty.\n");
		return;
	}

	int index = findContactIndex(addressBook);

	if(index == -2){
		printf("Returning to the main menu...\n");
                return;
	}
	
	if(index == -1){
		printf("Contact not found!\n");
                return;
	}

	printf("Contact found!\n");

}

void editContact(AddressBook *addressBook) 
{

	if(addressBook->contactCount == 0){
		printf("No contacts available to edit.\n");
		return;
	}

	int index = findContactIndex(addressBook);
	
	if(index == -2){
		printf("Returning to the main menu...\n");
		return;
	}

	if(index == -1){
		printf("Contact not found!\n");
		return;
	}

	/*Show found contact details*/
	printf("\nContact found!\n");
	printf("Name: %s\nPhone number: %s\nEmail-Id: %s\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);

	/*Ask the user what to edit*/
	int editChoice;

	do{
	     printf("\nEdit Contact:\n");
	     printf("0. Back\n1. Name\n2. Phone number\n3.Email-Id\n");
	     printf("Please select an option to edit: ");
	     scanf("%d", &editChoice);
	     getchar();  //clear newline
	
	     if(editChoice < 0 || editChoice > 3){
		   printf("Invalid Input! Please try again\n");
	     }

	   }while(editChoice < 0 || editChoice > 3);


	switch(editChoice){

		case 1:
			printf("Enter new Name: ");
			scanf(" %[^\n]", addressBook->contacts[index].name);
			break;
		case 2:
                        printf("Enter new Phone number: ");
                        scanf(" %[^\n]", addressBook->contacts[index].phone);
                        break;
		case 3:
                        printf("Enter new Email-Id: ");
                        scanf(" %[^\n]", addressBook->contacts[index].email);
                        break;
		case 0:
			printf(" Returning to the main menu...\n");
			return;

	}

	saveContact(addressBook);    //save to contact.csv file after edit

	printf("Contact updated and saved!");

}

void deleteContact(AddressBook *addressBook) 
{
	if(addressBook->contactCount == 0){
		printf("No contacts available to delete");
		return;
	}

	int index = findContactIndex(addressBook);
	
	if(index == -2){
                printf("Returning to the main menu...");
                return;
        }

        if(index == -1){
                printf("Contact not found!\n");
                return;
        }

	/*Showing found contacts before deleting*/
	printf("\nContact found!\n");
        printf("Name: %s\nPhone number: %s\nEmail-Id: %s\n", addressBook->contacts[index].name, addressBook->contacts[index].phone, addressBook->contacts[index].email);

	/*Confirm delete*/
	int confirm;

	do{
	     printf("Are you sure you want to delete this contact?\n");
	     printf("1. Yes\n2. No\n");
	     printf("Enter your choice: ");
	     scanf("%d", &confirm);
	     getchar();   //clear newline
	
	     if(confirm < 0 || confirm > 2){
		    printf("Invalid Input! Please try again\n");
	     }

	}while(confirm < 0 || confirm > 2);

	
	if(confirm == 1){
		for(int i = index; i<addressBook->contactCount-1; i++){
			addressBook->contacts[i] = addressBook->contacts[i+1];
		}
		addressBook->contactCount--;
		saveContact(addressBook);     //save after delete
		printf("Contact deleted and saved!\n");
	}else{
		printf("Contact not deleted!\n");
	}

}

void saveContact(AddressBook *addressBook){
	FILE *fptr = fopen("contact.csv", "w");
	if(fptr == NULL){
		printf("Error in opening file for writting\n");
		return;
	}
	fprintf(fptr, "%d\n", addressBook->contactCount);
	for(int i = 0;i<addressBook->contactCount; i++){
		fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
	}	

	fclose(fptr);
}

int loadContacts(AddressBook *addressBook){
	FILE *fptr = fopen("contact.csv", "r");
	if(fptr == NULL){
		printf("No saved contacts found\n");
		addressBook->contactCount = 0;
		return 0;
	}



	fscanf(fptr, "%d\n", &addressBook->contactCount);

	for(int i = 0; i<addressBook->contactCount; i++){
		fscanf(fptr, "%49[^,],%19[^,],%49[^\n]\n", 
				addressBook->contacts[i].name,
			       	addressBook->contacts[i].phone, 
				addressBook->contacts[i].email);

	}
	fclose(fptr);
	return 1;
}

