# Hello World, Sharing is Caring

In the previous installment we looked at dynamic linking and how globals are linked statically. Here we shall look at dynamic linking. Some functions, such as the `printf` function are part of the standard library. Instead of copying the code for this functions that get used across many programs into each executable, these functions are laoded into memory by the OS and when we are program calling these funtions, references to them are linked and mapped at run time. In this installment we shall look at this process.

## Exercise, Make your own Print Shared Library

* Create shared library using our minimal hello world
* Create hello world calling it
* Have side channel for seeing whats going on
* https://opensource.com/article/22/5/dynamic-linking-modular-libraries-linux

## ??

* PLT and GOT?
* How do I see what shared libraries are currently resident in memory?
    * stdlib
    * libc
* crt1.0?

## Linker Script Clean up