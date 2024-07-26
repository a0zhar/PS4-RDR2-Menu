#pragma once
#ifndef _INVOKER_HH
#define _INVOKER_HH

#include "../types.h"
#include <utility>

// Internal RAGE stuff???
struct NativeArg_s {
	uint64_t *returnValue;  // Pointer to store the return value from the native function call
	uint32_t argCount;	    // Number of arguments passed to the native function
	uint8_t  padding1[4];   // Padding for alignment
	uint64_t *argValues;    // Pointer to Array that holds the values of the arguments passed to the native function
	uint32_t vectorCount;   // Number of vector arguments passed to the native function
	uint8_t  padding2[4];   // Padding for alignment
	Vector3 *argVectors[4]; // Array of pointers to Vector3 structures (allowing up to 4 vector3 args)
	Vector4 tempVectors[4]; // Temporary storage for up to 4 Vector4 structures, used during processing or conversions
};

extern NativeArg_s nativeArg;
extern void resetArgs();
extern void setVectors();

// Used to push an argument of any type to the native argument list
template<typename T>
inline void pushArg(T value) {
	// Assign the value to the next position in the argument array
	// and increment the argument count
	*(T *)&nativeArg.argValues[nativeArg.argCount++] = value;
}

// Gets the return value of a specified type from the native call.
template<typename R>
inline R getReturn() { return *(R *)&nativeArg.returnValue[0]; }

// Used to invoke a native function with a specified return type and arguments
template<typename N, typename... A>
N invoke(uint64_t nativeAddress, A &&... args) {
	resetArgs(); // Reset argument count and values before invocation

	// Unpack and push all the arguments to the native argument list
	int dummy[] = { 0, ((void)pushArg(std::forward<A>(args)), 0) ... };

	// Call the native function at the given address with the prepared arguments
	((void(*)(NativeArg_s *))(void *)nativeAddress)(&nativeArg);
	setVectors();

	// Return the value of the specified return type
	return getReturn<N>();
}
#endif