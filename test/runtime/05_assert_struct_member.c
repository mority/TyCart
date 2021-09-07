// RUN: %run-tycart %s
// XFAIL: *

#include "../../lib/runtime/TyCartAssert.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int data;
  double x;
} DataStruct;

int main() {
  const int size   = 10;
  DataStruct* data = (DataStruct*)malloc(sizeof(DataStruct) * size);

  {
    // addr(data.data) == addr(data), strict mode demands data_stub == DataStruct
    int* data_stub = NULL;
    tycart_assert_stub_((const void*)&data[0].data, data_stub, size, 22);
  }

  printf("Test succeeded\n");
  return 0;
}
