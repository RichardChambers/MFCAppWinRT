# Introduction 
This is a Visual Studio 2017 Community Edition C++ solution using the MFC project templates.

The purpose of this solution is to investigate using newer technologies such as:
 - concurrency task threading functionality
 - C++/WinRT for functionality that is allowed to be used with desktop apps, that are not UWP packages
 - learning and using C++11/17 standard compliant, modern C++

See the stackoverflow question https://stackoverflow.com/questions/50669108/c11-threads-to-update-mfc-application-windows-sendmessage-postmessage-re

# Background Materials

There are a number of documents, text and video, containing materials on the subjects of MFC, Windows messages, C++11/17/20, and C++/WinRT.

Unfortunately the quality of the materials vary and quite a few seem to be a bit sparse on important details.

Following is a collection of materials from Microsoft, CppCon proceedings, and various bloggers which can provide quite a bit of the
necessary background to being able to understand threading in C++ and Windows and MFC and C++/WinRT.

It seems that there are a couple of different technologies which can be mixed together:
 - C++11/17/20 standards and Technical Specification for coroutines
 - Microsoft Visual Studio concurrency functionality and PPL in the header pplawait.h
 - Microsoft C++/WinRT, a C++ Language Projection of Windows Runtime or WinRT

## Videos

CppCon 2017: Scott Jones & Kenny Kerr “C++/WinRT and the Future of C++ on Windows” https://www.youtube.com/watch?v=7TdpWB_vRZM

# Getting Started
TODO: Guide users through getting your code up and running on their own system. In this section you can talk about:
1.	Installation process
2.	Software dependencies
3.	Latest releases
4.	API references

# Build and Test
TODO: Describe and show how to build your code and run the tests. 

# Contribute
TODO: Explain how other users and developers can contribute to make your code better. 

If you want to learn more about creating good readme files then refer the following [guidelines](https://www.visualstudio.com/en-us/docs/git/create-a-readme). You can also seek inspiration from the below readme files:
- [ASP.NET Core](https://github.com/aspnet/Home)
- [Visual Studio Code](https://github.com/Microsoft/vscode)
- [Chakra Core](https://github.com/Microsoft/ChakraCore)