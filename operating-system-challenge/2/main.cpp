#include <Windows.h>
#include <cmath>

DWORD WINAPI Thread1(_In_ LPVOID lpParameter) {
  int i;
  while (true) {
    i++;
  }
  return 0;
}

DWORD WINAPI Thread2(_In_ LPVOID lpParameter) {
  while (true) {
    for (long long i = 0; i < 5000000000; i++)
      ;
    Sleep(10000);
  }

  return 0;
}

DWORD WINAPI Thread3(_In_ LPVOID lpParameter) {
  while (true) {
    for (int i = 0; i < 4000000; i++)
      ;
    Sleep(10);
  }

  return 0;
}

DWORD WINAPI Thread4(_In_ LPVOID lpParameter) {
  LARGE_INTEGER frequency;
  QueryPerformanceFrequency(&frequency);

  LARGE_INTEGER count;
  QueryPerformanceCounter(&count);

  double current_y = 0;

  while (true) {
    for (int i = 0; i < 3000000.0 * (1.0 + current_y); i++)
      ;
    Sleep(10 * (1 - current_y));

    LARGE_INTEGER new_count;
    QueryPerformanceCounter(&new_count);

    auto s = (new_count.QuadPart - count.QuadPart) / frequency.QuadPart;
    current_y = std::sin(s / 30.0 * 2 * 3.1415926535) * 0.6;
  }

  return 0;
}

int main() {
  HANDLE thread1 = CreateThread(NULL, 0, Thread1, NULL, 0, NULL);
  HANDLE thread2 = CreateThread(NULL, 0, Thread2, NULL, 0, NULL);
  HANDLE thread3 = CreateThread(NULL, 0, Thread3, NULL, 0, NULL);
  HANDLE thread4 = CreateThread(NULL, 0, Thread4, NULL, 0, NULL);

  SetThreadAffinityMask(thread1, 1);
  SetThreadAffinityMask(thread2, 1 << 1);
  SetThreadAffinityMask(thread3, 1 << 2);
  SetThreadAffinityMask(thread4, 1 << 3);

  WaitForSingleObject(thread1, INFINITE);
  WaitForSingleObject(thread2, INFINITE);
  WaitForSingleObject(thread3, INFINITE);
  WaitForSingleObject(thread4, INFINITE);

  return 0;
}
