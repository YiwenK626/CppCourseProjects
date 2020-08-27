#include <stdlib.h>
#include <stdio.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

double balance(retire_info profile, double base, int period) {
  double PMT = profile.contribution;
  double interest_rate = profile.rate_of_return/12;
  
  double balance = base * (1 + interest_rate);
  balance += PMT;
  return balance;
}

void retirement (int startAge, double initial, retire_info working, retire_info retired) {

  // while working 
  double balance_working = initial;
  for (int w = 0; w < working.months; w++) {
    int age_year =(startAge + w ) / 12;
    int age_month = (startAge + w ) % 12;
    printf("Age %3d month %2d you have $%.2lf\n", age_year, age_month, balance_working);
    balance_working = balance(working, balance_working, w); 
  }

  // when retiring 
  double balance_retired = balance_working;
  for (int r = 0; r < retired.months; r++) {
    int age_year =(startAge + working.months + r ) / 12;
    int age_month = (startAge + working.months + r) % 12; 
    printf("Age %3d month %2d you have $%.2lf\n", age_year, age_month, balance_retired);
    balance_retired = balance(retired, balance_retired, r); 
  }
}

int main(void) {
  int startAge = 327;
  double initial = 21345;
  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;
  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;

  retirement (startAge, initial, working, retired);
  return EXIT_SUCCESS;
}