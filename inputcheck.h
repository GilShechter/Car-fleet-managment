

#ifndef HW_7_INPUTCHECK_H
#define HW_7_INPUTCHECK_H
#define ID_LEN 9
#define LICENSE_NUM_LEN 7
#define CURRENT_YEAR 2021
#define LICENSE_NUM_LEN 7
#define FRAME_NUM_LEN 5
#define SUPPLIER_NUM_LEN 10
#define PHONE_LEN 10
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

/* Returns if Date details are valid */
bool checkDateDetails(int year, int month, int day);

/* Returns if Time details are valid */
bool checkTimeDetails(int hour, int minute);


/* Check if a String is in a certain length */
int checkStrLen(const char* str,int len);

/* Returns if a char is a digit */
bool strIsDigit(const char* str,int size);

/* Return if a char is alpha */
bool strIsAlpha(const char* str, int size);

/* Return if year is leap */
bool isLeapYear(int year);

#endif
