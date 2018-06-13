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

This repository is a simple Microsoft Foundaton Classes (MFC) application to experiment with mixing in non-MFC technologies.

The initial application source code was created using the New Project menu item of Visual Studio 2017 Community Edition and
choosing the Visual Studio style them. This theme provides the various dockable panes and windows that are part of the
Visual Studio IDE for at least a decade or two (Visual Studio 2005 had this technology).

If you are new to using MFC with Visual Studio 2017 you should know that it now seems to be considered an optional component
of Visual Studio. In Visual Studio 2005, when you installed the IDE the templates for MFC were automatically installed. However in
Visual Studio 2017 the MFC templates must be selected.

If you have already installed Visual Studio 2017 then you can modify the installation. See this StackOverflow answer which
provides a procedure for doing so. https://stackoverflow.com/questions/43074045/mfc-development-in-vs2017/47104815#47104815

## Using MFC

The MFC framework is a bit old, from the 1990s and Visual Studio 6.x, however it is still supported as of Visual Studio 2017
and it provides a nice desktop style framework. It is a fairly heavy technology and requires the MFC DLL which is included
in the Windows operating system installation materials. It also requires the Win32 API so MFC can not be used on a Windows RT
version of the Windows operating system which does not have the Win32 API nor the MFC DLL.

Since MFC is an older technology desktop versions of Windows going back to Windows NT have the MFC DLL. This means that an
MFC application can be run on Windows 7 and POS Ready 7 as well as Windows 8 and Windows 10 and Windows 10 IoT Enterprise.
However an MFC application can not be run on Windows 10 IoT Core or any other Windows RT type of Windows operating system.

The original MFC framework and technology was developed at a time when the C++98 Standard was being hammered out and
due to the discussions about the C++ Standard Library content, the MFC framework contains a number of classes that
duplicate some of the collections functionality of C++. So MFC contains a `CArray` class and a `CString` class and
the original MFC was designed to work with those MFC specific versions of the C++ Standard Library classes.

However these days the C++11/17 Standard Library is superior to the MFC classes which duplicate collections and from
what I have read, the C++ Standard Library should be used for collections, strings, etc.

### A Note on MFC strings

The Windows Win32 API uses a 16 bit UNICODE character set for almost every function whose interface requires a text
string of some kind. Originally MFC offered the `CString` class for dynamic strings, similar to the `std::string`
functionality of the C++ Standard Library.

The default for `std::string` is an 8 bit character set so instead of using `std::string` to replace the use of the
`CString` MFC class you should use `std::wstring` which is a wide character or 16 bit character string.

In order to use `std::wstring` with MFC functions that normally call for a text string, you will need to use the `c_str()`
method of `std::wstring`.

# Build and Test
TODO: Describe and show how to build your code and run the tests. 

# Contribute
TODO: Explain how other users and developers can contribute to make your code better. 

If you want to learn more about creating good readme files then refer the following [guidelines](https://www.visualstudio.com/en-us/docs/git/create-a-readme). You can also seek inspiration from the below readme files:
- [ASP.NET Core](https://github.com/aspnet/Home)
- [Visual Studio Code](https://github.com/Microsoft/vscode)
- [Chakra Core](https://github.com/Microsoft/ChakraCore)