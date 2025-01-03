/*****************************************************************************
* | File      	:	Debug.h
* | Author      :   Waveshare team
* | Function    :	debug with printf
* | Info        :
*   Image scanning
*      Please use progressive scanning to generate images or fonts
*----------------
* |	This version:   V1.0
* | Date        :   2018-01-11
* | Info        :   Basic version
*
******************************************************************************/
#ifndef __DEBUG_H
#define __DEBUG_H

#include "esp_log.h"

#define USE_DEBUG 1
#if USE_DEBUG
	#define Debug(__info) ESP_LOG_INFO("esp" ,__info)
#else
	#define Debug(__info)  
#endif

#endif

