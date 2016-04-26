#include "StdAfx.h"
#include "GeneralHelper.h"

long writer(void* data, int size, int nmemb, string& content)
{
	long sizes = size * nmemb;
	string temp((char*)data, sizes);
	content += temp;
	return sizes;
}

long fwriter(void* data, int size, size_t nmemb, void* stream)
{
	int written = fwrite(data, size, nmemb, (FILE*)stream);
	return written;
}