


#include "Client.h"
#include "Car.h"


/* functions below are not available outside of this file */
int clientFree(Node* node);
int clientIDcmpr(void* client, void* id);
int clientNumberWithGivenCarYear_rec(Node* root,int year);
int idCmpr(void* client, void* id);
int dateCompare(void* client, void* d2);
/* functions above are not available outside of this file */


/* Gets a pointer to a new client and client details and creates a new client */
int createNewClient(Client* new, char *firstName, char *lastName,
                    char id[ID_LEN+1], char licenseNum[LICENSE_NUM_LEN+1],
                    Date rentDate, Time rentHour,
                    int dailyPrice){
    new->firstName = myStrdup(firstName);
    if(!new->firstName) return -1;
    new->lastName = myStrdup(lastName);
    if(!new->lastName) return -1;
    strcpy(new->id,id);
    strcpy(new->licenseNum,licenseNum);
    new->rentDate = rentDate;
    new->rentHour = rentHour;
    new->dailyPrice = dailyPrice;
    return 0;
}


/* Get 2 generic pointers to client structs and compare their license numbers using strcmp*/
int clientCmpr(void* a, void* b){
    return strcmp(((Client*)a)->id,((Client*)b)->id);
}


/* carFree will get a pointer to a node with a car struct and Free dynamically allocated fields and Node pointer */
int clientFree(Node* node){
    Client* client = (Client*)node->data;
    if(!client){
        return -1;
    }
    FREE(client->firstName);
    FREE(client->lastName);
    FREE(node->data);
    FREE(node);
    return 0;
}

/* Return empty tree struct for client management */
Tree* createClientTree(){
    return createTree(&getClientData,&clientCmpr,&clientFree);
}

/* Compare client ID num to given ID num*/
int clientIDcmpr(void* client, void* id){
    return strcmp(((Client *) client)->id,id);
}

/* Get client details from user, creates a new client and insert it to client tree */
int addNewClient(Tree* clients,Tree* cars){
    Node* newClient =  addNewNode(clients, &clientCmpr,stdin);
    if(newClient) {
        if(!(checkCarAvailable(cars, ((Client *) newClient->data)->licenseNum))){
            removeNode(clients,((Client *) newClient->data)->id,&clientIDcmpr);
            return -1;
        }
    }else{
        printf("Client not added, ID number already exists in tree\n");
        return -1;
    }
    return 0;
}


/* Get data for client and return pointer to a new client struct*/
void* getClientData(void* cpy,FILE* f){
    char firstName[300], lastName[300], id[ID_LEN+1],licenseNum[LICENSE_NUM_LEN+1];
    Date date;
    Time time;
    int dailyPrice;
    Client *client = ALLOC(Client, 1);
    getClientDetails(f, firstName,lastName,id,licenseNum,&date,&time, &dailyPrice);
    createNewClient(client,firstName,lastName,id,licenseNum,date,time,dailyPrice);
    return client;
}

/* Returns the amount of clients with a car with a given creation year */
int clientNumberWithGivenCarYear_rec(Node* root,int year){
    if(!root)
        return 0;
    if(((Car*)(root->data))->creationYear == year && !((Car*)(root->data))->isAvailable){
        return 1 + clientNumberWithGivenCarYear_rec(root->left, year) + clientNumberWithGivenCarYear_rec(root->right,year);
    }
    else{
        return 0 + clientNumberWithGivenCarYear_rec(root->left, year) + clientNumberWithGivenCarYear_rec(root->right,year);
    }
}

/* Returns the amount of clients with a car with a given creation year */
int clientNumberWithGivenCarYear(Tree* tree){
    char buff[300];
    int year,res;
    printf("\nEnter year to check: ");
    while((fscanf(stdin," %d",&year)!=1) || year > CURRENT_YEAR){
        fgets(buff,300,stdin);
        printf("\nInvalid year input. Try again: ");
    }
    if ((tree->elementCount) == 0 ) return 0;
    res = clientNumberWithGivenCarYear_rec(tree->root,year);
    printf("\nNumber of clients with car from %d is %d\n",year,res);
    return res;
}



/* Delete all Clients from given tree*/
int deleteAllClients(Tree* clients,Tree* cars){
    freeTree(clients);
    setAvailableAll(cars);
    return 0;
}

/* Compare string license number to a struct car license number*/
int idCmpr(void* client, void* id){
    return strcmp(((Client*)client)->id,(char*)id);
}

/* Delete client with given ID number from tree */
int deleteClient(Tree* clients,Tree* cars){
    char id[ID_LEN+1], temp[300];
    LList * node;
    if(!clients){
        printf("\nError: NULL tree pointer.\n");
        return -1;
    }
    if(clients->elementCount == 0){
        printf("\nClient Tree is empty.\n");
        return 0;
    }
    printf("\nEnter client ID number: ");
    while (getStrExactSize(temp,ID_LEN,stdin)!=0 || !strIsDigit(temp,ID_LEN)) {
        printf("\nClient ID number must be exactly %d digits (digits only), try again: ",ID_LEN);
    }
    strcpy(id, temp);
    node = findNode(clients,id,&idCmpr);
    if(!node){
        printf("\nNo client with given ID was found\n");
        return -1;
    }
    setAvailable(cars,((Client*)node->data)->licenseNum);
    FREE(node);
    removeNode(clients,id,&idCmpr);
    return 0;
}

/* Prints a single client */
void printClient(void * vClient){
    Client* client = (Client*)vClient;
    printf("%-20s %-20s %-20s %-20d %02d/%02d/%4d      %02d:%02d \n",client->firstName,client->lastName,client->id,
           client->dailyPrice, client->rentDate.day,client->rentDate.month, client->rentDate.year,
           client->rentHour.hour,client->rentHour.minute);
}

/* Print all clients in tree */
void printClients(Tree* tree){
    if(!tree){
        printf("\nError: NULL tree pointer\n");
        return;
    }
    if(tree->elementCount == 0){
        printf("\nClient tree is empty\n");
        return;
    }
    printf("\n\033[1;31m%-20s %-20s %-20s %-20s %s     %s\n\033[0m",
           "First-name", "Last-name", "ID", "Daily-price", "Rental-date", "Rental-Time");
    printTree(tree,&printClient);
}

/* Compare between two dates */
int dateCompare(void* client, void* d2){
    Date d1 = ((Client*)client)->rentDate;
    if(d1.year != ((Date *) d2)->year){
        return -1;
    }
    if(d1.month != ((Date *) d2)->month){
        return -1;
    }
    if(d1.day != ((Date *) d2)->day){
        return -1;
    }
    return 0;
}

/* Gets a client tree, user chooses between search by ID to search by Date. Returns client linked list if clients are found */
LList* findClient(Tree* clients){
    int choice;
    char temp[300], id[ID_LEN-1];
    LList* client_list = NULL;
    Date date;
    printf("  1. By ID\n  2. By date\n");
    printf("Enter you choice: \n");
    while (scanf(" %d", &choice) != 1 || choice < 1 || choice > 2){
        fgets(temp,300,stdin);
        printf("Invalid input. try again: \n");
    }
    fgets(temp,300,stdin);
    if (choice == 1){
        printf("\nEnter ID:");
        while (getStrExactSize(temp,ID_LEN,stdin)!=0 || !strIsDigit(temp,ID_LEN)) {
            printf("\nClient ID number must be exactly %d digits (digits only), try again: ",ID_LEN);
        }
        strcpy(id, temp);
        client_list = findNode(clients, id, &idCmpr);
        return client_list;
    }
    if (choice == 2){
        getDate(&date, stdin);
        client_list = findNode(clients, &date, &dateCompare);
        return client_list;
    }
    return NULL;
}


/* Gets a clients tree and prints all the clients who rented a car in a given date */
int printClientCarsForGivenRentDate(Tree* clients){
    LList *client_list = NULL, *temp;
    Date date;
    getDate(&date, stdin);
    client_list = findNode(clients, &date, &dateCompare);
    temp = client_list;
    if(!temp){
        printf("\nNo clients found.\n");
        return -1;
    }
    printf("\n\033[1;31m%-20s %-20s %-20s %-20s %s     %s\n\033[0m",
           "First-name", "Last-name", "ID", "Daily-price", "Rental-date", "Rental-Time");
    while(temp){
        printClient(temp->data);
        temp = temp->next;
    }
    freeLinkedList(&client_list);
    return 0;

}




