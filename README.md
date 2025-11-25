# C-based Image Processing Practice (ImageProc_20191362)

이 프로젝트는 학부 과정에서 수행한 **C 언어 기반 기초 영상처리 실습 과제**입니다.  
BMP 이미지 파일을 직접 읽고, 픽셀 단위로 연산하며 다양한 영상 필터를 구현하는 것을 목표로 했습니다.

로우레벨 이미지 처리 과정을 직접 구현해보며  
**2차원 배열, 포인터, 메모리 구조, 픽셀 연산, 필터링 알고리즘의 원리**를 경험할 수 있었던 프로젝트입니다.

---

## 📌 Implemented Features (구현 기능)

과제에서 구현한 주요 영상처리 기능입니다:

### 🔹 기본 처리
- Grayscale 변환
- 이미지 반전(Negative)
- 밝기 조절(Brightness)
- 임계값 처리(Thresholding)

### 🔹 필터링 / 컨볼루션
- Averaging Filter (블러)
- Sharpening Filter
- Edge Detection (Sobel, Laplacian 등)

### 🔹 파일 입출력
- BMP 파일 헤더 분석
- Raw pixel 데이터 읽기/쓰기
- 24bit BMP 포맷 처리

---

## 🛠 Tech Stack
- **Language:** C  
- **Environment:** Windows, Code::Blocks / Visual Studio  
- **Focus:** 포인터, 메모리 구조, 파일 입출력, 이미지 처리 알고리즘 기초  

---

## 📚 What I Learned (배운 점)
- C 언어의 메모리 구조와 포인터 활용 능력 향상  
- 2D 배열 기반 픽셀 데이터 처리 경험  
- 영상 필터링 알고리즘(Convolution)의 원리 이해  
- 이미지 파일 포맷(BMP) 구조 분석  
- 로우레벨 구현 경험을 통해, 이후 딥러닝/CameraX/TensorFlow Lite 사용에도 기반 지식이 도움됨  

---
