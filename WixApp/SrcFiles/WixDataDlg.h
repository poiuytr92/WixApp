

#pragma once
#include "ComboBox.h"
#include "Resource.h"
#include "afxwin.h"


// WixDataDlg dialog

class WixDataDlg : public CDialogEx {

  DECLARE_DYNAMIC(WixDataDlg)

public:

enum { IDD = IDD_DIALOG1 };           // Dialog Data

CEdit     wixNameEB;
CEdit     companyEB;
CEdit     productNameEB;
CEdit     wixVersionEB;
CEdit     progFtrIconEB;

ComboBox  groupCB;

ComboBox  componentCB;
CEdit     descriptionEB;
CEdit     pathEB;

CButton   startMenuCH;
CButton   deskTopCH;
CButton   versionAvailCH;
CButton   isOnPathCH;
CButton   isWin7ch;
CButton   isWinXPch;
CButton   isWin2Kch;

ComboBox  iconCB;
CEdit     progFileEB;
CEdit     startMenuEB;


  WixDataDlg(CWnd* pParent = NULL);
  virtual ~WixDataDlg();

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

  afx_msg void OnAppAbout();

public:

  afx_msg void OnFileNew();
  afx_msg void OnFileOpen();
  afx_msg void OnFileRecent();

  afx_msg void OnLeaveWixname();
  afx_msg void OnLeaveWixVersion();

  afx_msg void OnLeaveCompanyname();

  afx_msg void OnLeaveProductname();

  afx_msg void OnBrowseCtrlPanelIcon();

  afx_msg void OnChangeGroup();
  afx_msg void OnLeavingGroup();
  afx_msg void OnNewGroup();
  afx_msg void OnDeleteGroup();

  afx_msg void OnChangeComponent();
  afx_msg void OnLeavingComponent();
  afx_msg void OnNewComponent();
  afx_msg void OnDeleteComponent();

  afx_msg void OnBrowseComponentPath();

  afx_msg void OnLeavingDescription();

  afx_msg void OnUpdateIcon();
  afx_msg void OnBrowseForIcon();

  afx_msg void OnLeavingProgFile();

  afx_msg void OnLeavingStartMenu();

  afx_msg void createProduct();
  afx_msg void OnBnClickedCancel();

  afx_msg void OnLbnSelchangeList1();
  afx_msg void OnBnClickedOnstartmenu();
  afx_msg void OnBnClickedOndesktop();
  afx_msg void OnBnClickedVersionavail();
  afx_msg void OnBnClickedOnPath();
  afx_msg void OnBnClickedIsWin7();
  afx_msg void OnBnClickedIsWinXP();
  afx_msg void OnBnClickedIsWin2K();
  afx_msg void OnGetSolution();
  afx_msg void OnBnClickedButton1();

private:

  void loadFeatures();
public:
  afx_msg void OnOptions();
};
