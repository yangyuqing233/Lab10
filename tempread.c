
#include <stdio.h>
#include <wiringPi.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


void tempRead(char *serialNum, int verbose);

int main(int argc, char *argv[])
{


/*  char *device = "28-000f98430c3f"; */

char *device = "28-000f98430c3f";
 int verbose = 0;
 /* process the arguments */
 argc--; argv++;
 
 while(argc > 0)
 {
	 printf("%d %s\n", argc, argv[0]);
	 if(!strcmp("-v", argv[0])) {
	 verbose = 1;
 } else if(!strcmp("-d", argv[0])) {
	 if(argc == 0)
	 printf("argc == 0");
 
	argc--; argv++;
	device = argv[0];
 } 
 else
	 printf("no args");
 
 argc--; argv++;
 }
 
 tempRead(device, verbose);
 exit(0); 

}



void tempRead(char *serialNum, int verbose)
{
	
  FILE *fd; 
  int n;
  float tempC;
  
  char buf[1001]; /* string buffer of size 1001, first 1000 characters will be read, last one is terminating character */
  char temperature[6];/* temp *1000 */
  char path[1000] = "/sys/bus/w1/devices/"; /* create array for path */
  strcat(path, serialNum); /*concatenate the device serial  */
  strcat(path, "/w1_slave"); /*concatenate the text file that contains the temp, now full path is done*/

 

  if(serialNum == NULL)
  {
  	  perror("Please Provide a single argument to the tempRead function");
  	  (void) exit(1);
  }
  

  
  /* fprintf(stdout, "FIRST TIME '%s'\n", path); testing if the path works */
  fd = fopen(path, "r");/* make fd = to open path, read only  */
  if(fd == (FILE *)NULL)  /* if fd == NULL, then it means it cant opent the file, so exit*/
  {
  	 perror("open of w1_slave failed. Device not found or device Serial number is wrong \n");
  	 (void) exit(1);
  } 
  
  
  
  n = fread(buf,sizeof(char),1000,fd); delay(900); /* fread returns total number of elements successfully read*/
  if(n==0) /*if no items have been read*/
  {
  	  perror("read failed"); /* then read fails */
  	  exit(1); 
  }
  
  buf[n] = '\0'; /*terminate array with null character*/
  
 if(verbose == 1)
{
        printf("buffer is %s ",buf);
}
 


  /* fprintf(stdout, "Read '%s'\n", buf);  testing the reading of the file */
  
   strncpy(temperature, strstr(buf, "t=") + 2, 5);  /*skip 2 characters (t=) and count the next 5 (the temp) and copy into array temperature*/
   temperature[5]='\0'; /*terminate array with null character*/
  /* fprintf(stdout, "%s\n", temperature); */
     
  /* tempC = (float)atof(temperature); convert temperature from char array to float*/
 /* fprintf(stdout, " %s\n", temperature);*/
   tempC = (float)atof(temperature); /*convert temperature from char array to float*/   
  fprintf(stdout, "%.f\n", tempC);
  
 (void) fclose(fd); /* close the fd */
    exit(0);
  }


