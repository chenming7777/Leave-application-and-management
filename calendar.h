#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "assist_function.h"

// This function is for calander function.
char* calendar()
{
    time_t s, val = 1;
    struct tm* current_time;
    s = time(NULL);
    current_time = localtime(&s);
    char current_day[255];
    char current_month[255];
    char current_year[255];
    snprintf(current_day, sizeof(current_day),"%d",current_time->tm_mday);
    snprintf(current_month, sizeof(current_month),"%d",current_time->tm_mon + 1);
    snprintf(current_year, sizeof(current_year),"%d",current_time->tm_year + 1900);
    char* rtn = (char*)malloc(50);
    int date, month, year;
    char temp[50], final[50], str_date[10], str_month[10], str_year[10];
// enter year
    while (1)
    {
        printf("Please enter your year:");
        fgets(temp, sizeof(temp),stdin);
        strip(temp);
        if (strlen(temp) != 4){
            printf("Please only enter 4 number\n");
            continue;
        }
        year = atoi(temp);
        if ((current_time->tm_year + 1900) <= year && year <= 2023)
        {
            break;
        }
        else
        {
            printf("Year is pass or not exist\n");
            continue;
        }
    }
// enter month
    while(1)
    {
        printf("Please enter your month(Example:1,2,11):");
        fgets(temp,sizeof(temp),stdin);
        strip(temp);
        if (!(strlen(temp) == 1 || strcmp(temp,"10") == 0 || strcmp(temp, "11") == 0 || strcmp(temp, "12") == 0))
        {
            printf("Please enter a valid month\n");
            continue;
        }
        month = atoi(temp);
        if((current_time->tm_mon +1) <= month && month <= 12)
        {
            break;
        }
        else
        {
            printf("Month has passed or not exist\n");
            continue;
        }
    }
// enter date
    // this to indicate whether user entered month is larger than current month
    if((current_time->tm_mon +1) >= month)
    {   
        if (year % 4 == 0 && month == 2) // this is to indicate whether the year is a leap year
        {
            do
            {
                printf("Please enter your date(Example:02,12,30):");
                fgets(temp,sizeof(temp),stdin);
                strip(temp);
                if(strlen(temp) != 2 || check_digit(temp[0]) == 0 ||check_digit(temp[1]) == 0)
                {
                    printf("Please enter a valid date\n");
                    continue;
                }
                date = atoi(temp);
                if ((current_time->tm_mday <= date && date <= 29) == 0)
                {
                    printf("Day has passed or not exist\n");
                }
            } while ((current_time->tm_mday <= date && date <= 29) == 0);
        }
        else
        {
            if(month == 2)
            {
                do
                {
                    printf("Please enter your date(02,12,30):");
                    fgets(temp,sizeof(temp),stdin);
                    strip(temp);
                    if(strlen(temp) != 2 || check_digit(temp[0]) == 0 ||check_digit(temp[1]) == 0)
                    {
                        printf("Please enter a valid date\n");
                        continue;
                    }
                    date = atoi(temp);
                    if ((current_time->tm_mday <= date && date <= 28) == 0)
                    {
                        printf("Day has passed or not exist\n");
                    }
                }while((current_time->tm_mday <= date && date <= 28) == 0);
            }
            if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 
            || month == 10 || month == 12)
            {
                do
                {
                    printf("Please enter your date(Example:02,12,30):");
                    fgets(temp,sizeof(temp),stdin);
                    strip(temp);
                    if(strlen(temp) != 2 || check_digit(temp[0]) == 0 ||check_digit(temp[1]) == 0)
                    {
                        printf("Please enter a valid date\n");
                        continue;
                    }
                    date = atoi(temp);
                    if((current_time->tm_mday <= date && date <= 31) == 0)
                    {
                        printf("Day has passed or not exist\n");
                    }
                }while((current_time->tm_mday <= date && date <= 31) == 0);
            }
            if(month == 4 || month == 6 || month == 9 || month == 11)
            {
                do
                {
                    printf("Please enter your date(Example 02,12,30):");
                    fgets(temp,sizeof(temp),stdin);
                    strip(temp);
                    if(strlen(temp) != 2 || check_digit(temp[0]) == 0 ||check_digit(temp[1]) == 0)
                    {
                        printf("Please enter a valid date\n");
                        continue;
                    }
                    date = atoi(temp);
                    if((current_time->tm_mday <= date && date <= 30) == 0)
                    {
                        printf("Day has passed or not exist\n");
                    }
                }while((current_time->tm_mday <= date && date <= 30) == 0);
            }
        }
    }
    else
    {
        if (year % 4 == 0 && month == 2)
        {
            do
            {
                printf("Please enter your date(Example:02,12,30):");
                fgets(temp,sizeof(temp),stdin);
                strip(temp);
                if(strlen(temp) != 2 || check_digit(temp[0]) == 0 ||check_digit(temp[1]) == 0)
                {
                    printf("Please enter a valid date\n");
                    continue;
                }
                date = atoi(temp);
            } while ((1 <= date && date <= 29) == 0);
        }
        else
        {
            if(month == 2)
            {
                do
                {
                    printf("Please enter your date(Example:02,12,30):");
                    fgets(temp,sizeof(temp),stdin);
                    strip(temp);
                    if(strlen(temp) != 2 || check_digit(temp[0]) == 0 ||check_digit(temp[1]) == 0)
                    {
                        printf("Please enter a valid date\n");
                        continue;
                    }
                    date = atoi(temp);
                }while((1 <= date && date <= 28) == 0);
            }
            if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 
            || month == 10 || month == 12)
            {
                do
                {
                    printf("Please enter your date(Example:02,12,30):");
                    fgets(temp,sizeof(temp),stdin);
                    strip(temp);
                    if(strlen(temp) != 2 || check_digit(temp[0]) == 0 ||check_digit(temp[1]) == 0)
                    {
                        printf("Please enter a valid date\n");
                        continue;
                    }
                    date = atoi(temp);
                }while((1 <= date && date <= 31) == 0);
            }
            if(month == 4 || month == 6 || month == 9 || month == 11)
            {
                do
                {
                    printf("Please enter your date(Example:02,12,30):");
                    fgets(temp,sizeof(temp),stdin);
                    strip(temp);
                    if(strlen(temp) != 2 || check_digit(temp[0]) == 0 ||check_digit(temp[1]) == 0)
                    {
                        printf("Please enter a valid date\n");
                        continue;
                    }
                    date = atoi(temp);
                }while((1 <= date && date <= 30) == 0);
            }
        }
    }
    sprintf(str_date,"%d",date);
    sprintf(str_month,"%d",month);
    sprintf(str_year,"%d",year);
    snprintf(final, sizeof(final),"%s/%s/%s",str_date,str_month,str_year);
    strcpy(rtn, final);
    return rtn;
}
