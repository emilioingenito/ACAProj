#ifndef TYPES_H
#define TYPES_H
enum ForceStyle {FORCELJ, FORCEEAM};


struct double2 {
  double x, y;
};
struct float2 {
  float x, y;
};
struct double4 {
  double x, y, z, w;
};
struct float4 {
  float x, y, z, w;
};

#ifndef CHUNKSIZE
#define CHUNKSIZE 64
#endif

#ifdef NOCHUNK
#define OMPFORSCHEDULE  #pragma omp for schedule(static)
#else
#define OMPFORSCHEDULE  #pragma omp for schedule(static,CHUNKSIZE)
#endif

#ifndef PRECISION
#define PRECISION 2
#endif
#if PRECISION==1
typedef float MMD_float;
typedef float2 MMD_float2;
typedef float4 MMD_float4;
#else
typedef double MMD_float;
typedef double2 MMD_float2;
typedef double4 MMD_float4;
#endif
typedef int MMD_int;
typedef int MMD_bigint;


#ifndef PAD4
#define PAD 3
#else
#define PAD 4
#endif

#ifdef __INTEL_COMPILER
#ifndef ALIGNMALLOC
#define ALIGNMALLOC 64
#endif
#define RESTRICT __restrict
#endif


#ifndef RESTRICT
#define RESTRICT
#endif
#endif
