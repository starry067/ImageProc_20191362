
// ImageProc_20191362View.cpp: CImageProc20191362View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20191362.h"
#endif

#include "ImageProc_20191362Doc.h"
#include "ImageProc_20191362View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageProc20191362View

IMPLEMENT_DYNCREATE(CImageProc20191362View, CScrollView)

BEGIN_MESSAGE_MAP(CImageProc20191362View, CScrollView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CScrollView::OnFilePrintPreview)
	ON_COMMAND(ID_Pixel_Add, &CImageProc20191362View::OnPixelAdd)
	ON_COMMAND(ID_Pixel_Sub, &CImageProc20191362View::OnPixelSub)
	ON_COMMAND(ID_FIXEL_MUL, &CImageProc20191362View::OnFixelMul)
	ON_COMMAND(ID_FIXEL_DIV, &CImageProc20191362View::OnFixelDiv)
	ON_COMMAND(ID_PIXEL_HISTO_EQ, &CImageProc20191362View::OnPixelHistoEq)
	ON_COMMAND(ID_PIXEL_CONTRAST_STRACHING, &CImageProc20191362View::OnPixelContrastStraching)
	ON_COMMAND(ID_PIXEL_BINARIZATION, &CImageProc20191362View::OnPixelBinarization)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_ADD, &CImageProc20191362View::OnPixelTwoImageAdd)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_SUB, &CImageProc20191362View::OnPixelTwoImageSub)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_MUL, &CImageProc20191362View::OnPixelTwoImageMul)
	ON_COMMAND(ID_PIXEL_TWO_IMAGE_DIV, &CImageProc20191362View::OnPixelTwoImageDiv)
	ON_COMMAND(ID_REGION_SMOOTHING, &CImageProc20191362View::OnRegionSmoothing)
	ON_COMMAND(ID_REGION_SHARPENING, &CImageProc20191362View::OnRegionSharpening)
	ON_COMMAND(ID_REGION_ENBOSHING, &CImageProc20191362View::OnRegionEnboshing)
	ON_COMMAND(ID_REGION_Prewitt, &CImageProc20191362View::OnRegionPrewitt)
	ON_COMMAND(ID_REGION_Roberts, &CImageProc20191362View::OnRegionRoberts)
	ON_COMMAND(ID_REGION_SOBEL, &CImageProc20191362View::OnRegionSobel)
	ON_COMMAND(ID_REGION_AVERAGE_FILTERING, &CImageProc20191362View::OnRegionAverageFiltering)
	ON_COMMAND(ID_RESION_MEDIAN_FILTERLING, &CImageProc20191362View::OnResionMedianFilterling)
	ON_COMMAND(ID_MOPOLOGY_COLOR_GRAY, &CImageProc20191362View::OnMopologyColorGray)
	ON_COMMAND(ID_MOPOLOGY_BINARIZATION, &CImageProc20191362View::OnMopologyBinarization)
	ON_COMMAND(ID_MOPOLOGY_EROSION, &CImageProc20191362View::OnMopologyErosion)
	ON_COMMAND(ID_MOPOLOGY_OPENING, &CImageProc20191362View::OnMopologyOpening)
	ON_COMMAND(ID_MOPOLOGY_CLOSING, &CImageProc20191362View::OnMopologyClosing)
	ON_COMMAND(ID_MOPOLOGY_DILATION, &CImageProc20191362View::OnMopologyDilation)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_PIXEL_COPY, &CImageProc20191362View::OnGeometryZoominPixelCopy)
	ON_COMMAND(ID_GEOMETRY_ZOOMIN_BILINEAR_INTERPOLATION, &CImageProc20191362View::OnGeometryZoominBilinearInterpolation)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_SUBSAMPLING, &CImageProc20191362View::OnGeometryZoomoutSubsampling)
	ON_COMMAND(ID_GEOMETRY_ZOOMOUT_MEAN_SUB, &CImageProc20191362View::OnGeometryZoomoutMeanSub)
	ON_COMMAND(ID_GEOMETRY_AVG_FILTERING, &CImageProc20191362View::OnGeometryAvgFiltering)
	ON_COMMAND(ID_GEOMETRY_ROTATION, &CImageProc20191362View::OnGeometryRotation)
	ON_COMMAND(ID_GEOMETRY_HOLIZANTAL_FLIP, &CImageProc20191362View::OnGeometryHolizantalFlip)
	ON_COMMAND(ID_GEOMETRY_VERTICAL_CLIP, &CImageProc20191362View::OnGeometryVerticalClip)
END_MESSAGE_MAP()

// CImageProc20191362View 생성/소멸

CImageProc20191362View::CImageProc20191362View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageProc20191362View::~CImageProc20191362View()
{
}

BOOL CImageProc20191362View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CScrollView::PreCreateWindow(cs);
}

// CImageProc20191362View 그리기

void CImageProc20191362View::OnDraw(CDC* pDC)
{
	CImageProc20191362Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int x, y;
	if (pDoc->InputImg != NULL) {
		if (pDoc->depth == 1) {      // 반복문 바깥에 컬러 조건을 넣음으로써 줄은 길어져도 속도면에서 좋음
			for (y = 0; y < pDoc->ImageHeight; y++) {
				for (x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(x, y, RGB(pDoc->InputImg[y][x],   // 삽입 이미지 공간 생성
						pDoc->InputImg[y][x],
						pDoc->InputImg[y][x]));
				}
			}
		}
		else {   // 컬러일 때
			for (y = 0; y < pDoc->ImageHeight; y++) {
				for (x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(x, y, RGB(pDoc->InputImg[y][3 * x + 0],   // red 성분   3*x+0   
						pDoc->InputImg[y][3 * x + 1],   // green 성분 3*x+1
						pDoc->InputImg[y][3 * x + 2]));   // blue 성분  3*x+2
				}
			}
		}
	}
	if (pDoc->resultImg != NULL) {
		if (pDoc->depth == 1) {
			for (y = 0; y < pDoc->ImageHeight; y++) {
				for (x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(x + pDoc->ImageWidth + 20, y, RGB(pDoc->resultImg[y][x],
						pDoc->resultImg[y][x],
						pDoc->resultImg[y][x]));
				}
			}
		}
		else {
			for (y = 0; y < pDoc->ImageHeight; y++) {
				for (x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(x + pDoc->ImageWidth + 20, y, RGB(pDoc->resultImg[y][3 * x + 0],
						pDoc->resultImg[y][3 * x + 1],
						pDoc->resultImg[y][3 * x + 2]));
				}
			}
		}
	}
	if (pDoc->InputImg2 != NULL) {
		if (pDoc->depth == 1) {
			for (y = 0; y < pDoc->ImageHeight; y++) {
				for (x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(x + 2 * (pDoc->ImageWidth + 20), y, RGB(pDoc->InputImg2[y][x],
						pDoc->InputImg2[y][x],
						pDoc->InputImg2[y][x]));
				}
			}
		}
		else {
			for (y = 0; y < pDoc->ImageHeight; y++) {
				for (x = 0; x < pDoc->ImageWidth; x++) {
					pDC->SetPixel(x + 2 * (pDoc->ImageWidth + 20), y, RGB(pDoc->InputImg2[y][3 * x + 0],   // red 성분   3*x+0   
						pDoc->InputImg2[y][3 * x + 1],                  // green 성분 3*x+1
						pDoc->InputImg2[y][3 * x + 2]));                  // blue 성분  3*x+2
				}
			}
		}
	}
	if (pDoc->gResultImg != NULL) {
		if (pDoc->depth == 1) {
			for (y = 0; y < pDoc->gImageHeight; y++) {
				for (x = 0; x < pDoc->gImageWidth; x++) {
					pDC->SetPixel(x, pDoc->ImageWidth +20 + y, RGB(pDoc->gResultImg[y][x],
						pDoc->gResultImg[y][x],
						pDoc->gResultImg[y][x]));
				}
			}
		}
		else {
			for (y = 0; y < pDoc->gImageHeight; y++) {
				for (x = 0; x < pDoc->gImageWidth; x++) {
					pDC->SetPixel(x, pDoc->ImageWidth + 20 + y, RGB(pDoc->gResultImg[y][3 * x + 0],
						pDoc->gResultImg[y][3 * x + 1],
						pDoc->gResultImg[y][3 * x + 2]));
				}
			}
		}
	}
	
}

void CImageProc20191362View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: 이 뷰의 전체 크기를 계산합니다.
	sizeTotal.cx = sizeTotal.cy = 2048;
	SetScrollSizes(MM_TEXT, sizeTotal);
}


// CImageProc20191362View 인쇄

//BOOL CImageProc20191362View::OnPreparePrinting(CPrintInfo* pInfo)
//{
//	// 기본적인 준비
//	return DoPreparePrinting(pInfo);
//}

//void CImageProc20191362View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//{
//	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
//}

//void CImageProc20191362View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
//{
//	// TODO: 인쇄 후 정리 작업을 추가합니다.
//}


// CImageProc20191362View 진단

#ifdef _DEBUG
void CImageProc20191362View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CImageProc20191362View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CImageProc20191362Doc* CImageProc20191362View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageProc20191362Doc)));
	return (CImageProc20191362Doc*)m_pDocument;
}
#endif //_DEBUG

void CImageProc20191362View::OnPixelAdd()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	if (pDoc->InputImg == NULL)return;

	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = pDoc->InputImg[y][x] + 50;
			if (value > 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->resultImg[y][x] = value;
		}
	Invalidate(); // 데이터 수정한걸 다시 그리면서 화면에 나타남
}


void CImageProc20191362View::OnPixelSub()
{
	CImageProc20191362Doc* pDoc = GetDocument();
	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = pDoc->InputImg[y][x] - 50; // 뺄셈 연산으로 변경
			if (value > 255) {	value = 255;
			}else if (value < 0) value = 0;
			pDoc->resultImg[y][x] = value; // 할당 연산자 '='로 변경
		}
	}
	Invalidate();
}



void CImageProc20191362View::OnFixelMul()
{
	CImageProc20191362Doc* pDoc = GetDocument();
	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = pDoc->InputImg[y][x] * 2;
			if (value > 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->resultImg[y][x] = value;
		}
	Invalidate();

}

void CImageProc20191362View::OnFixelDiv()
{
	CImageProc20191362Doc* pDoc = GetDocument();
	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = pDoc->InputImg[y][x] / 2;
			if (value > 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->resultImg[y][x] = value;
		}
	Invalidate();

}

void CImageProc20191362View::OnPixelHistoEq()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	int x, y, i, k;
	int acc_Hist;                     // 누적된 히스토그램 값
	int N = pDoc->ImageHeight * pDoc->ImageWidth;                  // N 전체 화소 수 
	int hist[256], sum[256];            // hist 히스토그램 밝기 sum 누적분포

	for (i = 0; i < 256; i++) hist[i] = 0;  // 히스토그램 초기화

	// 히스토그램 구하기
	for (y = 0; y < 256; y++)
		for (x = 0; x < 256; x++) {
			k = pDoc->InputImg[y][x];
			hist[k]++;                     // 히스토그램 처리
		}

	// 누적분포
	acc_Hist = 0;
	for (i = 0; i < 256; i++) {            // 히스토그램 각 밝기 값을 sum에 저장
		acc_Hist += hist[i];
		sum[i] = acc_Hist;
	}

	// 평활화 화소값 저장
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			k = pDoc->InputImg[y][x];
			pDoc->resultImg[y][x] = (float)sum[k] / N * 255; // float 캐스트 연산자로 소수점을 구해야함 안그럼 0과 1 흰 검으로 나타남
		}
	Invalidate();
}


void CImageProc20191362View::OnPixelContrastStraching()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	int x, y;
	int minVal = 255;
	int maxVal = 0;

	// 입력 이미지에서 최소값과 최대값을 찾습니다.
	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			int pixelValue = pDoc->InputImg[y][x];
			if (pixelValue < minVal) {
				minVal = pixelValue;
			}
			if (pixelValue > maxVal) {
				maxVal = pixelValue;
			}
		}
	}

	// 명암 대비 스트레칭을 적용하여 결과 이미지를 생성합니다.
	for (y = 0; y < pDoc->ImageHeight; y++) {
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			int pixelValue = pDoc->InputImg[y][x];
			int stretchedValue = 255 * (pixelValue - minVal) / (maxVal - minVal);

			// 범위를 벗어난 값은 조정합니다.
			if (stretchedValue > 255) {
				stretchedValue = 255;
			}
			else if (stretchedValue < 0) {
				stretchedValue = 0;
			}
			pDoc->resultImg[y][x] = stretchedValue;
		}
	}
	Invalidate();
}


void CImageProc20191362View::OnPixelBinarization()
{
	CImageProc20191362Doc* pDoc = GetDocument();
	int x, y, value;
	int threshold = 128;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = pDoc->InputImg[y][x];                     // 인풋 이미지의 픽셀을 받아옴
			if (value > threshold)   pDoc->resultImg[y][x] = 255;   // 받은 각 픽셀의 값이 128보다 크면 흰
			else               pDoc->resultImg[y][x] = 0;      // 픽셀의 값이 128보다 같거나 작으면 검
		}
	Invalidate();
}

// 두 연산의 덧셈
void CImageProc20191362View::OnPixelTwoImageAdd()
{
	CImageProc20191362Doc* pDoc = GetDocument();
	
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() != IDOK) // DoModal 호출하면 뜸 // IDOK = 확인 // IDCANCEL == 취소
		return;

	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead); // 파일 열어서 읽기모드
	CArchive ar(&file, CArchive::load);
	//LoadTwoImage();      // 새로운 이미지 불러오기
	pDoc->LoadSecondImageFile(ar);
	file.Close();

	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = 0.5 * pDoc->InputImg[y][x] + 0.5 * pDoc->InputImg2[y][x];   // 0.* 수정해서 해당 이미지 선명도를 높임
			if (value > 255) value = 255;      // 픽셀 값이 255가 넘어가면 255로 고정
			else if (value < 0) value = 0;      //  " 0보다 작아지면 0으로 고정
			pDoc->resultImg[y][x] = value;
		}

	Invalidate();;
}

// 두 연산의 뺄셈
void CImageProc20191362View::OnPixelTwoImageSub()
{
	CImageProc20191362Doc* pDoc = GetDocument();
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() != IDOK) // DoModal 호출하면 뜸 // IDOK = 확인 // IDCANCEL == 취소
		return;

	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead); // 파일 열어서 읽기모드
	CArchive ar(&file, CArchive::load);
	//LoadTwoImage();      // 새로운 이미지 불러오기
	pDoc->LoadSecondImageFile(ar);
	file.Close();

	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = abs(pDoc->InputImg[y][x] - pDoc->InputImg2[y][x]);   // abs로 절댓값을 구함
			if (value > 255) value = 255;      // 픽셀 값이 255가 넘어가면 255로 고정
			else if (value < 0) value = 0;      //  " 0보다 작아지면 0으로 고정
			pDoc->resultImg[y][x] = value;
		}
	Invalidate();
}

// 두 연산의 곱셉
void CImageProc20191362View::OnPixelTwoImageMul()
{
	CImageProc20191362Doc* pDoc = GetDocument();
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() != IDOK) // DoModal 호출하면 뜸 // IDOK = 확인 // IDCANCEL == 취소
		return;

	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead); // 파일 열어서 읽기모드
	CArchive ar(&file, CArchive::load);
	//LoadTwoImage();      // 새로운 이미지 불러오기
	pDoc->LoadSecondImageFile(ar);
	file.Close();

	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = pDoc->InputImg[y][x] * pDoc->InputImg2[y][x];   // abs로 절댓값을 구함

			if (value > 255) value = 255;      // 픽셀 값이 255가 넘어가면 255로 고정
			else if (value < 0) value = 0;      //  " 0보다 작아지면 0으로 고정

			pDoc->resultImg[y][x] = value;
		}
	Invalidate();
}

// 두 연산의 나눗셈
void CImageProc20191362View::OnPixelTwoImageDiv()
{
	CImageProc20191362Doc* pDoc = GetDocument();
	CFileDialog dlg(TRUE);

	if (dlg.DoModal() != IDOK) // DoModal 호출하면 뜸 // IDOK = 확인 // IDCANCEL == 취소
		return;

	CFile file;
	file.Open(dlg.GetPathName(), CFile::modeRead); // 파일 열어서 읽기모드
	CArchive ar(&file, CArchive::load);
	//LoadTwoImage();      // 새로운 이미지 불러오기
	pDoc->LoadSecondImageFile(ar);
	file.Close();

	int x, y, value;
	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++) {
			value = (float)pDoc->InputImg[y][x] / pDoc->InputImg2[y][x];   // abs로 절댓값을 구함

			if (value > 255) value = 255;      // 픽셀 값이 255가 넘어가면 255로 고정
			else if (value < 0) value = 0;      //  " 0보다 작아지면 0으로 고정

			pDoc->resultImg[y][x] = value;
		}
	Invalidate();
}
void CImageProc20191362View::LoadTwoImage()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	CFileDialog dlg(TRUE);
	CFile file;

	if (dlg.DoModal() == IDOK) {   // DoModal 호출하면 뜸 // IDOK = 확인 // IDCANCEL == 취소

		file.Open(dlg.GetPathName(), CFile::modeRead); // 파일 열어서 읽기모드
		CArchive ar(&file, CArchive::load);
		ar.Read(pDoc->InputImg2, 256 * 256);
		//file.Read(pDoc->inputImg2, 256 * 256);         // 파일 읽어서 inputImage2에 삽입
		file.Close();                           // 파일 닫기

		int x, y;
		for (y = 0; y < 256; y++) {
			for (x = 0; x < 256; x++) {
				pDoc->resultImg[y][x] = pDoc->InputImg[y][x];   // 결과 이미지를 초기화
			}
		}
		Invalidate();
	}

}

void CImageProc20191362View::OnRegionSmoothing()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	float kernel[3][3] = { {1 / 9.0,1 / 9.0,1 / 9.0},
							{1 / 9.0,1 / 9.0,1 / 9.0},
							{1 / 9.0,1 / 9.0,1 / 9.0} };
	Convolve(pDoc->InputImg, pDoc->resultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);
	
	Invalidate();
}

void CImageProc20191362View::OnRegionSharpening()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	float kernel[3][3] = {	{0,-1,0},
							{-1,5,-1},
							{0,-1,0} };
	Convolve(pDoc->InputImg, pDoc->resultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}


void CImageProc20191362View::Convolve(unsigned char** Inimg, unsigned char** Outimg, int cols, int rows, float mask[][3], int bias, int depth)
{
	int x, y, value, i, j;
	float sum, redsum, greensum, bluesum;
	for (y = 1; y < rows - 1; y++) {      // 테두리 부분 계산 의미 없으므로
		for (x = 1; x < cols - 1; x++) {
			if (depth == 1) {            // 흑백일 때
				sum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++)
						sum += Inimg[y - 1 + j][x - 1 + i] * mask[j][i];
				sum += bias;
				if (sum > 255) sum = 255;
				else if (sum < 0)sum = 0;
				Outimg[y][x] = sum;
			}
			else {                  // 컬러일 때
				redsum = greensum = bluesum = 0;
				for (j = 0; j < 3; j++)
					for (i = 0; i < 3; i++) {
						redsum += Inimg[y - 1 + j][3 * (x - 1 + i) + 0] * mask[j][i];
						greensum += Inimg[y - 1 + j][3 * (x - 1 + i) + 1] * mask[j][i];
						bluesum += Inimg[y - 1 + j][3 * (x - 1 + i) + 2] * mask[j][i];
					}
				redsum += bias;
				greensum += bias;
				bluesum += bias;

				if (redsum > 255) redsum = 255;
				else if (redsum < 0)redsum = 0;
				if (greensum > 255) greensum = 255;
				else if (greensum < 0)greensum = 0;
				if (bluesum > 255) bluesum = 255;
				else if (bluesum < 0)bluesum = 0;

				Outimg[y][3 * x + 0] = redsum;
				Outimg[y][3 * x + 1] = greensum;
				Outimg[y][3 * x + 2] = bluesum;
			}
		}
	}
}
void CImageProc20191362View::OnRegionEnboshing()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	float kernel[3][3] = { {-1, 0, 0},
							{0,  0, 0},
							{0,  0, 1} };
	Convolve(pDoc->InputImg, pDoc->resultImg, pDoc->ImageWidth, pDoc->ImageHeight, kernel, 0, pDoc->depth);

	Invalidate();
}



void CImageProc20191362View::OnRegionPrewitt()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	float Hmask[3][3] = { {-1, -1, -1},
						  {0, 0, 0},
						  {1, 1, 1} };
	float Vmask[3][3] = { {-1, 0, 1},
						  {-1, 0, 1},
						  {-1, 0, 1} };

	unsigned char** Er, ** Ec;
	int x, y, value;

	// 메모리 할당
	Er = (unsigned char**)malloc(pDoc -> ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc -> ImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 0, pDoc->depth);
	Convolve(pDoc->InputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 0, pDoc->depth);

	for (y = 0; y < pDoc->ImageHeight; y++) 
		for (x = 0; x < pDoc->ImageWidth; x++) {
			if (pDoc->depth == 1) 
			{
				value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]);
				if (value > 255)		value = 255;
				else if (value < 0)		value = 0;
				pDoc->resultImg[y][x] = value;
			}
			else
			{
				value = sqrt(Er[y][3 * x + 0] * Er[y][3 * x + 0] + Ec[y][3 * x + 0] * Ec[y][3 *x + 0]);
				if (value > 255)		value = 255;
				else if (value < 0)		value = 0;
				pDoc->resultImg[y][3 * x + 0] = value;

				value = sqrt(Er[y][3 * x + 1] * Er[y][3 * x + 1] + Ec[y][3 * x + 1] * Ec[y][3 * x + 1]);
				if (value > 255)		value = 255;
				else if (value < 0)		value = 0;
				pDoc->resultImg[y][3 * x + 1] = value;

				value = sqrt(Er[y][3 * x + 2] * Er[y][3 * x + 2] + Ec[y][3 * x + 2] * Ec[y][3 * x + 2]);
				if (value > 255)		value = 255;
				else if (value < 0)		value = 0;
				pDoc->resultImg[y][3 * x + 2] = value;

				value = sqrt(pDoc->resultImg[y][3 * x + 0] * pDoc->resultImg[y][3 * x + 0] +
							pDoc->resultImg[y][3 * x + 1] * pDoc->resultImg[y][3 * x + 1] +
							pDoc->resultImg[y][3 * x + 2] * pDoc->resultImg[y][3 * x + 2]);
				if (value > 255)		value = 255;
				else if (value < 0)		value = 0;
				
				pDoc->resultImg[y][3 * x + 0] = value;
				pDoc->resultImg[y][3 * x + 1] = value;
				pDoc->resultImg[y][3 * x + 2] = value;


			}
		}
	
	// 메모리 해제
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProc20191362View::OnRegionRoberts()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.

	CImageProc20191362Doc* pDoc = GetDocument();

	float Hmask[3][3] = { {-1, 0, 0},
						   {0,  1, 0},
						   {0,  0, 0} }; //위 아래 달라지면 다르게 나옴


	float Vmask[3][3] = { {0, 0, -1},
						   {0,  1, 0},
						   {0,  0, 0} };;// 앞뒤 바뀌어도 상관은 없다


	unsigned char** Er, ** Ec;

	int x, y, value;

	//메모리 할당
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < pDoc->ImageHeight; i++) {
		//inputImg[] : unsigned char 포인터 // malloc(imageWidth * depth) 포인터의 값
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 0, pDoc->depth);//영역기반처리
	Convolve(pDoc->InputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 0, pDoc->depth);

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]); //연산해서 합침
			if (value > 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->resultImg[y][x] = value;
		}

	//메모리 할당 해제
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}


void CImageProc20191362View::OnRegionSobel()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	float Hmask[3][3] = { {-1, -2, -1},
						   {0,  0, 0},
						   {1,  2, 1} }; //위 아래 달라지면 다르게 나옴


	float Vmask[3][3] = { {1,  0, -1},
						  {2,  0, 2},
						  {1,  0, -1} };// 앞뒤 바뀌어도 상관은 없다


	unsigned char** Er, ** Ec;

	int x, y, value;

	//메모리 할당
	Er = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));
	Ec = (unsigned char**)malloc(pDoc->ImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < pDoc->ImageHeight; i++) {
		//inputImg[] : unsigned char 포인터 // malloc(imageWidth * depth) 포인터의 값
		Er[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
		Ec[i] = (unsigned char*)malloc(pDoc->ImageWidth * pDoc->depth);
	}

	Convolve(pDoc->InputImg, Er, pDoc->ImageWidth, pDoc->ImageHeight, Hmask, 0, pDoc->depth);//영역기반처리
	Convolve(pDoc->InputImg, Ec, pDoc->ImageWidth, pDoc->ImageHeight, Vmask, 0, pDoc->depth);

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			value = sqrt(Er[y][x] * Er[y][x] + Ec[y][x] * Ec[y][x]); //연산해서 합침
			if (value > 255) value = 255;
			else if (value < 0) value = 0;
			pDoc->resultImg[y][x] = value;
		}

	//메모리 할당 해제
	for (int i = 0; i < pDoc->ImageHeight; i++)
	{
		free(Er[i]);
		free(Ec[i]);
	}
	free(Er);
	free(Ec);

	Invalidate();
}
// 잡음제거------

void CImageProc20191362View::OnRegionAverageFiltering()
{// 평균값 필터링
	CImageProc20191362Doc* pDoc = GetDocument();

	int x, y, i, j;
	int xcor, ycor;
	int sum, count, rsum, gsum, bsum;		// 합과 몇개 필터

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++) 
		{
			if (pDoc->depth == 1) 
			{
				sum = 0;
				count = 0;
				for (j = -2; j <= 2; j++)
					for (i = -2; i <= 2; i++)
					{
						ycor = y + j;
						xcor = x + i;
						if (0 <= ycor && ycor <= pDoc->ImageHeight - 1 && 0 <= xcor && xcor <= pDoc->ImageWidth - 1)
						{
							sum += pDoc->InputImg[ycor][xcor];
							count++;
						}

					}
				pDoc->resultImg[y][x] = sum / count;
			}
			else
			{
				rsum = bsum = gsum = 0;
				count = 0;
				for (j = -2; j <= 2; j++)
					for (i = -2; i <= 2; i++)
					{
						ycor = y + j;
						xcor = x + i;
						if (0 <= ycor && ycor <= pDoc->ImageHeight - 1 && 0 <= xcor && xcor <= pDoc->ImageWidth - 1)
						{
							rsum += pDoc->InputImg[ycor][3 * xcor + 0];
							gsum += pDoc->InputImg[ycor][3 * xcor + 1];
							bsum += pDoc->InputImg[ycor][3 * xcor + 2];
							count++;
						}

					}
				pDoc->resultImg[y][3 * x + 0] = rsum / count;
				pDoc->resultImg[y][3 * x + 1] = gsum / count;
				pDoc->resultImg[y][3 * x + 2] = bsum / count;
			}
		}
	Invalidate();
}


void CImageProc20191362View::OnResionMedianFilterling()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	int x, y, i, j;
	int n[9], temp;


	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			if (pDoc->depth == 1) {
				n[0] = pDoc->InputImg[y - 1][x - 1];
				n[1] = pDoc->InputImg[y - 1][x - 0];
				n[2] = pDoc->InputImg[y - 1][x + 1];
				n[3] = pDoc->InputImg[y - 0][x - 1];
				n[4] = pDoc->InputImg[y - 0][x - 0];
				n[5] = pDoc->InputImg[y - 0][x + 1];
				n[6] = pDoc->InputImg[y + 1][x - 1];
				n[7] = pDoc->InputImg[y + 1][x - 0];
				n[8] = pDoc->InputImg[y + 1][x + 1];

				//sorting
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
				pDoc->resultImg[y][x] = n[4];
			}
			else {
				n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 0];
				n[1] = pDoc->InputImg[y - 1][3 * (x - 0) + 0];
				n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 0];
				n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 0];
				n[4] = pDoc->InputImg[y - 0][3 * (x - 0) + 0];
				n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 0];
				n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 0];
				n[7] = pDoc->InputImg[y + 1][3 * (x - 0) + 0];
				n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 0];

				//sorting
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
				pDoc->resultImg[y][3 * x + 0] = n[4];

				n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 1];
				n[1] = pDoc->InputImg[y - 1][3 * (x - 0) + 1];
				n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 1];
				n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 1];
				n[4] = pDoc->InputImg[y - 0][3 * (x - 0) + 1];
				n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 1];
				n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 1];
				n[7] = pDoc->InputImg[y + 1][3 * (x - 0) + 1];
				n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 1];

				//sorting
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
				pDoc->resultImg[y][3 * x + 1] = n[4];

				n[0] = pDoc->InputImg[y - 1][3 * (x - 1) + 2];
				n[1] = pDoc->InputImg[y - 1][3 * (x - 0) + 2];
				n[2] = pDoc->InputImg[y - 1][3 * (x + 1) + 2];
				n[3] = pDoc->InputImg[y - 0][3 * (x - 1) + 2];
				n[4] = pDoc->InputImg[y - 0][3 * (x - 0) + 2];
				n[5] = pDoc->InputImg[y - 0][3 * (x + 1) + 2];
				n[6] = pDoc->InputImg[y + 1][3 * (x - 1) + 2];
				n[7] = pDoc->InputImg[y + 1][3 * (x - 0) + 2];
				n[8] = pDoc->InputImg[y + 1][3 * (x + 1) + 2];

				//sorting
				for (i = 8; i > 0; i--)
					for (j = 0; j < i; j++)
						if (n[j] > n[j + 1])
						{
							temp = n[j + 1];
							n[j + 1] = n[j];
							n[j] = temp;
						}
				pDoc->resultImg[y][3 * x + 2] = n[4];
			}
			
		}
	Invalidate();
}


void CImageProc20191362View::OnMopologyColorGray()
{
	CImageProc20191362Doc* pDoc = GetDocument();
	if (pDoc->depth == 1)		return;

	int x, y;
	int gray;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			gray = (pDoc->InputImg[y][3 * x + 0] + pDoc->InputImg[y][3 * x + 1] + pDoc->InputImg[y][3 * x + 2]) / 3; // 빨간색
			
			pDoc->InputImg[y][3 * x + 0] = gray;
			pDoc->InputImg[y][3 * x + 1] = gray;
			pDoc->InputImg[y][3 * x + 2] = gray;
		
		}
	Invalidate();
}


void CImageProc20191362View::OnMopologyBinarization()
{
	CImageProc20191362Doc* pDoc = GetDocument();
	int x, y;
	int thresh = 128;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1) 
			{
				if (pDoc->InputImg[y][x] > thresh)
					pDoc->InputImg[y][x] = 255;
				else
					pDoc->InputImg[y][x] = 0;
			}
			else
			{
				if((pDoc->InputImg[y][3 * x + 0] + pDoc->InputImg[y][3 * x + 1] + pDoc->InputImg[y][3 * x + 2])/3 > thresh)
				{
					pDoc->InputImg[y][3 * x + 0] = 255;
					pDoc->InputImg[y][3 * x + 1] = 255;
					pDoc->InputImg[y][3 * x + 2] = 255;
				}
				else
				{
					pDoc->InputImg[y][3 * x + 0] = 0;
					pDoc->InputImg[y][3 * x + 1] = 0;
					pDoc->InputImg[y][3 * x + 2] = 0;
				}
			}
		}
	Invalidate();
}


void CImageProc20191362View::OnMopologyErosion()
{// 침식연산
	CImageProc20191362Doc* pDoc = GetDocument();
	int x, y, i, j;
	int min, rmin, gmin, bmin = 255;

	for (y = 1; y < pDoc->ImageHeight-1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++) 
		{
			if(pDoc->depth == 1)
			{
				min = 255;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImg[y + j][x + i] < min)
							min = pDoc->InputImg[y + j][x + i];
					}
				pDoc->resultImg[y][x] = min;
			}
			else
			{
				rmin = 255;
				gmin = 255;
				bmin = 255;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImg[y + j][3 * (x + i) + 0] < rmin)
							rmin = pDoc->InputImg[y + j][3 * (x + i) + 0];
						if (pDoc->InputImg[y + j][3 * (x + i) + 1] < gmin)
							gmin = pDoc->InputImg[y + j][3 * (x + i) + 1];
						if (pDoc->InputImg[y + j][3 * (x + i) + 2] < bmin)
							bmin = pDoc->InputImg[y + j][3 * (x + i) + 2];
					}
				pDoc->resultImg[y][3 * x + 0] = rmin;
				pDoc->resultImg[y][3 * x + 1] = gmin;
				pDoc->resultImg[y][3 * x + 2] = bmin;

			}
		}
	Invalidate();	// 연산 출력
}


void CImageProc20191362View::OnMopologyDilation()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	int x, y, i, j;
	
	int max, rmax, gmax, bmax = 255;

	for (y = 1; y < pDoc->ImageHeight - 1; y++)
		for (x = 1; x < pDoc->ImageWidth - 1; x++)
		{
			if (pDoc->depth == 1)
			{
				max = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImg[y + j][x + i] > max)
							max = pDoc->InputImg[y + j][x + i];
					}
				pDoc->resultImg[y][x] = max;
			}
			else
			{
				rmax = 0; gmax = 0; bmax = 0;
				for (j = -1; j <= 1; j++)
					for (i = -1; i <= 1; i++)
					{
						if (pDoc->InputImg[y + j][3 * (x + i) + 0] > rmax)
							rmax = pDoc->InputImg[y + j][3 * (x + i) + 0];
						if (pDoc->InputImg[y + j][3 * (x + i) + 1] > gmax)
							gmax = pDoc->InputImg[y + j][3 * (x + i) + 1];
						if (pDoc->InputImg[y + j][3 * (x + i) + 2] > bmax)
							bmax = pDoc->InputImg[y + j][3 * (x + i) + 2];
					}
				pDoc->resultImg[y][3 * x + 0] = rmax;
				pDoc->resultImg[y][3 * x + 1] = gmax;
				pDoc->resultImg[y][3 * x + 2] = bmax;

			}
		}
	Invalidate();	// 연산 출력
}


void CImageProc20191362View::OnMopologyOpening()
{
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();

	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
}


void CImageProc20191362View::CopyResultToInput()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth * pDoc->depth; x++)
		{
			pDoc->InputImg[y][x] = pDoc->resultImg[y][x];
		}
}


void CImageProc20191362View::OnMopologyClosing()
{// 열림연산 반대로
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	CopyResultToInput();
	OnMopologyErosion();
	
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
	OnMopologyDilation();
	CopyResultToInput();
}

void CImageProc20191362View::OnGeometryZoominPixelCopy()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	int x, y;

	int xscale = 3;
	int yscale = 2;
	
	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale;
	// 메모리 할당

	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++) 
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}
	// 역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++) 
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->gResultImg[y][x] = pDoc->InputImg[y / yscale][x / xscale];

			else
			{
				pDoc->gResultImg[y][3 * x + 0] = pDoc->InputImg[y / yscale][3 * (x / xscale) + 0];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->InputImg[y / yscale][3 * (x / xscale) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->InputImg[y / yscale][3 * (x / xscale) + 2];
			}
		}
	/* 전방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			pDoc->gResultImg[y][x] = pDoc->InputImg[y / yscale][x / xscale];
		}
	*/
	Invalidate();
}


void CImageProc20191362View::OnGeometryZoominBilinearInterpolation()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	int x, y;

	float xscale = 2.3;
	float yscale = 1.5;
	float src_x, src_y;
	float alpha, beta;
	int Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;				// 좌표값
	int E, F; // (위아래)픽셀값
	
	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth * xscale + 0.5;
	pDoc->gImageHeight = pDoc->ImageHeight * yscale + 0.5;
	// 메모리 할당

	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}
	// 역방향 사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			src_x = x / xscale;
			src_y = y / yscale;
			alpha = src_x - (int)src_x;
			beta = src_y - (int)src_y;

			Ax = (int)src_x;
			Ay = (int)src_y;
			Bx = Ax + 1;
			By = Ay;
			Cx = Ax;
			Cy = Ay + 1;
			Dx = Ax + 1;
			Dy = Ay + 1;
			
			if (Bx > pDoc->ImageWidth - 1) Bx = pDoc->ImageWidth - 1;
			if (Cy > pDoc->ImageHeight - 1) Cy = pDoc->ImageHeight - 1;
			if (Dx > pDoc->ImageWidth - 1) Dx = pDoc->ImageWidth - 1;
			if (Dy > pDoc->ImageHeight - 1) Dy = pDoc->ImageHeight - 1;

			if (pDoc->depth == 1)
			{
				E = (1 - alpha) * pDoc->InputImg[Ay][Ax] + alpha * pDoc->InputImg[By][Bx];
				F = (1 - alpha) * pDoc->InputImg[Cy][Cx] + alpha * pDoc->InputImg[Dy][Dx];

				pDoc->gResultImg[y][x] = (1 - beta) * E + beta * F;
			}
			else 
			{
				F = (1 - alpha) * pDoc->InputImg[Cy][3 * Cx + 0] + alpha * pDoc->InputImg[Dy][3 * Dx + 0];
				E = (1 - alpha) * pDoc->InputImg[Ay][3 * Ax + 0] + alpha * pDoc->InputImg[By][3 * Bx + 0];
				pDoc->gResultImg[y][3 * x + 0] = (1 - beta) * E + beta * F;

				F = (1 - alpha) * pDoc->InputImg[Cy][3 * Cx + 1] + alpha * pDoc->InputImg[Dy][3 * Dx + 1];
				E = (1 - alpha) * pDoc->InputImg[Ay][3 * Ax + 1] + alpha * pDoc->InputImg[By][3 * Bx + 1];
				pDoc->gResultImg[y][3 * x + 1] = (1 - beta) * E + beta * F;

				F = (1 - alpha) * pDoc->InputImg[Cy][3 * Cx + 2] + alpha * pDoc->InputImg[Dy][3 * Dx + 2];
				E = (1 - alpha) * pDoc->InputImg[Ay][3 * Ax + 2] + alpha * pDoc->InputImg[By][3 * Bx + 2];
				pDoc->gResultImg[y][3 * x + 2] = (1 - beta) * E + beta * F;
			}
				
		}
	Invalidate();
}


void CImageProc20191362View::OnGeometryZoomoutSubsampling()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	int xscale = 3;
	int yscale = 2;
	int x, y;

	if (pDoc->gResultImg != NULL) // 할당삭제, 새로 생성 
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;

	//메모리 할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		//inputImg[] : unsigned char 포인터 // malloc(imageWidth * depth) 포인터의 값
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//역방향사상
	for (y = 0; y < pDoc->gImageHeight; y++)
		for (x = 0; x < pDoc->gImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->gResultImg[y][x] = pDoc->InputImg[y * yscale][x * xscale];

			else
			{
				pDoc->gResultImg[y][3 * x + 0] = pDoc->InputImg[y * yscale][3 * (x * xscale) + 0];
				pDoc->gResultImg[y][3 * x + 1] = pDoc->InputImg[y * yscale][3 * (x * xscale) + 1];
				pDoc->gResultImg[y][3 * x + 2] = pDoc->InputImg[y * yscale][3 * (x * xscale) + 2];

			}
		}
	Invalidate();

}

void CImageProc20191362View::OnGeometryZoomoutMeanSub()
{
	OnRegionSmoothing();
	CopyResultToInput();
	OnGeometryZoomoutSubsampling();
}

void CImageProc20191362View::OnGeometryAvgFiltering()
{
	CImageProc20191362Doc* pDoc = GetDocument();

	int xscale = 3;
	int yscale = 2;
	int x, y, j, i;
	int sum, rsum, gsum, bsum;
	int src_x, src_y;

	if (pDoc->gResultImg != NULL) // 할당삭제, 새로 생성 
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	pDoc->gImageWidth = pDoc->ImageWidth / xscale;
	pDoc->gImageHeight = pDoc->ImageHeight / yscale;

	//메모리 할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		//inputImg[] : unsigned char 포인터 // malloc(imageWidth * depth) 포인터의 값
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	//정방향사상
	for (y = 0; y < pDoc->ImageHeight; y+=yscale)
		for (x = 0; x < pDoc->ImageWidth; x += xscale)
		{
			if (pDoc->depth == 1) {
				sum = 0;
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++)
					{
						src_x = x + i;
						src_y = y + j;

						sum += pDoc->InputImg[src_y][src_x];
					}
				pDoc->gResultImg[y / yscale][x / xscale] = sum / (yscale * xscale);
			}
			else
			{
				rsum = 0; gsum = 0; bsum;
				for (j = 0; j < yscale; j++)
					for (i = 0; i < xscale; i++)
					{
						src_x = x + i;
						src_y = y + i;

						rsum += pDoc->InputImg[src_y][3 * src_x + 0];
						gsum += pDoc->InputImg[src_y][3 * src_x + 1];
						bsum += pDoc->InputImg[src_y][3 * src_x + 2];
					}
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 0] = rsum / (yscale * xscale);
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 1] = gsum / (yscale * xscale);
				pDoc->gResultImg[y / yscale][3 * (x / xscale) + 2] = bsum / (yscale * xscale);
			}
		}
	Invalidate();
}

#define PI 3.1416926521

#include "CAngleDlg.h"
void CImageProc20191362View::OnGeometryRotation()
{
	CImageProc20191362Doc* pDoc = GetDocument();
	CAngleDlg dlg;
	
	int angle = -45;	// degree
	float radian;
	int Hy;
	int Cx, Cy;		// 영상의 가운데 좌표값
	int xdiff, ydiff;
	int x, y;
	int x_source, y_source;

	dlg.m_iAngle = angle;
	if (dlg.DoModal() == IDCANCEL)		return;
	angle = dlg.m_iAngle;

	radian = PI / 180 * angle;

	// y의 마지막 좌표값		(좌표랑 관련된 파라미터)
	Hy = pDoc->ImageHeight - 1;
	// 중심점
	Cx = pDoc->ImageWidth / 2;
	Cy = pDoc->ImageHeight / 2;

	if (pDoc->gResultImg != NULL)
	{
		for (int i = 0; i < pDoc->gImageHeight; i++)
			free(pDoc->gResultImg[i]);
		free(pDoc->gResultImg);
	}

	
	// 이미지 가로세로 크기구하기		fabs : 크기 음수되는 거를 막음
	pDoc->gImageWidth = pDoc->ImageWidth * fabs(cos(PI/2-radian)) + pDoc->ImageWidth * fabs(cos(radian));		// 90도
	pDoc->gImageHeight = pDoc->ImageHeight * fabs(cos(radian)) + pDoc->ImageWidth*fabs(cos(PI/2 - radian));

	//메모리 할당
	pDoc->gResultImg = (unsigned char**)malloc(pDoc->gImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < pDoc->gImageHeight; i++)
	{
		//inputImg[] : unsigned char 포인터 // malloc(imageWidth * depth) 포인터의 값
		pDoc->gResultImg[i] = (unsigned char*)malloc(pDoc->gImageWidth * pDoc->depth);
	}

	xdiff = (pDoc->gImageWidth - pDoc->ImageWidth) / 2;
	ydiff = (pDoc->gImageHeight - pDoc->ImageHeight) / 2;

	for(y=-ydiff;y<pDoc->gImageHeight-ydiff; y++)
		for (x = -xdiff; x < pDoc->gImageWidth - xdiff; x++)
		{
			x_source = (Hy - y - Cx) * sin(radian) + (x - Cx) * cos(radian) + Cx;
			y_source = Hy - ((Hy - y - Cy) * cos(radian) - (x - Cx) * sin(radian) + Cy);
			if (pDoc->depth == 1)
			{
				if (x_source<0 || x_source>pDoc->ImageWidth - 1 ||
					y_source <0 || y_source>pDoc->ImageHeight - 1)	//-1 : 크면 가져올 영역을 넘어선거임
					pDoc->gResultImg[y + ydiff][x + xdiff] = 0;		// 검은색
				else
					pDoc->gResultImg[y + ydiff][x + xdiff] = pDoc->InputImg[y_source][x_source];
			}
			else
			{
				if (x_source<0 || x_source>pDoc->ImageWidth - 1 || y_source<0 || y_source>pDoc->ImageHeight - 1) {
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = 255;
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = 255;
				}
				else {
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 0] = pDoc->InputImg[y_source][3 * x_source + 0];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 1] = pDoc->InputImg[y_source][3 * x_source + 1];
					pDoc->gResultImg[y + ydiff][3 * (x + xdiff) + 2] = pDoc->InputImg[y_source][3 * x_source + 2];
				}
			}
		}
	Invalidate();
}


void CImageProc20191362View::OnGeometryHolizantalFlip()
{
	CImageProc20191362Doc* pDoc = GetDocument();
	int x, y;

	for(y=0; y<pDoc->ImageHeight;y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if(pDoc->depth == 1)
				pDoc->resultImg[y][x] = pDoc->InputImg[y][pDoc->ImageWidth-1-x];
			else
			{
				pDoc->resultImg[y][3 * x + 0] = pDoc->InputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 0];
				pDoc->resultImg[y][3 * x + 1] = pDoc->InputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 1];
				pDoc->resultImg[y][3 * x + 2] = pDoc->InputImg[y][3 * (pDoc->ImageWidth - 1 - x) + 2];
			}
		}
	Invalidate();
}


void CImageProc20191362View::OnGeometryVerticalClip()
{
	CImageProc20191362Doc* pDoc = GetDocument();
	int x, y;

	for (y = 0; y < pDoc->ImageHeight; y++)
		for (x = 0; x < pDoc->ImageWidth; x++)
		{
			if (pDoc->depth == 1)
				pDoc->resultImg[y][x] = pDoc->InputImg[pDoc->ImageHeight - 1 - y][x];
			else
			{
				pDoc->resultImg[y][3 * x + 0] = pDoc->InputImg[pDoc->ImageHeight - 1 - y][3 * x + 0];
				pDoc->resultImg[y][3 * x + 1] = pDoc->InputImg[pDoc->ImageHeight - 1 - y][3 * x + 1];
				pDoc->resultImg[y][3 * x + 2] = pDoc->InputImg[pDoc->ImageHeight - 1 - y][3 * x + 2];
			}
		}
	Invalidate();
}
