#include "os_related.h"
 
double FileTimeToDouble(FILETIME* pFiletime)
{
	return (double)((*pFiletime).dwHighDateTime * 4.294967296E9) + (double)(*pFiletime).dwLowDateTime;
}
 
double m_fOldCPUIdleTime;
double m_fOldCPUKernelTime;
double m_fOldCPUUserTime;
 
int Initialize() 
{
	FILETIME ftIdle, ftKernel, ftUser;
	BOOL flag = FALSE;
	if (flag = GetSystemTimes(&ftIdle, &ftKernel, &ftUser))
	{
		m_fOldCPUIdleTime = FileTimeToDouble(&ftIdle);
		m_fOldCPUKernelTime = FileTimeToDouble(&ftKernel);
		m_fOldCPUUserTime = FileTimeToDouble(&ftUser);
 
	}
	return flag;
}
 
int GetCPUUseRate()
{
	int nCPUUseRate = -1;
	FILETIME ftIdle, ftKernel, ftUser;
	if (GetSystemTimes(&ftIdle, &ftKernel, &ftUser))
	{
		double fCPUIdleTime = FileTimeToDouble(&ftIdle);
		double fCPUKernelTime = FileTimeToDouble(&ftKernel);
		double fCPUUserTime = FileTimeToDouble(&ftUser);
		nCPUUseRate= (int)(100.0 - (fCPUIdleTime - m_fOldCPUIdleTime) / (fCPUKernelTime - m_fOldCPUKernelTime + fCPUUserTime - m_fOldCPUUserTime)*100.0);
		m_fOldCPUIdleTime = fCPUIdleTime;
		m_fOldCPUKernelTime = fCPUKernelTime;
		m_fOldCPUUserTime = fCPUUserTime;
	}
	return nCPUUseRate;
}
