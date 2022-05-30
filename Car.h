

#ifndef HW_7_CAR_H
#define HW_7_CAR_H
#include "getinput.h"
#include "BinarySearchTree.h"


typedef struct CCar {
    char licenseNum[LICENSE_NUM_LEN+1];
    char frameNum[FRAME_NUM_LEN+1];
    char *manufacturer;
    char *model;
    char *color;
    int creationYear;
    int yearOnRoad;
    unsigned int supplierPrice;
    unsigned int curr_price;
    unsigned int engineVolume;
    bool isAvailable;
} Car;

/* Gets a pointer to a new car and car details and creates a new car */
int createNewCar(Car* new, const char* licenseNum,const char* frame_num, char* manufacturer,
                 char* model, char* color, int creationYear, int yearOnRoad,
                 unsigned int supplierPrice, unsigned int price, unsigned int engineVolume);

/* Get data for car and return pointer to a new struct car */
void* getCarData();

/* Return empty tree struct for car management */
Tree* createCarTree();

/* Get car details from user, creates a new car and insert it to cars tree */
int addNewCar(Tree* tree);

/* Return number of cars in database with a given engine capacity */
int carNumberWithGivenCapacity(Tree* tree);

/* Delete car with given license number from tree */
int deleteCar(Tree* tree);

/* Delete all cars from given tree */
int deleteAllCars(Tree* tree);

/* Check if car with given license number is available to rent */
bool checkCarAvailable(Tree* tree, char license[LICENSE_NUM_LEN+1]);

/* Gets a car tree and a car license number, if the car exists in the tree, set it as available for rent */
int setAvailable(Tree* tree, char* license);

/* Gets a car tree a sets all cars in the tree to available for rent */
int setAvailableAll(Tree* cars);

/* printCar gets generic pointer to a struct car and prints the car data */
void printCar(void* data);

/* Use the generic printCar function and the binary printTree function to print all data for all cars in tree */
void printCarTree(Tree* tree);

/* Find car node by license number */
LList *findLicense(Tree* tree);

/* Get capacity to check from user, and return number of cars in tree with given capacity*/
int carNumberWithGivenCapacity(Tree* tree);

#endif
