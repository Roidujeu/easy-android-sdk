<p align="center">
	<img src="https://user-images.githubusercontent.com/30529572/72455010-fb38d400-37e7-11ea-9c1e-8cdeb5f5906e.png" />
	<h2 align="center"> Marvin  </h2>
	<h4 align="center"> Software to make setting up an android development environment much easier.<h4>
</p>

---

<!---
[![DOCS](https://img.shields.io/badge/Documentation-see%20docs-green?style=flat-square&logo=appveyor)](INSERT_LINK_FOR_DOCS_HERE) 
  [![UI ](https://img.shields.io/badge/User%20Interface-Link%20to%20UI-orange?style=flat-square&logo=appveyor)](INSERT_UI_LINK_HERE)
--->

## Functionalities
- [X]  Set up JDK.
- [X]  Set up the Android SDK.
- [X]  Set up Android SDK tools.
- [X]  Set up Android Virtual Device(s).
- [X]  Set up editors/IDEs for android development.

<br>


## Instructions to run

* Pre-requisites:
	-  POSIX(Unix-like) OS
	-  ncurses library
	-  bash
	-  cc/gcc
	-  terminal with 8-bit color
	-  curl
	-  unzip
	-  tar
	-  make(optional)

* Instruction for intallation(with make)  
cd into the the extracted directory  
```bash
$ make
$ make install
```  
to clean up files after installing, do  
```bash
$ make clean
```  
* Instruction for intallation(without make)  
 Extract the zip file and cd into extracted directory and  
```bash
$ cc marvin.c -o marvin -lncurses -lpanel
$ cp marvin /usr/bin 
```  

* Execute instructions  
```bash
$ marvin
```
<br>

* Uninstall instructions  
 with make, cd into the extracted directory and  
```bash
$ make uninstall
```  
 without make,  
```bash
$ rm -rf /usr/bin/marvin
```  
## Contributors

* [ Govind K ](https://github.com/Roidujeu/)
* [ Angad Sharma ](https://github.com/L04DB4L4NC3R/)

<br>
<br>

<p align="center">
	Made with :heart: by DSC VIT
</p>
