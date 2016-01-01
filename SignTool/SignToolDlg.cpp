
// SignToolDlg.cpp : ʵ���ļ�
//
#include "stdafx.h"
#include "../DRAutoPackageTool/SignHelper.h"
#include <string>
#include "SignTool.h"
#include "SignToolDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSignToolDlg �Ի���

CSignToolDlg::CSignToolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSignToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSignToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSignToolDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CSignToolDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &CSignToolDlg::OnEnChangeMfceditbrowse1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSignToolDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CSignToolDlg ��Ϣ�������

BOOL CSignToolDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSignToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSignToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSignToolDlg::OnBnClickedButton1()
{
	//TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_MFCEDITBROWSE1, str);
	std::wstring path(str);
	if (path.length() > 0)
	{
		wchar_t buf[1000];
		int i = 1000;
		GetCurrentDirectory(1000, buf);  //�õ���ǰ����·��
		SignHelper heper(std::wstring(buf) + L"\\signtool\\");
		if (heper.SignSinaFile(path))
		{
			SetDlgItemText(IDC_STATIC, L"�ɹ�");
		}
		else
		{
			SetDlgItemText(IDC_STATIC, L"ʧ��");
		}
		UpdateData(FALSE);
	}
}


void CSignToolDlg::OnEnChangeMfceditbrowse1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CSignToolDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString str;
	GetDlgItemText(IDC_MFCEDITBROWSE2, str);
	std::wstring path(str);
	if (path.length() > 0)
	{
		path += L"\\";
		wchar_t buf[1000];
		int i = 1000;
		GetCurrentDirectory(1000, buf);  //�õ���ǰ����·��
		SignHelper heper(std::wstring(buf) + L"\\signtool\\");
		if (heper.SignSinaFolder(path, L"*.exe") && heper.SignSinaFolder(path, L"*.dll"))
		{
			SetDlgItemText(IDC_STATIC, L"�ɹ�");
		}
		else
		{
			SetDlgItemText(IDC_STATIC, L"ʧ��");
		}
		UpdateData(FALSE);
	}
}
