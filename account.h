#include <stdio.h>
#include <ctype.h>
#include <math.h>
#ifndef ACCOUNT_H
#define ACCOUNT_H


#include <String.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>


// date, acc number, name, birthday, age, address
#define CORRECT_PASSWORD_LENGTH 6
#define MAX_PASSWORD_LENGTH 20
#define MAX_PASSWORD_ATTEMPTS 3
#define MAX_NAME_LENGTH 25
#define MAX_ADDRESS_LENGTH 50
#define MAX_CITIZENSHIP_LENGTH 20
#define MAX_PHONE_LENGTH 12
#define MAX_ACCTYPE_LENGTH 10


typedef struct date{
	int day;
	int month;
	int year;
}date;

typedef struct person{
	// use int for numeric values in struct and calculation but when storing in file, convert into string and vice versa
	char name[MAX_NAME_LENGTH];
    int acc_no,age;
    char address[MAX_ADDRESS_LENGTH];
    char citizenship[MAX_CITIZENSHIP_LENGTH];
    char phone_no[MAX_PHONE_LENGTH];
    char acc_type[MAX_ACCTYPE_LENGTH];
    float balance;
    struct date dob;
    struct date deposit;
    struct date withdraw;
}person;

#endif