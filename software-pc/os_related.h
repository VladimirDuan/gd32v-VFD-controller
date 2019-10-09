#ifndef __OS_RELATED_H
#define __OS_RELATED_H

#include <windows.h>
#include <stdio.h>
#include <conio.h>
double FileTimeToDouble(FILETIME* pFiletime);
int Initialize();
int GetCPUUseRate();

#endif
