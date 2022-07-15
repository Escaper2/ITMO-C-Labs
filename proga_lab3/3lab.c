#include <stdio.h>  
#include <string.h> 
#include <time.h>
#include <stdlib.h>
int main() {
  struct tm time;
  char s[400]; char remote_addr[32]; char local_time[32]; char request[340]; char bytes_send[16];  char mounth [3];
  int status; int countOfServerErrors = 0; int number = 0;   int mounths;   int *secsArray;   int countOfStrings = 0;   int window;
  long long secs = 0; long long n = 0;
  printf("Enter desired time interval\n");
  scanf("%d", &window);
  FILE* fil;
  FILE* fal;
  fal = fopen("access_log_Jul95.log","r");
  while(fgets(s,500,fal)!=NULL) {
    countOfStrings = countOfStrings + 1;
  }
  fclose(fal);
  secsArray = (int*)malloc(sizeof(int) * countOfStrings);
  fil = fopen("access_log_Jul95.log","r");
  if (fil == NULL){
    printf("%s","no file");
    return 1;
  }
  printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\");
  printf("\nRequests with server errors :\n\n");
  while (!feof(fil)) {
    fscanf(fil,"%s - - [%[^]]] \"%[^\"]\" %d %d", remote_addr, local_time, request, &status, &bytes_send);
    status = status / 100;
    if (status == 5) {
      number = number + 1;
      printf("%d) %s\n",number,request);
      countOfServerErrors = countOfServerErrors + 1;
    }
    sscanf(local_time,"%d/%3s/%d:%d:%d:%d",&time.tm_mday,mounth,&time.tm_year,&time.tm_hour,&time.tm_min,&time.tm_sec);
    time.tm_year = time.tm_year - 1900;
    if (strcmp(mounth,"Jan") == 0) {
      mounths = 1;
    }
    else if (strcmp(mounth,"Feb") == 0) {
      mounths = 2;
    }
    else if (strcmp(mounth,"Mar") == 0) {
      mounths = 3;
    }
    else if (strcmp(mounth,"Apr") == 0) {
      mounths = 4;
    }
    else if (strcmp(mounth,"May") == 0) {
      mounths = 5;
    }
    else if (strcmp(mounth,"Jun") == 0) {
      mounths = 6;
    }
    else if (strcmp(mounth,"Jul") == 0) {
      mounths = 7;
    }
    else if (strcmp(mounth,"Aug") == 0) {
      mounths = 8;
    }
    else if (strcmp(mounth,"Sep") == 0) {
      mounths = 9;
    }
    else if (strcmp(mounth,"Oct") == 0) {
      mounths = 10;
    }
    else if (strcmp(mounth,"Nov") == 0) {
      mounths = 11;
    }
    else if (strcmp(mounth,"Dec") == 0) {
      mounths = 12;
    }
    time.tm_mon = mounths;
    secs = mktime(&time);
    time.tm_mon = mounths;
    secs = mktime(&time);
    secsArray[n] = secs;
    n +=1;
  }
   long long supportArray = 0;
   long long counter = 1;
   long long maxRequest = 0;
   long long j = 1;
   for (long long i = 1; i<countOfStrings; i++) {
     supportArray += secsArray[i] - secsArray[i-1];
     counter = counter + 1;
     while (supportArray > window && j+1 < countOfStrings) {
       supportArray -= (secsArray[j] - secsArray[j-1]);
       j++;
       counter = counter - 1;
     }
     if (counter > maxRequest) {
       maxRequest = counter;
     }
   }



  printf("\nTotal Requests with server errors: %d\n",countOfServerErrors);
  printf("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\");
   printf("\nMax requests in %lld seconds window: %lld \n",window+1,maxRequest);
}