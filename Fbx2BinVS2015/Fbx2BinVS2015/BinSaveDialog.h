#pragma once


// CBinSaveDialog �_�C�A���O

class CBinSaveDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CBinSaveDialog)

public:
	CBinSaveDialog(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CBinSaveDialog();
	CString m_FileDir;
	CString m_FileNameNoExt;
	CString m_FileExt;



// �_�C�A���O �f�[�^
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SAVE_BINFILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	CString m_FullBinFileName;
	afx_msg void OnClickedButtonUpdateExt();
	virtual BOOL OnInitDialog();
	CString m_Scale;
	BOOL m_IsNowScale;
};
