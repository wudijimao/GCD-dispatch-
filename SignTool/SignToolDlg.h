
// SignToolDlg.h : ͷ�ļ�
//

#pragma once


// CSignToolDlg �Ի���
class CSignToolDlg : public CDialogEx
{
// ����
public:
	CSignToolDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SIGNTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnEnChangeMfceditbrowse1();
	afx_msg void OnBnClickedButton2();
};
