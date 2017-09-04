#include "stdafx.h"
#include "SSFile.h"
#include "ScreenWall.h"

using std::vector;

CSSFile::CSSFile(CString filename)
{

	m_vecStorage.resize(2); //��С���ݡ����ýṹͼ��
	auto& vecCfg = g_GobalVariable.vecCfg;
	m_vecStreamNode = { 
		//λ�������ݡ����ýṹͼ�� /*vector��Ա������ö�٣������ƣ�Ĭ�����ýṹ��λ������idx�����ƣ����ڵ�ָ�룩*/
		StreamNode(StgCfgEnum_LoginUser, _T("�û�"), vecCfg[StgCfgEnum_LoginUser], vector<StorageNode>({ StorageNode(0, _T("root"), m_vecStorage[0]) })/*λ����*/)/*,
																																				  StreamNode(StgCfgEnumRevision, _T("У��"), vec[StgCfgEnumRevision],
																																				  vector<StorageNode>({ StorageNode(0, _T("root"), m_vecStorage[0]), StorageNode(1,_T("У��"),m_vecStorage[0]) })),
																																				  StreamNode(StgCfgEnumRevision_AutoAmend,_T("�Զ�����"), vec[StgCfgEnumRevision_AutoAmend],
																																				  vector<StorageNode>({ StorageNode(0,_T("root"),m_vecStorage[0]), StorageNode(1,_T("У��"),m_vecStorage[0]), StorageNode(2,_T("�Զ�����"),m_vecStorage[1]) })),
																																				  StreamNode(StgCfgEnumRevision_Operator,_T("����"), vec[StgCfgEnumRevision_Operator],
																																				  vector<StorageNode>({ StorageNode(0,_T("root"),m_vecStorage[0]), StorageNode(1,_T("У��"),m_vecStorage[0]), StorageNode(2,_T("�Զ�����"),m_vecStorage[1]) }))*/
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
		for (; it != path.end(); ++it) { //λ����
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

			StgCfg* p = node.cfg;
			p->Write(pStream);
		}
	}

	return true;
}



bool CSSFile::OpenSSFile(CString & filename, DWORD mode)
{
	//if (m_bOpen)
	//	Close();

	if (StgOpenStorage(filename.GetBuffer(), NULL, mode, NULL, 0, &m_pRootStg) != S_OK) {
		return false;
	}

	return true;
}


bool CSSFile::IsOpen() const
{
	return m_bOpen;
}



void CSSFile::ReleaseStorage()
{
	//�ͷ��ڴ�
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
			StgCfg* pCfg = g_GobalVariable.vecCfg[node.em];

			pCfg->Read(pStream);
		}
	}

	return true;
}