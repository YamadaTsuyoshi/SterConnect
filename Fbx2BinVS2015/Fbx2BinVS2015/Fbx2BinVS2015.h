
// Fbx2BinVS2015.h : Fbx2BinVS2015 �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C��
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH �ɑ΂��Ă��̃t�@�C�����C���N���[�h����O�� 'stdafx.h' ���C���N���[�h���Ă�������"
#endif

#include "resource.h"       // ���C�� �V���{��


// CFbx2BinVS2015App:
// ���̃N���X�̎����ɂ��ẮAFbx2BinVS2015.cpp ���Q�Ƃ��Ă��������B
//

class CFbx2BinVS2015App : public CWinApp
{
	HWND m_DxHWnd;
public:
	CFbx2BinVS2015App();
	void CreateAppScene(HWND hWnd);


// �I�[�o�[���C�h
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual BOOL OnIdle(LONG lCount);

// ����

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFbx2BinVS2015App theApp;
