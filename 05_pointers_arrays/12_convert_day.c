// convert month/day to day of year & vice versa

#include "debug_print.h"

static int days_table[2][12] = {{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
                                {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

bool is_leap(int year);
int day_of_year(int year, int month, int month_day);
void day_of_month(int year, int year_day, int *month_ptr, int *day_ptr);

int main(void) {
    int month, day;
    PRINT_INT(day_of_year(2025, 4, 10));
    day_of_month(2025, 100, &month, &day);
    printf("day_of_month(2025, 100) = %d/%d\n", month, day);
    PRINT_INT(day_of_year(2024, 4, 10));
    day_of_month(2024, 101, &month, &day);
    printf("day_of_month(2024, 101) = %d/%d\n", month, day);
}

bool is_leap(int year) {
    return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

// get day of year from month & day (both 1-indexed)
int day_of_year(int year, int month, int month_day) {
    int i, (*days_ptr)[12] = days_table;
    bool leap;

    leap = is_leap(year);
    if (year < 0)
        return -1;
    if (month <= 0 || month > 12)
        return -1;
    // if (month_day <= 0 || month_day > days_table[leap][month - 1])
    if (month_day <= 0 || month_day > *(*(days_ptr + leap) + month - 1))
        return -1;

    for (i = 0; i < month - 1; i++)
        // month_day += days_table[leap][i];
        month_day += *(*(days_ptr + leap) + i);
    return month_day;
}

// get month & day of month from year & day (1-indexed)
void day_of_month(int year, int year_day, int *month_ptr, int *day_ptr) {
    int i, (*days_ptr)[12] = days_table;
    bool leap, invalid;

    leap = is_leap(year);
    invalid = false;
    if (year < 0)
        invalid = true;
    else if (year_day <= 0 || year_day > (leap ? 366 : 365))
        invalid = true;
    if (invalid) {
        *month_ptr = -1;
        *day_ptr = -1;
        return;
    }

    // for (i = 0; year_day > days_table[leap][i - 1]; i++)
    for (i = 0; year_day > *(*(days_ptr + leap) + i - 1); i++)
        // year_day -= days_table[leap][i];
        year_day -= *(*(days_ptr + leap) + i);
    *month_ptr = i + 1;
    *day_ptr = year_day;
}
