

#include "Supplier.h"

/* functions below are not available outside of this file */
int suppliercmp(void* sup1,void* sup2);
int supplierFree(Node* node);
int supplierLicenseCmp(void* sup, void* license);
void printSupplier(void* supplier);
double addSupplierdeals(void* sup,double num);
int threeGreatestSuppleirs_REC(Node* root,char list[3][SUPPLIER_NUM_LEN+1],unsigned long max_sums[3]);
/* functions above are not available outside of this file */

/* Gets a pointer to a new supplier and supplier details and creates a new supplier */
int createNewSupplier(Supplier* new,
                      char license_num[LICENSE_NUM_LEN+1],
                      char* name,
                      char* phone,
                      int num_of_deals,
                      unsigned long deals_sum){
    new->name = myStrdup(name);
    if(!new->name) return -1;
    strcpy(new->license_num,license_num);
    strcpy(new->phone_num,phone);
    new->num_of_deals = num_of_deals;
    new->deals_sum = deals_sum;
    return 0;
}

/* Compare between two suppliers license number */
int suppliercmp(void* sup1,void* sup2){
    return strcmp(((Supplier*)sup1)->license_num,((Supplier*)sup2)->license_num);
}
/* Function will get pointer to node containing supplier and free all dynamically allocated memory blocks*/
int supplierFree(Node* node){
    Supplier* supplier = (Supplier*)node->data;
    if(!node){
        return -1;
    }
    if(node->data){
        FREE(supplier->name);
        FREE(node->data);
    } else {
        printf("\nError: NULL data pointer\n");
    }
    FREE(node);
    return 0;
}

/* Returns pointer to an empty Supplier tree */
Tree* createSupplierTree(){
    Tree* tree = createTree(&getSupplierData,&suppliercmp,&supplierFree);
    return tree;
}

/* Function will get data for new supplier from user*/
void* getSupplierData(void* data,FILE* f){
    char license_num[SUPPLIER_NUM_LEN+1], name[300], phone[PHONE_LEN+1];
    int num_of_deals;
    unsigned long deals_sum;
    Supplier * supplier = ALLOC(Supplier ,1);
    getSupplierDetails(f,license_num,name,phone,&num_of_deals,&deals_sum);
    createNewSupplier(supplier,license_num,name,phone,num_of_deals,deals_sum);
    return supplier;
}

/* Function will get pointer to supplier struct and compare it to given license number*/
int supplierLicenseCmp(void* sup, void* license){
    return strcmp(((Supplier*)sup)->license_num,(char*)license);
}

/* Get supplier details from user, creates a new supplier and insert it to suppliers tree */
int addNewSupplier(Tree* tree){
    if(!addNewNode(tree,&supplierLicenseCmp,stdin)){
        printf("Supplier not added, given supplier license number already exists in system\n");
        return -1;
    }
    return 0;
}

/* Print data for single supplier*/
void printSupplier(void* supplier) {
    Supplier* sup = (Supplier*)supplier;
    printf("%-20s %-20s %-20s %-20d %lu\n", sup->license_num, sup->name, sup->phone_num,
           sup->num_of_deals, sup->deals_sum);
}

/* Print all suppliers in given supplier tree */
int printSuppliers(Tree *tree){
    if(!tree){
        printf("\nError: NULL tree pointer\n");
        return -1;
    }
    if(tree->elementCount == 0){
        printf("\nNo supliers in tree\n");
        return 0;
    }
    printf("\n\033[1;31m\n%-20s %-20s %-20s %-20s %s\033[0m", "License-num", "Name", "Phone-num", "Num-of-Deals", "Sum-of-Deals");
    printTree(tree,&printSupplier);
    return 0;
}

/* Get supplier license number and delete supplier with given supplier number from tree */
int deleteSupplier(Tree* tree){
    char temp[300], licenseNum[SUPPLIER_NUM_LEN];
    if(!tree){
        printf("\nError: NULL tree pointer.\n");
        return -1;
    }
    if(tree->elementCount == 0){
        printf("\nCar Tree is empty.\n");
        return 0;
    }
    printf("\nEnter supplier license number for supplier you wish to delete: ");
    while ((getStrExactSize(temp,SUPPLIER_NUM_LEN,stdin)!=0) || !strIsDigit(temp,SUPPLIER_NUM_LEN)) {
        printf("\nsupplier license number must be exactly %d digits (digits only), try again: ",SUPPLIER_NUM_LEN);
    }
    strcpy(licenseNum,temp);
    removeNode(tree,licenseNum,&supplierLicenseCmp);
    return 0;
}

/* Delete all suppliers from a given supplier tree */
int deleteAllSuppliers(Tree* tree){
    freeTree(tree);
    return 0;
}

/* Add given supplier deals sum to num*/
double addSupplierdeals(void* sup,double num){
    return ((double)(((Supplier*)sup)->deals_sum))+num;
}

/* Function will calculate and return average of total sum of deals with all suppliers */
double averageOfSupplierMoney(Tree* tree){
    return averageKey(tree,&addSupplierdeals);
}

/* Recursively search and insert the three greatest suppliers to given array (list) */
int threeGreatestSuppleirs_REC(Node* root,char list[3][SUPPLIER_NUM_LEN+1],unsigned long max_sums[3]){
    Supplier* supplier;
    if(!root)
        return 0;
    threeGreatestSuppleirs_REC(root->left,list,max_sums);
    threeGreatestSuppleirs_REC(root->right,list,max_sums);
    supplier = (Supplier*)root->data;
    if(supplier->deals_sum > max_sums[0]){
        max_sums[1] = max_sums[0];
        max_sums[2] = max_sums[1];
        max_sums[0] = supplier->deals_sum;
        strcpy(list[2],list[1]);
        strcpy(list[1],list[0]);
        strcpy(list[0],supplier->license_num);
        return 0;
    }
    if(supplier->deals_sum > max_sums[1]){
        max_sums[2] = max_sums[1];
        max_sums[1] = supplier->deals_sum;
        strcpy(list[2],list[1]);
        strcpy(list[1],supplier->license_num);
        return 0;
    }
    if(supplier->deals_sum > max_sums[2]){
        max_sums[2] = supplier->deals_sum;
        strcpy(list[2],supplier->license_num);
        return 0;
    }
    return 0;
}

/* Gets a pointer to suppliers tree and a 3-suppliers-array and inserts the three suppliers with the largest deals-sum to the array */
int threeGreatestSuppliers(Tree* tree,char list[3][SUPPLIER_NUM_LEN+1]){
    unsigned long max_sums[3] = {0,0,0};
    if(!tree){
        printf("\nError: NULL tree pointer.\n");
        return -1;
    }
    if(tree->elementCount == 0){
        printf("\nNo suppliers in list.\n");
        return -1;
    }
    threeGreatestSuppleirs_REC(tree->root,list,max_sums);
    return 0;
}










