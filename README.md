[English](./README.md) | [한국어](./README.ko.md) | [日本語](./README.ja.md)

---

# Vocabulary Memorization App

A console-based vocabulary memorization application written in C. It supports efficient word learning through various viewing modes and an interactive memory card game.

## ✨ Key Features

### 📚 Word Viewing Modes

You can view words in 3 different sorting orders:

- **RANDOM**: Displays words in random order.
- **ALPHABET**: Displays words sorted alphabetically.
- **CUSTOM**: Displays words in the order they appear in the file.

In each mode, you can choose one of the following 3 options:

- Whole (Word + Meaning)
- Word Only
- Meaning Only

### 🎮 Memory Card Game

- **Know/Don't Know Selection**: Judge whether you know each word.
- **Review System**: Automatically collects words marked as "Don't Know".
- **Recursive Learning**: Allows you to review only the words you got wrong (supports repetitive learning).
- **3 Modes**: Learning is possible in Random, Alphabet, and Custom order.

### 🌐 Multilingual Support

- Supports learning words in multiple languages such as Korean, Japanese, and Chinese with UTF-8 encoding.
- Works correctly on both Windows and Linux.

## 🛠️ Build and Run

### Linux / macOS

```bash
# Build
gcc -o voca-app main.c vocaList.c memoryCard.c ui.c

# Run
./voca-app
```

### Windows (Visual Studio)

1.  Open the `memorizing-voca-app.sln` file with Visual Studio.
2.  **Set Project Properties** (Important):
    - Right-click on the project → Properties
    - C/C++ → SDL checks → Set to **No (/sdl-)**
3.  Build and Run (F5 or Ctrl+F5)

### Windows (GCC/MinGW)

```bash
gcc -o voca-app.exe main.c vocaList.c memoryCard.c ui.c
voca-app.exe
```

## 📝 How to Write the Vocabulary File

You can add/edit words by editing the `vocabulary.txt` file in the project directory.

**File Format:**

```
word1 meaning1
word2 meaning2 (can be multiple words)
word3 meaning3, meaning4
```

**Example:**

```
apple 사과
banana 바나나
cat 고양이
life 생활, 삶
computer 컴퓨터, 전산기
```

**Notes:**

- One word per line.
- Before the first space: the word.
- After the first space: the meaning (can include spaces).
- Supports a maximum of 100 words.

## 🎯 How to Use

### Main Menu

When you run the program, the following menu will be displayed:

```
---[RANDOM]---
1. Whole          (Random: All)
2. Voca Only      (Random: Word only)
3. Meaning Only   (Random: Meaning only)

---[ALPHABET]---
4. Whole          (Alphabetical: All)
5. Voca Only      (Alphabetical: Word only)
6. Meaning Only   (Alphabetical: Meaning only)

---[CUSTOM]---
7. Whole          (File order: All)
8. Voca Only      (File order: Word only)
9. Meaning Only   (File order: Meaning only)

100. Memory Card game [RANDOM]
101. Memory Card game [ALPHABET]
102. Memory Card game [CUSTOM]

0. EXIT
```

### Playing the Memory Card Game

1.  Select one of 100-102 from the menu.
2.  A word will be displayed on the screen.
3.  Enter `1` if you know the word, `2` if you don't.
4.  The meaning will be displayed.
5.  After reviewing all words, you can choose to review the words marked as "Don't Know" again.
6.  Even after review, you can re-review only the words you got wrong (repetitive learning).

## 📂 Project Structure

```
voca-app-c/
├── main.c              # Program entry point, UTF-8 settings
├── vocaList.c/h        # Vocabulary list management (file parsing, sorting, shuffling)
├── memoryCard.c/h      # Memory card game logic
├── ui.c/h              # User interface (menu, input handling)
├── vocabulary.txt      # Vocabulary data file
└── README.md           # Project documentation (this file)
```

## 🔧 Tech Stack

- **Language**: C (C99 or later)
- **Data Structure**: Doubly Linked List
- **Algorithms**: Fisher-Yates Shuffle, Quick Sort
- **Platform**: Windows, Linux, macOS (Cross-platform)

## 💡 Core Algorithms

### Fisher-Yates Shuffle

A standard shuffle algorithm used to mix words in random mode, ensuring a fair random distribution.

### Spaced Repetition

A system that supports efficient memorization by selecting and repeatedly reviewing only the "Don't Know" words.

## 🐛 Troubleshooting

### Build errors in Visual Studio

- Ensure SDL checks are set to **No (/sdl-)**.
- Warnings related to UTF-8 encoding can be ignored.

### Garbled Korean characters on Linux

```bash
# Set terminal encoding to UTF-8
export LANG=ko_KR.UTF-8
```

### More than 100 words

Modify the array size in the `initList()` function of `vocaList.c`:

```c
LinkedList* nodes[100];  // Change to the desired size
```

## 📄 License

This project was created for educational purposes.

## 👨‍💻 Developer

For questions or suggestions about the project, please leave them via GitHub Issues.
