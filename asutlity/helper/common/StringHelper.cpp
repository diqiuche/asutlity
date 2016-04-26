#include "StdAfx.h"
#include "StringHelper.h"

StringHelper::StringHelper(void)
{
}

StringHelper::~StringHelper(void)
{
}

// to
bool StringHelper::ToBool(string value)
{
	if ("True" == value || "true" == value)
	{
		return true;
	}

	return false;
}

int	StringHelper::ToInt(string value)
{
	return atoi(value.c_str());
}

__int64 StringHelper::ToInt64(string value)
{
	return _atoi64(value.c_str());
}

unsigned long StringHelper::ToDword(string value)
{
	unsigned long total_value = 0;

	for (int i = 0; i < (int)value.size(); i++)
	{
		char a_char = value[i];

		long inter_result = 0;

		char upper_a = 'A';

		char lower_a = 'a';

		if (!isdigit(a_char))
		{
			if (!islower(a_char))
			{
				inter_result =  a_char + 10;

				inter_result -= upper_a;
			}
			else
			{
				inter_result =  a_char + 10;

				inter_result -=  lower_a;
			}				
		}
		else
		{
			inter_result = a_char - '0';
		}

		total_value *= 16;

		total_value += inter_result;
	}

	return total_value;
}

float StringHelper::ToFloat(string value)
{
	return (float)atof(value.c_str());
}

double StringHelper::ToDouble(string value)
{
	return atof(value.c_str());
}

wstring	StringHelper::ToWstring(string value)
{
	setlocale (LC_ALL, ".ACP");
	int required_size = mbstowcs(NULL, value.c_str(), 0);
	wchar_t* wide_string = new wchar_t[required_size + 1];
	mbstowcs (wide_string, value.c_str(), required_size + 1);

	wstring ret_string = wide_string;

	if (wide_string != NULL)
	{
		delete[] wide_string;
		wide_string = NULL;
	}

	return ret_string;
}

CTime StringHelper::ToCtime(string value)
{
	CTime netTime = CTime(1980, 01, 01, 0, 0, 0);

	string strTime = value;
	StringHelper::Replace(strTime, " ", "-");
	StringHelper::Replace(strTime, ":", "-");
	vector<string> vec = StringHelper::Split(strTime, "-");
	if (vec.size() < 6)
	{
		return netTime;
	}
	
	int nYear = StringHelper::ToInt(vec.at(0));
	int nMonth = StringHelper::ToInt(vec.at(1));
	int nDay = StringHelper::ToInt(vec.at(2));
	int nHour = StringHelper::ToInt(vec.at(3));
	int nMinte = StringHelper::ToInt(vec.at(4));
	int nSecond = StringHelper::ToInt(vec.at(5));

	netTime = CTime(nYear, nMonth, nDay, nHour, nMinte, nSecond);

	return netTime;
}

CString StringHelper::ToCString(string value)
{
	CString strRtn(value.c_str());
	return strRtn;
}

// from
string StringHelper::FromBool(bool value)
{
	if (value)
	{
		return string("true");
	}

	return string("false");
}

string StringHelper::FromInt(int value)
{
	char value_text[16] = {0};
	memset(value_text, 0, 16);
	return ltoa(value, value_text, 10);
}

string StringHelper::FromInt64(__int64 value)
{
	char value_text[65] = {0};
	memset(value_text, 0, 65);
	return _i64toa(value, value_text , 10);
}

string StringHelper::FromDword(unsigned long value)
{
	char value_text[16] = {0};
	memset(value_text, 0, 16);
	return ultoa(value, value_text , 10);
}

string	StringHelper::FromFloat(float value)
{
	char value_text[64] = {0};
	memset(value_text, 0, 64);

	sprintf(value_text, "%f", value);

	return string(value_text);
}

string StringHelper::FromDouble(double value)
{
	char value_text[128] = {0};
	memset(value_text, 0, 128);

	sprintf(value_text, "%.16f", value);

	return string(value_text);
}

string StringHelper::FromWstring(wstring value)
{
	/*
	int char_number = WideCharToMultiByte(CP_ACP, 0, value.c_str(), -1, NULL, 0, NULL, NULL);

	char *multi_string = new char[char_number];
	WideCharToMultiByte(CP_ACP, 0, value.c_str(), -1, multi_string, char_number, NULL, NULL);

	string ret_string = multi_string;

	AUTO_DELETE(multi_string);

	return ret_string; 
	*/

	setlocale (LC_ALL, ".ACP");

	int required_size = wcstombs (NULL, value.c_str(), 0);
	char* mb_str = new char[ required_size + 1 ];
	wcstombs (mb_str, value.c_str(), required_size + 1);

	string ret_string = mb_str;

	if (mb_str != NULL)
	{
		delete[] mb_str;
		mb_str = NULL;
	}

	return ret_string;
}

string StringHelper::FromCtime(CTime t)
{
	CString strTemp = t.Format("%Y-%m-%d %H:%M:%S");
	string strTime = FromCString(strTemp);
	return strTime;
}

string StringHelper::FromCString(CString str)
{
	wstring strRtn(str);
	return FromWstring(strRtn);
}

// w to
bool StringHelper::WToBool(wstring value)
{
	if (L"True" == value || L"true" == value)
	{
		return true;
	}

	return false;
}

int StringHelper::WToInt(wstring value)
{
	string mb_str = FromWstring(value);
	return ToInt (mb_str);
}

unsigned long StringHelper::WToDword(wstring value)
{
	string mb_str = FromWstring(value);
	return ToDword(mb_str);
}

float StringHelper::WToFloat(wstring value)
{
	string mb_str = FromWstring(value);
	return ToFloat(mb_str);
}

double StringHelper::WToDouble(wstring value)
{
	string mb_str = FromWstring(value);
	return ToDouble(mb_str);
}

// w from
wstring	StringHelper::WFromBool(bool value)
{
	if (value)
	{
		return wstring(L"true");
	}

	return wstring(L"false");
}

wstring	StringHelper::WFromInt(int value)
{
	string mb_str = FromInt(value);
	return ToWstring(mb_str);
}

wstring StringHelper::WFromDword (unsigned long value)
{
	string mb_str = FromDword(value);
	return ToWstring(mb_str);
}

wstring StringHelper::WFromFloat (float value)
{
	string mb_str = FromFloat(value);
	return ToWstring(mb_str);
}

wstring	StringHelper::WFromDouble(double value)
{
	string mb_str = FromDouble(value);
	return ToWstring(mb_str);
}

string StringHelper::ToUpper(const string& strSrc)
{
	string strDest = "";
	if (strSrc == "")
		return strDest;

	strDest = strSrc;
	std::transform(strDest.begin(), strDest.end(), strDest.begin(), toupper);

	return strDest;
}

string StringHelper::ToLower(const string& strSrc)
{
	string strDest = "";
	if (strSrc == "")
		return strDest;

	strDest = strSrc;
	std::transform(strDest.begin(), strDest.end(), strDest.begin(), tolower);

	return strDest;
}

COLORREF StringHelper::ToColorref(string cvalue)
{
	DWORD r,g,b;
	sscanf(cvalue.c_str(), "#%2X%2X%2X", &r, &g, &b);
	COLORREF rgb = RGB(r, g, b);
	return rgb;
}

string StringHelper::FromColorref(COLORREF cvalue)
{
	int r = GetRValue(cvalue);
	int g = GetGValue(cvalue);
	int b = GetBValue(cvalue);

	CString szColor;
	szColor.Format(L"#%02X%02X%02X", r, g, b);

	return FromCString(szColor);
}

// other
vector<string> StringHelper::Split(const string& str, const string& delimiters)
{
	vector<std::string> result;
	for(unsigned int i=0; i<str.size(); i++)
	{
		string::size_type pos = str.find(delimiters, i);
		if (string::npos == pos)
			break;

		if(pos < str.size())
		{
			string sub = str.substr(i, pos-i);
			result.push_back(sub);
			i = pos + delimiters.size()-1;
		}
	}

	string::size_type pos = str.rfind(delimiters);
	int nlastpos = pos + delimiters.size();
	if (pos != string::npos && nlastpos <= str.size() - 1)
	{
		string sub = str.substr(pos+delimiters.size(), str.size() - nlastpos);
		result.push_back(sub);
	}

	return result;
}

double StringHelper::SimilarDegree(const string& sa, const string& sb)
{
	const int sz_a = sa.size() + 1;
	const int sz_b = sb.size() + 1;
	int sz_max = sz_a;
	int sz_min = sz_b;
	const char* longer = sa.data();
	const char* shorter = sb.data();
	if (sz_a < sz_b)
	{
		sz_max = sz_b;
		sz_min = sz_a;
		longer = sb.data();
		shorter = sa.data();
	}

	vector<int> arr(sz_min + 1);
	for (int j=0; j<sz_min; ++j) 
		arr[j+1]=j;

	for (int i=1; i<sz_max; ++i)
	{
		arr[0]=i;
		for (int j=1; j<sz_min; ++j)
		{
			if(longer[i-1] != shorter[j-1]) 
			{
				int tmp = arr[j+1] > arr[j] ? arr[j] : arr[j+1];
				if (tmp > arr[j-1])
					tmp = arr[j-1];

				arr[j] = tmp + 1;
			}
		}

		for(int j = sz_min-1; j>=0; --j) 
			arr[j+1] = arr[j];
	}

	int nDist = arr[sz_min];
	int nMaxNum = max(sa.size(), sb.size());
	double dres = (nMaxNum - nDist) * 1.0 / nMaxNum;

	return dres;
}

bool StringHelper::Replace(string& str_source, string str_search, string str_replace, bool bonce)
{
	if (str_source.empty())
	{
		return false;
	}

	string::size_type pos = 0;
	while((pos = str_source.find(str_search, pos)) != string::npos)
	{
		str_source.replace(pos, str_search.size(), str_replace);
		pos++;

		if (bonce)
			break;
	}

	return true;
}