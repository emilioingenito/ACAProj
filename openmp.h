#ifdef _OPENMP
#include <omp.h>
#else
inline int omp_get_thread_num()
{
  return 0;
}
inline int omp_get_max_threads()
{
  return 1;
}
inline int omp_set_num_threads(int num_threads)
{
  return 1;
}
inline int __sync_fetch_and_add(int* ptr, int value)
{
  int tmp = *ptr;
  ptr[0] += value;
  return tmp;
}
#endif

