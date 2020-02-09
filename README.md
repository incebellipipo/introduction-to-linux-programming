# Introduction to Linux Programming
## Brief
This repository contains sample codes for [introduction to linux programming workshop](https://kamp.linux.org.tr/2020/kis/kurslar/linux-sistem-programlamaya-giris/) conducted at Anadolu University in January 2020. There were no lecture notes therefore there is no notes in this repository either. However, we are working on to write lecture notes with the collaboration of participants. In the mean time, If you need resources take a look at the [Good Resources](#good-resources) section. Source codes in repository uses both POSIX API and System V API.
#### Contributing
Any contribution is welcomed, as always. Most important part is how and what.

This repository needs:
- Translation. Any translation will be welcomed. You may create `README.<LANG_CODE>.md` file next to `README.md` file.
- More examples. Yes we need more examples
- Explanations for examples. I also didn't write what which code does. _Sorry folks™, didn't have time to write docs, classic._
- Resources. Good ones. If you think you know a good resource, let us know.

How you can contribute:
- Fork this repository _You'll need a github account. If you don't want to create it, clone it, change it, [mail it](mailto:emircem.gezer@gmail.com)._
- Do what you do.
- Test your code. or I'll. _You may make me test your code_.
- Use [conventional commits](https://www.conventionalcommits.org). _I'm really sensitive about it_.
- Create pull request as usual.

## Get It Working
Clone the repository to your home directory:
```sh
cd ~
git clone https://github.com/incebellipipo/introduction-to-linux-programming.git
```
Enter the downloaded folder and create a new build folder, then enter the folder you just created:
```sh
cd introduction-to-linux-programming/
mkdir build
cd build/
```
Generate a Makefile with `cmake`. Lastly, build and compile using `make` command:
```sh
cmake ..
make
```
Now the executable files, under the build folder, are ready to run.

## Topics
- [Introduction](00-introduction)
- [Develepment Environment](01-development-environment)
- [File Operations](02-file-operations)
- [Sockets](03-sockets)
- [Process Management](04-process-management)
- [Multithreading](05-multithreading)
- [Inter Process Communication](06-inter-process-communication)

## Examples
- [HTTP Server](07-projects/01-http-server-fantasy)
- [Music Maker](07-projects/02-musicmaker)
- [Reverse Shell](07-projects/03-reverse-shell)
- [Worst Shell](07-projects/04-worst-shell)
- [Makefile Example](07-projects/05-make-example)

## Good Resources
- [Unix Lecture Notes - Stewart Weiss, Associate Professor](http://www.compsci.hunter.cuny.edu/~sweiss/course_materials/unix_lecture_notes.php?fbclid=IwAR3q1vunyp8N2yxauL_pqTGllDxSKBOjl-DrjGcd3A0E5JEuc72djsJDMAw)
