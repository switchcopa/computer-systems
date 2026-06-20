static const char non_leap[]    = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static const char leap[]        = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

static const char *daytab[]     = {
        non_leap,
        leap
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
        int i, leap;
        leap = year%4 == 0 && year%100 != 0 || year%400 == 0;

        if ((1 <= month && month <= 12) && (1 <= day && day <= *(*(daytab + leap) + i))) { 
                for (i = 1; i < month; i++) 
                        day += *(*(daytab + leap) + i);
                return day;
        } else
                return -1;
}

/* month_day: set month, day from day of year*/
void month_day(int year, int yearday, int *pmonth, int *pday)
{
        int i, leap, maxday;
        leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
         
        maxday = leap ? 366 : 365; 
        if (yearday < 1 || yearday > maxday) {
                *pmonth = *pday = -1;
                return;
        }

        for (i = 1; yearday > daytab[leap][i]; i++)
                yearday -= *(*(daytab + leap) + i);
        *pmonth = i;
        *pday = yearday;
}
