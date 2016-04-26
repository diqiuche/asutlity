/*!
* Copyright (c) 2016,airsurfish team.
* WebSite:http://www.eyusoft.com
* Official Author QQ:1473849376
* OpenSource:Apache License 2.0
*
* \file GuidHelper.h
* \brief 类声明
*
* \date 2016年04月26日
* \version 1.0
*/
#pragma once

// GUID 生成
class ASUTLITY_EXT_CLASS GuidHelper
{
public:
	GuidHelper(void);
	~GuidHelper(void);

public:
	static wstring CreateGuidWstring(void);

	static string  CreateGuidString(void);

	static GUID    CreateGuid(void);
};
