#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact; //structure variable

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);

void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
//void initialize(AddressBook *addressBook);
//void populateContact(AddressBook *addressBook);
int findContactIndex(AddressBook *addressBook);
void saveContact(AddressBook *addressBook);
int loadContacts(AddressBook *addressBook);
int isValidPhone(const char *phone);
int isValidEmail(const char *email);

#endif
