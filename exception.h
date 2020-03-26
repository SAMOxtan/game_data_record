#ifndef EXCEPTION_H_INCLUDED
#define EXCEPTION_H_INCLUDED
#include "conio.h"

#include "setjmp.h"

jmp_buf Jump_Buffer;

#define try if(!setjmp(Jump_Buffer))

#define catch else

#define throw longjmp(Jump_Buffer,1)

#endif // EXCEPTION_H_INCLUDED
