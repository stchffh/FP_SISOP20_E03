#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

void faktor(int n)
{
  if (n==1||n==0)
  {
	 printf(1,"\n");
   return;
  }
   int angka=2;
   while (n%angka != 0) angka++;
   printf(1,"%d ",angka);
   faktor(n/angka);
}

int main (int argc,char *argv[])
{
  int n;
  for(n=1;n<argc;n++)
  {
    printf(1,"%d: ",atoi(argv[n]));
  	faktor(atoi(argv[n]));
  }
  exit();
}
