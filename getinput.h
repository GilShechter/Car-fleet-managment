

#ifndef HW_7_GETINPUT_H
#define HW_7_GETINPUT_H
#define ID_LEN 9
#define LICENSE_NUM_LEN 7
#define CURRENT_YEAR 2021
#define FRAME_NUM_LEN 5
#define SUPPLIER_NUM_LEN 10
#define PHONE_LEN 10
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include "inputcheck.h"
#include "matam.h"
#include "dateTime.h"
#include "BinarySearchTree.h"

/* Get all Car details from user */
int getCarDetails(FILE* f,char* licenseNum, char* frame_num, char* manufacturer,
                  char* model, char* color, int* creationYear, int* yearOnRoad,
                  unsigned int* supplierPrice, unsigned int* price, unsigned int* engineVolume);

/* Get all Client details from user*/
int getClientDetails(  FILE* f, char* firstName, char* lastName, char* id,
                       char* licenseNum, Date* rentDate, Time* rentHour,
                       int* dailyPrice);

/* Get all Supplier details from user*/
int getSupplierDetails(FILE* f,char* license_num,
                       char* name,
                       char* phone_num,
                       int* num_of_deals,
                       unsigned long* deals_sum);

/* Gate date details from user */
int getDate(Date* date,FILE* f);

/* Get a String from user in the exact size*/
int getStrExactSize(char* str,int size,FILE* f);

/*allocate memory and duplicate given string, return pointer to new duplicate string*/
char* myStrdup(char* str);

#endif


