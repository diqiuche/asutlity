/*!
* Copyright (c) 2016,airsurfish team.
* WebSite:http://www.eyusoft.com
* Official Author QQ:1473849376
* OpenSource:Apache License 2.0
*
* \file StringHelper.h
* \brief 类声明
*
* \date 2016年04月26日
* \version 1.0
*/
#pragma once

// 字符串常用类
class ASUTLITY_EXT_CLASS StringHelper
{
public:
	StringHelper(void);
	~StringHelper(void);

public:
	static bool			  ToBool(string value);
	static int			  ToInt(string value);// base = 10
	static __int64		  ToInt64(string value);// base = 19
	static unsigned long  ToDword(string value);// base = 16
	static float		  ToFloat(string value);
	static double		  ToDouble(string value);
	static wstring		  ToWstring(string value);
	static CTime          ToCtime(string value);
	static CString        ToCString(string value);

public:
	static string		  FromBool(bool value);
	static string		  FromInt(int value);// base = 10
	static string		  FromInt64(__int64 value);// base = 19
	static string		  FromDword(unsigned long value);// base = 16
	static string		  FromFloat(float value);
	static string		  FromDouble(double value);
	static string		  FromWstring(wstring value);
	static string		  FromCtime(CTime t);
	static string         FromCString(CString str);

public:
	// unicode version
	static bool			  WToBool(wstring value);
	static int			  WToInt(wstring value);
	static unsigned long  WToDword(wstring value);
	static float	      WToFloat(wstring value);
	static double	      WToDouble(wstring value);

public:
	// w from
	static wstring		  WFromBool(bool value);
	static wstring	      WFromInt(int value);
	static wstring		  WFromDword(unsigned long value);
	static wstring		  WFromFloat(float value);
	static wstring		  WFromDouble(double value);

public:
	static string         ToUpper(const string& strSrc);
	static string         ToLower(const string& strSrc);

public:
	// color(COLORREF中颜色的排列是BGR)
	static COLORREF       ToColorref(string cvalue = "#CE0000");
	static string         FromColorref(COLORREF cvalue = 3452212);

public:
	static vector<string> Split(const string& str, const string& delimiters);
	static double		  SimilarDegree(const string& sa, const string& sb);
	static bool		      Replace(string& str_source, string str_search, string str_replace, bool bonce = false);
};