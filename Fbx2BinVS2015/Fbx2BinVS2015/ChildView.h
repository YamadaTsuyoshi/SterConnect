
// ChildView.h : CChildView �N���X�̃C���^�[�t�F�C�X
//


#pragma once
#include "DxWindow.h"


// CChildView �E�B���h�E

class CChildView : public CWnd
{
	CDxWindow m_DxWindow;
// �R���X�g���N�V����
public:
	CChildView();

// ����
public:

// ����
public:

// �I�[�o�[���C�h
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ����
public:
	virtual ~CChildView();

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

