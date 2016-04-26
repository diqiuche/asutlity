#include "StdAfx.h"
#include "RegexHelper.h"

#include <regex>
using namespace std::tr1;

RegexHelper::RegexHelper(void)
{
}

RegexHelper::~RegexHelper(void)
{
}

string RegexHelper::Replace(const string& src, const string& exp, const string& rp)
{
	regex expression(exp);
	string str_new =  regex_replace(src, expression, rp);
	return str_new;
}

vector<string> RegexHelper::ReplaceList(const vector<string>& src, const string& exp, const string& rp)
{
	vector<string> vec_new;
	for (unsigned int i=0; i<src.size(); i++)
	{
		string str_src = src.at(i);
		string str_new = Replace(str_src, exp, rp);
		vec_new.push_back(str_new);
	}

	return vec_new;
}

string RegexHelper::Match(const string& src, const string& exp)
{
	string str_match = "";
	regex expression(exp);
	std::string::const_iterator start = src.begin();
	std::string::const_iterator end = src.end();
	match_results<std::string::const_iterator> matchList; 
	while (regex_search(start, end, matchList, expression))
	{
		str_match = matchList[0].str().c_str();
		break;
	}

	return str_match;
}

vector<string> RegexHelper::MatchList(const string& src, const string& exp)
{
	vector<string> vec_match;

	regex expression(exp);
	std::string::const_iterator start = src.begin();
	std::string::const_iterator end = src.end();
	match_results<std::string::const_iterator> matchList; 
	while (regex_search(start, end, matchList, expression))
	{
		string str_match = matchList[0].str().c_str();
		start = matchList[0].second;
		vec_match.push_back(str_match);
	}

	return vec_match;
}

vector<string>  RegexHelper::MatchList(const vector<string>& src, const string& exp)
{
	vector<string> vec_match;

	for (unsigned int i=0; i<src.size(); i++)
	{
		string str_temp = src.at(i);
		string str_result = RegexHelper::Match(str_temp, exp);
		vec_match.push_back(str_result);
	}

	return vec_match;
}

void RegexHelper::Trim(string& src, const string& searcher)
{
	if (src == "" || searcher == "")
		return;

	int pos = 0;
	while (pos != -1)
	{
		pos = src.find(searcher);
		if( pos == -1 )
		{
			break;
		}
		else
		{
			src.erase(pos, searcher.length());
		}
	}
}

void RegexHelper::TrimList(vector<string>& v_src_list, const string& searcher)
{
	for (unsigned int i=0; i<v_src_list.size(); i++)
	{
		string& str = v_src_list.at(i);
		Trim(str, searcher);
	}
}

void RegexHelper::TrimLeftRight(string& src, const string& searcher)
{
	TrimLeft(src, searcher);
	TrimRight(src, searcher);
}

void RegexHelper::TrimLeft(string& src, const string& searcher)
{
	if (src == "" || searcher == "")
		return;

	int pos = 0;
	while (pos != -1)
	{
		pos = src.find(searcher);
		if(pos == -1 || pos != 0)
		{
			break;
		}
		else
		{
			src.erase(pos, searcher.length());
		}
	}
}

void RegexHelper::TrimRight(string& src, const string& searcher)
{
	if (src == "" || searcher == "")
		return;

	int pos = 0;
	while (pos != -1)
	{
		int despos = src.size() - searcher.size();
		pos = src.rfind(searcher);
		if(pos == -1 || pos != despos)
		{
			break;
		}
		else
		{
			src.erase(pos, searcher.length());
		}
	}
}