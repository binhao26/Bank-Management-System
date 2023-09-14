/**
 * A bank management system that mimics
 * basic operations of real life banking
 * 
 * This is my own implementation with added features.
 * A similar project can be found at https://www.studytonight.com/c-projects/bank-management-system-project-using-c-language
 * 
 * */


#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <String.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include "account.h"
#include "helpers.h"
#include "bank-commands.h"

// date, acc number, name, birthday, age, address
#define CORRECT_PASSWORD_LENGTH 6
#define MAX_PASSWORD_LENGTH 20
#define MAX_PASSWORD_ATTEMPTS 3
#define MAX_NAME_LENGTH 25
#define MAX_ADDRESS_LENGTH 50
#define MAX_CITIZENSHIP_LENGTH 20
#define MAX_PHONE_LENGTH 12
#define MAX_ACCTYPE_LENGTH 10


int main() {
	
	/** 
	 * At the start check whether an fixed saving account has expired
	 * If expired, revert to Current account
	 * */
	FILE *old_file,*new_file;
	old_file = fopen("record.dat", "r");
	int size;
	int flag = 0;

	if (old_file == NULL) {
		printf("Error opening file at start\n");
		exit(1);
	}
	else {
		if (fseek(old_file, 0, SEEK_END) == 0) {
			size = ftell(old_file);
			if (size != -1L) {
				// check if file is empty
				if (size != 0) {
					printf("--------File is not emptied--------\n");
					new_file = fopen("new.dat", "w");
					fseek(old_file, 0, SEEK_SET); // re-position file pointer back to beginning
					

					person account;
					int days_saved = 0;
					while(fread(&account, sizeof(person), 1, old_file)) {
						days_saved = calculate_days(account); // gets number of days since account opened
						// check if a fixed account has expired or not
						if (has_saving_expired(days_saved, account)) {
							memset(account.acc_type, '\0', sizeof(account.acc_type));
							strcpy(account.acc_type, "Current");
							printf("Account type is %s\n", account.acc_type);
							flag = fwrite(&account, sizeof(person), 1, new_file);

							if (flag) {
								printf("Some fixed saving account has ended and reverted to Current account\n");
							}
							else {
								printf("Failed to update account saving status\n");
							}
						}
						else {
							fwrite(&account, sizeof(person), 1, new_file);
						}

					}
					fclose(old_file);
   				fclose(new_file);
   				remove("record.dat");
   				rename("new.dat","record.dat");
				}
			}
			else {
				printf("File content checking failed");
			}
		}
		else {
			printf("File traversing failed");
		}

	}

	
//**********************************************Main Menue***************************************************************//
	// all login control vars
	char login_password[CORRECT_PASSWORD_LENGTH + 1] = "wuchan"; // password
	bool is_matched = false;
	int c;
	int counter = 0;
	int attempts = 0; // count number of login attempts
	char pass[MAX_PASSWORD_LENGTH];
	int try_again;
	
	do {

		printf("\t\t\t\tEnter password to login: ");
		while((c = getchar()) != EOF && c != '\n') {
			
			pass[counter] = c;
			counter = counter + 1;
		}
	
		if (strcmp(pass, login_password) == 0) {
			printf("Password matched\n");
			printf("Logging");
			for(int i = 0; i <= 6; i++) {
            fordelay(100000000);
            printf(".");
         }
			system("cls");
			is_matched = true;
		}
		else {
			putchar('\n'  );
			printf("Wrong password\n");
			memset(pass, '\0', sizeof(pass));
			enter_again:
			printf("Enter 1 to try again and 0 to exit:");
			scanf("%d", &try_again);
			while ((getchar()) != '\n'); 
			
			if (try_again == 0) {
				break;
			}
			else if (try_again == 1) {
				system("cls");
				counter = 0;
				attempts = attempts + 1;
			}
			else {
				printf("Invalid entry, enter 1 or 0 only\n");
				goto enter_again;
			}
			
		}
		
	}while(!is_matched && attempts < MAX_PASSWORD_ATTEMPTS); // continue while password not matched and login attempts below threshold

	bool is_continue = true;
	int answer;
	if (is_matched) {
		system("color 2");
		jump:
		system("cls");
		printf("\t\t\t\t\tCUSTOMER ACCOUNT BANKING MANAGEMENT SYSTEM\n\n\n");
		printf("\t\t\t\tWELCOME TO THE MAIN MENU\n");

		while(is_continue) {
			int choice;
			int exit;
			printf("\t\t\t1.Create new account\n");
			printf("\t\t\t2.Update information of existing account\n");
			printf("\t\t\t3.For Tranascations\n");
			printf("\t\t\t4.Check the details of existing account\n");
			printf("\t\t\t5.Removing existing account\n");
			printf("\t\t\t6.View customer's list\n");
			printf("\t\t\t7.Exist\n\n\n\n\n");

			printf("\t\t\tEnter your choice: ");
			scanf("%d", &choice);
			system("cls");
			switch(choice) {

			case 1:
				on_create();
				break;
			case 2:
				answer = update_info();
				
				if (answer == 1) {
					goto jump;
				}
				else if (answer == 2) {
					goto leave;
				}
				break;
			case 3:
				answer = transact();
				
				if (answer == 1) {
					goto jump;
				}
				else if (answer == 2) {
					goto leave;
				}
				break;
			case 4:
				view_info();
				break;
			case 5:
				delete_account();
				break;
			case 6:
				view_accounts();
				break;
			case 7:
				
				is_continue = false;
				
				goto leave;
				break;
			default:
				goto leave;
				break;

			}

			printf("Enter 1 to go to the main menu and 0 to exist:");
			scanf("%d", &exit);
			if (exit == 0) {
				
				break;
			}
			else {
				
				goto jump;
			} 



		}


	}

	leave:

	return 0;
}


