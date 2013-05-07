#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <USRTCapabilityBearer.h>
#include <USRTHardTimer.h>

#include <usrttype.h>
#include <MapMem.h>
#include <md5api.h>
#include <unistd.h>

using namespace std;
int main(int argc, char *argv[])
{
  const char *tName;
  int64 key;
  int64 capKey;
  int num;
  char cap[256];
  char task0[]="queue0";
  char buf[256];
  int bufLen=0; 
  tName=task0;
  int delay = 0;
  
  strcpy( cap, "cap" );
  strcat( cap, argv[1] );
  capKey = md5first( cap );
  
  int opt;
  while((opt=getopt(argc-1,argv+1,"t:k:c:n:d:"))!=-1) {
    switch(opt) {
      case 't':
        tName=optarg;
        break;
      case 'k':
        sscanf(optarg,"%llx",&key);
        *(int64 *)buf=key;
        bufLen=8;
        break;
      case 'c':
        strcpy(buf,optarg);
        bufLen=strlen(optarg)+1;
        buf[bufLen-1]='\0';
        break;
      case 'n':
        sscanf(optarg,"%d",&num);
        *(int *)buf=num;
        bufLen=4;
        break;
      case 'd':
        sscanf(optarg,"%d",&delay);
        break;
      default:
        fprintf(stderr,"Usage: %s(%c) capability [-t taskMem] [-k key] [-c string] [-n num] [-d delay]\n",
                    argv[0],opt);
        exit(EXIT_FAILURE);
        break;
    }
  }
  fprintf(stderr,"Run: %llx -t %s \n",capKey,tName);            
  attach(tName);
  void *a = allocMem(tName,((bufLen+16)/16)*16);
  memset(a,0,bufLen+16);
  memcpy(a,buf,bufLen);
  fprintf(stderr,"prepare args\n");
  task_t *task = allocTask(tName,1LL);
  L2G(&(task->argv),a);
  task->key = capKey;
  USRTHardTimer time(0);
  task->noE = task->noL = time.date()+(long long int)delay;
  fprintf(stderr,"prepare task\n");
  pushTask(tName,task);
  fprintf(stderr,"push task\n");
  release(tName);
}