#include "Car.h"
#include "Supplier.h"
#include "Client.h"

/* Prints menu */
void printOptions(){
    printf("\n1.  Add new car\n");
    printf("2.  Add new client\n");
    printf("3.  Add new supplier\n");
    printf("4.  Print 3 greatest suppliers\n");
    printf("5.  Print all suppliers\n");
    printf("6.  Print all clients\n");
    printf("7.  Number of cars with given capacity\n");
    printf("8.  Print clients' cars with given rent date\n");
    printf("9.  Find Client by ID\\rent date\n");
    printf("10. Number of clients with cars from given year\n");
    printf("11. Print Average of sum of all deals made with suppliers.\n");
    printf("12. Delete client\n");
    printf("13. Delete car\n");
    printf("14. Delete supplier\n");
    printf("15. Delete all cars\n");
    printf("16. Delete all clients\n");
    printf("17. Delete all suppliers\n");
    printf("0.  Exit\n");
}

/* Gets action number as presented in the menu and performs */
void action(Tree* cars,Tree* suppliers,Tree* clients,int choice){
    if(choice==1){
        addNewCar(cars);
        return;
    }
    if(choice==2){
        addNewClient(clients,cars);
        return;
    }
    if(choice==3){
        addNewSupplier(suppliers);
        return;
    }
    if(choice==4){
        char threeGreatest[3][SUPPLIER_NUM_LEN+1];
        int i = 0;
        if (threeGreatestSuppliers(suppliers,threeGreatest) == -1) {
            return;
        }
        printf("The license numbers for the suppliers with highest sum of deals are: \n");
        for (; i<3; i++){
            if ( (threeGreatest[i][0] >= '0') && (threeGreatest[i][0] <= '9') ){
                printf("\033[1;31m%s\n\033[0m",threeGreatest[i]);
            }
        }
        return;
    }
    if (choice==5){
        printSuppliers(suppliers);
        return;
    }
    if(choice==6){
        printClients(clients);
        return;
    }
    if(choice==7){
        carNumberWithGivenCapacity(cars);
        return;
    }

    if(choice==8){
        printClientCarsForGivenRentDate(clients);
        return;
    }

    if(choice==9){
        LList *head, *temp;
        head = findClient(clients);
        if(!head){
            printf("No clients found.\n");
            return;
        }
        printf("\033[1;31m%-20s %-20s %-20s %-20s %s     %s\n\033[0m",
               "First-name", "Last-name", "ID", "Daily-price", "Rental-date", "Rental-Time");
        temp = head;
        while(temp){
            printClient(temp->data);
            temp = temp->next;
        }
        freeLinkedList(&head);
        return;
    }

    if(choice == 10){
        clientNumberWithGivenCarYear(cars);
        return;
    }
    if(choice == 11){
        double avg = 0;
        avg = averageOfSupplierMoney(suppliers);
        printf("The average for sum of all deals made with suppliers is: %f\n",avg);
        return;
    }
    if(choice==12){
        deleteClient(clients,cars);
        return;
    }
    if(choice==13){
        deleteCar(cars);
        return;
    }
    if(choice==14){
        deleteSupplier(suppliers);
        return;
    }
    if(choice==15){
        deleteAllCars(cars);
    }
    if(choice==16){
        deleteAllClients(clients,cars);
    }
    if(choice==17){
        deleteAllSuppliers(suppliers);
    }

}


/*
 * This program runs and manages Car rental company data base and inventory
 *
 */

int main(){
    Tree *carTree = createCarTree();
    Tree * supplierTree = createSupplierTree();
    Tree* clientTree = createClientTree();
    int choice;
    char buff[300];
    while(1) {
        printOptions();
        printf("Enter your choice: ");
        while (scanf("%d", &choice) != 1) {
            fgets(buff,300,stdin);
            printf("Not a number, try again: ");
        }
        fgets(buff,300,stdin);
        if (choice < 0 || choice > 17){
            printf("Choice number not available, try again.\n");
            continue;
        }
        if(choice==0)
            break;
        action(carTree,supplierTree,clientTree,choice);
    }
    if(clientTree->elementCount!=0){
        deleteAllClients(clientTree,carTree);
    }
    if(carTree->elementCount!=0){
        deleteAllCars(carTree);
    }
    if(supplierTree->elementCount!=0){
        deleteAllSuppliers(supplierTree);
    }
    FREE(carTree);
    FREE(supplierTree);
    FREE(clientTree);
    check_for_exit();
    return 0;
}
