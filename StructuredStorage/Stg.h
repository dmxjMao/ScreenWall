#pragma once

/*
���ýṹ�嶼�á��ƶ���
*/

enum StgCfgs {
	StgCfgs_Normal,
	StgCfgs_Revision,
	StgCfgs_Save,
	StgCfgs_Custom,
	StgCfgs_Buff
};

enum StgNormalColorScheme {
	StgNormalColorScheme_Red,
	StgNormalColorScheme_Green,
	StgNormalColorScheme_Blue,
	StgNormalColorScheme_Buff
};
//const CString StgNormalColorScheme

enum StgNormalScreenTipStyle {
	StgNormalScreenTipStyle_1,
	StgNormalScreenTipStyle_2,
	StgNormalScreenTipStyle_3,
	StgNormalScreenTipStyle_Buff
};

struct StgNormalCfg {
	bool bfloatToolbar = true;
	bool bRealtimePreview = true;
	StgNormalColorScheme  emColorScheme = StgNormalColorScheme_Green;
	StgNormalScreenTipStyle emScreenTipStyle = StgNormalScreenTipStyle_1;
	CString strUsername;
	CString strShortname;
	bool bOpenEmailWhenInReadView = false;

	//��������
	//������ֵ
	//�ƶ�����
	//�ƶ���ֵ
	//����
	//StgNormalCfg() {}
	//StgNormalCfg::StgNormalCfg(StgNormalCfg&& rhs) noexcept;
	//StgNormalCfg& operator=(const StgNormalCfg& rhs);
	//StgNormalCfg& operator=(StgNormalCfg rhs);
	StgNormalCfg& operator=(StgNormalCfg&& rhs) noexcept;
	friend void swap(StgNormalCfg& lhs, StgNormalCfg& rhs);
};