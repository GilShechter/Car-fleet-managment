

#ifndef HW_7_DATETIME_H
#define HW_7_DATETIME_H

typedef struct Date{
    int year,month,day;
}Date;

typedef struct Time{
    int hour,minute;
}Time;

/* Creates and initializes new Date struct and returns it */
Date createNewDate(int year, int month, int day);

/* Creates and initializes new Time struct and returns it */
Time createNewTime(int hour, int minute);

#endif
