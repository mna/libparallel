#include <time.h>

#include "../deps/greatest/greatest.h"
#include "../src/oneone.h"

static void spawn_change_val(void* arg) {
  one_locked_val_s* lv = arg;
  int* val = one_locked_val_get(lv);
  *val = 10;
}

TEST test_version() {
  one_version_s v = one_version();
  ASSERT_EQ(oneone_VERSION_MAJOR, v.major);
  ASSERT_EQ(oneone_VERSION_MINOR, v.minor);
  ASSERT_EQ(oneone_VERSION_PATCH, v.patch);

  PASS();
}

TEST test_spawn() {
  int val = 1;
  one_locked_val_s* lv = one_locked_val_new(&val);
  one_spawn(spawn_change_val, lv);

  // TODO: better assert...
  struct timespec ts = {.tv_nsec = 1000000};
  nanosleep(&ts, NULL);
  ASSERT_EQ(10, val);

  PASS();
}

SUITE(spawn) {
  RUN_TEST(test_version);
  RUN_TEST(test_spawn);
}
