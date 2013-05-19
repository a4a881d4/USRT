#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <USRTWorkers.h>
#include <Log.h>
int main( int argc, char *argv[] )
{
  clearLog();
  attachLog(6);
  std::USRTWorkers *workers = new std::USRTWorkers( argv[1] );
  workers->mainWorker( workers );
}
