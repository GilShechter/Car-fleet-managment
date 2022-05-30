

#ifndef HW_7_SUPPLIER_H
#define HW_7_SUPPLIER_H
#include "getinput.h"

typedef struct SSupplier{
    char license_num[SUPPLIER_NUM_LEN+1];
    char *name;
    char phone_num[PHONE_LEN+1];
    int num_of_deals;
    unsigned long deals_sum;
} Supplier;


/* Returns pointer to an empty Supplier tree */
Tree* createSupplierTree();

/* Get supplier details from user, creates a new supplier and insert it to suppliers tree */
int addNewSupplier(Tree* tree);

/* Gets a pointer to a new supplier and supplier details and creates a new supplier */
int createNewSupplier(Supplier* new,
                      char license_num[LICENSE_NUM_LEN+1],
                      char* name,
                      char* phone,
                      int num_of_deals,
                      unsigned long deals_sum);



/* Function will get data for new supplier from user */
void* getSupplierData(void* data,FILE* f);

/* Function will calculate and return average of total sum of deals with all suppliers */
double averageOfSupplierMoney(Tree* tree);

/* Gets a pointer to suppliers tree and a 3-suppliers-array and inserts the three suppliers with the largest deals-sum to the array */
int threeGreatestSuppliers(Tree* tree,char list[3][SUPPLIER_NUM_LEN+1]);

/* Print all suppliers in given supplier tree */
int printSuppliers(Tree *tree);

/* Get supplier license number and delete supplier with given supplier number from tree */
int deleteSupplier(Tree* tree);

/* Delete all suppliers from a given supplier tree */
int deleteAllSuppliers(Tree* tree);

#endif
