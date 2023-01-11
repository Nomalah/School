// Written by Dallas Hart on 2023-01-11
// This program belongs to Assignment 1 in ENGG*1420 at UOG
// Purpose: Design a function that finds the next date from an original date,
// Design a function that can compare dates that can do <, ==, >

#include <stdio.h>

typedef struct Date
{
    int year;
    int month;
    int day;
} Date;

// Part A
Date getNextDate(Date date)
{
    if (date.month == 12 && date.day == 31)
    {
        return (Date){ date.year + 1, 1, 1 }; // Jan 1
    }

    int last_day_of_months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
        
    if (last_day_of_months[date.month - 1] == date.day)
    {
        return (Date){ date.year, date.month + 1, 1 };
    }

    return (Date){ date.year, date.month, date.day + 1 };
}

int compDate(Date a, Date b)
{
    // Check if both dates are equal
    if (a.year == b.year && a.month == b.month && a.day == b.day)
    {
        return 0;
    }
    // If the years are different, there's a result
    if (a.year > b.year)
    {
        return 1;
    }
    // Logic for determining month & day, to see if a > b
    if (a.year == b.year && (a.month > b.month || (a.month == b.month && a.day > b.day)))
    {
        return 1;
    }

    return -1;
}

// Example test program
int main() 
{
    Date date = {.year = 2002, .month = 1, .day = 31};
    Date next_day = getNextDate(date);
    printf("A) Y: %d, M: %d, D: %d\n", next_day.year, next_day.month, next_day.day);
    printf("B) i: %d, ii: %d, iii: %d\n", compDate(date, date), compDate(next_day, date), compDate(date, next_day));
}