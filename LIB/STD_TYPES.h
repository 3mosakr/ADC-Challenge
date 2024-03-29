#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef enum {
	E_OK,
	E_NOT_OK,
	E_NOK_NULL_PTR,
	E_NOK_OUT_OF_RANGE
}ReturnType_State_t;

typedef unsigned char u8;
typedef unsigned long int u32;
typedef unsigned long long int u64;
typedef unsigned short int u16;

typedef signed char s8;
typedef signed long int s32;
typedef signed long long int s64;
typedef signed short int s16;

typedef float f32;
typedef double f64;
typedef long double f128;

typedef void (*ptrToFunc_void)(void);
 #define NULL (void *)0

#endif // STD_TYPES_H_
