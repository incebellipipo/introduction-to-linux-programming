# Introduction to Linux Programming

This is the lecture notes and the sample code of the [introduction to linux programming workshop](https://web.archive.org/web/20200923065040/https://kamp.linux.org.tr/2020/kis/kurslar/linux-sistem-programlamaya-giris/) conducted at Anadolu University in January 2020. The code uses both the POSIX API and the System V API.

Every chapter keeps its notes next to its code, in the `src` folder of the chapter. The source code is also available on [GitHub](https://github.com/incebellipipo/introduction-to-linux-programming).

## Contents

0. [Introduction](00-introduction/readme.md): arguments, errno, standard descriptors, memory allocation
1. [Development Environment](01-development-environment/readme.md): GCC, Make, CMake, GDB, Vim, man pages
   - [Debugging with GDB](01-development-environment/debugging.md)
2. [File Operations](02-file-operations/readme.md): descriptors, streams, metadata, permissions
3. [Sockets](03-sockets/readme.md): TCP, UDP and UNIX domain sockets
4. [Process Management](04-process-management/readme.md): fork, exec, pipes, signals
5. [Multithreading](05-multithreading/readme.md): threads and mutex locks
6. [Inter Process Communication](06-inter-process-communication/readme.md): shared memory, message queues, semaphores

## Good Resources

- [Unix Lecture Notes - Stewart Weiss, Associate Professor](http://www.compsci.hunter.cuny.edu/~sweiss/course_materials/unix_lecture_notes.php)
