

#include "Car.h"


/* functions below are not available outside of this file */
LList *findLicense_given(Tree* tree,char license[LICENSE_NUM_LEN+1]);
int carFree(Node* node);
int carcmpr(void* a, void* b);
int licensecmp(void* car, void* license);
int carNumberWIthGivenCapacity_rec(Node* root,int cap);
LList *findLicense_given(Tree* tree,char license[LICENSE_NUM_LEN+1]);
void setAvailableAll_REC(Node* root);
/* functions above are not available outside of this file */


/* Gets a pointer to a new car and car details and creates a new car */
int createNewCar(Car* new, const char* licenseNum,const char* frame_num, char* manufacturer,
                 char* model,char* color, int creationYear, int yearOnRoad,
                 unsigned int supplierPrice, unsigned int price, unsigned int engineVolume){
    strcpy(new->licenseNum,licenseNum);
    strcpy(new->frameNum,frame_num);
    new->manufacturer = myStrdup(manufacturer);
    if(!new->manufacturer) return -1;
    new->model = myStrdup(model);
    if(!new->model) return -1;
    new->color = myStrdup(color);
    if(!new->color) return -1;
    new->creationYear = creationYear;
    new->yearOnRoad = yearOnRoad;
    new->supplierPrice = supplierPrice;
    new->curr_price = price;
    new->engineVolume = engineVolume;
    new->isAvailable = true;
    return 0;
}

/* carFree will get a pointer to a node with a car struct and Free dynamically allocated fields and Node pointer */
int carFree(Node* node){
    Car* car = (Car*)node->data;
    if(!car){
        return -1;
    }
    if(node->data) {
        FREE(car->manufacturer);
        FREE(car->model);
        FREE(car->color);
        FREE(node->data);
    }
    FREE(node);
    return 0;
}

/* carcmpr will get 2 generic pointers to struct cars and compare their license numbers using strcmp*/
int carcmpr(void* a, void* b){
    return strcmp(((Car*)a)->licenseNum,((Car*)b)->licenseNum);
}

/* Return empty car tree struct */
Tree* createCarTree(){
    return createTree(&getCarData,&carcmpr,&carFree);
}

/* Get data for car and return pointer to a new struct car*/
void* getCarData(void* cpy,FILE* f){
    char license[LICENSE_NUM_LEN+1], frame[FRAME_NUM_LEN+1], manu[300],
            model[300], color[300];
    int create_year,yearOnRoad;
    unsigned int sup_Price,curr_price, volume;
    Car* car = ALLOC(Car,1);
    getCarDetails(f,license,frame,manu,model,color,&create_year,&yearOnRoad,&sup_Price,&curr_price,&volume);
    createNewCar(car,license,frame,manu,model,color,create_year,yearOnRoad,sup_Price,curr_price,volume);
    return car;

}

/* Compare string license number to a struct car license number*/
int licensecmp(void* car, void* license){
    return strcmp(((Car*)car)->licenseNum,(char*)license);
}


/* Get car details from user, creates a new car and insert it to cars tree */
int addNewCar(Tree* tree){
    if(!addNewNode(tree, &carcmpr,stdin)){
        printf("Car was not added, license number already exists.\n");
        return -1;
    }
    return 0;
}

/* printCar gets generic pointer to a struct car and prints the car data */
void printCar(void* data){
    Car* car = (Car*)data;
    printf("%-10s %-7s %-10s %-7s %-7s\n",car->licenseNum,car->frameNum,car->manufacturer,car->model,car->color);
}

/* Use the generic printCar function and the binary printTree function to print all data for all cars in tree */
void printCarTree(Tree* tree){
    printTree(tree,&printCar);
}

/* Delete car with given license number from tree */
int deleteCar(Tree* tree){
    char license[LICENSE_NUM_LEN+1], temp[300];
    if(!tree){
        printf("\nError: NULL tree pointer.\n");
        return -1;
    }
    if(tree->elementCount == 0){
        printf("\nCar Tree is empty.\n");
        return 0;
    }
    printf("\nEnter car license number: ");
    while (getStrExactSize(temp,LICENSE_NUM_LEN,stdin)!=0 || !strIsDigit(temp,LICENSE_NUM_LEN)) {
        printf("\nCar license number must be exactly %d digits (digits only), try again: ",LICENSE_NUM_LEN);
    }
    strcpy(license, temp);
    removeNode(tree,license,&licensecmp);
    return 0;
}

/* Find car with a given license number */
LList *findLicense(Tree* tree){
    char temp[300],licenseNum[LICENSE_NUM_LEN];
    LList* head;
    printf("\nEnter license number: ");
    while (getStrExactSize(temp,LICENSE_NUM_LEN,stdin)!=0 || !strIsDigit(temp,LICENSE_NUM_LEN)) {
        printf("\nCar license number must be exactly %d digits (digits only), try again: ",LICENSE_NUM_LEN);
    }
    strcpy(licenseNum, temp);
    head = findNode(tree,licenseNum,&licensecmp);
    return head;
}

/* Find number of cars with a given capacity recursively */
int carNumberWIthGivenCapacity_rec(Node* root,int cap){
    int res_l,res_r;
    if(!root)
        return 0;
    res_l = carNumberWIthGivenCapacity_rec(root->left,cap);
    res_r = carNumberWIthGivenCapacity_rec(root->right,cap);
    if(((Car*)(root->data))->engineVolume == cap){
        return res_l+res_r+1;
    }
    return res_l+res_r;
}
/* Get engine capacity from user and return amount of cars in tree with given capacity */
int carNumberWithGivenCapacity(Tree* tree){
    char buff[300];
    int cap,res;
    printf("\nEnter capacity to check: ");
    while((fscanf(stdin," %d",&cap)!=1) || cap > 9999){
        fgets(buff,300,stdin);
        printf("\nEngine volume must be a number under 9999, try again: ");
    }
    res = carNumberWIthGivenCapacity_rec(tree->root,cap);
    printf("\nnumber of cars with engine capacity of %d is %d\n",cap,res);
    return res;
}

/* Delete all cars from given tree */
int deleteAllCars(Tree* tree){
    freeTree(tree);
    return 0;
}

/* Find car with a given license number */
LList *findLicense_given(Tree* tree,char license[LICENSE_NUM_LEN+1]){
    LList* head;
    head = findNode(tree,license,&licensecmp);
    return head;
}


/* Gets a car tree and a car license number, if the car exists in the tree, set it as available for rent */
int setAvailable(Tree* tree, char* license){
    LList* node = NULL;
    if(!tree){
        printf("\nError: NULL tree pointer\n");
        return -1;
    }
    if(tree->elementCount == 0){
        printf("\nNo cars in tree\n");
        return -1;
    }
    node = findLicense_given(tree,license);
    if(!node){
        printf("\nNo car with given license number was found\n");
        return -1;
    }
    ((Car*)node->data)->isAvailable = true;
    freeLinkedList(&node);
    return 0;
}



/* Check if car with given license number is available to rent*/
bool checkCarAvailable(Tree* tree, char license[LICENSE_NUM_LEN+1]){
    LList* node;
    if(!tree){
        printf("\nError: NULL tree pointer\n");
        return -1;
    }
    if(tree->elementCount == 0){
        printf("\nNo cars in tree\n");
        return -1;
    }
    node = findLicense_given(tree,license);
    if(!node){
        printf("\nNo car with given license number was found.\n");
        return false;
    }
    if(!((Car*)node->data)->isAvailable){
        printf("Car not available.\n");
        freeLinkedList(&node);
        return false;
    }
    ((Car*)node->data)->isAvailable = false;
    freeLinkedList(&node);
    return true;
}

/* Gets a car tree a sets all cars in the tree to available for rent recursively */
void setAvailableAll_REC(Node* root){
    if(!root)
        return;
    ((Car*)root->data)->isAvailable = true;
    setAvailableAll_REC(root->right);
    setAvailableAll_REC(root->left);
}

/* Gets a car tree a sets all cars in the tree to available for rent */
int setAvailableAll(Tree* tree){
    if(!tree){
        printf("\nError: NULL tre pointer\n");
        return -1;
    }
    if(tree->elementCount == 0){
        printf("\nNo cars in tree\n");
        return -1;
    }
    setAvailableAll_REC(tree->root);
    return 0;
}

