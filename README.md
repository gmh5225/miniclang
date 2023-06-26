# MiniClang: A small C language front-end for LLVM

This is a personal toy project created for the following purposes:
1. Learn about compiler front-end construction;
2. Train my coding skill with modern C++.

Currently, I am following [chibicc](https://github.com/rui314/chibicc) which constructs a C11 compiler step by step with every commit clean and bug-free (I will also try but no guarantees ~_~), except that:
1. I use C++ out of personal preference;
2. I target at the LLVM IR instead of asm code to leverage the great LLVM toolchains (that's why I call it miniclang).

I also refer to LLVM/Clang docs for better architecture and API design.