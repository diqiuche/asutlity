/*!
* Copyright (c) 2016,airsurfish team.
* WebSite:http://www.eyusoft.com
* Official Author QQ:1473849376
* OpenSource:Apache License 2.0
*
* \file RegexHelper.h
* \brief 类声明
*
* \date 2016年04月26日
* \version 1.0
*/
#pragma once

// 正则表达式
class ASUTLITY_EXT_CLASS RegexHelper
{
public:
	RegexHelper(void);
	~RegexHelper(void);

public:
	static string		   Replace(const string& src, const string& exp, const string& rp);
	static vector<string>  ReplaceList(const vector<string>& src, const string& exp, const string& rp);

	static string		   Match(const string& src, const string& exp);
	static vector<string>  MatchList(const string& src, const string& exp);
	static vector<string>  MatchList(const vector<string>& src, const string& exp);

	static void			   Trim(string& src, const string& searcher);
	static void		       TrimList(vector<string>& v_src_list, const string& searcher);

	static void            TrimLeftRight(string& src, const string& searcher);
	static void			   TrimLeft(string& src, const string& searcher);
	static void			   TrimRight(string& src, const string& searcher);
};