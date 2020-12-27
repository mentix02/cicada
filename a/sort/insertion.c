#include <stdint.h>
#include <stddef.h>

void insertionSortI32Array(int32_t* arr, const size_t n) {
  size_t j;
  int32_t key;
  for (size_t i = 0; i < n; ++i) {
    j = i - 1;
    key = arr[i];
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}

void insertionSortI64Array(int64_t* arr, const size_t n) {
  size_t j;
  int64_t key;
  for (size_t i = 0; i < n; ++i) {
    j = i - 1;
    key = arr[i];
    while (j >= 0 && arr[j] > key) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = key;
  }
}
