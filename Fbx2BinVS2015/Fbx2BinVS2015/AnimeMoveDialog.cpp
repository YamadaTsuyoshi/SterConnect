// AnimeMoveDialog.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "Fbx2BinVS2015.h"
#include "AnimeMoveDialog.h"
#include "afxdialogex.h"


// CAnimeMoveDialog �_�C�A���O

IMPLEMENT_DYNAMIC(CAnimeMoveDialog, CDialogEx)

CAnimeMoveDialog::CAnimeMoveDialog(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ANIME_MOVE, pParent)
	, m_FrameRate(_T("10"))
	, m_AnimeStartSec(_T("0"))
	, m_AnimeEndSec(_T("1"))
	, m_IsLooped(TRUE)
{

}

CAnimeMoveDialog::~CAnimeMoveDialog()
{
}

void CAnimeMoveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FRAME_RATE, m_FrameRate);
	DDV_MaxChars(pDX, m_FrameRate, 2);
	DDX_Text(pDX, IDC_EDIT_ANIME_START_SEC, m_AnimeStartSec);
	DDV_MaxChars(pDX, m_AnimeStartSec, 4);
	DDX_Text(pDX, IDC_EDIT_ANIME_END_SEC, m_AnimeEndSec);
	DDV_MaxChars(pDX, m_AnimeEndSec, 4);
	DDX_Check(pDX, IDC_CHECK_LOOP, m_IsLooped);
}


BEGIN_MESSAGE_MAP(CAnimeMoveDialog, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAnimeMoveDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CAnimeMoveDialog ���b�Z�[�W �n���h���[


void CAnimeMoveDialog::OnBnClickedOk()
{
	UpdateData(TRUE);
	if (_wtoi(m_FrameRate) <= 0) {
		AfxMessageBox(L"�t���[�����[�g��0�ȉ��͐ݒ�ł��܂���B");
		return;
	}

	if (_wtoi(m_AnimeStartSec) < 0) {
		AfxMessageBox(L"�X�^�[�g��0�����͐ݒ�ł��܂���B");
		return;
	}
	if (_wtoi(m_AnimeStartSec) >= _wtoi(m_AnimeEndSec)) {
		AfxMessageBox(L"�X�^�[�g���I���͑傫���Ȃ���΂Ȃ�܂���B");
		return;
	}


	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
	CDialogEx::OnOK();
}


BOOL CAnimeMoveDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}
