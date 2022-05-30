

#ifndef HW_7_CLIENT_H
#define HW_7_CLIENT_H
#include "getinput.h"
#include "BinarySearchTree.h"

typedef struct CClient{
    char *firstName;
    char *lastName;
    char id[ID_LEN+1];
    char licenseNum[LICENSE_NUM_LEN+1];
    Date rentDate;
    Time rentHour;
    int dailyPrice;
} Client;

/* Gets a pointer to a new client and client details and creates a new client */
int createNewClient(Client* new, char *firstName, char *lastName,
                    char id[ID_LEN+1], char licenseNum[LICENSE_NUM_LEN+1],
                    Date rentDate, Time rentHour,
                    int dailyPrice);

/* Return empty tree struct for client management */
Tree* createClientTree();

/* Get client details from user, creates a new client and insert it to client tree */
int addNewClient(Tree* tree,Tree* cars);

/* Returns the amount of clients with a car with a given creation year */
int clientNumberWithGivenCarYear(Tree* tree);

/* Get 2 generic pointers to client structs and compare their license numbers using strcmp */
int clientcmpr(void* a, void* b);

/* Get data for client and return pointer to a new client struct */
void* getClientData(void* cpy,FILE* f);

/* Delete client with given ID num */
int deleteClient(Tree* clients,Tree* cars);

/* Deletes all clients from given tree */
int deleteAllClients(Tree* clients,Tree* cars);

/* Print all clients in tree */
void printClients(Tree* tree);

/* Prints a single client */
void printClient(void * vClient);

/* Gets a clients tree and prints all the clients who rented a car in a given date */
int printClientCarsForGivenRentDate(Tree* clients);

/* Gets a client tree, user chooses between search by ID to search by Date. Returns client linked list if clients are found */
LList* findClient(Tree* clients);

#endif
