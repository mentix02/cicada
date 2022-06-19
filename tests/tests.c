#include "tests.h"
#include "acutest.h"

TEST_LIST = {
  { "testNewList", testNewList },
  { "testCleanList", testCleanList },
  { "testGetListEl", testGetListEl },
  { "testLPopListEl", testLPopListEl },
  { "testRPopListEl", testRPopListEl },
  { "testLPushListEl", testLPushListEl },
  { "testRPushListEl", testRPushListEl },
  { "testDeleteListEl", testDeleteListEl },

  { "testNewVector", testNewVector },
  { "testLPopVectorEl", testLPopVectorEl },
  { "testRPopVectorEl", testRPopVectorEl },
  { "testLPushVectorEl", testLPushVectorEl },
  { "testRPushVectorEl", testRPushVectorEl },
  { "testDeleteVectorEl", testDeleteVectorEl },

  { NULL, NULL }
};
