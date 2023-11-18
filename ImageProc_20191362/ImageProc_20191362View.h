
// ImageProc_20191362View.h: CImageProc20191362View 클래스의 인터페이스
//

#pragma once


class CImageProc20191362View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageProc20191362View() noexcept;
	DECLARE_DYNCREATE(CImageProc20191362View)

// 특성입니다.
public:
	CImageProc20191362Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
//	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
//	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
//	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageProc20191362View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnFixelMul();
	afx_msg void OnFixelDiv();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelContrastStraching();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelTwoImageAdd();
	void LoadTwoImage();
	afx_msg void OnPixelTwoImageSub();
	afx_msg void OnPixelTwoImageMul();
	afx_msg void OnPixelTwoImageDiv();
	afx_msg void OnRegionSmoothing();
	void Convolve(unsigned char** inimg, unsigned char** OutImg, int cols, int rows, float mask[][3], int bias, int depth);
	afx_msg void OnRegionSharpening();
	afx_msg void OnRegionEnboshing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnResionMedianFilterling();
	afx_msg void OnMopologyColorGray();
	afx_msg void OnMopologyBinarization();
	afx_msg void OnMopologyErosion();
	afx_msg void OnMopologyOpening();
	afx_msg void OnMopologyClosing();
	afx_msg void OnMopologyDilation();
//	int CopyResultTonInput();
	void CopyResultToInput();
	afx_msg void OnGeometryZoominPixelCopy();
//	afx_msg void OnGeometryZoominInterpolation();
	afx_msg void OnGeometryZoominBilinearInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutMeanSub();
	afx_msg void OnGeometryAvgFiltering();
	afx_msg void OnGeometryRotation();
	afx_msg void OnGeometryHolizantalFlip();
	afx_msg void OnGeometryVerticalClip();
};

#ifndef _DEBUG  // ImageProc_20191362View.cpp의 디버그 버전
inline CImageProc20191362Doc* CImageProc20191362View::GetDocument() const
   { return reinterpret_cast<CImageProc20191362Doc*>(m_pDocument); }
#endif

