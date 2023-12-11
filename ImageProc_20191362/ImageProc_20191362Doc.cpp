﻿// ImageProc_20191362Doc.cpp: CImageProc20191362Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProc_20191362.h"
#endif

#include "ImageProc_20191362Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define NUM_FRAMES 10
// CImageProc20191362Doc

IMPLEMENT_DYNCREATE(CImageProc20191362Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageProc20191362Doc, CDocument)
END_MESSAGE_MAP()


// CImageProc20191362Doc 생성/소멸

CImageProc20191362Doc::CImageProc20191362Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	InputImg = NULL;
	InputImg2 = NULL;
	resultImg = NULL;
	gResultImg = NULL;
	for (int i = 0; i < NUM_FRAMES; i++) morphedImg[i] = NULL;
}

CImageProc20191362Doc::~CImageProc20191362Doc()
{
	if (InputImg != NULL)
	{
		for (int i = 0; i < ImageHeight; i++)
			free(InputImg[i]);
		free(InputImg);
	}
	if (InputImg2 != NULL)
	{
		for (int i = 0; i < ImageHeight; i++)
			free(InputImg2[i]);
		free(InputImg2);
	}
	if (resultImg != NULL)
	{
		for (int i = 0; i < ImageHeight; i++)
			free(resultImg[i]);
		free(resultImg);
	}
	if (gResultImg != NULL)
	{
		for (int i = 0; i < gImageHeight; i++)
			free(gResultImg[i]);
		free(gResultImg);
	}
	for (int i = 0; i < NUM_FRAMES; i++) {
		if (morphedImg[i] != NULL) {
			int  j;
			for (j = 0; j < ImageHeight; j++)
				free(morphedImg[i][j]);
			free(morphedImg[i]);
		}
	}
}

BOOL CImageProc20191362Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}

// CImageProc20191362Doc serialization

void CImageProc20191362Doc::Serialize(CArchive& ar)	// 선택한 변수에 대한 정보(ar)가 CArchive로 넘어감
{
	if (ar.IsStoring() == TRUE)
	{

	}
	else
	{
		LoadImageFile(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProc20191362Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProc20191362Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProc20191362Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProc20191362Doc 진단

#ifdef _DEBUG
void CImageProc20191362Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProc20191362Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProc20191362Doc 명령


void CImageProc20191362Doc::LoadImageFile(CArchive& ar)
{
	int i, maxValue;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();// 파일에 대한 정보 읽어옴
	CString fname = fp->GetFilePath();	// 문자열 저장
	bool isbmp = false;	// 나머지 포맷은 false, bmp 포멧은 true

	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 || strcmp(strrchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strrchr(fname, '.'), ".pgm") == 0 || strcmp(strrchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);
		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &ImageWidth, &ImageHeight);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0)		depth = 1;
		else								depth = 3;
	}
	else if (strcmp(strrchr(fname, '.'), ".bmp") == 0 || strcmp(strrchr(fname, '.'), ".BMP") == 0)
	{
		//bitmap file header읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));
		if (bmfh.bfType != (WORD)('B' | ('M' << 8)))	return;

		//bitmap info header 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		ImageWidth = bih.biWidth;
		ImageHeight = bih.biHeight;
		depth = bih.biBitCount / 8;

		if (depth == 1)
		{	// palette 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		// 실제 데이터 읽어서 메모리 할당

		isbmp = true;

	}
	else if (strcmp(strrchr(fname, '.'), ".raw") == 0 || strcmp(strrchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256)
		{
			//에러났을때 표현
			AfxMessageBox("256*256 크기의 raw 파일만 사용가능합니다.");
			return;
		}
		ImageWidth = 256;
		ImageHeight = 256;
		depth = 1;
	}
	// 메모리 할당
	InputImg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	resultImg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < ImageHeight; i++)
	{
		InputImg[i] = (unsigned char*)malloc(ImageWidth * depth);
		resultImg[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	// 영상데이터 읽기
	if (!isbmp)
	{
		for (int i = 0; i < ImageHeight; i++)
			ar.Read(InputImg[i], ImageWidth * depth);
	}
	else
	{
		// 파일에서 읽어서 저장
		BYTE nu[4 * 3]; // 캐릭터에 unsigned char 의미
		int widthfile;
		widthfile = (ImageWidth * 8 + 32) / 32 * 4;		// 104
		for (int j = 0; j < ImageHeight; j++) // 세로
		{
			if (depth == 1)
				ar.Read(InputImg[ImageHeight - 1 - j], ImageWidth * depth);// -1-i : 메모리 영역 제거 + 제일마지막위치 거꾸로함.
			else
			{
				for (int i = 0; i < ImageWidth; i++)  // 가로
				{
					BYTE r, g, b;
					ar.Read(&b, 1); ar.Read(&g, 1); ar.Read(&r, 1);

					InputImg[ImageHeight - 1 - j][3 * i + 0] = r;
					InputImg[ImageHeight - 1 - j][3 * i + 1] = g;
					InputImg[ImageHeight - 1 - j][3 * i + 2] = b;
				}
			}
			if ((widthfile - ImageWidth != 0))	// 셀 픽셀
			{
				ar.Read(nu, (widthfile - ImageWidth) * depth);	// 칼라영상 = 9바이트 읽어서 버려야함
			}
			// 이대로 하면 이미지가 뒤집어주니 이미지 조정 필요
		}
	}

}


void CImageProc20191362Doc::LoadSecondImageFile(CArchive& ar) {
	int i, maxValue;
	char type[16], buf[256];
	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();	// CStrung - 문자열을 다루는 여러 기능 포함// fp-> 함수 이름 넘김
	bool isbmp = false;


	int imgw, imgh, imgd;

	// strcmp : 문자열 비교 / strrchr : 
	if (strcmp(strrchr(fname, '.'), ".ppm") == 0 || strcmp(strrchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strrchr(fname, '.'), ".pgm") == 0 || strcmp(strrchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);	// type 변수 15글자 읽음 마지막 하나는 null값
		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');	// #으로 시작하면 버림
		sscanf_s(buf, "%d %d", &imgw, &imgh);	// sscanf 문자열(버퍼)에 들어간걸 처리 (저장된 변수, 숫자로 바꿈, 숫자

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');	// #으로 시작하면 버림
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) imgd = 1;	// 흑백
		else                         imgd = 3;	// 컬러
	}

	else if (strcmp(strrchr(fname, '.'), ".bmp") == 0 || strcmp(strrchr(fname, '.'), ".BMP") == 0)
	{
		//bitmap file header읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));
		if (bmfh.bfType != (WORD)('B' | ('M' << 8)))
			return;

		//bitmap info header 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		imgw = bih.biWidth;
		imgh = bih.biHeight;
		imgd = bih.biBitCount / 8;


		if (imgd == 1)
		{
			// palette 존재함
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		isbmp = true;

	}



	else if (strcmp(strrchr(fname, '.'), ".raw") == 0 || strcmp(strrchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256x256 크기의 파일만 가능합니다.");
			return;
		}

		imgw = 256;
		imgh = 256;
		imgd = 1;
	}

	if (imgw != ImageWidth || imgh != ImageHeight || imgd != depth) {
		AfxMessageBox("동일한 크기의 화일만 읽어들일 수 있습니다.");
		return;
	}

	// 메모리 할당
	//메모리 얼로케이션?
	//inputImg : unsigned char 포인터의 포인터
	InputImg2 = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	for (int i = 0; i < ImageHeight; i++) {
		//inputImg[] : unsigned char 포인터 // malloc(imageWidth * depth) 포인터의 값
		InputImg2[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	// 영상데이터 읽기
	//for (int i = 0; i < imageHeight; i++) {
	//	ar.Read(inputImg2[i], imageWidth * depth);	//ar.Read는 아스키 코드 문자열을 읽음
	//}

		// 영상데이터 읽기
	if (!isbmp)
	{
		for (int i = 0; i < ImageHeight; i++)
			ar.Read(InputImg2[i], ImageWidth * depth);	//ar.Read는 아스키 코드 문자열을 읽음
	}

	else
	{
		//파일에서 읽어서 저장
		BYTE nu[4 * 3];
		int widthfile;
		widthfile = (ImageWidth * 8 + 32) / 32 * 4; // 4의 배수를 만들기 위해서 필요한 부분
		for (int j = 0; j < ImageHeight; j++)
		{
			if (depth == 1)
				ar.Read(InputImg2[ImageHeight - 1 - j], ImageWidth * depth); // 이 부분을 추가해야 사선이 사라짐   //ar.Read는 아스키 코드 문자열을 읽음

			else
			{
				for (int i = 0; i < ImageWidth; i++)
				{
					BYTE r, g, b;
					ar.Read(&b, 1);
					ar.Read(&g, 1);
					ar.Read(&r, 1);

					InputImg2[ImageHeight - 1 - j][3 * i + 0] = r;
					InputImg2[ImageHeight - 1 - j][3 * i + 1] = g;
					InputImg2[ImageHeight - 1 - j][3 * i + 2] = b;

				}
			}

			if ((widthfile - ImageHeight) != 0)
			{
				ar.Read(nu, (widthfile - ImageWidth) * depth);
			}
		}
	}
}