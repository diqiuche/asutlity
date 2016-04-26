#include "StdAfx.h"
#include "DirectoryHelper.h"
#include <shlwapi.h>

DirectoryHelper::DirectoryHelper(void)
{
}

DirectoryHelper::~DirectoryHelper(void)
{
}

bool DirectoryHelper::DirectoryValid(const string str_path)
{
	BOOL b_valid = PathFileExistsA(str_path.c_str());

	return (b_valid ? true : false);
}

bool DirectoryHelper::CreateDirectory(const string str_path)
{
	return (SHCreateDirectoryExA(NULL, str_path.c_str(), NULL) == ERROR_SUCCESS);
}

void DirectoryHelper::CopyDirectory(const string str_src_dir, const string str_des_dir)
{
	string src_dir = str_src_dir + "\\";
	string des_dir = str_des_dir + "\\";

	// 创建子目录
	vector<string> f_list;
	DirectoryHelper::GetRelativeSubDirectory(src_dir, "", f_list);
	for (unsigned int i=0; i<f_list.size(); i++)
	{
		string str_src_sub = src_dir + f_list.at(i);
		string str_des_sub = des_dir + f_list.at(i);
		DirectoryHelper::CreateDirectory(str_des_sub);
		DirectoryHelper::CopyDirectory(str_src_sub, str_des_sub);
	}
	f_list.clear();

	DirectoryHelper::GetRelativeDirectoryFileExt(src_dir, "", "*", f_list);
	for (unsigned int i=0; i<f_list.size(); i++)
	{
		string src_file = src_dir + f_list.at(i);
		string des_file = des_dir + f_list.at(i);
		::CopyFileA(src_file.c_str(), des_file.c_str(), true);
	}
	f_list.clear();
}

bool DirectoryHelper::DeleteDirectory(const string str_path)
{
	if (DirectoryHelper::PathFileExist(str_path) == false)
		return true;

	string str_input = str_path;

	LPWIN32_FIND_DATAA fd = NULL;
	HANDLE h_find = NULL;

	string str_file = str_input + "\\*";
	string str_directory  = str_input + "\\";	
	BOOL b_working = false;

	h_find = FindFirstFileA(str_file.c_str(), fd);
	while(h_find)
	{
		b_working = FindNextFileA(h_find, fd);

		if (!b_working) { break; }


		if ((fd->cFileName == ".") || (fd->cFileName == ".."))  { continue; }

		if (fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			string str_dir_path;
			str_dir_path = str_directory + fd->cFileName;
			DeleteDirectory(str_dir_path.c_str());
		}

		DeleteFileA((str_directory + fd->cFileName).c_str());
	}

	FindClose(h_find);
	h_find = NULL;

	RemoveDirectoryA(str_path.c_str());

	return true;
}

void DirectoryHelper::RenameDirectoryFile(const string str_path, const string str_ext, const string str_new_ext)
{
	vector<string> v_listfile;
	DirectoryHelper::GetDirectoryFile(str_path, str_ext, v_listfile);
	for (unsigned int i=0; i<v_listfile.size(); i++)
	{
		string str_file = v_listfile.at(i);
		string str_new_file = str_file + "." + str_new_ext;
		DirectoryHelper::RenameFile(str_file, str_new_file);
	}

	vector<string> v_subdir;
	DirectoryHelper::GetSubDirectory(str_path, v_subdir);
	for (unsigned int i=0; i<v_subdir.size(); i++)
	{
		string str_dirtemp = v_subdir.at(i);
		DirectoryHelper::RenameDirectoryFile(str_dirtemp, str_ext, str_new_ext);
	}
}

void DirectoryHelper::DeleteDirectoryFile(const string str_path, const string str_ext)
{
	vector<string> v_listfile;
	DirectoryHelper::GetDirectoryFile(str_path, str_ext, v_listfile);
	for (unsigned int i=0; i<v_listfile.size(); i++)
	{
		string str_file = v_listfile.at(i);
		DirectoryHelper::DeleteFile(str_file);
	}

	vector<string> v_subdir;
	DirectoryHelper::GetSubDirectory(str_path, v_subdir);
	for (unsigned int i=0; i<v_subdir.size(); i++)
	{
		string str_dirtemp = v_subdir.at(i);
		DeleteDirectoryFile(str_dirtemp, str_ext);
	}
}

string DirectoryHelper::GetCurrentDirectory()
{
	char szpath[MAX_PATH] = {0};
	GetModuleFileNameA(NULL, szpath, MAX_PATH); 
	string str_path = szpath;
	int npos = str_path.rfind("\\");
	str_path = str_path.substr(0, npos);

	return str_path;
}

string DirectoryHelper::GetTempDirectory()
{
	char szpath[MAX_PATH] = {0};
	::GetTempPathA(sizeof(szpath), szpath);
	string str_path(szpath);

	return str_path;
}

string DirectoryHelper::GetDesktopDirectory()
{
	char szPath[MAX_PATH] = {0};
	SHGetSpecialFolderPathA(NULL, szPath, CSIDL_DESKTOP, 0);
	string str_path(szPath);

	return str_path;
}

void DirectoryHelper::GetRelativeSubDirectory(const string str_dir, const string str_pre, vector<string>& v_list)
{
	string str_input = str_dir;
	if (str_input.rfind("\\") != (str_input.size() - 1))
		str_input += "\\";

	LPWIN32_FIND_DATAA fd = NULL;
	HANDLE h_find = NULL;

	string str_file = str_input + "*";
	string str_directory  = str_input;
	BOOL b_working   = false;

	h_find = FindFirstFileA(str_file.c_str(), fd);
	while(h_find)
	{
		b_working = FindNextFileA(h_find, fd);

		if (!b_working) { break; }

		if ((fd->cFileName == ".") || (fd->cFileName == ".."))  { continue; }

		if (fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			string str_dir_path = string(str_pre) + fd->cFileName;
			v_list.push_back(str_dir_path);

			GetRelativeSubDirectory((str_directory + fd->cFileName).c_str(), str_dir_path.c_str(), v_list);
		}
	}

	FindClose(h_find);
	h_find = NULL;
}

void DirectoryHelper::GetSubDirectory(const string str_dir, vector<string>& v_list)
{
	string str_input = str_dir;
	if (str_input.rfind("\\") != (str_input.size() - 1)) 
		str_input += "\\";

	LPWIN32_FIND_DATAA fd = NULL;
	HANDLE h_find = NULL;

	string str_file = str_input + "*";
	string str_directory  = str_input;
	BOOL b_working   = false;

	h_find = FindFirstFileA(str_file.c_str(), fd);
	while(h_find)
	{
		b_working = FindNextFileA(h_find, fd);

		if (!b_working) { break; }

		if ((fd->cFileName == ".") || (fd->cFileName == ".."))  { continue; }

		if (fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			string str_dir_path = str_directory + fd->cFileName;
			v_list.push_back(str_dir_path);
		}
	}

	FindClose(h_find);
	h_find = NULL;
}

void DirectoryHelper::GetDirectoryFile(const string str_path, const string str_ext, vector<string>& v_list)
{
	string str_dir = string(str_path);
	if (str_dir.rfind("\\") != (str_dir.size() - 1)) 
		str_dir += "\\";

	string str_file = str_dir + "*." + str_ext;

	LPWIN32_FIND_DATAA fd = NULL;
	HANDLE h_file = NULL;

	BOOL v_working = true;
	for (h_file = FindFirstFileA(str_file.c_str(), fd); h_file != INVALID_HANDLE_VALUE; v_working = FindNextFileA(h_file, fd))
	{	
		if (!v_working)
			break;

		if ((fd->cFileName == ".") || (fd->cFileName == "..")) 
		{
			continue;
		}

		if (fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			continue;
		}

		string str_file_path;
		str_file_path = str_dir + fd->cFileName;
		v_list.push_back(str_file_path);
	}

	FindClose(h_file);
	h_file = NULL;
}

void DirectoryHelper::GetRelativeDirectoryFileExt(const string str_path, const string str_pre, const string str_ext, vector<string>& v_list)
{
	string str_dir = (string)str_path;
	if (str_dir.rfind("\\") != (str_dir.size() - 1)) 
		str_dir += "\\";

	string str_file = str_dir + "*." + str_ext;

	LPWIN32_FIND_DATAA fd = NULL;
	HANDLE h_file = NULL;

	bool b_use_all = false;
	h_file = FindFirstFileA(str_file.c_str(), fd);
	if (h_file == INVALID_HANDLE_VALUE)
	{
		string str_file_ext = str_dir + "*.*";
		h_file = FindFirstFileA(str_file_ext.c_str(), fd);
		if (h_file == INVALID_HANDLE_VALUE)
			return;

		b_use_all = true;
	}

	BOOL v_working = true;
	for (; h_file != INVALID_HANDLE_VALUE; v_working = FindNextFileA(h_file, fd))
	{
		if (v_working == false)
			break;

		if ((fd->cFileName == ".") || (fd->cFileName == "..")) 
		{
			continue;
		}

		if (fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			string str_sub_dir = str_dir + fd->cFileName;
			string str_sub_pre = string(str_pre) + fd->cFileName;
			GetRelativeDirectoryFileExt(str_sub_dir.c_str(), str_sub_pre.c_str(), str_ext, v_list);
		}
		else 
		{
			if (!b_use_all)
			{
				string str_file_path;
				str_file_path = string(str_pre) + fd->cFileName;
				v_list.push_back(str_file_path);
			}
		}		
	}

	FindClose(h_file);
	h_file = NULL;
}

void DirectoryHelper::GetDirectoryFileExt(const string str_path, const string str_ext, vector<string>& v_list)
{
	string str_dir = (string)str_path;
	if (str_dir.rfind("\\") != (str_dir.size() - 1)) 
		str_dir += "\\";

	string str_file = str_dir + "*." + str_ext;

	LPWIN32_FIND_DATAA fd = NULL;
	HANDLE h_file = NULL;

	bool b_use_all = false;
	h_file = FindFirstFileA(str_file.c_str(), fd);
	if (h_file == INVALID_HANDLE_VALUE)
	{
		string str_file_ext = str_dir + "*.*";
		h_file = FindFirstFileA(str_file_ext.c_str(), fd);
		if (h_file == INVALID_HANDLE_VALUE)
			return;

		b_use_all = true;
	}

	BOOL v_working = true;
	for (; h_file != INVALID_HANDLE_VALUE; v_working = FindNextFileA(h_file, fd))
	{
		if (v_working == false)
			break;

		if ((fd->cFileName == ".") || (fd->cFileName == "..")) 
		{
			continue;
		}

		if (fd->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			GetDirectoryFileExt((str_dir +  fd->cFileName).c_str(), str_ext, v_list);
		}
		else 
		{
			if (!b_use_all)
			{
				string str_file_path;
				str_file_path = str_dir + fd->cFileName;
				v_list.push_back(str_file_path);
			}
		}
	}

	FindClose(h_file);
	h_file = NULL;
}

string DirectoryHelper::GetCurrentFile()
{
	char szpath[MAX_PATH] = {0};
	GetModuleFileNameA(NULL, szpath, MAX_PATH);
	string str_path = szpath;
	return str_path;
}

bool DirectoryHelper::PathFileExist(const string str_file)
{
	return (PathFileExistsA(str_file.c_str()) ? true : false);
}

string DirectoryHelper::GetFilePath(const string str_in_path)
{
	string str_link = str_in_path;
	string::size_type v_pos = str_link.find_last_of('/');
	if(v_pos != string::npos)
	{
		str_link = str_link.substr(0, v_pos + 1);
	}
	else
	{
		string::size_type v_pos = str_link.find_last_of('\\');
		if(v_pos != string::npos)
			str_link = str_link.substr(0, v_pos + 1);
	}

	return str_link;
}

string DirectoryHelper::GetFileName(const string str_in_path)
{
	string str_link = str_in_path;
	string::size_type v_pos = str_link.find_last_of('/');
	if(v_pos != string::npos)
	{
		str_link = str_link.substr(v_pos+1, str_link.size() - v_pos);
	}
	else
	{
		string::size_type v_pos = str_link.find_last_of('\\');
		if(v_pos != string::npos)
			str_link = str_link.substr(v_pos+1, str_link.size() - v_pos);
	}

	return str_link;
}

string DirectoryHelper::GetFileNameWithoutExt(const string str_file)
{
	string str_file_name = GetFileName(str_file);
	int v_pos = (int)str_file_name.rfind(".");
	if (v_pos > 0)
		return str_file_name.substr(0, v_pos);

	str_file_name.clear();
	return str_file_name;
}

string DirectoryHelper::GetFileExt(const string str_in_path)
{
	string str_in = str_in_path;
	int v_pos = (int)str_in.rfind(".");
	if (v_pos > 0)
		return str_in.substr(v_pos+1, str_in.size() - v_pos );

	str_in.clear();
	return str_in;
}

string DirectoryHelper::GetFileWithoutExt(const string str_in_path)
{
	string str_in = str_in_path;
	int v_pos = (int)str_in.rfind(".");
	if (v_pos > 0)
		return str_in.substr(0, v_pos);

	str_in.clear();
	return str_in;
}

void DirectoryHelper::RenameFile(const string old_file, const string new_file)
{
	::rename(old_file.c_str(), new_file.c_str());
}

bool DirectoryHelper::CopyFile(const string str_src, const string str_desc, bool bfaillexist)
{
	BOOL rtn = ::CopyFileA(str_src.c_str(), str_desc.c_str(), bfaillexist);
	return (rtn == TRUE);
}

void DirectoryHelper::DeleteFile(const string str_file)
{
	::DeleteFileA(str_file.c_str());
}

bool DirectoryHelper::FilePathDialog(string& str_file, const string str_filter, bool bopen)
{
	CString strFilePathName;
	CFileDialog dlg(bopen, //TRUE为OPEN对话框，FALSE为SAVE AS对话框
		NULL,
		NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		(LPCTSTR)str_filter.c_str(),
		NULL);
	if(dlg.DoModal() == IDOK)
	{
		strFilePathName = dlg.GetPathName(); //文件名保存在了FilePathName里
	}
	else
	{
		strFilePathName = "";
	}

	str_file = StringHelper::FromCString(strFilePathName);

	return (str_file != "");
}

bool DirectoryHelper::DirectoryPathDialog(string& str_file, HWND hwnd)
{
	// 选择文件夹
	CHAR pszPath[MAX_PATH] = {0};
	BROWSEINFO bi;
	bi.hwndOwner      = hwnd;
	bi.pidlRoot       = NULL;
	bi.pszDisplayName = NULL;
	bi.lpszTitle      = TEXT("请选择文件夹");
	bi.ulFlags        = BIF_RETURNONLYFSDIRS | BIF_STATUSTEXT;
	bi.lpfn           = NULL;
	bi.lParam         = 0;
	bi.iImage         = 0;

	LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
	if (pidl == NULL)
	{
		AfxMessageBox(L"请选择文件夹！");
		return false;
	}

	SHGetPathFromIDListA(pidl, pszPath);

	// 配置文件夹
	str_file = pszPath;

	return (str_file != "");
}