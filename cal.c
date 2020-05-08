#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "date.h"

#define TRUE    1
#define FALSE   0

struct rtcdate r;
int days_in_month[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
char *months[]=
{
	" ",
	"\n\tJanuary",
	"\n\tFebruary",
	"\n\tMarch",
	"\n\tApril",
	"\n\tMay",
	"\n\tJune",
	"\n\tJuly",
	"\n\tAugust",
	"\n\tSeptember",
	"\n\tOctober",
	"\n\tNovember",
	"\n\tDecember"
};


int determinedaycode(int year)
{
	int daycode;
	int d1, d2, d3;
	// Leap years because of 365.24 days, actual conversion.
	d1 = (year - 1)/ 4;
	d2 = (year - 1)/ 100;
	d3 = (year - 1)/ 400;
	daycode = (year + d1 - d2 + d3) %7;
	return daycode;
}


int determineleapyear(int year)
{
	if((year% 4 == FALSE && year%100 != FALSE) || year%400 == FALSE)
	{
		days_in_month[2] = 29;
		return TRUE;
	}
	else
	{
		days_in_month[2] = 28;
		return FALSE;
	}
}

void calendar(int year, int daycode)
{
	int month, day;
	for ( month=1 ; month < r.month; month++ )
	{
		//Set position for next month
		daycode = ( daycode + days_in_month[month] ) % 7;
	}
	printf(1,"%s %d", months[month],year);
	printf(1,"\n\nSun  Mon  Tue  Wed  Thu  Fri  Sat\n" );
		
	// Correct the position for the first date
	for ( day = 1; day <= 1 + daycode * 5 ; day++ )
	{
		printf(1," ");
	}
		
	// Print all the dates for one month
	for ( day = 1; day <= days_in_month[month]; day++ )
	{
		(day < 10) ? printf(1," %d", day ) :printf(1,"%d", day );
		
		// Is day before Sat? Else start next line Sun.
		if ( ( day + daycode ) % 7 > 0 ) printf(1,"  " );
		else printf(1,"\n " );
	}
        printf(1,"\n");
}

int main(int argc,char *argv[])
{
    int year;
    int daycode;
    if(date(&r)) 
    {
        printf(2, "calender failed\n");
        exit();
    }
    
    year= r.year;
    daycode= determinedaycode(year);
    determineleapyear(year);
    calendar(year,daycode);
    printf(1,"\n");
}
