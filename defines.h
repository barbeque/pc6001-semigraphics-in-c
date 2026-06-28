#ifndef _DEFINES_H_
#define _DEFINES_H_

#define TRUE 0xff
#define FALSE 0
#define BOOL unsigned char

// I was seeing some visual corruption, disabling the stdio
// stuff seems to have helped.
#pragma define CRT_ENABLE_STDIO=0

#endif