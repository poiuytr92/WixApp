// Options.cpp : implementation file
//

#include "stdafx.h"
#include "Options.h"
#include "DefaultPath.h"
#include "GetPathDlg.h"
#include "WixApp.h"
//#include "afxdialogex.h"


static TCchar* DefLicensePathKey = _T("LicensePath");


// Options dialog

IMPLEMENT_DYNAMIC(Options, CDialogEx)

Options::Options(CWnd* pParent) : CDialogEx(Options::IDD, pParent), allowSameVer(FALSE), addLic(false) { }

Options::~Options() { }





void Options::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Check(pDX, IDC_AllowSameVer, allowSameVer);
  DDX_Control(pDX, IDC_AddLicense, addLicenseCH);
  DDX_Control(pDX, IDC_License, licensePathEB);
}


BEGIN_MESSAGE_MAP(Options, CDialogEx)
  ON_BN_CLICKED(IDC_AddLicense, &Options::OnAddLicense)
END_MESSAGE_MAP()




BOOL Options::OnInitDialog() {
  CDialogEx::OnInitDialog();

  addLicenseCH.SetCheck(addLic);

  licensePathEB.SetWindowText(String(licPath));

  return TRUE;
  }


// Options message handlers


void Options::OnAddLicense() {
TCchar* defPath;

  addLic = addLicenseCH.GetCheck()  != 0;

  if (addLic) {
    defPath = defaultPath.get(DefLicensePathKey);

    getPathDlg(_T("License RTF file"),  defPath, _T("*"), _T(""), licPath.full());

    defaultPath.add(DefLicensePathKey, licPath.full());

    licensePathEB.SetWindowText(String(licPath));
    }

  else {licPath.clear();  licensePathEB.SetWindowText(_T(""));}
  }
