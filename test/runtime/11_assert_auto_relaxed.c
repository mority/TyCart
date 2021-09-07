// RUN: TYCART_ASSERT=relaxed %run-tycart %s | FileCheck %s
// XFAIL: *

// FIXME: make this test work?

#include "../../lib/runtime/TyCartAssert.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int data;
  double x[10];
} DataStruct;

int main() {
  const int size   = 10;
  DataStruct* data = (DataStruct*)malloc(sizeof(DataStruct) * size);

  {
    int* data_stub = NULL;
    tycart_assert_auto_stub_((const void*)&data[0].data, data_stub, 22);
  }

  printf("Test succeeded\n");
  return 0;
}

// CHECK: Test succeeded
