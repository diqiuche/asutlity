/*!
* Copyright (c) 2016,airsurfish team.
* WebSite:http://www.eyusoft.com
* Official Author QQ:1473849376
* OpenSource:Apache License 2.0
*
* \file DirectoryHelper.h
* \brief 类声明
*
* \date 2016年04月26日
* \version 1.0
*/
#pragma once

// 目录操作类
class ASUTLITY_EXT_CLASS DirectoryHelper
{
public:
	DirectoryHelper(void);
	~DirectoryHelper(void);

public:
	static bool   DirectoryValid(const string str_path);

	static bool   CreateDirectory(const string str_path);

	static void   CopyDirectory(const string src_dir, const string des_dir);

	static bool   DeleteDirectory(const string str_path);

	static void   RenameDirectoryFile(const string str_path, const string str_ext, const string str_new_ext);

	static void   DeleteDirectoryFile(const string str_path, const string str_ext);

	static string GetCurrentDirectory();

	static string GetTempDirectory();

	static string GetDesktopDirectory();

	static void   GetSubDirectory(const string str_dir, vector<string>& v_list);

	static void   GetRelativeSubDirectory(const string str_dir, const string str_pre, vector<string>& v_list);

	static void   GetDirectoryFile(const string str_dir, const string str_ext, vector<string>& v_list);

	static void   GetDirectoryFileExt(const string str_path, const string str_ext, vector<string>& v_list);

	static void   GetRelativeDirectoryFileExt(const string str_path, const string str_pre, const string str_ext, vector<string>& v_list);

public:
	static string GetCurrentFile();

	static bool   PathFileExist(const string str_file);

	static string GetFilePath(const string str_file);

	static string GetFileName(const string str_file);

	static string GetFileNameWithoutExt(const string str_file);

	static string GetFileExt(const string str_file);

	static string GetFileWithoutExt(const string str_file);

	static void   RenameFile(const string old_file, const string new_file);

	static bool   CopyFile(const string str_src, const string str_desc, bool bfaillexist = true);

	static void   DeleteFile(const string str_file);

	// 对话框函数
public:
	// 过滤 txt files (*.txt)|*.txt|All Files (*.*)|*.*||
	static bool   FilePathDialog(string& str_file, const string str_filter, bool bopen = true);
	static bool   DirectoryPathDialog(string& str_file, HWND hwnd);
};
