# Bank-Management-System
A basic command line bank management system that mimics basic operations of real life banking, written in C. Please check README for more details

This program is entirely case sensitive, every input has to match exactly to respective value. 
Login password is: wuchan
A window machine and GCC compiler are reccomended to run this program, some C libraries used are windows only.
Program contains some minor unexpected behaviours that required fixing, such as not displaying full address and full name.

For the program to run correctly: bank-box.c bank-commands.c helpers.c , have to compile together. 
E.g: in the case of GCC, use "gcc bank-box.c helpers.c bank-commands.c -o bank

This program is my own implementation inspired by a similar project idea from https://www.studytonight.com/c-projects/bank-management-system-project-using-c-language
