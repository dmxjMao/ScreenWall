#include "stdafx.h"
#include "Stg.h"
//#include <vector>
#include <algorithm>
#include <functional>
#include <exception>

using std::vector;

//namespace {
//	struct lambdaFindNodeName {
//		bool operator()(const CSSFile::Node& node, const CString& name) {
//			return node.name == name;
//		}
//	};
//};


//����
/*
���ýṹ�嶼�á��ƶ���
operator= �� swap���ڲ���ģ��
*/
//StgNormalCfg::StgNormalCfg(StgNormalCfg&& rhs) noexcept {
//	swap(*this, rhs);
//}
//StgNormalCfg& StgNormalCfg::operator=(const StgNormalCfg& rhs) {
//	swap(*this, const_cast<StgNormalCfg&>(rhs));
//	return *this;
//}
//StgNormalCfg& StgNormalCfg::operator=(StgNormalCfg rhs) {
//	/*���rhs����ֵ����û�п���*/
//	swap(*this, rhs);
//	return *this;
//}
//StgNormalCfg& StgNormalCfg::operator=(StgNormalCfg&& rhs) noexcept{
//	swap(*this, rhs);
//	return *this;
//}
//
//inline void swap(StgNormalCfg& lhs, StgNormalCfg& rhs)
//{
//	using std::swap;
//	swap(lhs.bfloatToolbar, rhs.bfloatToolbar);
//	swap(lhs.bRealtimePreview, rhs.bRealtimePreview);
//	swap(lhs.emColorScheme, rhs.emColorScheme);
//	swap(lhs.emScreenTipStyle, rhs.emScreenTipStyle);
//	swap(lhs.strUsername, rhs.strUsername);
//	swap(lhs.strShortname, rhs.strShortname);
//	swap(lhs.bOpenEmailWhenInReadView, rhs.bOpenEmailWhenInReadView);
//}


//
CSSFile::CSSFile(CString& filename)
{
	/*���ڵ��������ڵ������ڵ����ͣ�
	����һ�ŷ�ƽ�����������δ�ҵ����ʵ����ݽṹ�����б���ǰ���Ҹ��ڵ�ķ�ʽ���ܻ������⣨��˳����ң�����ʱ��
	*/
	//auto& vec = g_GobalVariable.vecCfg;
	//m_liNode = {
	//	Node(_T("STGCFG"),_T(""),Storage), //���ڵ�Ҫ��ֵһ��
	//	Node(_T("Normal"),_T("STGCFG"),Stream, vec[StgCfgEnumNormal], StgCfgEnumNormal),
	//	Node(_T("Revision"),_T("STGCFG"),Storage),
	//	Node(_T("AutoAmend"),_T("Revision"),Storage),
	//	Node(_T("Revision"),_T("Revision"),Stream, vec[StgCfgEnumRevision], StgCfgEnumRevision),
	//	Node(_T("AutoAmend"),_T("AutoAmend"),Stream, vec[StgCfgEnumRevision_AutoAmend], StgCfgEnumRevision_AutoAmend),
	//	Node(_T("Operator"),_T("AutoAmend"),Stream, vec[StgCfgEnumRevision_Operator], StgCfgEnumRevision_Operator)
	//};
	m_vecStorage.resize(3); //��С���ݡ����ýṹͼ��
	//m_vecStreamNode.resize(StgCfgEnumBuff);
	auto& vec = g_GobalVariable.vecCfg;
	m_vecStreamNode = { //λ�������ݡ����ýṹͼ�� /*vector��Ա������ö�٣������ƣ�Ĭ�����ýṹ��λ������idx�����ƣ����ڵ�ָ�룩*/
		StreamNode(StgCfgEnumNormal, _T("����"), vec[StgCfgEnumNormal], vector<StorageNode>({ StorageNode(0, _T("root"), m_vecStorage[0]) })/*λ����*/),
		StreamNode(StgCfgEnumRevision, _T("У��"), vec[StgCfgEnumRevision], 
			vector<StorageNode>({ StorageNode(0, _T("root"), m_vecStorage[0]), StorageNode(1,_T("У��"),m_vecStorage[0]) })),
		StreamNode(StgCfgEnumRevision_AutoAmend,_T("�Զ�����"), vec[StgCfgEnumRevision_AutoAmend],
			vector<StorageNode>({ StorageNode(0,_T("root"),m_vecStorage[0]), StorageNode(1,_T("У��"),m_vecStorage[0]), StorageNode(2,_T("�Զ�����"),m_vecStorage[1]) })),
		StreamNode(StgCfgEnumRevision_Operator,_T("����"), vec[StgCfgEnumRevision_Operator],
			vector<StorageNode>({ StorageNode(0,_T("root"),m_vecStorage[0]), StorageNode(1,_T("У��"),m_vecStorage[0]), StorageNode(2,_T("�Զ�����"),m_vecStorage[1]) }))
	};


	bool bRet = true;
	bRet = OpenSSFile(filename, STGM_READWRITE | STGM_SHARE_EXCLUSIVE);
	if (false == bRet) {
		//�ĵ������ڣ��򴴽�Ĭ������
		//�Ż���Ĭ�������ڰ�װ������д��������ýṹ�����˱仯���ڰ�װ�������ȡ������д������
		try {
			bRet = CreateSSFile(filename);
			if (false == bRet)
				throw std::logic_error("CreateSSFile Failed !");
		}
		catch (std::logic_error err) {
			AfxMessageBox(CA2T(err.what()));
		}
		return;
	}
	else {
		//���洢û�йرգ��ĵ����޷�ɾ����ReleaseStorage��ɾ��
		m_vecStorage[0] = m_pRootStg;
		m_bOpen = true;
	}
		
}

CSSFile::~CSSFile()
{
	ReleaseStorage();
}

bool CSSFile::GetAllCfg()
{
	if (m_bOpen) {
		//�ɹ����ļ������ȡ����						
		return ReadAllCfg();
	}
	else {
		return false;
	}
}

bool CSSFile::GetCfg(StgCfgEnum em, LPSTREAM* pStream)
{
	if (m_bOpen) {
		HRESULT hr = S_OK;
		DWORD mode = STGM_READWRITE | STGM_SHARE_EXCLUSIVE;
		auto& path = m_vecStreamNode[em].vecPos;
		auto it = path.begin();
		std::advance(it, 1);
		for (; it != path.end(); ++it) { //λ����
			StorageNode& stgnode = *it;
			int idx = stgnode.idx;
			if (nullptr == m_vecStorage[idx]) {//������
				LPSTORAGE pParent = stgnode.pParentStorage;
				hr = pParent->OpenStorage(stgnode.name, nullptr, mode, nullptr, 0, &m_vecStorage[idx]);
				if (FAILED(hr)) {//�Ż����ṹ���쳣����
					ReleaseStorage();//�ͷ�vecStorage
					return false;
				}
			}
		}
		// �ڴ洢�������һ���洢�����´�����������ģʽ
		//DWORD sMode = STGM_TRANSACTED;  //�����ĵ���������֧������ģʽ��
		std::advance(it, -1);
		LPSTORAGE pStg = m_vecStorage[(*it).idx];
		//LPSTREAM pStream = nullptr; //��ʱ��������������[out]��Ҫ��**
		//pStream->Release()��Ҫ�Լ����ã�mode�ڴ��ĵ���ʱ��ֻ��READ���������GG��
		hr = pStg->OpenStream(m_vecStreamNode[em].name, nullptr, mode, 0, pStream);
		if (FAILED(hr)) {
			//pStream->Release();
			return false;
		}
		return true;
	}
	else {
		return false;
	}
}

bool CSSFile::CreateSSFile(const CString & filename, DWORD mode)
{
	if (::StgCreateDocfile(filename, mode, 0, &m_pRootStg) != S_OK)
		return false;

	m_bOpen = true;
	//m_strFilename = filename;
	m_vecStorage[0] = m_pRootStg; //����Ĭ��Ϊ��

	//����Ĭ������
	HRESULT hr = S_OK;
	for (auto& node : m_vecStreamNode) {
		auto& path = node.vecPos;
		auto it = path.begin();
		std::advance(it, 1);
		for (; it != path.end();++it) { //λ����
			StorageNode& stgnode = *it;
			int idx = stgnode.idx;
			if (nullptr == m_vecStorage[idx]) {//������
				LPSTORAGE pParent = stgnode.pParentStorage;
				hr = pParent->CreateStorage(stgnode.name, mode, 0, 0, &m_vecStorage[idx]);
				if (FAILED(hr)) {//�Ż����ṹ���쳣����
					//ReleaseStorage();
					ReleaseStorage();//�ͷ�vecStorage
					return false;
				}		
			}
		}
		//�ڴ洢�������һ���洢�����´�����
		std::advance(it, -1);
		LPSTORAGE pStg = m_vecStorage[(*it).idx];
		LPSTREAM pStream = nullptr;
		hr = pStg->CreateStream(node.name, mode, 0, 0, &pStream);
		if (FAILED(hr)) {
			pStream->Release();
			return false;
		}
		else {
			void* pv = nullptr;
			ULONG len = 0;
			TransformBase2Derived(node, pv, len);
			//StgNormalCfg* p = (StgNormalCfg*)pv;
			//p->bfloatToolbar = false;
			//_tcscpy_s(p->szUsername, _T("mao���"));
			//p->szUsername = _T("mao��ã�");
			
			ULONG ulWritten = 0;
			hr = pStream->Write(pv, len, &ulWritten);
			pStream->Release();
		}	
	}

	//����ȱ�㣺��ʼ��m_liNode���ң��������⣻
	//auto it = m_liNode.begin();
	//it->pStorage = m_pRootStg; //��ֵ���ڵ�
	////it->info.pStorage = m_pRootStg;
	//std::advance(it, 1); //�������ڵ�
	//for (; it != m_liNode.end(); ++it) {
	//	Node& node = *it;
	//	Node& parentNode = FindParentNode(it, node.parentName);//���Ҹ��ڵ�

	//	if(Storage == node.type){
	//		hr = parentNode.pStorage->CreateStorage(node.name, mode, 0, 0, &node.pStorage);
	//		if (FAILED(hr)) {//�Ż����ṹ���쳣����
	//			ReleaseStorage();
	//			return false;
	//		}		
	//	}
	//	else/* if (Stream == node.type)*/ {
	//		LPSTREAM pStream = nullptr;
	//		hr = parentNode.pStorage->CreateStream(node.name, mode, 0, 0, &pStream);
	//		if (FAILED(hr)) {
	//			pStream->Release();
	//			return false;
	//		}
	//		else {
	//			ULONG ulWritten(0);
	//			hr = pStream->Write(node.pCfg, sizeof(*node.pCfg), &ulWritten);
	//			pStream->Release();
	//		}			
	//	}
		
	//}

	//StorageData *sd = new StorageData;
	//sd->Stg = m_pRootStg;
	//sd->ParentStg = NULL;
	//m_pCurrentStg = sd;

	return true;
}


void CSSFile::TransformBase2Derived(StreamNode& node, void*& pv, ULONG& len)
{
	//StgNormalCfg* p = nullptr;
	switch (node.em) { //�Ż�����δ���̳й�ϵ��
		MACRO_Trans2Derived(StgCfgEnumNormal, StgNormalCfg);
		MACRO_Trans2Derived(StgCfgEnumRevision, StgRevisionCfg);
		MACRO_Trans2Derived(StgCfgEnumRevision_AutoAmend, StgRevisionCfg_AutoAmend);
		MACRO_Trans2Derived(StgCfgEnumRevision_Operator, StgRevisionCfg_Operator);
	//case StgCfgEnumNormal:
	//	//p = (StgNormalCfg*)node.cfg;
	//	//p->pszShortname = _T("abc");
	//	pv = (StgNormalCfg*)node.cfg;
	//	len = sizeof(StgNormalCfg);
	//	break;
	//case StgCfgEnumRevision_AutoAmend:
	//	pv = (StgRevisionCfg_AutoAmend*)node.cfg;
	//	len = sizeof(StgRevisionCfg_AutoAmend);
	//	break;
	
	}
}


bool CSSFile::OpenSSFile(CString & filename, DWORD mode)
{
	//if (m_bOpen)
	//	Close();

	//bool bRet = true;
	if (StgOpenStorage(filename.GetBuffer(), NULL, mode, NULL, 0, &m_pRootStg) != S_OK) {
		return false;
	}

	//m_bOpen = true;
	//m_strFilename = filename;

	//StorageData *sd = new StorageData;
	//sd->Stg = m_pRootStg;
	//sd->ParentStg = NULL;
	//m_pCurrentStg = sd;
	return true;
	//return bRet;
}

//bool CSSFile::CreateStroage(const CString & name, LPSTORAGE pStorage, DWORD mode)
//{
	//ASSERT(m_pCurrentStg && m_bOpen);

	//LPSTORAGE pStorage;
	//HRESULT hr = m_pCurrentStg->Stg->CreateStorage(name, mode, 0, 0, &pStorage);
	////if (S_OK == hr) {

	////}
	//return hr == S_OK;
//	return true;
//}

//bool CSSFile::OpenStroage(const CString & name, /*LPSTORAGE* pStorage, */DWORD mode)
//{
	/*ASSERT(m_pCurrentStg && m_bOpen);

	IStorage* pStg;
	HRESULT hr = m_pCurrentStg->Stg->OpenStorage(name, NULL, mode, NULL, 0, &pStg);
	if (hr == S_OK) {
		m_pCurrentStg->ParentStg = m_pCurrentStg;
		m_pCurrentStg->Stg = pStg;
	}
	else {
		if (CreateStroage(name, pStg)) {
			StorageData* pSD = new StorageData;
			pSD->ParentStg = m_pCurrentStg;
			pSD->Stg = pStg;

			m_pCurrentStg = pSD;

			return true;
		}

	}*/
//	return false;
//}

//bool CSSFile::CreateStream(const CString & name, LPSTREAM* pStream, DWORD mode)
//{
	//HRESULT hr = m_pCurrentStg->Stg->CreateStream(name, mode, 0, 0, pStream);
	//return hr == S_OK;
//	return true;
//}

//bool CSSFile::OpenStream(const CString & name, LPSTREAM* pStream, DWORD mode)
//{
	//ASSERT(m_pCurrentStg && m_bOpen);

	//HRESULT hr = m_pCurrentStg->Stg->OpenStream(name, 0, mode, 0, pStream);
	//if (S_OK != hr) {
	//	if (!CreateStream(name, pStream)) {
	//		return false;
	//	}
	//}
	//return false;
//}


//void CSSFile::Close()
//{
	//if (m_bOpen)
	//{
	//	// Release all pointers in the open tree:
	//	while (ExitStorage())
	//		;

	//	m_pCurrentStg->Stg->Release();
	//	delete m_pCurrentStg;

	//	m_pCurrentStg = NULL;
	//	m_pRootStg = NULL;
	//}

	//m_bOpen = false;
	//m_strFilename = _T("");
//}


//IStorage * CSSFile::GetRootStorage() const
//{
//	//ASSERT(m_pCurrentStg && m_bOpen);
//
//	return m_pRootStg;
//}

bool CSSFile::IsOpen() const
{
	return m_bOpen;
}

//bool CSSFile::CreateDefaultCfg()
//{
//	return true;
//}

//
//CSSFile::Node& CSSFile::FindParentNode(std::list<Node>::iterator it/*��ǰ�ڵ�*/, const CString& name/*���ڵ���*/)
//{
//	using std::placeholders::_1;
//	auto f = std::bind(lambdaFindNodeName(), _1, name);
//	auto itFind = std::find_if(m_liNode.begin(), it, f);
//	return (*itFind);
//}


void CSSFile::ReleaseStorage()
{
	//�ͷ��ڴ�
	//for (auto& node : m_liNode) {
	//	if (node.pStorage)
	//		node.pStorage->Release();
	//}
	for (auto lp : m_vecStorage) {
		if (lp)
			lp->Release();
	}
	m_bOpen = false;
}


bool CSSFile::ReadAllCfg()
{
	HRESULT hr = S_OK;
	DWORD mode = STGM_READ | STGM_SHARE_EXCLUSIVE;
	/*m_vecStreamNode ��Ա������ö�٣������ƣ�Ĭ�����ýṹ��λ����
	*/
	for (auto& node : m_vecStreamNode) {
		auto& path = node.vecPos;
		auto it = path.begin();
		std::advance(it, 1);
		for (; it != path.end(); ++it) {
			StorageNode& stgnode = *it;
			int idx = stgnode.idx;
			if (nullptr == m_vecStorage[idx]) {//δ��
				LPSTORAGE pParent = stgnode.pParentStorage;
				hr = pParent->OpenStorage(stgnode.name, nullptr, mode, nullptr, 0, &m_vecStorage[idx]);
				if (FAILED(hr)) {//�Ż����ṹ���쳣����
					ReleaseStorage();//�ͷ�m_vecStorage
					return false;
				}
			}
		}
		//��λ���������һ���洢�����¶�ȡ��
		std::advance(it, -1);
		LPSTORAGE pStg = m_vecStorage[(*it).idx];
		LPSTREAM pStream = nullptr;
		hr = pStg->OpenStream(node.name, nullptr, mode, 0, &pStream);
		if (FAILED(hr)) {
			//pStream->Release();  ���Ҫ��Ҫ�أ�
			return false;
		}
		else {
			void* pv = nullptr;
			ULONG len = 0;
			StgCfg* pCfg = g_GobalVariable.vecCfg[node.em];
			StreamNode stTmp(node.em, _T(""), pCfg, vector<StorageNode>());//ֻ����ʱ����
			TransformBase2Derived(stTmp, pv, len);

			//StgNormalCfg stRead;
			//stRead.pszUsername = _T("hello,word!");
			/*stRead.bfloatToolbar = false;
			stRead.nScreenTipStyle = 100;
			len = sizeof(StgNormalCfg);*/
			ULONG ulRead = 0;
			hr = pStream->Read(pv, len, &ulRead);
			//hr = pStream->Read(&stRead, len, &ulRead);
			StgNormalCfg* p = (StgNormalCfg*)pv;
			pStream->Release();
		}
	}

	return true;
}