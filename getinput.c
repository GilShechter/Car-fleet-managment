
#include "getinput.h"

/* Get all Car details from user */
int getCarDetails(FILE* f,char* licenseNum, char* frame_num, char* manufacturer,
                  char* model, char* color, int* creationYear, int* yearOnRoad,
                  unsigned int* supplierPrice, unsigned int* price, unsigned int* engineVolume) {
    char temp[300];
    printf("\nEnter car license number: ");
    while (getStrExactSize(temp,LICENSE_NUM_LEN,f)!=0 || !strIsDigit(temp,LICENSE_NUM_LEN)) {
        printf("\nCar license number must be exactly %d digits (digits only), try again: ",LICENSE_NUM_LEN);
    }
    strcpy(licenseNum, temp);
    printf("\nEnter car frame number: ");
    while (getStrExactSize(temp,FRAME_NUM_LEN,f)!=0 || !strIsDigit(temp,FRAME_NUM_LEN)) {
        printf("\nCar frame number must be exactly %d digits (digits only), try again: ",FRAME_NUM_LEN);
    }
    strcpy(frame_num,temp);
    printf("\nEnter car manufacturer name: ");
    fgets(manufacturer,300,f);
    manufacturer[strcspn(manufacturer,"\r\n")] = 0;
    printf("\nEnter car model: ");
    fgets(model,300,f);
    model[strcspn(model,"\r\n")] = 0;
    printf("\nPlease enter car color: ");
    fgets(color,300,f);
    color[strcspn(color,"\r\n")] = 0;
    printf("\nEnter car manufacturing year: ");
    while((fscanf(f," %d",creationYear)!=1) || *creationYear<1990 || *creationYear > CURRENT_YEAR){
        fgets(temp,300,f);
        printf("\nYear must be a number between 1990 and %d, try again: ",CURRENT_YEAR);
    }
    printf("\nenter year the car got on the road: ");
    while((fscanf(f," %d",yearOnRoad)!=1) || *yearOnRoad<1990 || *yearOnRoad > CURRENT_YEAR){
        fgets(temp,300,f);
        printf("\nYear must be a number between 1990 and %d, try again: ",CURRENT_YEAR);
    }
    printf("\nEnter supplier price for car: ");
    while((fscanf(f," %u",supplierPrice)!=1) || *supplierPrice > 9999999){
        fgets(temp,300,f);
        printf("\nSupplier price must be a number under 9999999, try again: ");
    }
    printf("\nEnter current car price: ");
    while((fscanf(f," %u",price)!=1) || *price > 9999999){
        fgets(temp,300,f);
        printf("\nCurrent price must be a number under 9999999, try again: ");
    }
    printf("\nEnter car engine volume: ");
    while((fscanf(f," %u",engineVolume)!=1) || *engineVolume > 9999){
        fgets(temp,300,f);
        printf("\nEngine volume must be a number under 9999, try again: ");
    }
    printf("\n");
    fgets(temp,300,f);
    return 0;
}

/* Get all Supplier details from user */
int getSupplierDetails(FILE* f,char* license_num,
                       char* name,
                       char* phone_num,
                       int* num_of_deals,
                       unsigned long* deals_sum){
    char temp[300];
    printf("\nEnter supplier license number: ");
    while ((getStrExactSize(temp,SUPPLIER_NUM_LEN,f)!=0) || !strIsDigit(temp,SUPPLIER_NUM_LEN)) {
        printf("\nsupplier license number must be exactly %d digits (digits only), try again: ",SUPPLIER_NUM_LEN);
    }
    strcpy(license_num,temp);
    printf("\nEnter supplier name: ");
    fgets(name,300,f);
    name[strcspn(name,"\r\n")] = 0;
    printf("\nEnter supplier phone number: ");
    while (getStrExactSize(temp,PHONE_LEN,f)!=0 || !strIsDigit(temp,PHONE_LEN)) {
        printf("\nphone number must be exactly %d digits (digits only), try again: ",PHONE_LEN);
    }
    strcpy(phone_num,temp);
    printf("\nenter number of deals with supplier: ");
    while((fscanf(f," %d",num_of_deals)!=1) || *num_of_deals < 10000 || *num_of_deals > 99999){
        fgets(temp,300,f);
        printf("\nnumber of deals with supplier must be an integer between 10000 and 99999, try again: ");
    }
    printf("\nenter total sum of deals with supplier: ");
    while((fscanf(f," %lu",deals_sum)!=1) || *deals_sum < 1000000000 || *deals_sum > 9999999999){
        fgets(temp,300,f);
        printf("\nsum of deals with supplier must be between 1000000000 and 9999999999: ");
    }
    printf("\n");
    fgets(temp,300,f);
    return 0;
}

/* Get all Client details from user */
int getClientDetails(FILE* f, char *first_name, char *last_name, char* id, char *license_num,
                     Date *rentDate, Time *rentHour, int *daily_price){
    char temp[300], check;
    int hour, minute;
    printf("\nEnter client first name: ");
    fgets(first_name,300,f);
    first_name[strcspn(first_name,"\r\n")] = 0;
    while(!strIsAlpha(first_name,strlen(first_name))){
        printf("\nClient name must be latin characters only, enter name again: ");
        fgets(first_name,300,f);
        first_name[strcspn(first_name,"\r\n")] = 0;
    }
    printf("\nEnter client last name: ");
    fgets(last_name,300,f);
    last_name[strcspn(last_name,"\r\n")] = 0;
    while (!strIsAlpha(last_name,strlen(last_name))) {
        printf("\nClient last name must be latin characters only, enter name again: ");
        fgets(last_name,300,f);
        last_name[strcspn(last_name,"\r\n")] = 0;
    }
    printf("\nEnter client ID: ");
    while (getStrExactSize(temp,ID_LEN,f)!=0 || !strIsDigit(temp,ID_LEN)) {
        printf("\nClient ID number must be exactly %d digits (digits only), try again: ",ID_LEN);
    }
    strcpy(id,temp);
    printf("\nEnter license number of car to be rented: ");
    while (getStrExactSize(temp,LICENSE_NUM_LEN,f)!=0) {
        printf("\nCar license number must be exactly %d digits, try again: ",LICENSE_NUM_LEN);
    }
    strcpy(license_num,temp);
    printf("\nEnter rent date and time details: ");
    getDate(rentDate,f);
    while(1){
        printf("\nEnter rent time (HH:MM): ");
        while((fscanf(f," %d:%d%c",&hour,&minute,&check)!=3) || ((check!='\n') && (check!= '\r'))){
            fgets(temp,300,f);
            printf("\nInvalid input, try again: ");
        }
        if(!checkTimeDetails(hour,minute))
            continue;
        break;
    }
    rentHour->hour = hour;
    rentHour->minute = minute;
    printf("\nEnter daily price for car: ");
    while((fscanf(f," %d",daily_price)!=1) || *daily_price<100 || *daily_price>999){
        fgets(temp,300,f);
        printf("\nDaily price must be a number between 100 and 999, try again: ");
    }
    printf("\n");
    fgets(temp,300,f);
    return 0;
}

/* Gate date details from user */
int getDate(Date* date,FILE* f){
    int day,month,year;
    char check, buff[300];
    while(1){
        printf("\nEnter date (dd/mm/yyyy): ");
        while((fscanf(f," %d/%d/%d%c",&day,&month,&year,&check)!=4) || ((check!='\n') && (check!='\r'))){
            fgets(buff,300,f);
            printf("\nInvalid input, enter again: ");
        }
        if(!checkDateDetails(year,month,day)){
            printf("\nInvalid input, enter again: ");
            fgets(buff,300,f);
            continue;
        }
        break;
    }
    date->day = day;
    date->month = month;
    date->year = year;
    return 0;
}

/* Get a String from user in the exact size */
int getStrExactSize(char* str,int size,FILE* f){
    fgets(str,300,f);
    str[strcspn(str,"\r\n")] = 0;
    if(checkStrLen(str,size)!=0){
        return -1;
    }
    return 0;
}

/*allocate memory and duplicate given string, return pointer to new duplicate string*/
char* myStrdup(char* str){
    char* ret = ALLOC(char,strlen(str)+1);
    if(!ret){
        printf("\nMemory allocation error\n");
        return NULL;
    }
    strcpy(ret,str);
    return ret;
}

