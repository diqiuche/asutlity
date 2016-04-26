#include "StdAfx.h"
#include "GuidHelper.h"
#pragma comment(lib,"rpcrt4.lib")

GuidHelper::GuidHelper(void)
{
}

GuidHelper::~GuidHelper(void)
{
}

wstring GuidHelper::CreateGuidWstring(void)
{
	GUID guid;
	CoCreateGuid(&guid);

	RPC_WSTR wsGuid = NULL;
	UuidToString(&guid, &wsGuid);

	wstring str_ret = (LPCWSTR)wsGuid;

	RpcStringFree(&wsGuid);

	return str_ret;
	
}

string GuidHelper::CreateGuidString(void)
{
	return StringHelper::FromWstring(CreateGuidWstring());
}

GUID GuidHelper::CreateGuid(void)
{
	GUID guid;
	CoCreateGuid(&guid);

	return guid;
}