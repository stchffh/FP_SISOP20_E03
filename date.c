#include "types.h"  
#include "user.h"  
#include "date.h"   

// prototypes of all the functions used
long long power(int,int);
int check_leap(int);
void month_name(int);
void day_name(int,int,int);
void time(void);
void plus(void);
void s(void);
void today(void);

int main(int argc, char *argv[])
{
	//date command
	if(argc==1)
	today();

	else
	{
		//date -+ command
		if((argc==2)&&(strcmp("-+",*(argv+1))==0))
	  plus(); 
    
		// date -s command
		else if((argc==2)&&(strcmp("-s",*(argv+1))==0))
	  s(); 

		else
			printf(1,"Invalid command. Please try again.\n");
	 }
exit();
}

//a power b
long long power(int x,int y)
{
	long long res = 1;
	for(int i=0;i<y;i++)
	{
		res = res * x;
	}
	return(res);
}

int check_leap(int x)
{
	int flag = 0;
	if(x%400==0)
		flag = 1;
	else if(x%100==0)
		flag = 0;
	else if(x%4==0)
		flag = 1;
	else 
		flag = 0;
	return(flag);
}

void month_name(int x)
{
	switch(x)
	{
		case 1:printf(1," Jan");
		       break;
		case 2:printf(1," Feb");
		       break;
		case 3:printf(1," Mar");
		       break;
		case 4:printf(1," Apr");
		       break;
		case 5:printf(1," May");
		       break;
		case 6:printf(1," Jun");
		       break;
		case 7:printf(1," Jul");
		       break;
		case 8:printf(1," Aug");
		       break;
		case 9:printf(1," Sep");
		       break;
		case 10:printf(1," Oct");
		       break;
		case 11:printf(1," Nov");
		       break;
		case 12:printf(1," Dec");
		       break;
	}
}

void day_name(int x,int y,int z)
{
	int initial_day = 4;
	int count = 0;	
	if(x>1970)
	{
		  for(int i=1970;i<x;i++)
		  {
			  if(check_leap(i))
				  count += 366;
			  else
				  count += 365;
		  }
	}
	for(int i=1;i<y;i++)
	{
		if(i==2)
		{
			  if(check_leap(x))
				  count += 29;
			  else
				  count += 28;
		}
		else if((i<8)&&(i%2==1)) count += 31;
		else if((i<8)&&(i%2==0)) count += 30;
		else if((i>=8)&&(i%2==0)) count += 31;
		else count += 30;
   }

int final_day = (initial_day+count+z-1)%7;
	switch(final_day)
	{
		case 0:printf(1,"Sun");
		       break;
		case 1:printf(1,"Mon");
		       break;
		case 2:printf(1,"Tue");
		       break;
		case 3:printf(1,"Wed");
		       break;
		case 4:printf(1,"Thur");
		       break;
		case 5:printf(1,"Fri");
		       break;
		case 6:printf(1,"Sat");
		       break;
	 }
}

void time()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date failed\n");
		exit();
	}
	if(r.minute>=60)
	{
		r.hour += 7;
	}
	else
	{
		r.hour += 7;
	}
	if(r.hour>=24)
		r.hour -= 24;
	printf(1," %d:%d:%d",r.hour,r.minute,r.second);
}
	     
void today()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date failed\n");
		exit();
	}
	day_name(r.year,r.month,r.day);	 // prints the name of day of the week
	month_name(r.month);  // prints the name of the month of the year
	printf(1," %d",r.day);  // prints the today's date
	time();  // prints the current time 
	printf(1," ");
	printf(1," %d\n",r.year);  // prints the current year
}

void plus()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date failed\n");
		exit();
	}
	day_name(r.year,r.month,r.day);	 // prints the name of day of the week
	month_name(r.month);  // prints the name of the month of the year
	printf(1," %d",r.day);  // prints the today's date
	printf(1," ");
	printf(1," %d\n",r.year);  // prints the current year
}

void s()
{
	struct rtcdate r;
	if (date(&r)) 
	{
		printf(2, "date failed\n");
		exit();
	}
        month_name(r.month); 
	      day_name(r.year,r.month,r.day);	 // prints the name of day of the week
        printf(1," ");
        printf(1," %d",r.day);  // prints the today's date
        time();
        printf(1," ");
        printf(1," %d\n",r.year);
  }
