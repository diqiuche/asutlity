#include "StdAfx.h"
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1
#include "md2.h"
#include "md4.h"
#include "md5.h"
#include "sha.h"
#include "des.h"
#include "aes.h"
#include "rsa.h"
#include "dsa.h"
#include "hex.h"
#include "modes.h"
#include "osrng.h"
#include "files.h"
#include "base64.h"
#include "eccrypto.h"
#include "oids.h"
#include "asn.h"
#include "integer.h"
#include "iconv.h"
#include "EncodingHelper.h"
using namespace CryptoPP;

EncodingHelper::EncodingHelper(void)
{
}

EncodingHelper::~EncodingHelper(void)
{
}

char EncodingHelper::DecHex(int n)
{
	if (0 <= n && n <= 9)
	{
		return char(short('0') + n);
	}
	else if (10 <= n && n <= 15)
	{
		return char(short('A') + n - 10);
	}
	else
	{
		return char(0);
	}
}

int EncodingHelper::HexDec(char c)
{
	if ('0'<=c && c<='9')
	{
		return short(c-'0');
	}
	else if ('a'<=c && c<='f')
	{
		return (short(c-'a') + 10);
	}
	else if ('A'<=c && c<='F')
	{
		return (short(c-'A') + 10);
	}
	else
	{
		return -1;
	}
}

string EncodingHelper::HexEncode(const string& strSrc)
{
	string strDest = "";
	if (strSrc == "")
		return strDest;

	StringSource(strSrc.c_str(), true, new HexEncoder(new StringSink(strDest)));

	return strDest;
}

string EncodingHelper::HexDecode(const string& strSrc)
{
	string strDest = "";
	if (strSrc == "")
		return strDest;

	StringSource(strSrc.c_str(), true, new HexDecoder(new StringSink(strDest)));

	return strDest;
}

string EncodingHelper::UrlEncode(const string& str_source)
{
	// 不编码字符0-9 a-z A-Z - _ . / ! ~ * ' ( )
	string strResult = "";
	for (unsigned int i=0; i<str_source.size(); i++)
	{
		char c = str_source[i];
		if (('0'<=c && c<='9') ||
			('a'<=c && c<='z') ||
			('A'<=c && c<='Z') ||
			c=='-' || c=='_' || c=='.')
		{
			strResult += c;
		}
		else if (c==' ')
		{
			strResult +='+';
		}
		else
		{
			int j = (short int)c;
			if (j < 0)
			{
				j += 256;
			}

			int i1 = j / 16;
			int i0 = j - i1*16;
			strResult += '%';
			strResult += DecHex(i1);
			strResult += DecHex(i0);
		}
	}

	return strResult;
}

string EncodingHelper::UrlDecode(const string& str_source)
{
	string result = "";
	for (unsigned int i=0; i<str_source.size(); i++)
	{
		char c = str_source[i];
		if(c == '+')
		{
			result += ' ';
		}
		else if (c != '%')
		{
			result += c;
		}
		else
		{
			char c1 = str_source[++i];
			char c0 = str_source[++i];
			int num = 0;
			num += HexDec(c1) * 16 + HexDec(c0);
			result += char(num);
		}
	}

	return result;
}

char* EncodingHelper::IconvConvert(const char* szSrc, string strFromCode, string strToCode)
{
	char* szResult = NULL;
	iconv_t conveter = iconv_open(strToCode.c_str(), strFromCode.c_str());
	if(conveter== iconv_t(-1))
	{
		return szResult;
	}

	// 待转换的字符串
	const char* input = szSrc;
	size_t insize = strlen(input);

	// 存储转换结果的字符串
	size_t outsize = insize * 3 + 1;
	szResult = new char[outsize];
	char* output_old = szResult;//记录转换后的字符串的地址
	memset(szResult, 0, outsize);

	size_t ret = iconv(conveter, &input, &insize, &output_old, &outsize);
	if(ret==(size_t)-1)
	{
		iconv_close(conveter);
		return szResult;
	}

	iconv_close(conveter);

	return szResult;
}

string EncodingHelper::MbUtf8(const string& str_mb)
{
	string str_utf8 = "";
	if (str_mb.empty())
		return str_utf8;

	// 方法：先转换成CP_ACP再转换成CP_UTF8
	int nLength = MultiByteToWideChar(CP_ACP, 0, str_mb.c_str(), -1, NULL, NULL);   // 获取缓冲区长度，再分配内存
	wchar_t* tch = new wchar_t[nLength];
	memset(tch, 0, nLength);

	nLength = MultiByteToWideChar(CP_ACP, 0, str_mb.c_str(), -1, tch, nLength);   // 将MBCS转换成Unicode

	int nUTF8len = WideCharToMultiByte(CP_UTF8, 0, tch, -1, 0, 0, 0, 0);     // 获取UTF-8编码长度
	char* utf8_string = new char[nUTF8len];
	memset(utf8_string, 0, nUTF8len);
	WideCharToMultiByte(CP_UTF8, 0, tch, -1, utf8_string, nUTF8len, 0, 0);   //转换成UTF-8编码

	if (tch != NULL)
	{
		delete[] tch;
		tch = NULL;
	}

	str_utf8 = utf8_string;

	if (utf8_string != NULL)
	{
		delete[] utf8_string;
		utf8_string = NULL;
	}

	return str_utf8;
}

string EncodingHelper::Utf8Mb(const string& str_utf8)
{
	string str_mb = "";
	int nLen = str_utf8.size();
	if (nLen <= 0)
		return str_mb;

	// convert an UTF8 string to widechar
	int nWLen = MultiByteToWideChar(CP_UTF8, 0, str_utf8.c_str(), -1, NULL, 0);
	WCHAR* strTemp = new WCHAR[nWLen];
	memset(strTemp, 0, nWLen);
	if(NULL == strTemp)
	{
		return str_mb;
	}

	int nRtn = MultiByteToWideChar(CP_UTF8, 0, str_utf8.c_str(), -1, strTemp, nWLen);
	if(nRtn == 0)
	{
		if (strTemp != NULL)
		{
			delete[] strTemp;
			strTemp = NULL;
		}
		return str_mb;
	}

	// convert an widechar string to Multibyte  
	int MBLen = WideCharToMultiByte(CP_ACP, 0, strTemp, -1, NULL, 0, NULL, NULL);  
	if(0 == MBLen)
	{
		if (strTemp != NULL)
		{
			delete[] strTemp;
			strTemp = NULL;
		}
		return str_mb;
	}

	char* str = new char[MBLen];
	memset(str, 0, MBLen);
	if(NULL == str)
	{
		return str_mb;
	}

	nRtn = WideCharToMultiByte(CP_ACP, 0, strTemp, -1, str, MBLen, NULL, NULL); 
	if(0 == nRtn)
	{
		if (strTemp != NULL)
		{
			delete[] strTemp;
			strTemp = NULL;
		}

		if (str != NULL)
		{
			delete[] str;
			str = NULL;
		}
		return str_mb;
	}

	// 最后释放所有的变量
	str_mb = str;

	if (strTemp != NULL)
	{
		delete[] strTemp;
		strTemp = NULL;
	}

	if (str != NULL)
	{
		delete[] str;
		str = NULL;
	}

	return str_mb;
}

string SingleUnicodeChinese(const string& src)
{
	string strRet = "";
	CString strText(src.c_str());
	int nCount = strText.Replace(_T("\\u"), _T(" 0x"));

	wchar_t* buf = new wchar_t[nCount + 1];
	memset(buf, 0, sizeof(wchar_t)*(nCount + 1));

	int nIndex = 0;
	TCHAR seps[] = _T(" ");
	TCHAR* token = _tcstok(strText.GetBuffer(strText.GetLength()), seps);
	while (NULL != token)
	{
		buf[nIndex++] = (wchar_t)_tcstoul(token, NULL, 16);
		token = _tcstok(NULL, seps);
	}

	strRet = (LPSTR)(LPCTSTR)CString(buf);
	if (buf != NULL)
	{
		delete[] buf;
		buf = NULL;
	}

	return strRet;
}

string EncodingHelper::UnicodeChinese(const string& src)
{
	string strRet = "";
	char* pSrc = (char*)src.c_str();
	for (size_t i = 0; i < src.size(); )
	{
		if ((i < src.size() - 5) &&
			pSrc[i] == '\\'  && 
			pSrc[i+1] == 'u' &&
			isxdigit(pSrc[i+2]) &&
			isxdigit(pSrc[i+3]) &&
			isxdigit(pSrc[i+4]) &&
			isxdigit(pSrc[i+5]))
		{
			char chTemp[32] = {0};
			sprintf(chTemp, "%c%c%c%c%c%c", pSrc[i], pSrc[i+1], pSrc[i+2], pSrc[i+3], pSrc[i+4], pSrc[i+5]);
			string strTemp = SingleUnicodeChinese(chTemp);
			strRet += strTemp;
			i += 6;
		}
		else
		{
			strRet.push_back(pSrc[i]);
			i++;
		}
	}

	return strRet;
}

string EncodingHelper::ChineseUnicode(const string& src)
{
	string str_unicode = "";
	if (src.empty())
		return str_unicode;

	int len = src.size();
	const int bufferSize = len; // 4*len 目前暂时设置为len好像没问题
	WCHAR* buffer = new WCHAR[bufferSize];
	memset(buffer, 0, sizeof(WCHAR)*(bufferSize));
	MultiByteToWideChar(CP_ACP, 0, src.c_str(), -1, buffer, bufferSize); 

	for(int i=0; i<len/2; i++)
	{
		str_unicode += "\\u";

		int nCode = buffer[i];
		int nDec = (nCode) / (16*16*16);
		char szHex = DecHex(nDec);
		str_unicode += tolower(szHex);

		nCode = nCode - (nCode) / (16*16*16)*16*16*16;
		nDec = (nCode) / (16*16);
		szHex = DecHex(nDec);
		str_unicode += tolower(szHex);

		nCode = nCode - (nCode) / (16*16)*16*16;
		nDec = (nCode)/16;
		szHex = DecHex(nDec);
		str_unicode += tolower(szHex);

		nCode = nCode - nCode / 16*16;
		nDec = nCode;
		szHex = DecHex(nDec);
		str_unicode += tolower(szHex);
	}

	if (buffer != NULL)
	{
		delete[] buffer;
		buffer = NULL;
	}

	return str_unicode;
}

string EncodingHelper::Base64Encode(const string& strSrc)
{
	string strDest = "";
	if (strSrc == "")
		return strDest;

	StringSource(strSrc.c_str(), true, new Base64Encoder(new StringSink(strDest)));

	return strDest;
}

string EncodingHelper::Base64EncodeJPG(const string& strFileName)
{
	string strDest = "";
	if (strFileName == "")
		return strDest;

	FileSource(strFileName.c_str(), true, new Base64Encoder(new StringSink(strDest)));

	return strDest;
}

string EncodingHelper::Base64Decode(const string& strSrc)
{
	string strDest = "";
	if (strSrc == "")
		return strDest;

	StringSource(strSrc.c_str(), true, new Base64Decoder(new StringSink(strDest)));

	return strDest;
}