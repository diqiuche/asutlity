/*!
* Copyright (c) 2016,airsurfish team.
* WebSite:http://www.eyusoft.com
* Official Author QQ:1473849376
* OpenSource:Apache License 2.0
*
* \file asUtlityDLL.h
* \brief 类声明
*
* \date 2016年04月26日
* \version 1.0
*/
#pragma once

#include <windows.h>
#ifdef  ASUTLITY_EXPORTS
#define ASUTLITY_EXT_CLASS	__declspec(dllexport)
#else
#define ASUTLITY_EXT_CLASS	__declspec(dllimport)
#endif