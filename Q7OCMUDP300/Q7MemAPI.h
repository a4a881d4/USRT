#include <usrttype.h>
#include "Q7Mem.h"

extern "C" {
  void initQ7Mem( const char *fileName );
  Q7Mem *attachQ7Mem( const char *fileName );
  void dumpQ7Mem( Q7Mem *h );
};// extern "C"

