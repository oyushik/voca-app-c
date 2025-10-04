[English](./README.md) | [한국어](./README.ko.md) | [日本語](./README.ja.md)

---

# 단어 암기 프로그램 (Vocabulary Memorization App)

C언어로 작성된 콘솔 기반 단어 암기 애플리케이션입니다. 다양한 보기 모드와 인터랙티브한 메모리 카드 게임을 통해 효율적인 단어 학습을 지원합니다.

## ✨ 주요 기능

### 📚 단어 보기 모드

3가지 정렬 방식으로 단어를 확인할 수 있습니다:

- **RANDOM**: 무작위 순서로 단어 표시
- **ALPHABET**: 알파벳 순서로 정렬된 단어 표시
- **CUSTOM**: 파일에 입력된 순서대로 표시

각 모드에서 다음 3가지 옵션을 선택 가능:

- 전체 (단어 + 의미)
- 단어만
- 의미만

### 🎮 메모리 카드 게임

- **Know/Don't Know 선택**: 각 단어를 보고 아는지 모르는지 판단
- **복습 시스템**: "Don't Know"로 표시한 단어들을 자동으로 수집
- **재귀적 학습**: 틀린 단어만 다시 복습 가능 (반복 학습 지원)
- **3가지 모드**: Random, Alphabet, Custom 순서로 학습 가능

### 🌐 다국어 지원

- UTF-8 인코딩으로 한국어, 일본어, 중국어 등 다국어 단어 학습 가능
- Windows와 Linux에서 모두 정상 작동

## 🛠️ 빌드 및 실행

### Linux / macOS

```bash
# 빌드
gcc -o voca-app main.c vocaList.c memoryCard.c ui.c

# 실행
./voca-app
```

### Windows (Visual Studio)

1. `memorizing-voca-app.sln` 파일을 Visual Studio로 엽니다
2. **프로젝트 속성 설정** (중요):
   - 프로젝트 우클릭 → 속성
   - C/C++ → SDL 검사 → **아니요(/sdl-)** 로 설정
3. 빌드 및 실행 (F5 또는 Ctrl+F5)

### Windows (GCC/MinGW)

```bash
gcc -o voca-app.exe main.c vocaList.c memoryCard.c ui.c
voca-app.exe
```

## 📝 단어 파일 작성법

프로젝트 디렉토리의 `vocabulary.txt` 파일을 편집하여 단어를 추가/수정할 수 있습니다.

**파일 형식:**

```
단어1 의미1
단어2 의미2 (여러 단어 가능)
단어3 의미3, 의미4
```

**예시:**

```
apple 사과
banana 바나나
cat 고양이
life 생활, 삶
computer 컴퓨터, 전산기
```

**주의사항:**

- 한 줄에 하나의 단어
- 첫 번째 공백 이전: 단어
- 첫 번째 공백 이후: 의미 (공백 포함 가능)
- 최대 100개의 단어 지원

## 🎯 사용 방법

### 메인 메뉴

프로그램 실행 시 다음과 같은 메뉴가 표시됩니다:

```
---[RANDOM]---
1. Whole          (무작위: 전체)
2. Voca Only      (무작위: 단어만)
3. Meaning Only   (무작위: 의미만)

---[ALPHABET]---
4. Whole          (알파벳순: 전체)
5. Voca Only      (알파벳순: 단어만)
6. Meaning Only   (알파벳순: 의미만)

---[CUSTOM]---
7. Whole          (파일순서: 전체)
8. Voca Only      (파일순서: 단어만)
9. Meaning Only   (파일순서: 의미만)

100. Memory Card game [RANDOM]      (메모리 카드 게임: 무작위)
101. Memory Card game [ALPHABET]    (메모리 카드 게임: 알파벳순)
102. Memory Card game [CUSTOM]      (메모리 카드 게임: 파일순서)

0. EXIT
```

### 메모리 카드 게임 플레이

1. 메뉴에서 100~102 중 하나를 선택
2. 단어가 화면에 표시됨
3. 아는 단어면 `1`, 모르는 단어면 `2` 입력
4. 의미가 표시됨
5. 모든 단어를 확인한 후, "Don't Know"로 표시한 단어들을 다시 복습할지 선택 가능
6. 복습 후에도 틀린 단어만 다시 복습 가능 (반복 학습)

## 📂 프로젝트 구조

```
voca-app-c/
├── main.c              # 프로그램 진입점, UTF-8 설정
├── vocaList.c/h        # 단어 리스트 관리 (파일 파싱, 정렬, 셔플)
├── memoryCard.c/h      # 메모리 카드 게임 로직
├── ui.c/h              # 사용자 인터페이스 (메뉴, 입력 처리)
├── vocabulary.txt      # 단어 데이터 파일
└── README.md           # 프로젝트 문서 (이 파일)
```

## 🔧 기술 스택

- **언어**: C (C99 이상)
- **자료구조**: 이중 연결 리스트 (Doubly Linked List)
- **알고리즘**: Fisher-Yates 셔플, Quick Sort
- **플랫폼**: Windows, Linux, macOS (크로스 플랫폼)

## 💡 핵심 알고리즘

### Fisher-Yates 셔플

무작위 모드에서 단어를 섞을 때 사용하는 표준 셔플 알고리즘으로, 공정한 무작위 배치를 보장합니다.

### 간격 반복 학습 (Spaced Repetition)

"Don't Know" 단어만 선별하여 반복 학습하는 시스템으로, 효율적인 암기를 지원합니다.

## 🐛 문제 해결

### Visual Studio에서 빌드 오류

- SDL 검사를 **아니요(/sdl-)** 로 설정했는지 확인
- UTF-8 인코딩 관련 경고는 무시 가능

### Linux에서 한글이 깨짐

```bash
# 터미널 인코딩을 UTF-8로 설정
export LANG=ko_KR.UTF-8
```

### 단어가 100개 이상일 때

`vocaList.c`의 `initList()` 함수에서 배열 크기를 수정:

```c
LinkedList* nodes[100];  // 원하는 크기로 변경
```

## 📄 라이선스

이 프로젝트는 교육 목적으로 작성되었습니다.

## 👨‍💻 개발자

프로젝트에 대한 문의사항이나 개선 제안은 GitHub Issues를 통해 남겨주세요.
