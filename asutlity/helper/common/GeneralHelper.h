/*!
* Copyright (c) 2016,airsurfish team.
* WebSite:http://www.eyusoft.com
* Official Author QQ:1473849376
* OpenSource:Apache License 2.0
*
* \file GeneralHelper.h
* \brief 类声明
*
* \date 2016年04月26日
* \version 1.0
*/
#pragma once

// call back
ASUTLITY_EXT_CLASS long writer(void* data, int size, int nmemb, string& content);

ASUTLITY_EXT_CLASS long fwriter(void* data, int size, size_t nmemb, void* stream);