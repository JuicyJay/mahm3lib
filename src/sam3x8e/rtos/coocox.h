/**
 *******************************************************************************
 * @file       coocox.h
 * @version    V1.13    
 * @date       2010.04.26
 * @brief      Gather for all header file of CooCox CoOS.	
 *******************************************************************************
 * @copy
 *
 * INTERNAL FILE,DON'T PUBLIC.
 * 
 * <h2><center>&copy; COPYRIGHT 2009 CooCox </center></h2>
 *******************************************************************************
 */ 


#ifndef _COOCOX_H
#define _COOCOX_H

#define  OS_VERSION       (U16)0x0113   /*!< OS version.(format: Vx.xx), 	
                                            e.g. value 0x0113 is version V1.13*/
/*---------------------------- Include ---------------------------------------*/
#include "CoOS.h"
#include "OsArch.h"
#include "OsCore.h"
#include "OsTask.h"
#include "OsServiceReq.h"
#include "OsError.h"
#include "OsTime.h"

#ifndef NULL
#define NULL          ((void *)0)
#endif



#if CFG_TMR_EN > 0
	#include "OsTimer.h"
#endif

#if CFG_KHEAP_EN > 0
	#include "OsKernelHeap.h"
#endif

#if CFG_MM_EN >0
	#include "OsMM.h"
#endif

#if CFG_EVENT_EN > 0
	#include "OsEvent.h"
#endif

#if CFG_MUTEX_EN > 0
	#include "OsMutex.h"
#endif

#if CFG_QUEUE_EN > 0
	#include "OsQueue.h"
#endif

#if CFG_FLAG_EN	 > 0
	#include "OsFlag.h"
#endif

#endif    /* _COOCOX_H    */  
