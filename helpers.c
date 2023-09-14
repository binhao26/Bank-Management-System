#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <String.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include "helpers.h"

const float SAVER_RATE = 0.05;
const float FIXED_1_RATE = 0.1;
const float FIXED_2_RATE = 0.2;
const float FIXED_3_RATE = 0.3;

#define ONE_YEAR 365
#define TWO_YEARS 730
#define THREE_YEARS 1095


// Update an account's balance based on respective interest rates
float get_interest_rate(person account) {

   // get raw time in seconds
	time_t rawtime = time(NULL);
	float updated_balance;
	int years_difference = 0;
	int current_year;

	 if (rawtime == -1) {

        puts("The time() function failed");
        return 1;
    }

    struct tm *ptm = localtime(&rawtime); // convert to local time and assign to struct tm

     if (ptm == NULL) {

        puts("The localtime() function failed");
        return 2;
    }

    current_year = ptm->tm_year + 1900; // get current year

    years_difference = current_year - account.deposit.year;

    // Update account balance based on account type
    if (strcmp(account.acc_type, "Saving") == 0) {
    	updated_balance = account.balance + (account.balance * SAVER_RATE * years_difference);
    }
    else if (strcmp(account.acc_type, "Fixed1")) {
    	updated_balance = account.balance + (account.balance * FIXED_1_RATE * years_difference);
    }
    else if (strcmp(account.acc_type, "Fixed2")) {
    	updated_balance = account.balance + (account.balance * FIXED_2_RATE * years_difference);
    }
    else if (strcmp(account.acc_type, "Fixed3")) {
    	updated_balance = account.balance + (account.balance * FIXED_3_RATE * years_difference);
    }
    else {
    	return account.balance;
    }

    return updated_balance;

}

// check if an account is one of fixed type saving accounts
bool in_saving(person account) {
	if (strcmp(account.acc_type, "Fixed1") == 0 || strcmp(account.acc_type, "Fixed2") == 0 || strcmp(account.acc_type, "Fixed3") == 0) {
		return false;
	}
	return true;
}

// calculate number of days since account opened
int calculate_days(person account) {
   int current_day,current_month,current_year;
   int leftover_days = 0;
   int leftover_months = 0;
   
   int total_days = 0;

    time_t rawtime = time(NULL);

    if (rawtime == -1) {

        puts("The time() function failed");
        return 1;
    }

    struct tm *ptm = localtime(&rawtime);

    if (ptm == NULL) {

        puts("The localtime() function failed");
        return 1;
    }

    current_year = ptm->tm_year + 1900;
    current_month = ptm->tm_mon + 1;
    current_day = ptm->tm_mday;

    // sum all all future days starting and including current month on account opened date
    switch (account.deposit.month) {
      case 1:
         leftover_days += (31 - account.deposit.day) + 1;
      break;
      case 2:
         if (account.deposit.year % 4 == 0) {
            leftover_days += (29 - account.deposit.day) + 1;
         }
         else {
            leftover_days += (28 - account.deposit.day) + 1;
         }
      break;
      case 3:
         leftover_days += (31 - account.deposit.day) + 1;
      break;
      case 5:
         leftover_days += (31 - account.deposit.day) + 1;
      break;
      case 7:
         leftover_days += (31 - account.deposit.day) + 1;
      break;
      case 10:
         leftover_days += (31 - account.deposit.day) + 1;
      break;
      case 12:
         leftover_days += (31 - account.deposit.day) + 1;
      break;
      default:
         leftover_days += (30 - account.deposit.day) + 1;
      break;   
    }

  
    int next_month = 0;
    if (current_year - account.deposit.year > 0) { // if not same year
      // sum all days from rest of the months up to december for old date
      if (account.deposit.month + 1 <= 12) {
         
         next_month = account.deposit.month + 1; // month after old date month 

         for (int i = next_month; i <= 12; i++) {
            switch (i) {
               case 1:
                  total_days += 31;
               break;
               case 2:
                  if (account.deposit.year % 4 == 0) {
                  total_days += 29;
               }
               else {
                  total_days += 28;
               }
               break;
               case 3:
                  total_days += 31;
               break;
               case 5:
                  total_days += 31;
               break;
               case 7:
                  total_days += 31;
               break;
               case 10:
                  total_days += 31;
               break;
               case 12:
                  total_days += 31;
               break;
               default:
                  total_days += 30;
               break;

            }
         }
      }
      // if more than 1 year between old date and current date, sum up total days for those years
      int interval_years = current_year - account.deposit.year;
      int year_increments = account.deposit.year;
      if (interval_years > 1) {
         for(int k = 0; k < interval_years - 1; k++) {
            year_increments = year_increments + 1;
            if (year_increments % 4 == 0) {
               total_days = total_days + 366;
            }
            else {
               total_days = total_days + 365;
            }
         }
      }
      
         // calculate days from left over months leading up to current month in current date
      for(int n = 1; n < current_month; n++) {
         switch (n) {
            case 1:
               total_days += 31;
            break;
            case 2:
               if (account.deposit.year % 4 == 0) {
               total_days += 29;
            }
            else {
               total_days += 28;
            }
            break;
            case 3:
               total_days += 31;
            break;
            case 5:
               total_days += 31;
            break;
            case 7:
               total_days += 31;
            break;
            case 10:
               total_days += 31;
            break;
            case 12:
               total_days += 31;
            break;
            default:
               total_days += 30;
            break;

         }
      }


    }
    else {
      // make sure the month after old month is not current month 
      if (account.deposit.month + 1 != current_month) {
         int month_after_old_month = account.deposit.month + 1;
         for (int m = month_after_old_month; m < current_month; m++) {
            switch (m) {
               case 1:
                  total_days += 31;
               break;
               case 2:
                  if (account.deposit.year % 4 == 0) {
                  total_days += 29;
               }
               else {
                  total_days += 28;
               }
               break;
               case 3:
                  total_days += 31;
               break;
               case 5:
                  total_days += 31;
               break;
               case 7:
                  total_days += 31;
               break;
               case 10:
                  total_days += 31;
               break;
               case 12:
                  total_days += 31;
               break;
               default:
                  total_days += 30;
               break;

            }
         }

      }
      
    }

    // sum all days leading up to current day in current date
    for (int q = 1; q <= current_day; q++) {
      leftover_days = leftover_days + 1;
    }
    
    total_days = total_days + leftover_days; // sum all total days
    return total_days;

}

// check if a fixed account expired.
// days - number of days since account opened.
bool has_saving_expired(int total_days, person account) {
   
   if (strcmp(account.acc_type, "Fixed1") == 0) {
      if (total_days > ONE_YEAR) return true;
   }
   else if (strcmp(account.acc_type, "Fixed2") == 0) {
      if (total_days > TWO_YEARS) return true;
   }
   else if (strcmp(account.acc_type, "Fixed3") == 0) {
      if (total_days > THREE_YEARS) return true;
   }
   else {
      return false;
   }
   return false;
}

// delay 
void fordelay(int j) {
   int i,k;
   for(i=0; i<j; i++) {
      k=i;
   }
         
}

