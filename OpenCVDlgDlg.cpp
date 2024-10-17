// OpenCVDlgDlg.cpp : 구현 파일

#include "pch.h"
#include "framework.h"
#include "OpenCVDlg.h"
#include "OpenCVDlgDlg.h"
#include "afxdialogex.h"
#include <Shlobj.h>
#include <vector>
#include <map>
#include <string>
#include <atlstr.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

    // 구현입니다.
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// COpenCVDlgDlg 대화 상자
COpenCVDlgDlg::COpenCVDlgDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_OPENCVDLG_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenCVDlgDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_IMAGE, m_picture);
    DDX_Control(pDX, IDC_FOCUS_SLIDER, m_focusSlider);
    DDX_Control(pDX, IDC_FOCUS_SLIDER2, m_brightnessSlider);
    DDX_Control(pDX, IDC_FOCUS_SLIDER3, m_contrastSlider);
    DDX_Control(pDX, IDC_FOCUS_SLIDER4, m_saturationSlider);
    DDX_Control(pDX, IDC_FOCUS_SLIDER5, m_exposureSlider);
    DDX_Control(pDX, IDC_COMBO1, m_presetCombo);
    DDX_Control(pDX, IDC_LIST1, m_patternList);
    DDX_Control(pDX, IDC_LIST_GR, m_listGr);
}

BEGIN_MESSAGE_MAP(COpenCVDlgDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_DESTROY()
    ON_WM_TIMER()
    ON_WM_VSCROLL()
    
    ON_BN_CLICKED(IDC_AUTO_FOCUS, &COpenCVDlgDlg::OnBnClickedAutoFocus)
    ON_BN_CLICKED(IDC_AUTO_FOCUS3, &COpenCVDlgDlg::OnBnClickedAutoBrightness)
    ON_BN_CLICKED(IDC_AUTO_FOCUS4, &COpenCVDlgDlg::OnBnClickedAutoContrast)
    ON_BN_CLICKED(IDC_AUTO_FOCUS5, &COpenCVDlgDlg::OnBnClickedAutoSaturation)
    ON_BN_CLICKED(IDC_AUTO_FOCUS6, &COpenCVDlgDlg::OnBnClickedAutoExposure)
    ON_BN_CLICKED(IDC_BUTTON1, &COpenCVDlgDlg::OnBnClickedButton1)
    ON_BN_CLICKED(IDC_BUTTON2, &COpenCVDlgDlg::OnBnClickedButton2)
    ON_BN_CLICKED(IDC_BUTTON3, &COpenCVDlgDlg::OnBnClickedButton3)
    ON_BN_CLICKED(IDC_BUTTON_PT, &COpenCVDlgDlg::OnBnClickedButtonPt)
    ON_BN_CLICKED(IDC_BUTTON_PY, &COpenCVDlgDlg::OnBnClickedButtonPy)
    ON_LBN_SELCHANGE(IDC_LIST1, &COpenCVDlgDlg::OnLbnSelchangeList1)
    ON_BN_CLICKED(IDC_BUTTON_DL, &COpenCVDlgDlg::OnBnClickedButtonDl)
    ON_LBN_SELCHANGE(IDC_LIST1, &COpenCVDlgDlg::OnLbnSelchangeList1)
    ON_LBN_DBLCLK(IDC_LIST1, &COpenCVDlgDlg::OnLbnDblclkList1)

    ON_NOTIFY(NM_CUSTOMDRAW, IDC_LIST_GR, OnCustomDrawList)
    ON_NOTIFY(NM_CLICK, IDC_LIST_GR, &COpenCVDlgDlg::OnNMClickListGr)
    
END_MESSAGE_MAP()

// COpenCVDlgDlg 메시지 처리기
BOOL COpenCVDlgDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

    // IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        BOOL bNameValid;
        CString strAboutMenu;
        bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
        ASSERT(bNameValid);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // 이 대화 상자의 아이콘을 설정합니다.
    SetIcon(m_hIcon, TRUE);         // 큰 아이콘을 설정합니다.
    SetIcon(m_hIcon, FALSE);        // 작은 아이콘을 설정합니다.

    // TODO: 여기에 추가 초기화 작업을 추가합니다.
    capture = new VideoCapture(0);

    capture->set(cv::CAP_PROP_FRAME_WIDTH, 1920);
    capture->set(cv::CAP_PROP_FRAME_HEIGHT, 1080);

    double actualWidth = capture->get(cv::CAP_PROP_FRAME_WIDTH);
    double actualHeight = capture->get(cv::CAP_PROP_FRAME_HEIGHT);

    // 결과를 문자열로 변환

    m_focusSlider.EnableWindow(FALSE);
    // 초점 슬라이더 초기화
    m_focusSlider.SetRange(0, 255);
    m_focusSlider.SetPos(127); // 중간값으로 설정

    m_brightnessSlider.EnableWindow(FALSE);  // 초기에 비활성화
    m_brightnessSlider.SetRange(0, 255);
    m_brightnessSlider.SetPos(127);

    // 대비 슬라이더 초기화
    m_contrastSlider.EnableWindow(FALSE);  // 초기에 비활성화
    m_contrastSlider.SetRange(0, 255);
    m_contrastSlider.SetPos(127);
    // 채도 슬라이더 초기화
    m_saturationSlider.EnableWindow(FALSE);  // 초기에 비활성화
    m_saturationSlider.SetRange(0, 255);
    m_saturationSlider.SetPos(127);

    m_exposureSlider.EnableWindow(FALSE);  // 초기에 비활성화
    m_exposureSlider.SetRange(0, 255);

    // 노출 슬라이더 초기화
    double currentExposure = capture->get(cv::CAP_PROP_EXPOSURE);
    int exposureSliderPos = 255 - static_cast<int>((currentExposure + 14) * 255 / 28);
    exposureSliderPos = std::max(0, std::min(255, exposureSliderPos));
    m_exposureSlider.SetPos(exposureSliderPos);


    // 채도 슬라이더 초기화
    double currentSaturation = capture->get(cv::CAP_PROP_SATURATION);
    int saturationSliderPos = 255 - static_cast<int>(currentSaturation);
    m_saturationSlider.SetPos(saturationSliderPos);


    // 대비 슬라이더 초기화
    double currentContrast = capture->get(cv::CAP_PROP_CONTRAST);
    int contrastSliderPos = 255 - static_cast<int>(currentContrast);
    m_contrastSlider.SetPos(contrastSliderPos);

    // 현재 카메라의 밝기 값을 가져와 슬라이더 초기 위치 설정
    double currentBrightness = capture->get(cv::CAP_PROP_BRIGHTNESS);
    int sliderPos = 255 - static_cast<int>(currentBrightness);  // 슬라이더 값을 반전
    m_brightnessSlider.SetPos(sliderPos);

    // 자동 밝기 설정
    capture->set(cv::CAP_PROP_AUTO_EXPOSURE, 3);


    // 자동 초점 해제
    capture->set(cv::CAP_PROP_AUTOFOCUS, 0);

    m_isPatternRecognitionRunning = false;
    m_buttonPy.SubclassDlgItem(IDC_BUTTON_PY, this);
   


    LoadPresetsFromFile();
    UpdatePresetCombo();

    // 리스트 박스 컨트롤과 변수를 연결합니다.
    m_patternList.SubclassDlgItem(IDC_LIST1, this);

    // 초기 패턴 리스트를 업데이트합니다.
    UpdatePatternList();

    DWORD dwStyle = m_patternList.GetStyle();
    dwStyle |= LBS_NOTIFY | LBS_STANDARD | LBS_WANTKEYBOARDINPUT;
    ::SetWindowLong(m_patternList.GetSafeHwnd(), GWL_STYLE, dwStyle);

    m_isCalibrated = false;
   // EnableAllButtons(FALSE);  // 모든 버튼을 비활성화

    SetTimer(1000, 16, NULL);

    // 캘리브레이션 자동 시작
   // StartCalibration();

    InitializeListControl();

    return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void COpenCVDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialogEx::OnSysCommand(nID, lParam);
    }
}

void COpenCVDlgDlg::OnPaint()
{
    if (IsIconic())
    {
        CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

        SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

        // 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
        int cxIcon = GetSystemMetrics(SM_CXICON);
        int cyIcon = GetSystemMetrics(SM_CYICON);
        CRect rect;
        GetClientRect(&rect);
        int x = (rect.Width() - cxIcon + 1) / 2;
        int y = (rect.Height() - cyIcon + 1) / 2;

        // 아이콘을 그립니다.
        dc.DrawIcon(x, y, m_hIcon);
    }
    else
    {
        CDialogEx::OnPaint();
    }
}

HCURSOR COpenCVDlgDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

void COpenCVDlgDlg::OnDestroy()
{
    CDialogEx::OnDestroy();

    // TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void COpenCVDlgDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    if (pScrollBar == (CScrollBar*)&m_focusSlider)
    {
        int sliderValue = m_focusSlider.GetPos();
        int focusValue = 255 - sliderValue;  // 슬라이더 값을 반전시킴

        // 255가 가장 먼 초점, 0이 가장 가까운 초점
        if (capture->set(cv::CAP_PROP_FOCUS, focusValue))
        {
            // 설정 성공
            double actualFocus = capture->get(cv::CAP_PROP_FOCUS);
            CString str;
            str.Format(_T("Focus set to: %.2f (Slider: %d)"), actualFocus, sliderValue);

            // 디버그 출력
            OutputDebugString(str);

            // 상태 표시를 위한 정적 컨트롤이 있다면 사용
            // SetDlgItemText(IDC_STATIC_FOCUS, str);
        }
        else
        {
            OutputDebugString(_T("Failed to set focus"));
        }
    }
    else if (pScrollBar == (CScrollBar*)&m_brightnessSlider)
    {
        int sliderValue = m_brightnessSlider.GetPos();
        int brightnessValue = 255 - sliderValue;  // 슬라이더 값을 반전

        if (capture->set(cv::CAP_PROP_BRIGHTNESS, brightnessValue))
        {
            double actualBrightness = capture->get(cv::CAP_PROP_BRIGHTNESS);
            CString str;
            str.Format(_T("Brightness set to: %.0f (Slider: %d)"), actualBrightness, sliderValue);

            // 디버그 출력
            OutputDebugString(str);

            // 상태 표시를 위한 정적 컨트롤이 있다면 사용
            // SetDlgItemText(IDC_STATIC_BRIGHTNESS, str);
        }
        else
        {
            OutputDebugString(_T("Failed to set brightness"));
        }
    }
    else if (pScrollBar == (CScrollBar*)&m_exposureSlider)
    {
        int sliderValue = m_exposureSlider.GetPos();
        double exposureValue = ((255 - sliderValue) / 255.0 * 28) - 14;  // 반전된 슬라이더 값을 -14 to 14로 매핑

        if (capture->set(cv::CAP_PROP_EXPOSURE, exposureValue))
        {
            double actualExposure = capture->get(cv::CAP_PROP_EXPOSURE);
            CString str;
            str.Format(_T("Exposure set to: %.2f (Slider: %d)"), actualExposure, sliderValue);
            OutputDebugString(str);
        }
        else
        {
            OutputDebugString(_T("Failed to set exposure"));
        }
    }
    else if (pScrollBar == (CScrollBar*)&m_contrastSlider)
    {
        int sliderValue = m_contrastSlider.GetPos();
        int contrastValue = 255 - sliderValue;  // 슬라이더 값을 반전

        if (capture->set(cv::CAP_PROP_CONTRAST, contrastValue))
        {
            double actualContrast = capture->get(cv::CAP_PROP_CONTRAST);
            CString str;
            str.Format(_T("Contrast set to: %.0f (Slider: %d)"), actualContrast, sliderValue);
            OutputDebugString(str);
        }
        else
        {
            OutputDebugString(_T("Failed to set contrast"));
        }
    }
    else if (pScrollBar == (CScrollBar*)&m_saturationSlider)
    {
        int sliderValue = m_saturationSlider.GetPos();
        int saturationValue = 255 - sliderValue;  // 슬라이더 값을 반전

        if (capture->set(cv::CAP_PROP_SATURATION, saturationValue))
        {
            double actualSaturation = capture->get(cv::CAP_PROP_SATURATION);
            CString str;
            str.Format(_T("Saturation set to: %.0f (Slider: %d)"), actualSaturation, sliderValue);
            OutputDebugString(str);
        }
        else
        {
            OutputDebugString(_T("Failed to set saturation"));
        }
    }

    CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}

void COpenCVDlgDlg::OnTimer(UINT_PTR nIDEvent)
{
    if (!capture->isOpened()) // 카메라가 열려있는지 확인
        return;

    // DetectContours 함수를 사용하여 이미지 처리
    m_matImage = DetectContours();
    if (m_matImage.empty()) // 유효한 프레임인지 확인
        return;

    int bpp = 8 * m_matImage.elemSize();
    assert((bpp == 8 || bpp == 24 || bpp == 32));

    int padding = 0;
    if (bpp < 32)
        padding = 4 - (m_matImage.cols % 4);
    if (padding == 4)
        padding = 0;

    int border = 0;
    if (bpp < 32)
        border = 4 - (m_matImage.cols % 4);

    Mat mat_temp;
    if (border > 0 || m_matImage.isContinuous() == false)
        copyMakeBorder(m_matImage, mat_temp, 0, 0, 0, border, BORDER_CONSTANT, 0);
    else
        mat_temp = m_matImage;

    // IDC_IMAGE의 크기 가져오기
    RECT r;
    m_picture.GetClientRect(&r);
    cv::Size winSize(r.right, r.bottom);

    // 원본 영상의 크기를 winSize에 맞추어 변형 (비율을 유지하지 않고 강제 조정)
    cv::resize(mat_temp, mat_temp, winSize);

    // 24비트 이미지 생성
    cimage.Create(winSize.width, winSize.height, 24);

    BITMAPINFO* bitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
    bitInfo->bmiHeader.biBitCount = bpp;
    bitInfo->bmiHeader.biWidth = mat_temp.cols;
    bitInfo->bmiHeader.biHeight = -mat_temp.rows;
    bitInfo->bmiHeader.biPlanes = 1;
    bitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitInfo->bmiHeader.biCompression = BI_RGB;
    bitInfo->bmiHeader.biClrImportant = 0;
    bitInfo->bmiHeader.biClrUsed = 0;
    bitInfo->bmiHeader.biSizeImage = 0;
    bitInfo->bmiHeader.biXPelsPerMeter = 0;
    bitInfo->bmiHeader.biYPelsPerMeter = 0;

    // 그레이스케일인 경우 팔레트가 필요
    if (bpp == 8)
    {
        RGBQUAD* palette = bitInfo->bmiColors;
        for (int i = 0; i < 256; i++)
        {
            palette[i].rgbBlue = palette[i].rgbGreen = palette[i].rgbRed = (BYTE)i;
            palette[i].rgbReserved = 0;
        }
    }

    SetDIBitsToDevice(cimage.GetDC(), 0, 0, winSize.width, winSize.height,
        0, 0, 0, mat_temp.rows, mat_temp.data, bitInfo, DIB_RGB_COLORS);

    HDC dc = ::GetDC(m_picture.m_hWnd);
    cimage.BitBlt(dc, 0, 0);
    ::ReleaseDC(m_picture.m_hWnd, dc);

    cimage.ReleaseDC();
    cimage.Destroy();
    free(bitInfo);

    if (m_isPatternRecognitionRunning)
    {
        PerformPatternRecognition();
    }
    else
    {
        DisplayImage(m_matImage, IDC_IMAGE);  // 처리된 영상 표시
    }

    CDialogEx::OnTimer(nIDEvent);
}


void COpenCVDlgDlg::OnBnClickedAutoFocus()
{
    static bool isAutoFocus = false;
    isAutoFocus = !isAutoFocus;

    if (isAutoFocus)
    {
        // 자동 초점 모드: 슬라이더 비활성화
        capture->set(cv::CAP_PROP_AUTOFOCUS, 1);
        m_focusSlider.EnableWindow(FALSE);
        GetDlgItem(IDC_AUTO_FOCUS)->SetWindowText(_T("수동 초점"));

        // 자동 초점 값 가져오기
        double autoFocusValue = capture->get(cv::CAP_PROP_FOCUS);
        int sliderPos = static_cast<int>(255 - autoFocusValue);  // 슬라이더 값은 반전시켜 사용

        // 슬라이더 위치를 자동 초점 값에 맞춤
        m_focusSlider.SetPos(sliderPos);
    }
    else
    {
        // 수동 초점 모드: 슬라이더 활성화
        capture->set(cv::CAP_PROP_AUTOFOCUS, 0);
        m_focusSlider.EnableWindow(TRUE);
        GetDlgItem(IDC_AUTO_FOCUS)->SetWindowText(_T("자동 초점"));
    }
}

void COpenCVDlgDlg::OnBnClickedAutoBrightness()
{
    static bool isAutoBrightness = false;
    isAutoBrightness = !isAutoBrightness;

    if (isAutoBrightness)
    {
        // 자동 밝기 모드
        capture->set(cv::CAP_PROP_AUTO_EXPOSURE, 3);  // 3 = aperture priority mode
        m_brightnessSlider.EnableWindow(FALSE);
        GetDlgItem(IDC_AUTO_FOCUS3)->SetWindowText(_T("수동 밝기"));
    }
    else
    {
        // 수동 밝기 모드
        capture->set(cv::CAP_PROP_AUTO_EXPOSURE, 1);  // 1 = manual mode
        m_brightnessSlider.EnableWindow(TRUE);
        GetDlgItem(IDC_AUTO_FOCUS3)->SetWindowText(_T("자동 밝기"));
    }

    // 현재 밝기 값 가져오기 및 슬라이더 위치 업데이트
    double currentBrightness = capture->get(cv::CAP_PROP_BRIGHTNESS);
    int sliderPos = 255 - static_cast<int>(currentBrightness);  // 슬라이더 값을 반전
    m_brightnessSlider.SetPos(sliderPos);
}

void COpenCVDlgDlg::OnBnClickedAutoContrast()
{
    static bool isAutoContrast = true;  // 초기 상태는 '자동'으로 설정
    isAutoContrast = !isAutoContrast;

    if (isAutoContrast)
    {
        // '자동' 대비 모드
        m_contrastSlider.EnableWindow(FALSE);
        GetDlgItem(IDC_AUTO_FOCUS4)->SetWindowText(_T("활성화"));
    }
    else
    {
        // '수동' 대비 모드
        m_contrastSlider.EnableWindow(TRUE);
        GetDlgItem(IDC_AUTO_FOCUS4)->SetWindowText(_T("비활성화"));
    }

    // 현재 대비 값 가져오기 및 슬라이더 위치 업데이트
    double currentContrast = capture->get(cv::CAP_PROP_CONTRAST);
    int sliderPos = static_cast<int>(currentContrast);
    m_contrastSlider.SetPos(sliderPos);
}

void COpenCVDlgDlg::OnBnClickedAutoSaturation()
{
    static bool isAutoSaturation = true;  // 초기 상태는 '자동'으로 설정
    isAutoSaturation = !isAutoSaturation;

    if (isAutoSaturation)
    {
        // '자동' 채도 모드
        // 참고: OpenCV에는 자동 채도 모드가 없으므로, 여기서는 단순히 슬라이더를 비활성화합니다.
        m_saturationSlider.EnableWindow(FALSE);
        GetDlgItem(IDC_AUTO_FOCUS5)->SetWindowText(_T("활성화"));
    }
    else
    {
        // '수동' 채도 모드
        m_saturationSlider.EnableWindow(TRUE);
        GetDlgItem(IDC_AUTO_FOCUS5)->SetWindowText(_T("비활성화"));
    }

    // 현재 채도 값 가져오기 및 슬라이더 위치 업데이트
    double currentSaturation = capture->get(cv::CAP_PROP_SATURATION);
    int sliderPos = static_cast<int>(currentSaturation);
    m_saturationSlider.SetPos(sliderPos);
}

void COpenCVDlgDlg::OnBnClickedAutoExposure()
{
    static bool isAutoExposure = true;  // 초기 상태는 '자동'으로 설정
    isAutoExposure = !isAutoExposure;

    if (isAutoExposure)
    {
        // '자동' 노출 모드
        capture->set(cv::CAP_PROP_AUTO_EXPOSURE, 0.75);  // 자동 노출 모드 (참고: 0.75는 일반적으로 자동 모드를 의미)
        m_exposureSlider.EnableWindow(FALSE);
        GetDlgItem(IDC_AUTO_FOCUS6)->SetWindowText(_T("수동 노출"));
    }
    else
    {
        // '수동' 노출 모드
        capture->set(cv::CAP_PROP_AUTO_EXPOSURE, 0.25);  // 수동 노출 모드 (참고: 0.25는 일반적으로 수동 모드를 의미)
        m_exposureSlider.EnableWindow(TRUE);
        GetDlgItem(IDC_AUTO_FOCUS6)->SetWindowText(_T("자동 노출"));
    }

    // 현재 노출 값 가져오기 및 슬라이더 위치 업데이트
    double currentExposure = capture->get(cv::CAP_PROP_EXPOSURE);
    int sliderPos = static_cast<int>((currentExposure + 14) * 255 / 28);  // -14 to 14 범위를 0-255로 매핑
    sliderPos = std::max(0, std::min(255, sliderPos));  // 값을 0-255 범위로 제한
    m_exposureSlider.SetPos(sliderPos);
}

void COpenCVDlgDlg::OnBnClickedButton1()
{
    SavePreset();
}

void COpenCVDlgDlg::OnBnClickedButton2()
{
    LoadPreset();
}

void COpenCVDlgDlg::OnBnClickedButton3()
{
    DeletePreset();
}

void COpenCVDlgDlg::SavePreset()
{
    CString presetName;
    m_presetCombo.GetWindowText(presetName);
    if (presetName.IsEmpty())
    {
        AfxMessageBox(_T("프리셋 이름을 입력하세요."));
        return;
    }

    std::vector<double> values = {
        static_cast<double>(255 - m_focusSlider.GetPos()),
        static_cast<double>(255 - m_brightnessSlider.GetPos()),
        static_cast<double>(255 - m_contrastSlider.GetPos()),
        static_cast<double>(255 - m_saturationSlider.GetPos()),
        ((255 - m_exposureSlider.GetPos()) / 255.0 * 28) - 14  // 0-255 범위를 -14에서 14로 변환
    };

    m_presets[presetName] = values;
    UpdatePresetCombo();
    SavePresetsToFile();
    AfxMessageBox(_T("프리셋이 저장되었습니다."));
}

void COpenCVDlgDlg::LoadPreset()
{
    int index = m_presetCombo.GetCurSel();
    if (index == CB_ERR)
    {
        AfxMessageBox(_T("프리셋을 선택하세요."));
        return;
    }

    CString presetName;
    m_presetCombo.GetLBText(index, presetName);

    auto it = m_presets.find(presetName);
    if (it != m_presets.end())
    {
        const std::vector<double>& values = it->second;

        // 카메라 설정 변경
        capture->set(cv::CAP_PROP_FOCUS, values[0]);
        capture->set(cv::CAP_PROP_BRIGHTNESS, values[1]);
        capture->set(cv::CAP_PROP_CONTRAST, values[2]);
        capture->set(cv::CAP_PROP_SATURATION, values[3]);
        capture->set(cv::CAP_PROP_EXPOSURE, values[4]);

        // 슬라이더 위치 업데이트
        m_focusSlider.SetPos(255 - static_cast<int>(values[0]));
        m_brightnessSlider.SetPos(255 - static_cast<int>(values[1]));
        m_contrastSlider.SetPos(255 - static_cast<int>(values[2]));
        m_saturationSlider.SetPos(255 - static_cast<int>(values[3]));

        // 노출의 경우 범위 변환
        double exposureValue = values[4];
        int exposurePos = static_cast<int>((exposureValue + 14) / 28 * 255);
        exposurePos = 255 - std::max(0, std::min(255, exposurePos));  // 반전 및 범위 제한
        m_exposureSlider.SetPos(exposurePos);

        AfxMessageBox(_T("프리셋이 로드되었습니다."));
    }
}

void COpenCVDlgDlg::DeletePreset()
{
    int index = m_presetCombo.GetCurSel();
    if (index == CB_ERR)
    {
        AfxMessageBox(_T("삭제할 프리셋을 선택하세요."));
        return;
    }

    CString presetName;
    m_presetCombo.GetLBText(index, presetName);

    m_presets.erase(presetName);
    UpdatePresetCombo();
    AfxMessageBox(_T("프리셋이 삭제되었습니다."));
    SavePresetsToFile();
}

void COpenCVDlgDlg::UpdatePresetCombo()
{
    m_presetCombo.ResetContent();
    for (const auto& preset : m_presets)
    {
        m_presetCombo.AddString(preset.first);
    }
}

void COpenCVDlgDlg::SavePresetsToFile()
{
    CStdioFile file;
    if (file.Open(GetPresetFilePath(), CFile::modeCreate | CFile::modeWrite))
    {
        for (const auto& preset : m_presets)
        {
            CString line;
            line.Format(_T("%s,%.2f,%.2f,%.2f,%.2f,%.2f\n"),
                preset.first,
                preset.second[0], preset.second[1], preset.second[2],
                preset.second[3], preset.second[4]);
            file.WriteString(line);
        }
        file.Close();
    }
    else
    {
        AfxMessageBox(_T("프리셋 파일을 저장할 수 없습니다."));
    }
}

void COpenCVDlgDlg::LoadPresetsFromFile()
{
    CStdioFile file;
    if (file.Open(GetPresetFilePath(), CFile::modeRead))
    {
        m_presets.clear();
        CString line;
        while (file.ReadString(line))
        {
            int pos = 0;
            CString presetName = line.Tokenize(_T(","), pos);
            std::vector<double> values;
            for (int i = 0; i < 5; i++)
            {
                CString token = line.Tokenize(_T(","), pos);
                values.push_back(_tstof(token));
            }
            m_presets[presetName] = values;
        }
        file.Close();
        UpdatePresetCombo();
    }
}

CString COpenCVDlgDlg::GetPresetFilePath()
{
    TCHAR path[MAX_PATH];
    SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path);
    CString filePath(path);
    filePath += _T("\\CameraPresets.txt");
    return filePath;
}

// OpenCVDlgDlg.cpp
// ... (existing code)

void COpenCVDlgDlg::OnBnClickedButtonPt()
{
    if (m_matImage.empty())
    {
        AfxMessageBox(_T("유효한 이미지가 없습니다."));
        return;
    }

    // 현재 표시 중인 이미지(캘리브레이션 적용된)를 사용
    m_patternImage = m_matImage.clone();
    m_tempImage = m_patternImage.clone();
    m_isDrawing = false;
    m_startPoint = cv::Point(-1, -1);
    m_endPoint = cv::Point(-1, -1);

    cv::namedWindow("Select Pattern", cv::WINDOW_NORMAL);
    cv::setMouseCallback("Select Pattern", MouseCallback, this);
    cv::imshow("Select Pattern", m_patternImage);

    while (true)
    {
        int key = cv::waitKey(1);
        if (key == 13)  // Enter key
        {
            break;
        }
        else if (key == 27)  // Esc key
        {
            m_startPoint = cv::Point(-1, -1);
            m_endPoint = cv::Point(-1, -1);
            break;
        }
    }

    cv::destroyWindow("Select Pattern");

    if (m_startPoint != cv::Point(-1, -1) && m_endPoint != cv::Point(-1, -1))
    {
        cv::Rect roi(
            std::min(m_startPoint.x, m_endPoint.x),
            std::min(m_startPoint.y, m_endPoint.y),
            std::abs(m_startPoint.x - m_endPoint.x),
            std::abs(m_startPoint.y - m_endPoint.y)
        );

        if (roi.width > 0 && roi.height > 0)
        {
            cv::Mat pattern = m_patternImage(roi);

            CString patternName;
            if (InputBox(_T("패턴의 이름을 입력하세요:"), patternName))
            {
                CString fileName = patternName + _T(".jpg");
                std::string fileNameStr = CT2A(fileName);
                cv::imwrite(fileNameStr, pattern);
                AfxMessageBox(_T("패턴이 저장되었습니다: ") + fileName);

                // 패턴 리스트를 업데이트합니다.
                UpdatePatternList();
            }
            else
            {
                AfxMessageBox(_T("패턴 저장이 취소되었습니다."));
            }
        }
        else
        {
            AfxMessageBox(_T("유효하지 않은 선택 영역입니다."));
        }
    }
    else
    {
        AfxMessageBox(_T("패턴 선택이 취소되었습니다."));
    }
}

// ... (rest of the existing code)

void COpenCVDlgDlg::OnMouseEvent(int event, int x, int y, int flags, void* userdata)
{
    switch (event)
    {
    case cv::EVENT_LBUTTONDOWN:
        m_startPoint = cv::Point(x, y);
        m_isDrawing = true;
        m_tempImage = m_patternImage.clone();
        break;
    case cv::EVENT_MOUSEMOVE:
        if (m_isDrawing)
        {
            m_tempImage = m_patternImage.clone();
            cv::rectangle(m_tempImage, m_startPoint, cv::Point(x, y), cv::Scalar(0, 255, 0), 2);
            cv::imshow("Select Pattern", m_tempImage);
        }
        break;
    case cv::EVENT_LBUTTONUP:
        m_endPoint = cv::Point(x, y);
        m_isDrawing = false;
        cv::rectangle(m_tempImage, m_startPoint, m_endPoint, cv::Scalar(0, 255, 0), 2);
        cv::imshow("Select Pattern", m_tempImage);
        break;
    }
}

void COpenCVDlgDlg::MouseCallback(int event, int x, int y, int flags, void* userdata)
{
    COpenCVDlgDlg* dlg = static_cast<COpenCVDlgDlg*>(userdata);
    dlg->OnMouseEvent(event, x, y, flags, userdata);
}

void COpenCVDlgDlg::OnBnClickedButtonPy()
{
    m_isPatternRecognitionRunning = !m_isPatternRecognitionRunning;
    if (m_isPatternRecognitionRunning)
    {
        m_buttonPy.SetWindowText(_T("ON"));

        // 모든 패턴 템플릿 로드
        m_patternTemplates.clear();
        CFileFind finder;
        BOOL bWorking = finder.FindFile(_T("*.jpg"));
        while (bWorking)
        {
            bWorking = finder.FindNextFile();
            if (finder.IsDots() || finder.IsDirectory()) continue;

            CString fileName = finder.GetFileName();
            CT2CA pszConvertedAnsiString(fileName);
            std::string str(pszConvertedAnsiString);
            cv::Mat patternTemplate = cv::imread(str, cv::IMREAD_COLOR);
            if (!patternTemplate.empty())
            {
                m_patternTemplates.push_back(patternTemplate);
            }
        }
        finder.Close();

        if (m_patternTemplates.empty())
        {
            AfxMessageBox(_T("패턴 이미지를 불러올 수 없습니다."));
            m_isPatternRecognitionRunning = false;
            m_buttonPy.SetWindowText(_T("OFF"));
            return;
        }
        // 패턴 인식 동작 시작
    }
    else
    {
        m_buttonPy.SetWindowText(_T("OFF"));
        // 패턴 인식 중지
        m_isPatternRecognitionRunning = false;
        m_listGr.DeleteAllItems();  // 결과 목록 지우기
    }

    // 패턴 목록 업데이트
    UpdatePatternList();
}

void COpenCVDlgDlg::PerformPatternRecognition()
{
    if (m_patternTemplates.empty() || m_matImage.empty())
        return;

    m_processedImage = m_matImage.clone();  // 처리된 이미지를 m_processedImage에 저장
    bool anyMatch = false;
    std::vector<bool> matchResults;
    m_detectedPatternRects.clear();  // 탐지된 패턴 위치 초기화

    for (const auto& patternTemplate : m_patternTemplates)
    {
        cv::Mat result;
        cv::matchTemplate(m_matImage, patternTemplate, result, cv::TM_CCOEFF_NORMED);

        double minVal, maxVal;
        cv::Point minLoc, maxLoc;
        cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

        if (maxVal > 0.9) // 임계값 설정 (0.8은 예시, 필요에 따라 조정)
        {
            cv::Rect matchRect(maxLoc, patternTemplate.size());
            cv::rectangle(m_processedImage, matchRect, cv::Scalar(0, 255, 0), 5);  // 초록색으로 표시
            matchResults.push_back(true);
            anyMatch = true;
            m_detectedPatternRects.push_back(matchRect);  // 탐지된 패턴 위치 저장
        }
        else
        {
            cv::Rect matchRect(maxLoc, patternTemplate.size());
            cv::rectangle(m_processedImage, matchRect, cv::Scalar(0, 0, 255), 5);  // 빨간색으로 표시
            matchResults.push_back(false);
            m_detectedPatternRects.push_back(matchRect);  // 탐지되지 않은 패턴의 위치도 저장
        }
    }

    // 결과 이미지를 IDC_IMAGE에 표시
    DisplayImage(m_processedImage, IDC_IMAGE);

    // 패턴 인식 결과 업데이트
    UpdatePatternRecognitionResults(matchResults);
}



void COpenCVDlgDlg::DisplayImage(const cv::Mat& image, UINT nID)
{
    CStatic* pStatic = (CStatic*)GetDlgItem(nID);
    if (pStatic == nullptr || image.empty())
        return;

    CDC* pDC = pStatic->GetDC();
    HDC hDC = pDC->GetSafeHdc();

    CRect rect;
    pStatic->GetClientRect(&rect);

    cv::Mat resized;
    cv::resize(image, resized, cv::Size(rect.Width(), rect.Height()));

    CImage cimage;
    cimage.Create(rect.Width(), rect.Height(), 24);

    BITMAPINFO bitmapInfo;
    bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfo.bmiHeader.biWidth = resized.cols;
    bitmapInfo.bmiHeader.biHeight = -resized.rows;  // 상단-하단 방향으로 
    bitmapInfo.bmiHeader.biPlanes = 1;
    bitmapInfo.bmiHeader.biBitCount = 24;
    bitmapInfo.bmiHeader.biCompression = BI_RGB;

    SetDIBitsToDevice(cimage.GetDC(),
        0, 0, rect.Width(), rect.Height(),
        0, 0, 0, resized.rows,
        resized.data, &bitmapInfo, DIB_RGB_COLORS);

    cimage.BitBlt(hDC, 0, 0);

    cimage.ReleaseDC();
    pStatic->ReleaseDC(pDC);
}

bool COpenCVDlgDlg::InputBox(LPCTSTR lpszPrompt, CString& result)
{
    class CInputDialog : public CDialog
    {
    public:
        CString m_strInput;
        CString m_strPrompt;

        CInputDialog(LPCTSTR lpszPrompt) : CDialog(IDD_INPUT_DIALOG)
        {
            m_strPrompt = lpszPrompt;
        }

    protected:
        virtual BOOL OnInitDialog()
        {
            CDialog::OnInitDialog();
            SetWindowText(_T("패턴 이름 입력"));
            GetDlgItem(IDC_STATIC)->SetWindowText(m_strPrompt);
            return TRUE;
        }

        virtual void DoDataExchange(CDataExchange* pDX)
        {
            CDialog::DoDataExchange(pDX);
            DDX_Text(pDX, IDC_EDIT_INPUT, m_strInput);
        }
    };

    CInputDialog dlg(lpszPrompt);
    if (dlg.DoModal() == IDOK)
    {
        result = dlg.m_strInput;
        return true;
    }
    return false;
}

void COpenCVDlgDlg::UpdatePatternList()
{
    int nSelectedIndex = m_patternList.GetCurSel();
    CString selectedFileName;
    if (nSelectedIndex != LB_ERR)
    {
        m_patternList.GetText(nSelectedIndex, selectedFileName);
    }

    m_patternList.ResetContent();

    CFileFind finder;
    BOOL bWorking = finder.FindFile(_T("*.jpg"));

    while (bWorking)
    {
        bWorking = finder.FindNextFile();
        if (finder.IsDots()) continue;
        if (finder.IsDirectory()) continue;

        CString fileName = finder.GetFileName();
        int nIndex = m_patternList.AddString(fileName);

        // 이전에 선택된 항목을 다시 선택
        if (!selectedFileName.IsEmpty() && fileName == selectedFileName)
        {
            m_patternList.SetCurSel(nIndex);
        }
    }
    finder.Close();

    // 이전에 선택된 항목이 없거나 삭제된 경우, 첫 번째 항목 선택
    if (m_patternList.GetCurSel() == LB_ERR && m_patternList.GetCount() > 0)
    {
        m_patternList.SetCurSel(0);
    }
}

void COpenCVDlgDlg::OnLbnSelchangeList1()
{
    // 리스트 박스에서 항목이 선택되었을 때 수행할 작업을 여기에 추가합니다.
    // 예를 들어:
    int nIndex = m_patternList.GetCurSel();
    if (nIndex != LB_ERR)
    {
        CString fileName;
        m_patternList.GetText(nIndex, fileName);

        // 선택된 파일 이름을 사용하여 원하는 작업을 수행합니다.
        // 예: 디버그 출력
        OutputDebugString(_T("Selected file: ") + fileName + _T("\n"));
    }
}

void COpenCVDlgDlg::ShowImageInNewWindow(const CString& fileName)
{
    OutputDebugString(_T("ShowImageInNewWindow called with fileName: ") + fileName + _T("\n"));

    CT2CA pszConvertedAnsiString(fileName);
    std::string strFileName(pszConvertedAnsiString);

    // 현재 작업 디렉토리 확인
    TCHAR buffer[MAX_PATH] = { 0 };
    GetCurrentDirectory(MAX_PATH, buffer);
    CString currentDir(buffer);

    // 전체 파일 경로 생성
    CString fullPath = currentDir + _T("\\") + fileName;

    OutputDebugString(_T("Full path: ") + fullPath + _T("\n"));

    // 파일 존재 여부 확인
    if (!PathFileExists(fullPath))
    {
        OutputDebugString(_T("File does not exist: ") + fullPath + _T("\n"));
        AfxMessageBox(_T("파일이 존재하지 않습니다: ") + fullPath);
        return;
    }

    // CString을 std::string으로 변환
    CT2CA pszConvertedAnsiString2(fullPath);
    std::string strFullPath(pszConvertedAnsiString2);

    OutputDebugString(_T("Attempting to read image...\n"));

    cv::Mat image = cv::imread(strFullPath, cv::IMREAD_COLOR);
    if (image.empty())
    {
        OutputDebugString(_T("Failed to read image\n"));
        AfxMessageBox(_T("이미지를 불러올 수 없습니다: ") + fullPath);
        return;
    }

    OutputDebugString(_T("Image loaded successfully\n"));

    try {
        cv::namedWindow(strFullPath, cv::WINDOW_NORMAL);
        cv::imshow(strFullPath, image);
        cv::resizeWindow(strFullPath, image.cols, image.rows);
        OutputDebugString(_T("Image displayed\n"));
    }
    catch (const cv::Exception& e) {
        OutputDebugString(_T("OpenCV exception: ") + CString(e.what()) + _T("\n"));
        AfxMessageBox(_T("OpenCV 오류: ") + CString(e.what()));
    }
    catch (const std::exception& e) {
        OutputDebugString(_T("Standard exception: ") + CString(e.what()) + _T("\n"));
        AfxMessageBox(_T("표준 예외: ") + CString(e.what()));
    }
    catch (...) {
        OutputDebugString(_T("Unknown exception occurred\n"));
        AfxMessageBox(_T("알 수 없는 오류가 발생했습니다."));
    }
}

void COpenCVDlgDlg::OnLbnDblclkList1()
{
    OutputDebugString(_T("OnLbnDblclkList1 called\n"));

    int nIndex = m_patternList.GetCurSel();
    if (nIndex != LB_ERR)
    {
        CString fileName;
        m_patternList.GetText(nIndex, fileName);
        OutputDebugString(_T("Selected file: ") + fileName + _T("\n"));
        ShowImageInNewWindow(fileName);
    }
    else
    {
        OutputDebugString(_T("No item selected\n"));
    }
}

void COpenCVDlgDlg::OnBnClickedButtonDl()
{
    int nIndex = m_patternList.GetCurSel();
    if (nIndex != LB_ERR)
    {
        CString fileName;
        m_patternList.GetText(nIndex, fileName);

        // 사용자에게 삭제 확인
        CString message;
        message.Format(_T("'%s' 파일을 삭제하시겠습니까?"), fileName);
        if (AfxMessageBox(message, MB_YESNO | MB_ICONQUESTION) == IDYES)
        {
            // 파일 삭제
            if (DeleteFile(fileName))
            {
                // 리스트에서 항목 제거
                m_patternList.DeleteString(nIndex);
                AfxMessageBox(_T("파일이 성공적으로 삭제되었습니다."));

                // 리스트 갱신
                UpdatePatternList();
            }
            else
            {
                AfxMessageBox(_T("파일 삭제에 실패했습니다."));
            }
        }
    }
    else
    {
        AfxMessageBox(_T("삭제할 항목을 선택해주세요."));
    }
}

void COpenCVDlgDlg::StartCalibration()
{
    m_calibrationPoints.clear();
    m_isCalibrated = false;

    // 캘리브레이션 창 생성
    cv::namedWindow("Calibration", cv::WINDOW_NORMAL);
    cv::resizeWindow("Calibration", 640, 480);
    cv::setMouseCallback("Calibration", MouseCalibrationCallback, this);

    // 안내 메시지 표시
    AfxMessageBox(_T("화면에 4개의 점을 순서대로 클릭하여 수평을 맞추세요.\n"
        "1. 좌상단\n2. 우상단\n3. 우하단\n4. 좌하단"));

    // 캘리브레이션 루프 시작
    RunCalibrationLoop();
}

void COpenCVDlgDlg::RunCalibrationLoop()
{
    m_currentMousePos = cv::Point(-1, -1);

    while (m_calibrationPoints.size() < 4)
    {
        cv::Mat frame;
        if (capture->read(frame))
        {
            cv::Mat displayFrame = frame.clone();

            // 현재까지 클릭한 점들 표시 및 선 그리기
            for (size_t i = 0; i < m_calibrationPoints.size(); i++)
            {
                cv::circle(displayFrame, cv::Point(static_cast<int>(m_calibrationPoints[i].x), static_cast<int>(m_calibrationPoints[i].y)), 5, cv::Scalar(0, 255, 0), -1);
                cv::putText(displayFrame, std::to_string(i + 1), cv::Point(static_cast<int>(m_calibrationPoints[i].x), static_cast<int>(m_calibrationPoints[i].y)),
                    cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(255, 0, 0), 2);

                if (i > 0)
                {
                    cv::line(displayFrame, m_calibrationPoints[i - 1], m_calibrationPoints[i], cv::Scalar(0, 255, 255), 2);
                }
            }

            // 마지막으로 클릭한 점과 현재 마우스 위치 사이에 선 그리기
            if (!m_calibrationPoints.empty() && m_currentMousePos.x != -1 && m_currentMousePos.y != -1)
            {
                cv::line(displayFrame, m_calibrationPoints.back(), m_currentMousePos, cv::Scalar(0, 255, 255), 2);
            }

            // 마지막 점과 첫 번째 점을 연결 (4번째 점 선택 후)
            if (m_calibrationPoints.size() == 4)
            {
                cv::line(displayFrame, m_calibrationPoints[3], m_calibrationPoints[0], cv::Scalar(0, 255, 255), 2);
            }

            // 안내 메시지 추가
            cv::putText(displayFrame, "Left click: Add point, Right click: Cancel last point, ESC: Exit",
                cv::Point(10, 30), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 255, 255), 1);

            cv::imshow("Calibration", displayFrame);
        }

        int key = cv::waitKey(1);
        if (key == 27)  // ESC key
        {
            break;
        }
    }

    cv::destroyWindow("Calibration");

    if (m_calibrationPoints.size() == 4)
    {
        PerformCalibration();
    }
    else
    {
        AfxMessageBox(_T("캘리브레이션이 취소되었습니다."));
    }
}

void COpenCVDlgDlg::OnMouseCalibration(int event, int x, int y, int flags, void* userdata)
{
    switch (event)
    {
    case cv::EVENT_MOUSEMOVE:
        m_currentMousePos = cv::Point(x, y);
        break;

    case cv::EVENT_LBUTTONDOWN:
        if (m_calibrationPoints.size() < 4)
        {
            m_calibrationPoints.push_back(cv::Point2f(static_cast<float>(x), static_cast<float>(y)));

            if (m_calibrationPoints.size() == 4)
            {
                // 4개의 점이 모두 선택되면 자동으로 PerformCalibration이 호출됩니다.
                cv::setMouseCallback("Calibration", nullptr, nullptr);
            }
        }
        break;

    case cv::EVENT_RBUTTONDOWN:
        if (!m_calibrationPoints.empty())
        {
            m_calibrationPoints.pop_back();
            // 메시지 출력
            CString message;
            message.Format(_T("마지막 점이 취소되었습니다. 남은 점: %d"), m_calibrationPoints.size());
            AfxMessageBox(message);
        }
        break;
    }
}

void COpenCVDlgDlg::MouseCalibrationCallback(int event, int x, int y, int flags, void* userdata)
{
    COpenCVDlgDlg* dlg = static_cast<COpenCVDlgDlg*>(userdata);
    dlg->OnMouseCalibration(event, x, y, flags, userdata);
}


void COpenCVDlgDlg::EnableAllButtons(BOOL enable)
{
    GetDlgItem(IDC_BUTTON_PT)->EnableWindow(enable);
    GetDlgItem(IDC_BUTTON_PY)->EnableWindow(enable);
    GetDlgItem(IDC_BUTTON_DL)->EnableWindow(enable);
    GetDlgItem(IDC_BUTTON1)->EnableWindow(enable);
    GetDlgItem(IDC_BUTTON2)->EnableWindow(enable);
    GetDlgItem(IDC_BUTTON3)->EnableWindow(enable);
    // ... 다른 버튼들도 필요에 따라 추가
}

void COpenCVDlgDlg::PerformCalibration()
{
    if (m_calibrationPoints.size() != 4) {
        AfxMessageBox(_T("캘리브레이션을 위해 4개의 점이 필요합니다."));
        return;
    }

    // 목표 점 (직사각형)
    std::vector<cv::Point2f> dstPoints;
    dstPoints.push_back(cv::Point2f(0, 0));
    dstPoints.push_back(cv::Point2f(static_cast<float>(m_matImage.cols - 1), 0));
    dstPoints.push_back(cv::Point2f(static_cast<float>(m_matImage.cols - 1), static_cast<float>(m_matImage.rows - 1)));
    dstPoints.push_back(cv::Point2f(0, static_cast<float>(m_matImage.rows - 1)));

    // Homography 행렬 계산
    m_homographyMatrix = cv::getPerspectiveTransform(m_calibrationPoints, dstPoints);

    // 이미지 변환
    cv::warpPerspective(m_matImage, m_matImage, m_homographyMatrix, m_matImage.size());

    // 결과 표시
    DisplayImage(m_matImage, IDC_IMAGE);

    m_isCalibrated = true;
    EnableAllButtons(TRUE);  // 모든 버튼 활성화

    // 캘리브레이션 완료 메시지
    AfxMessageBox(_T("캘리브레이션이 완료되었습니다. 영상이 수평으로 조정되어 계속 표시됩니다."));
}


void COpenCVDlgDlg::InitializeListControl()
{
    m_listGr.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

    // 첫 번째 열 추가 (종류)
    m_listGr.InsertColumn(0, _T("종류"), LVCFMT_LEFT, 100);

    // 두 번째 열 추가 (결과)
    m_listGr.InsertColumn(1, _T("결과"), LVCFMT_LEFT, 50);
}
void COpenCVDlgDlg::UpdatePatternRecognitionResults(const std::vector<bool>& matchResults)
{
    m_listGr.DeleteAllItems();

    int itemCount = m_patternList.GetCount();
    for (int i = 0; i < itemCount && i < matchResults.size(); ++i)
    {
        CString fileName;
        m_patternList.GetText(i, fileName);

        int nIndex = m_listGr.InsertItem(i, fileName);
        CString result = matchResults[i] ? _T("T") : _T("F");
        m_listGr.SetItemText(nIndex, 1, result);

        // 결과에 따라 텍스트 색상 설정
        COLORREF textColor = matchResults[i] ? RGB(0, 255, 0) : RGB(255, 0, 0);
        m_listGr.SetItemData(nIndex, textColor);
    }

    // 리스트 컨트롤에 사용자 정의 그리기를 적용
    m_listGr.SetExtendedStyle(m_listGr.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
    m_listGr.SetCallbackMask(LVIS_OVERLAYMASK);
    m_listGr.SetCallbackMask(LVIS_OVERLAYMASK | LVIS_STATEIMAGEMASK);
}

void COpenCVDlgDlg::DrawListItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    if ((int)lpDrawItemStruct->itemID < 0)
        return;

    CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
    CRect rcItem(lpDrawItemStruct->rcItem);
    int nItem = lpDrawItemStruct->itemID;
    CString strText;

    // 아이템 배경 그리기
    pDC->FillSolidRect(rcItem, RGB(255, 255, 255));  // 흰색 배경

    // 첫 번째 열 (종류) 그리기
    strText = m_listGr.GetItemText(nItem, 0);
    pDC->SetTextColor(RGB(0, 0, 0));  // 검은색 텍스트
    pDC->DrawText(strText, rcItem, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

    // 두 번째 열 (결과) 그리기
    CRect rcSubItem;
    m_listGr.GetSubItemRect(nItem, 1, LVIR_BOUNDS, rcSubItem);
    strText = m_listGr.GetItemText(nItem, 1);
    COLORREF textColor = (COLORREF)m_listGr.GetItemData(nItem);
    pDC->SetTextColor(textColor);
    pDC->DrawText(strText, rcSubItem, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

    // 아이템이 선택된 경우 하이라이트 표시
    if (lpDrawItemStruct->itemState & ODS_SELECTED)
    {
        pDC->DrawFocusRect(rcItem);
    }
}

    void COpenCVDlgDlg::OnCustomDrawList(NMHDR * pNMHDR, LRESULT * pResult)
    {
        NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);
        *pResult = CDRF_DODEFAULT;

        if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
        {
            *pResult = CDRF_NOTIFYITEMDRAW;
        }
        else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
        {
            COLORREF textColor = (COLORREF)m_listGr.GetItemData(pLVCD->nmcd.dwItemSpec);
            pLVCD->clrText = textColor;
            *pResult = CDRF_DODEFAULT;
        }
    }

    void COpenCVDlgDlg::OnNMClickListGr(NMHDR* pNMHDR, LRESULT* pResult)
    {
        LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
        int nItem = pNMItemActivate->iItem;

        if (nItem >= 0 && nItem < m_detectedPatternRects.size())
        {
            SaveDetectedPattern(nItem);
        }

        *pResult = 0;
    }

    void COpenCVDlgDlg::SaveDetectedPattern(int index)
    {
        if (index < 0 || index >= m_detectedPatternRects.size() || m_processedImage.empty())
        {
            AfxMessageBox(_T("유효하지 않은 인덱스이거나 이미지가 없습니다."));
            return;
        }

        cv::Rect rect = m_detectedPatternRects[index];
        cv::Mat patternImage = m_processedImage(rect).clone();

        CString fileName;
        fileName.Format(_T("detected_pattern_%d.jpg"), index);

        try
        {
            cv::imwrite(std::string(CT2A(fileName)), patternImage);
            AfxMessageBox(_T("패턴 이미지가 저장되었습니다: ") + fileName);
        }
        catch (const cv::Exception& e)
        {
            CString errorMsg;
            errorMsg.Format(_T("이미지 저장 중 오류 발생: %s"), CString(e.what()));
            AfxMessageBox(errorMsg);
        }
    }


    cv::Mat COpenCVDlgDlg::DetectContours() {
        cv::Mat frame, gray, thresh, hsv, mask, rotated;
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;

        if (capture->read(frame)) {
            // 1. 원본 프레임을 'Original Frame' 창에 표시
            cv::imshow("Original Frame", frame);

            // 2. 두 번째로 큰 사각형 검출
            cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
            cv::GaussianBlur(gray, gray, cv::Size(5, 5), 1.5);
            cv::threshold(gray, thresh, 127, 255, cv::THRESH_BINARY);
            cv::findContours(thresh, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

            std::vector<cv::RotatedRect> minRects;
            for (const auto& contour : contours) {
                if (contour.size() >= 5) {
                    minRects.push_back(cv::minAreaRect(contour));
                }
            }

            // 윤곽선을 크기순으로 정렬
            std::sort(minRects.begin(), minRects.end(), [](const cv::RotatedRect& a, const cv::RotatedRect& b) {
                return a.size.area() > b.size.area();
                });

            if (minRects.size() > 1) {
                // 두 번째로 큰 사각형 선택
                cv::RotatedRect secondLargestRect = minRects[1];

                // 3. 그레이스케일 이미지를 'Gray Image' 창에 표시
                //cv::imshow("Gray Image", gray);

                // 4. 두 번째 사각형의 가장 긴 선분을 화면에 수평하게 회전
                float angle = secondLargestRect.angle;
                if (secondLargestRect.size.width < secondLargestRect.size.height) {
                    angle += 90;
                }

                // 이미지의 중심 기준으로 회전 매트릭스 생성
                cv::Mat rotationMatrix = cv::getRotationMatrix2D(cv::Point2f(frame.cols / 2, frame.rows / 2), angle, 1);
                cv::warpAffine(frame, rotated, rotationMatrix, frame.size());

                // 회전된 이미지를 'Rotated Image' 창에 표시
                //cv::imshow("Rotated Image", rotated);

                // 5. 빨간색 영역 검출
                cv::cvtColor(rotated, hsv, cv::COLOR_BGR2HSV);
                cv::Scalar lower_red1(0, 100, 100);
                cv::Scalar upper_red1(10, 255, 255);
                cv::Scalar lower_red2(160, 100, 100);
                cv::Scalar upper_red2(179, 255, 255);

                cv::Mat mask1, mask2;
                cv::inRange(hsv, lower_red1, upper_red1, mask1);
                cv::inRange(hsv, lower_red2, upper_red2, mask2);
                mask = mask1 | mask2;

                // 마스크된 이미지를 'Red Mask' 창에 표시
              //  cv::imshow("Red Mask", mask);

                std::vector<std::vector<cv::Point>> redContours;
                cv::findContours(mask, redContours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

                cv::Point2f redCenter;
                double maxRedArea = 0;
                for (const auto& redContour : redContours) {
                    double area = cv::contourArea(redContour);
                    if (area > maxRedArea) {
                        maxRedArea = area;
                        cv::Moments m = cv::moments(redContour);
                        redCenter = cv::Point2f(m.m10 / m.m00, m.m01 / m.m00);
                    }
                }

                // 6. 사각형 내에서 빨간 포인트의 위치 확인
                cv::Point2f rectPoints[4];
                secondLargestRect.points(rectPoints);

                // 사각형의 중심점 계산
                cv::Point2f rectCenter = (rectPoints[0] + rectPoints[2]) * 0.5f;

                // 사각형 내에서 빨간 포인트의 상대적 위치 계산
                cv::Point2f relativeRedCenter = redCenter - rectCenter;

                // 사각형의 방향 벡터 계산 (가장 긴 변의 방향)
                cv::Point2f rectDirection = rectPoints[1] - rectPoints[0];
                if (cv::norm(rectPoints[2] - rectPoints[1]) > cv::norm(rectDirection)) {
                    rectDirection = rectPoints[2] - rectPoints[1];
                }

                // 빨간 포인트가 사각형의 오른쪽에 있는지 확인
                bool isRedPointOnRight = (relativeRedCenter.dot(cv::Point2f(-rectDirection.y, rectDirection.x)) > 0);

                // 7. 빨간 포인트가 오른쪽에 있을 때만 180도 회전
                if (isRedPointOnRight) {
                    cv::Mat additionalRotationMatrix = cv::getRotationMatrix2D(cv::Point2f(rotated.cols / 2, rotated.rows / 2), 180, 1);
                    cv::warpAffine(rotated, rotated, additionalRotationMatrix, rotated.size());
                    // 회전 후 빨간색 중심점 업데이트
                    redCenter = cv::Point2f(rotated.cols, rotated.rows) - redCenter;
                }

                // 8. 최종 회전된 이미지에서 다시 두 번째로 큰 사각형 검출 및 추출
                cv::cvtColor(rotated, gray, cv::COLOR_BGR2GRAY);
                cv::GaussianBlur(gray, gray, cv::Size(5, 5), 1.5);
                cv::threshold(gray, thresh, 127, 255, cv::THRESH_BINARY);
                cv::findContours(thresh, contours, hierarchy, cv::RETR_LIST, cv::CHAIN_APPROX_SIMPLE);

                std::vector<cv::RotatedRect> finalRects;
                for (const auto& contour : contours) {
                    if (contour.size() >= 5) {
                        finalRects.push_back(cv::minAreaRect(contour));
                    }
                }

                std::sort(finalRects.begin(), finalRects.end(), [](const cv::RotatedRect& a, const cv::RotatedRect& b) {
                    return a.size.area() > b.size.area();
                    });

                if (finalRects.size() > 1) {
                    cv::RotatedRect finalRect = finalRects[1];
                    cv::Rect boundingRect = finalRect.boundingRect();

                    // 바운딩 박스가 이미지 경계를 벗어나지 않도록 조정
                    boundingRect &= cv::Rect(0, 0, rotated.cols, rotated.rows);

                    // 두 번째로 큰 사각형 영역 추출
                    cv::Mat extractedRegion = rotated(boundingRect).clone();

                    // 추출된 영역에 사각형 그리기
                    cv::rectangle(extractedRegion, cv::Point(0, 0), cv::Point(extractedRegion.cols - 1, extractedRegion.rows - 1), cv::Scalar(0, 255, 255), 2);

                    // 빨간색 포인트 표시 (extractedRegion 내부의 상대 위치로 조정)
                    cv::Point adjustedRedCenter(redCenter.x - boundingRect.x, redCenter.y - boundingRect.y);
                    if (adjustedRedCenter.inside(cv::Rect(0, 0, extractedRegion.cols, extractedRegion.rows))) {
                        cv::circle(extractedRegion, adjustedRedCenter, 5, cv::Scalar(0, 0, 255), -1);
                    }

                    return extractedRegion;  // 추출된 영역 반환
                }
                else {
                    std::cout << "No second largest rectangle detected in rotated image" << std::endl;
                    return rotated;  // 회전된 전체 이미지 반환
                }
            }
            else {
                std::cout << "No second largest rectangle detected in original image" << std::endl;
                return frame;  // 원본 프레임 반환
            }
        }
        return cv::Mat();  // 빈 Mat 객체 반환 (에러 케이스)
    }