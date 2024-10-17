// OpenCVDlgDlg.h : 헤더 파일
#pragma once
#include "ColorButton.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/types_c.h>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <map>
#include <vector>
#include <fstream>
#include <Shlobj.h>
using namespace cv;

// COpenCVDlgDlg 대화 상자
class COpenCVDlgDlg : public CDialogEx
{
public:
    COpenCVDlgDlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_OPENCVDLG_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);

protected:
    HICON m_hIcon;

    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

public:
    
    Mat m_matImage;
    BITMAPINFO* m_pBitmapInfo;
    VideoCapture* capture;
    CImage cimage;
    CStatic m_picture;
    CSliderCtrl m_focusSlider;
    CSliderCtrl m_brightnessSlider;
    CSliderCtrl m_contrastSlider;
    CSliderCtrl m_saturationSlider;
    CSliderCtrl m_exposureSlider;

    afx_msg void OnBnClickedButtonPt();
    void OnMouseEvent(int event, int x, int y, int flags, void* userdata);
    static void MouseCallback(int event, int x, int y, int flags, void* userdata);

    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
    afx_msg void OnBnClickedAutoFocus();
    afx_msg void OnBnClickedAutoBrightness();
    afx_msg void OnBnClickedAutoContrast();
    afx_msg void OnBnClickedAutoSaturation();
    afx_msg void OnBnClickedAutoExposure();

    CComboBox m_presetCombo;
    std::map<CString, std::vector<double>> m_presets;

    afx_msg void OnBnClickedButton1();
    afx_msg void OnBnClickedButton2();
    afx_msg void OnBnClickedButton3();

    void SavePreset();
    void LoadPreset();
    void DeletePreset();
    void UpdatePresetCombo();

    void SavePresetsToFile();
    void LoadPresetsFromFile();
    CString GetPresetFilePath();

    cv::Mat m_patternImage;
    cv::Mat m_tempImage;
    cv::Point m_startPoint;
    cv::Point m_endPoint;
    bool m_isDrawing;

    afx_msg void OnBnClickedButtonPy();
    void PerformPatternRecognition();

    bool m_isPatternRecognitionRunning;
    cv::Mat m_patternTemplate;
    CButton m_buttonPy;
    cv::Mat m_resultImage;
    void DisplayImage(const cv::Mat& image, UINT nID);
    bool InputBox(LPCTSTR lpszPrompt, CString& result);

    CListBox m_patternList;
    void UpdatePatternList();
    afx_msg void OnLbnSelchangeList1();

    void ShowImageInNewWindow(const CString& fileName);
    afx_msg void OnLbnDblclkList1();

    afx_msg void OnBnClickedButtonDl();

    std::vector<cv::Mat> m_patternTemplates;

    // 새로운 멤버 변수
    std::vector<cv::Point2f> m_calibrationPoints;
    bool m_isCalibrated;
    cv::Mat m_homographyMatrix;

    // 새로운 멤버 함수
    void StartCalibration();
    void RunCalibrationLoop();
    void OnMouseCalibration(int event, int x, int y, int flags, void* userdata);
    static void MouseCalibrationCallback(int event, int x, int y, int flags, void* userdata);
    void PerformCalibration();
    void EnableAllButtons(BOOL enable);
    

    CListCtrl m_listGr;
    void InitializeListControl();
    
    void UpdatePatternRecognitionResults(const std::vector<bool>& matchResults);

    cv::Point m_currentMousePos;


    void DrawListItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
    afx_msg void OnCustomDrawList(NMHDR* pNMHDR, LRESULT* pResult);
    afx_msg void OnNMClickListGr(NMHDR* pNMHDR, LRESULT* pResult);
    void SaveDetectedPattern(int index);

    // 새로운 멤버 변수 추가
    std::vector<cv::Rect> m_detectedPatternRects;

    cv::Mat m_processedImage;
    cv::Mat DetectContours();
};