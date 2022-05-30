

#include "dateTime.h"

/* Creates and initializes new Date struct and returns it */
Date createNewDate(int year, int month, int day){
    Date ret;
    ret.year = year; ret.month = month; ret.day = day;
    return ret;
}

/* Creates and initializes new Time struct and returns it */
Time createNewTime(int hour, int minute){
    Time ret;
    ret.hour = hour; ret.minute = minute;
    return ret;
}