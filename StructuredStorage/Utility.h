#pragma once

#define SAFE_DELETE(p)	\
if((p)){	\
delete (p); (p) = nullptr;	\
}

/*�����������ҵ�����λ�ã�Ȼ��д��
cfg_type �ṹ����
cfg_member �ṹ��Ա
*/
#define MACRO_StgWrite2Pos(cfg_type, cfg_member) \
	size_t pos = offsetof(cfg_type, cfg_member);	\
	LARGE_INTEGER li;	\
	li.QuadPart = pos;	\
	HRESULT hr = m_pStream->Seek(li, STREAM_SEEK_SET, nullptr);	\
	hr = m_pStream->Write(&m_pCfg->cfg_member, sizeof(m_pCfg->cfg_member), nullptr);

/*ת������ָ��
em ����ṹö��
cfg_type �ṹ����
*/
#define MACRO_Trans2Derived(em,cfg_type)	\
	case em:	\
	pv = (cfg_type*)node.cfg;	\
	len = sizeof(cfg_type);	\
	break;


typedef unsigned(__stdcall* PTHREAD_START)(void*);//__beginthreadex

LRESULT EnableWindowTheme(HWND hwnd, LPCWSTR classList, LPCWSTR subApp, LPCWSTR idlist);
