
// stdafx.cpp : source file that includes just the standard includes
// StructuredStorage.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "Stg.h"


//��ȡ�����߳�
unsigned int __stdcall ReadStgCfgThread(PVOID pv);


CGobalVariable::CGobalVariable()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//m_ssFile = new CSSFile;
	hEventReadStgCfg = CreateEvent(nullptr, TRUE, FALSE, nullptr);//�ֶ�δ����
}

CGobalVariable::~CGobalVariable()
{
	//pStgRoot->Release();
	//SAFE_DELETE(m_ssFile);

	for (auto& p : vecCfg) {
		SAFE_DELETE(p);
	}
	//strStgCfgname.ReleaseBuffer(); //�ڴ�й¶

	//_CrtDumpMemoryLeaks();
}


/*�Ż�����Ҫ��stdafx��д���룬��һ�£�����stdafx.h���ļ�ȫ���ر࣡*/
bool CGobalVariable::Init()
{
	//_CrtMemState s1,s2,s3;
	//_CrtMemCheckpoint(&s1);

	//��������Ŀ¼
	GetModuleFileName(AfxGetInstanceHandle(), szExePath, MAX_PATH);
	TCHAR* pFind = _tcsrchr(szExePath, '\\');
	szExePath[_tcslen(szExePath) - _tcslen(pFind) + 1] = '\0';

	//��ȡ����
	strStgCfgname = g_GobalVariable.szExePath;
	strStgCfgname += _T("STGCFG.stg");//�����ļ���
	
	vecCfg.resize(StgCfgEnumBuff);
	vecCfg[StgCfgEnumNormal] = new StgNormalCfg;
	//vecCfg[StgCfgEnumRevision] = new StgRevisionCfg;
	//vecCfg[StgCfgEnumRevision_AutoAmend] = new StgRevisionCfg_AutoAmend;
	//vecCfg[StgCfgEnumRevision_Operator] = new StgRevisionCfg_Operator;
	//vecCfg[StgCfgEnumSave] = new StgSaveCfg(sizeof(StgSaveCfg));

	//_CrtMemCheckpoint(&s2);
	//_CrtMemDifference(&s3, &s1, &s2);
	//_CrtMemDumpStatistics(&s3);

	//��ȡ�����߳�
	unsigned int nThreadID(0);
	HANDLE hThread = (HANDLE)_beginthreadex(nullptr, 0, ReadStgCfgThread, nullptr, 0, &nThreadID);
	CloseHandle(hThread); hThread = nullptr;

	return true;
}


unsigned int __stdcall ReadStgCfgThread(PVOID pv)
{
	//_CrtMemState s1, s2, s3;
	//_CrtMemCheckpoint(&s1);

	unsigned int nRet = 0;

	//�������ĵ�����ȡ����
	CSSFile* pSSFile = new CSSFile(g_GobalVariable.strStgCfgname);
	nRet = pSSFile->GetAllCfg();
	SAFE_DELETE(pSSFile);
	//delete pSSFile; pSSFile = nullptr;
	//�û�������ò˵��ڵȴ�
	SetEvent(g_GobalVariable.hEventReadStgCfg);

	//_CrtMemCheckpoint(&s2);
	//_CrtMemDifference(&s3, &s1, &s2);
	//_CrtMemDumpStatistics(&s3);

	return nRet;
}