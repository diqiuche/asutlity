/*!
* Copyright (c) 2016,airsurfish team.
* WebSite:http://www.eyusoft.com
* Official Author QQ:1473849376
* OpenSource:Apache License 2.0
*
* \file EncodingHelper.h
* \brief 类声明
*
* \date 2016年04月26日
* \version 1.0
*/
#pragma once

// 加密解密类
class ASUTLITY_EXT_CLASS EncodingHelper
{
public:
	EncodingHelper(void);
	~EncodingHelper(void);

public:
	// 十进制/十六进制转换
	static char	  DecHex(int n);
	static int	  HexDec(char c);

	// Hex编码/解码
	static string HexEncode(const string& strSrc);
	static string HexDecode(const string& strSrc);

	// Url编码/解码
	static string UrlEncode(const string& strSrc);
	static string UrlDecode(const string& strSrc);

	// ICONV字符编码转码
	static char*  IconvConvert(const char* szSrc, string strFromCode, string strToCode);

	// MB/UTF-8转码
	static string MbUtf8(const string& strMb);
	static string Utf8Mb(const string& strUtf8);

	// Unicode/中文转码
	static string UnicodeChinese(const string& strUnicode);
	static string ChineseUnicode(const string& strChinese);

	// Base64编码/解码
	static string Base64Encode(const string& strSrc);
	static string Base64Decode(const string& strSrc);
	static string Base64EncodeJPG(const string& strFileName);
};