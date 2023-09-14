#include "account.h"
#ifndef HELPERS_H
#define HELPERS_H


float get_interest_rate(person account);
bool in_saving(person account);
bool has_saving_expired(int total_days, person account);
int calculate_days(person account);
void fordelay(int j);

#endif 
