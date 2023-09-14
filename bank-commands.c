#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <String.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#include "bank-commands.h"


/**
 * If record.dat file is empty, write new data to file
 * If not, append new data to existing data in file
 * 
 * */
void on_create() {
	
	FILE *ptr,*btr;
	//ptr = fopen("record.dat", "r");
	btr = fopen("record.dat", "a+"); // because every w mode will always overwrite existing data in file
	// use read mode to read old data, then write mode to write old data into new file.

	if (btr == NULL) {
   		fprintf(stderr, "\nError opened  file\n");
   		exit(1);
    }

    person new_account;
    person check_account; // for checking existing acc info
    date acc_date;

    int c,k;

    int char_length = 0;
    int check_acc_no;
    
    printf("\t\t\t\tADD RECORD\n");
	again:
	printf("Enter an account number: ");
	scanf("%d", &check_acc_no);

	while(fread(&check_account, sizeof(person), 1, btr)) {
		if (check_acc_no == check_account.acc_no) {
			printf("Account number already exist\n");
			goto again;
		}
		
	}

	new_account.acc_no = check_acc_no;

	printf("Enter today's date:");
	scanf("%d/%d/%d", &acc_date.day, &acc_date.month, &acc_date.year);
	new_account.deposit.day = acc_date.day;
	new_account.deposit.month = acc_date.month;
	new_account.deposit.year = acc_date.year;
	while((c = getchar()) != '\n');
	printf("Enter full name:");
	scanf("%s", &new_account.name);
	while((c = getchar()) != '\n');
	printf("Enter date of birth:");
	scanf("%d/%d/%d", &new_account.dob.day, &new_account.dob.month, &new_account.dob.year);
	while((c = getchar()) != '\n');
	printf("Enter age:");
	scanf("%d", &new_account.age);
	while((c = getchar()) != '\n');
	printf("Enter address:");
	scanf("%s", &new_account.address);
	while((c = getchar()) != '\n');
	
	
	
	printf("Enter citizenship number:");
	scanf("%s", &new_account.citizenship);
	while((c = getchar()) != '\n');
	printf("Enter phone number:");
	scanf("%s", &new_account.phone_no);
	while((c = getchar()) != '\n');
	printf("Enter amount to deposit:$");
	scanf("%f", &new_account.balance);
	while((c = getchar()) != '\n');
	printf("Type of account:\n");
	printf("\t\t-Saving\n");
	printf("\t\t-Current\n");
	printf("\t\t-Fixed1\n");
	printf("\t\t-Fixed2\n");
	printf("\t\t-Fixed3\n");  
	scanf("%s", &new_account.acc_type); 
	while((c = getchar()) != '\n');
	int flag = 0;
   	flag = fwrite(&new_account, sizeof(person), 1, btr);

   	if (flag) {
   		printf("Contents of the structure written\n");
   	}
   	else {
   		printf("Error!!!\n");
   	}


   	fclose(btr);

}

/**
 * Update selected account info
 * write old and updated info to a new record file
 * 
 * */

int update_info() {

	FILE *old_file,*new_file;
	old_file = fopen("record.dat", "r"); // for reading existing account info
	new_file = fopen("new.dat", "w"); // for storing existing and updated info into a new file

	if (old_file == NULL || new_file == NULL) {
   		fprintf(stderr, "\nError opened  file\n");
   		exit(1);
    }

	int option = 0; // for jumping between options when account number not found
	int select;
	int c;
	int counter = 0;
	bool acc_matched = false;
	int check_acc_no;
	int flag = 0;
	person account;

	again:
	system("cls");
	printf("Enter the account number you want to change:");
	scanf("%d", &check_acc_no);

	while(fread(&account, sizeof(person), 1, old_file)) { // read exisiting info

		if (check_acc_no == account.acc_no) {
			acc_matched = true;
			do {
				printf("Select the following you want to change:\n");
				printf("1.Phone number\n");
				printf("2.Address\n");
				scanf(" %d", &select);
				while ((getchar()) != '\n'); 

				system("cls");
				if (select == 1) {
					// empty out old phone number and update new one
					memset(account.phone_no, '\0', sizeof(account.phone_no));
					printf("Enter new phone number:");
					while ((c = getchar()) != EOF && c != '\n') {
						account.phone_no[counter] = c;
						counter++;
					}
					
					
					// declare a new dat, use fseek to begining , and then rewrite everything in new file, delete old file, rename new file as record
					flag = fwrite(&account, sizeof(person), 1, new_file);
					if (flag) {
						printf("Phone number has been successfully updated\n");
					}
					else {
						printf("Error updating phone number\n");
						exit(1);
					} // write updated phone number into associated account into new file
					
					
				}
				else if (select == 2) {
					memset(account.address, '\0', sizeof(account.address));
					printf("Enter new address:");
					while ((c = getchar()) != EOF && c != '\n') {
						account.address[counter] = c;
						counter++;
					}
					
					flag = fwrite(&account, sizeof(person), 1, new_file);
					if (flag) {
						printf("Address has been successfully updated\n");
					}
					else {
						printf("Error updating address\n");
						exit(1);
					}

				}
				else {
					printf("Select 1 or 2 only, try again\n");
					
				}
			}while(select < 1 && select > 2);   
		}
		else {
			fwrite(&account, sizeof(person), 1, new_file); // if not matching account number, write other exisiting acc info into new file from old file
		}



	}



	fclose(old_file);
    fclose(new_file);
    remove("record.dat");
    rename("new.dat","record.dat");


    if (!acc_matched) {
    	printf("Account number not found\n");
    	select_again:
    	printf("Select 0 to try again, 1 go back to main menu, 2 to exit\n");
    	scanf("%d", &option);
    	printf("option is %d\n", option);
    	if (option == 0) {
    		goto again;
    	}
    	else if (option == 1) {
    		return 1;
    	}
    	else if (option == 2) {
    		return 2;
    	}
    	else {
    		printf("Select 0, 1, 2 please\n");
    		goto select_again;
    	}
    }

	
}

/**
 * Update account balance and save updated balance to new record file
 * return a number to jump between options
 * */
int transact() {
	again:
	FILE *old_file,*new_file;

	old_file = fopen("record.dat", "r");
	new_file = fopen("new.dat", "w");

	if (old_file == NULL || new_file == NULL) {
		fprintf(stderr, "\nError opened  file\n");
   		exit(1);
	}

	int select,option,choice;
	float amount;
	int check_acc_no;
	bool is_matched = false;
	bool can_withdraw = true;
	int flag = 0;

	person account;
	//again:
	printf("Enter an account number:");
	scanf("%d", &check_acc_no);

	while(fread(&account, sizeof(person), 1, old_file)) {
		if (check_acc_no == account.acc_no) {
			is_matched = true;
			do {
				system("cls");
				printf("\n\n\nSelect the following options:\n1.Deposit\n2.Withdraw\n\n");
				printf("Enter your choice: ");
				scanf("%d", &select);

				if (select == 1) {
					printf("Enter an amount to deposit: ");
					scanf("%f", &amount);
					account.balance += amount;

					flag = fwrite(&account, sizeof(person), 1, new_file); 
					if (flag) {
						printf("%.2f has been successfully deposited to your account: %d\n", amount, account.acc_no);
					}
					else {
						printf("Error depositing into account\n");
						exit(1);
					}

				}
				else if (select == 2) {
					// check if account is in saving, if yes, cannot withdraw
					can_withdraw = in_saving(account);
					if (can_withdraw) {
						enter_amount:
						printf("Enter an amount to withdraw: ");
						scanf("%f", &amount);
						if (amount > account.balance) { // if withdraw amount is larger than balance, cannot withdraw that amount
							printf("Insufficient fund, your current balance is %.2f\n", account.balance);
							printf("1.Withdraw a different amount, 2.Leave\n");
							scanf("%d", &choice);
							if (choice == 1) {
								goto enter_amount;
							}
							else {
								amount = 0; // set amount to 0 to prevent withdrawing bank balance
							}

						}
						account.balance -= amount;

						flag = fwrite(&account, sizeof(person), 1, new_file); 
						if (flag) {
							printf("%.2f has been successfully withdrew to your account: %d\n", amount, account.acc_no);
						}
						else {
							printf("Error depositing into account\n");
							exit(1);
						}

					}
					else {
						printf("Account is in Saving: %s, cannot withdraw\n", account.acc_type);
					}
					
				}	
				else {
					printf("Enter options 1 or 2 only\n");
				}

			}while(select < 1 && select > 2);
			
			
		}
		else {
			fwrite(&account, sizeof(person), 1, new_file); 
		}
	}

	fclose(old_file);
    fclose(new_file);
    remove("record.dat");
    rename("new.dat","record.dat");


    if (!is_matched) {
    	printf("Account number not found\n");
    	select_again:
    	printf("Select 0 to try again, 1 go back to main menu, 2 to exit\n");
    	scanf("%d", &option);

    	if (option == 0) {
    		goto again;
    	}
    	else if (option == 1) {
    		return 1;
    	}
    	else if (option == 2) {
    		leave:
    		return 2;
    	}
    	else {
    		printf("Select 0, 1, 2 please\n");
    		goto select_again;
    	}
    }


}

void view_info() {

	FILE *read_file;
	read_file = fopen("record.dat", "r");

	int check_acc_no,option,select;
	bool acc_found,name_found = false;
	person account;

	int c;
	int name_length = 0;
	char name[MAX_NAME_LENGTH];
	float updated_balance;


	do {
		
		printf("Do you want to check by:\n 1.Name\n 2.Account Number\nEnter your choice:");
		scanf("%d", &option);
		//while((c = getchar()) != EOF);
		if (option < 1 && option > 2) {
			
			printf("Enter 1 or 2 only, try again\n");

		} 

	}while(option < 1 && option > 2);
	while((c = getchar()) != '\n'); // catch newline char
	switch(option) { 

		case 1:
			printf("Enter name: ");
			while((c = getchar()) != EOF && c != '\n') {
				name[name_length] = c;
				name_length++;
			}
		break;
		case 2:
			printf("Enter account number: ");
			scanf("%d", &check_acc_no);
		break;
		default:
		break;
	}
	

	while(fread(&account, sizeof(person), 1, read_file)) {
		if (option == 2) {
			if (check_acc_no == account.acc_no) {
				acc_found = true;
				updated_balance = get_interest_rate(account);
				account.balance = updated_balance;
				printf("Name: %s\nAccount number: %d\nAge: %d\nAddress: %s\nCitizenship: %s\nPhone number: %s\nAccount Type: %s\nBalance: %.2f\nDay of Birth: %d/%d/%d\n", account.name,account.acc_no,account.age,account.address,account.citizenship,account.phone_no,account.acc_type,account.balance,account.dob.day,account.dob.month,account.dob.year);
				break;

			}
		}
		else {
			if (strcmp(name, account.name) == 0) {
				name_found = true;
				updated_balance = get_interest_rate(account);
				account.balance = updated_balance;
				printf("Name: %s\nAccount number: %d\nAge: %d\nAddress: %s\nCitizenship: %s\nPhone number: %s\nAccount Type: %s\nBalance: %.2f\nDay of Birth: %d/%d/%d\n", account.name,account.acc_no,account.age,account.address,account.citizenship,account.phone_no,account.acc_type,account.balance,account.dob.day,account.dob.month,account.dob.year);
				break;
			}
		}
	}
	fclose(read_file);
	if (option == 2) {
		if (!acc_found) {
			printf("account number not found\n");
		}
	}
	else {
		if (!name_found) {
			printf("Name not found\n");
		}

	}


}

void delete_account() {
	FILE *old_file,*new_file;
	old_file = fopen("record.dat", "r");
	new_file = fopen("new.dat", "w");

	int check_acc_no;
	int c;
	bool acc_found = false;
	person account;


	printf("Enter the account number you wish to delete:");
	scanf("%d", &check_acc_no);
	while((c = getchar()) != '\n'); // catch newline
	// add all other accounts to new file besides the one to delete
	while(fread(&account, sizeof(person), 1, old_file)) {
		if (check_acc_no != account.acc_no) {
			fwrite(&account, sizeof(person), 1, new_file);
		}
		else {
			acc_found = true;
		}
	}

	fclose(old_file);
    fclose(new_file);
    remove("record.dat");
    rename("new.dat","record.dat");


	if (!acc_found) {
		printf("This account number doesn't exist\n");

	}
	else {
		printf("Account has been deleted successfully\n");
	}



}


void view_accounts() {
	FILE *read_file;
	read_file = fopen("record.dat", "r");
	fseek(read_file, 0, SEEK_SET); // set file pointer back to beginning
	person account;

	printf("ACCOUNT NUMBER\t\t\tNAME\t\t\t\tADDRESS\t\t\t\tPHONE\n");

	while(fread(&account, sizeof(person), 1, read_file)) {
		printf("%d\t\t\t%s\t\t\t\t%s\t\t\t\t%s\n", account.acc_no, account.name, account.address, account.phone_no);
	}

	fclose(read_file);


}