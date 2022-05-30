

#include "inputcheck.h"


/* Return if year is leap */
bool isLeapYear(int year){
    if((year%4)==0){
        if((year%100)==0){
            if((year%400)==0){
                return true;
            }
            else
                return false;
        }
        else
            return true;
    }
    return false;
}

/* Check if a String is in a certain length */
int checkStrLen(const char* str,int len){
    int strLen = strlen(str);
    if(strLen>len)
        return 1;
    else if(strLen==len)
        return 0;
    else
        return -1;
}

/* Returns if a char is a digit */
bool strIsDigit(const char* str,int size){
    int i=0;
    for(;i<size;i++){
        if((str[i] < '0') || (str[i] > '9'))
            return false;
    }
    return true;
}

/* Return if a char is alpha */
bool strIsAlpha(const char* str, int size){
    int i = 0;
    for(;i<size;i++){
        if(((str[i] < 'A') || (str[i] >'Z')) && ((str[i] < 'a') || (str[i] >'z')))
            return false;
    }
    return true;
}

/* Returns if Date details are valid */
bool checkDateDetails(int year, int month, int day){
    if((year < CURRENT_YEAR-10)&&(year>CURRENT_YEAR+10)){
        printf("Year should be in range %d - %d", CURRENT_YEAR-10, CURRENT_YEAR+10);
        return false;
    }
    if((month<1) || (month>12)){
        puts("Invalid month value. ");
        return false;
    }
    if((month==1) || (month==3) || (month==5) || (month==7)
       ||  (month==8) || (month==10) || (month==12)){
        if((day < 1) || (day > 31)){
            puts("Invalid date. ");
            return false;
        }
    }
    else if(month==2){
        if(isLeapYear(year)){
            if((day<1) || (day>29)){
                puts("Invalid date. ");
                return false;
            }
        }
        else{
            if((day<1) || (day>28)){
                puts("Invalid date. ");
                return false;
            }
        }
    }
    else{
        if((day<1) || (day>30)){
            puts("Invalid date. ");
            return false;
        }
    }
    return true;
}

/* Returns if Time details are valid */
bool checkTimeDetails(int hour, int minute){
    if((hour<1) || (hour>24)){
        puts("Invalid time. ");
        return false;
    }
    if((minute<0) || (minute>59)){
        puts("Invalid time. ");
        return false;
    }
    return true;
}
