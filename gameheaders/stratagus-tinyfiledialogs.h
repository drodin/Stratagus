/*
 _________
/         \ tinyfiledialogs.c 
|tiny file| Unique code file of "tiny file dialogs" created [November 9, 2014]
| dialogs | Copyright (c) 2014 - 2016 Guillaume Vareille http://ysengrin.com
\____  ___/ http://tinyfiledialogs.sourceforge.net
     \|           	                     mailto:tinfyfiledialogs@ysengrin.com

            git://git.code.sf.net/p/tinyfiledialogs/code

 Please
	1) let me know
	- if you are including tiny file dialogs,
	  I'll be happy to add your link to the list of projects using it.
	- If you are using it on different hardware / OS / compiler.
	2) Be the first to leave a review on Sourceforge. Thanks.

tiny file dialogs (cross-platform C C++)
InputBox PasswordBox MessageBox ColorPicker
OpenFileDialog SaveFileDialog SelectFolderDialog
Native dialog library for WINDOWS MAC OSX GTK+ QT CONSOLE & more
v2.3.6 [April 16, 2016] zlib licence.

A single C file (add it to your C or C++ project) with 6 modal function calls:
- message box & question box
- input box & password box
- save file dialog
- open file dialog & multiple files
- select folder dialog
- color picker.

Complement to OpenGL GLFW GLUT GLUI VTK SDL Ogre3D Unity3D
or any GUI-less program, there is NO INIT & NO MAIN LOOP.
The dialogs can be forced into console mode.

On Windows:
- native code & some vbs create the graphic dialogs
- enhanced console mode can use dialog.exe from
  http://andrear.altervista.org/home/cdialog.php
- basic console input.

On Unix (command line call attempts):
- applescript
- zenity
- kdialog
- Xdialog
- python2 tkinter
- dialog (opens a console if needed)
- whiptail, gdialog, gxmessage
- basic console input.
The same executable can run across desktops & distributions.

tested with C & C++ compilers
on Visual Studio MinGW OSX LINUX FREEBSD ILLUMOS SOLARIS MINIX RASPBIAN
using Gnome Kde Enlightenment Mate Cinnamon Unity
Lxde Lxqt Xfce WindowMaker IceWm Cde Jds OpenBox
 
- License -

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software.  If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#ifndef TINYFILEDIALOGS_H
#define TINYFILEDIALOGS_H

/*
if tinydialogs.c is compiled with a C++ compiler
rather than with a C compiler, you need to comment out:
extern "C" {
and the corresponding closing bracket:
}
*/

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */


int tinyfd_messageBox (
  char const * const aTitle , /* "" */
  char const * const aMessage , /* "" may contain \n \t */
  char const * const aDialogType , /* "ok" "okcancel" "yesno" */
  char const * const aIconType , /* "info" "warning" "error" "question" */
  int const aDefaultButton ) ; /* 0 for cancel/no , 1 for ok/yes */
	/* returns 0 for cancel/no , 1 for ok/yes */

char const * tinyfd_inputBox (
	char const * const aTitle , /* "" */
	char const * const aMessage , /* "" may NOT contain \n \t on windows */
	char const * const aDefaultInput ) ;  /* "" , if NULL it's a passwordBox */
	/* returns NULL on cancel */

char const * tinyfd_saveFileDialog (
  char const * const aTitle , /* "" */
  char const * const aDefaultPathAndFile , /* "" */
  int const aNumOfFilterPatterns , /* 0 */
  char const * const * const aFilterPatterns , /* NULL | {"*.jpg","*.png"} */
  char const * const aSingleFilterDescription ) ; /* NULL | "text files" */
	/* returns NULL on cancel */

char const * tinyfd_openFileDialog (
  char const * const aTitle , /* "" */
  char const * const aDefaultPathAndFile , /* "" */
  int const aNumOfFilterPatterns , /* 0 */
  char const * const * const aFilterPatterns , /* NULL {"*.jpg","*.png"} */
  char const * const aSingleFilterDescription , /* NULL | "image files" */
  int const aAllowMultipleSelects ) ; /* 0 or 1 */
	/* in case of multiple files, the separator is | */
	/* returns NULL on cancel */

char const * tinyfd_selectFolderDialog (
	char const * const aTitle , /* "" */
  char const * const aDefaultPath ) ; /* "" */
	/* returns NULL on cancel */

char const * tinyfd_colorChooser(
	char const * const aTitle , /* "" */
	char const * const aDefaultHexRGB , /* NULL or "#FF0000" */
	unsigned char const aDefaultRGB[3] , /* { 0 , 255 , 255 } */
	unsigned char aoResultRGB[3] ) ; /* { 0 , 0 , 0 } */
	/* returns the hexcolor as a string "#FF0000" */
	/* aoResultRGB also contains the result */
	/* aDefaultRGB is used only if aDefaultHexRGB is NULL */
	/* aDefaultRGB and aoResultRGB can be the same array */
	/* returns NULL on cancel */

int tinyfd_forceConsole ;  /* 0 (default) or 1
can be modified at run time.
for unix & windows: 0 (graphic mode) or 1 (console mode).
0: try to use a graphic solution, if it fails then it uses console mode.
1: forces all dialogs into console mode even when the X server is present.
   it will use the package dialog or dialog.exe if installed.
on windows it only make sense for console applications */

/* #define TINYFD_WIN_CONSOLE_ONLY //*/
/* On windows, Define this if you don't want to include the code
creating the GUI dialogs.
Then you don't need link against Comdlg32.lib and Ole32.lib */


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif /* TINYFILEDIALOGS_H */


/*
- This is not for android nor ios.
- The code is pure C, perfectly compatible with C++.
- AVOID USING " AND ' IN TITLES AND MESSAGES.
- There's one file filter only, it may contain several patterns.
- If no filter description is provided,
  the list of patterns will become the description.
- char const * filterPatterns[3] = { "*.obj" , "*.stl" , "*.dxf" } ;
- On windows, inputbox and passwordbox are not as smooth as they should be:
  they open a console window for a few seconds.
- On visual studio:
        set Configuration Properties/General Character Set to Multi-Byte.
- On windows link against Comdlg32.lib and Ole32.lib
  This linking is not compulsary for console mode (see above).
- On unix: it tries command line calls, so no such need.
- On unix you need applescript, zenity, kdialog, Xdialog, python2/tkinter
  or dialog (will open a terminal if running without console);
- One of those is already included on most (if not all) desktops.
- In the absence of those it will use gdialog, gxmessage or whiptail
  with a textinputbox.
- If nothing is found, it switches to basic console input,
  it opens a console if needed.
- Use windows separators on windows and unix separators on unix.
- String memory is preallocated statically for all the returned values.
- File and path names are tested before return, they are valid.
- If you pass only a path instead of path + filename,
  make sure it ends with a separator.
- tinyfd_forceConsole=1; at run time, forces dialogs into console mode.
- On windows, console mode only make sense for console applications.
- Mutiple selects are not allowed in console mode.
- The package dialog must be installed to run in enhanced console mode.
  It is already installed on most unix systems.
- On osx, the package dialog can be installed via http://macports.org
- On windows, for enhanced console mode,
  dialog.exe should be copied somewhere on your executable path.
  It can be found at the bottom of the following page:
  http://andrear.altervista.org/home/cdialog.php
- If dialog is missing, it will switch to basic console input.

- Here is the Hello World (and a bit more):
    if a console is missing, it will use graphic dialogs
    if a graphical display is absent, it will use console dialogs
*/

/* hello.c
#include <stdio.h>
#include "tinyfiledialogs.h"
int main()
{
	char const * lThePassword;
	char const * lTheSaveFileName;
	char const * lTheOpenFileName;
	FILE * lIn;
	char lBuffer[1024];

  tinyfd_forceConsole = tinyfd_messageBox("Hello World",
    "force dialogs into console mode?\
    \n\t(it is better if dialog is installed)",
    "yesno", "question", 0);

  lThePassword =  tinyfd_inputBox(
    "a password box","your password will be revealed",NULL);

  lTheSaveFileName = tinyfd_saveFileDialog (
	"let us save this password",
    "passwordFile.txt",
    0,
    NULL,
    NULL );

#pragma warning(disable:4996) // silences warning about fopen
	lIn = fopen(lTheSaveFileName, "w");
#pragma warning(default:4996)
	if (!lIn)
	{
		tinyfd_messageBox(
			"Error",
			"Can not open this file in writting mode",
			"ok",
			"error",
			1 );
		return(1);
	}
	fputs(lThePassword, lIn);
	fclose(lIn);

    lTheOpenFileName = tinyfd_openFileDialog (
		"let us read this password back",
		"",
		0,
		NULL,
		NULL,
		0);

#pragma warning(disable:4996) // silences warning about fopen
	lIn = fopen(lTheOpenFileName, "r");
#pragma warning(default:4996)
	if (!lIn)
	{
		tinyfd_messageBox(
			"Error",
			"Can not open this file in reading mode",
			"ok",
			"error",
			1 );
		return(1);
	}
	fgets(lBuffer, sizeof(lBuffer), lIn);
	fclose(lIn);

  if ( *lBuffer )
    tinyfd_messageBox("your password is", lBuffer, "ok", "info", 1);
}

OSX :
$ gcc -o hello.app hello.c tinyfiledialogs.c
 
UNIX :
$ gcc -o hello hello.c tinyfiledialogs.c

MinGW :
> gcc -o hello.exe hello.c tinyfiledialogs.c -LC:/mingw/lib -lcomdlg32 -lole32
 
VisualStudio :
  Create a console application project,
	it links against Comdlg32.lib & Ole32.lib.
	Right click on your Project, select Properties.
	Configuration Properties/General Character Set to Multi-Byte.
*/

/*
 _________
/         \ tinyfiledialogs.c
|tiny file| Unique code file of "tiny file dialogs" created [November 9, 2014]
| dialogs | Copyright (c) 2014 - 2016 Guillaume Vareille http://ysengrin.com
\____  ___/ http://tinyfiledialogs.sourceforge.net
	 \|									 mailto:tinfyfiledialogs@ysengrin.com

			git://git.code.sf.net/p/tinyfiledialogs/code

 Please
	1) let me know
	- if you are including tiny file dialogs,
	  I'll be happy to add your link to the list of projects using it.
	- If you are using it on different hardware / OS / compiler.
	2) Be the first to leave a review on Sourceforge. Thanks.

tiny file dialogs (cross-platform C C++)
InputBox PasswordBox MessageBox ColorPicker
OpenFileDialog SaveFileDialog SelectFolderDialog
Native dialog library for WINDOWS MAC OSX GTK+ QT CONSOLE & more
v2.3.6 [April 16, 2016] zlib licence.

A single C file (add it to your C or C++ project) with 6 modal function calls:
- message box & question box
- input box & password box
- save file dialog
- open file dialog & multiple files
- select folder dialog
- color picker.

Complement to OpenGL GLFW GLUT GLUI VTK SDL Ogre3D Unity3D
or any GUI-less program, there is NO INIT & NO MAIN LOOP.
The dialogs can be forced into console mode.

On Windows:
- native code & some vbs create the graphic dialogs
- enhanced console mode can use dialog.exe from
  http://andrear.altervista.org/home/cdialog.php
- basic console input.

On Unix (command line call attempts):
- applescript
- zenity
- kdialog
- Xdialog
- python2 tkinter
- dialog (opens a console if needed)
- whiptail, gdialog, gxmessage
- basic console input.
The same executable can run across desktops & distributions.

tested with C & C++ compilers
on Visual Studio MinGW OSX LINUX FREEBSD ILLUMOS SOLARIS MINIX RASPBIAN
using Gnome Kde Enlightenment Mate Cinnamon Unity
Lxde Lxqt Xfce WindowMaker IceWm Cde Jds OpenBox

- License -

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software.  If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* #define TINYFD_WIN_CONSOLE_ONLY //*/

#ifdef _WIN32
 #ifndef _WIN32_WINNT
 #define _WIN32_WINNT 0x0500
 #endif
 #ifndef TINYFD_WIN_CONSOLE_ONLY
  #include <Windows.h>
  #include <Shlobj.h>
 #endif /* TINYFD_WIN_CONSOLE_ONLY */
 #include <sys/stat.h>
 #include <conio.h>
 #define SLASH "\\"
#else
 #include <limits.h>
 #include <unistd.h>
 #include <dirent.h> /* on old systems try <sys/dir.h> instead */
 #include <termios.h>
 #include <sys/utsname.h>
 #define SLASH "/"
#endif /* _WIN32 */

#define MAX_PATH_OR_CMD 1024 /* _MAX_PATH or MAX_PATH */
#define MAX_MULTIPLE 32

#pragma warning(disable:4996)
/* allows usage of strncpy, strcpy, strcat, sprintf, fopen */

static int gWarningDisplayed = 0 ;
static char gTitle[]= "missing software! (so we switch to basic console input)";
static char gMessageWin[] = "tiny file dialogs on Windows needs:\n\t\
a graphic display\nor\tdialog.exe (enhanced console mode)\
\nor\ta console for basic input" ;

static char gMessageUnix[] = "tiny file dialogs on UNIX needs:\n\tapplescript\
\nor\tzenity (version 3 for the color chooser)\nor\tkdialog\
\nor\tXdialog\nor\tpython 2 with tkinter\
\nor\tdialog (opens a console if needed)\
\nor\twhiptail, gdialog or gxmessage (really?)\
\nor\tit will open a console (if needed) for basic input (you had it comming!)";

static char * getPathWithoutFinalSlash(
	char * const aoDestination, /* make sure it is allocated, use _MAX_PATH */
	char const * const aSource) /* aoDestination and aSource can be the same */
{
	char const * lTmp ;
	if ( aSource )
	{
		lTmp = strrchr(aSource, '/');
		if (!lTmp)
		{
			lTmp = strrchr(aSource, '\\');
		}
		if (lTmp)
		{
			strncpy(aoDestination, aSource, lTmp - aSource);
			aoDestination[lTmp - aSource] = '\0';
		}
		else
		{
			* aoDestination = '\0';
		}
	}
	else
	{
		* aoDestination = '\0';
	}
	return aoDestination;
}


static char * getLastName(
	char * const aoDestination, /* make sure it is allocated */
	char const * const aSource)
{
	/* copy the last name after '/' or '\' */
	char const * lTmp ;
	if ( aSource )
	{
		lTmp = strrchr(aSource, '/');
		if (!lTmp)
		{
			lTmp = strrchr(aSource, '\\');
		}
		if (lTmp)
		{
			strcpy(aoDestination, lTmp + 1);
		}
		else
		{
			strcpy(aoDestination, aSource);
		}
	}
	else
	{
		* aoDestination = '\0';
	}
	return aoDestination;
}


static void ensureFinalSlash ( char * const aioString )
{
	if ( aioString && strlen ( aioString ) )
	{
		char * lastcar = aioString + strlen ( aioString ) - 1 ;
		if ( strncmp ( lastcar , SLASH , 1 ) )
		{
			strcat ( lastcar , SLASH ) ;
		}
	}
}


static void Hex2RGB( char const aHexRGB [ 8 ] ,
					 unsigned char aoResultRGB [ 3 ] )
{
	char lColorChannel [ 8 ] ;
	if ( aoResultRGB )
	{
		if ( aHexRGB )
		{
			strcpy(lColorChannel, aHexRGB ) ;
			aoResultRGB[2] = (unsigned char)strtoul(lColorChannel+5,NULL,16);
			lColorChannel[5] = '\0';
			aoResultRGB[1] = (unsigned char)strtoul(lColorChannel+3,NULL,16);
			lColorChannel[3] = '\0';
			aoResultRGB[0] = (unsigned char)strtoul(lColorChannel+1,NULL,16);
/* printf("%d %d %d\n", aoResultRGB[0], aoResultRGB[1], aoResultRGB[2]); //*/
		}
		else
		{
			aoResultRGB[0]=0;
			aoResultRGB[1]=0;
			aoResultRGB[2]=0;
		}
	}
}

static void RGB2Hex( unsigned char const aRGB [ 3 ] ,
					 char aoResultHexRGB [ 8 ] )
{
	if ( aoResultHexRGB )
	{
		if ( aRGB )
		{
			sprintf(aoResultHexRGB,"#%02hhx%02hhx%02hhx",
						aRGB[0],aRGB[1],aRGB[2]);
			/* printf("aoResultHexRGB %s\n", aoResultHexRGB); //*/
		}
		else
		{
			aoResultHexRGB[0]=0;
			aoResultHexRGB[1]=0;
			aoResultHexRGB[2]=0;
		}
	}
}


static void replaceSubStr ( char const * const aSource ,
							char const * const aOldSubStr ,
							char const * const aNewSubStr ,
							char * const aoDestination )
{
	char const * pOccurence ;
	char const * p ;
	char const * lNewSubStr = "" ;
	int lOldSubLen = strlen ( aOldSubStr ) ;

	if ( ! aSource )
	{
		* aoDestination = '\0' ;
		return ;
	}
	if ( ! aOldSubStr )
	{
		strcpy ( aoDestination , aSource ) ;
		return ;
	}
	if ( aNewSubStr )
	{
		lNewSubStr = aNewSubStr ;
	}
	p = aSource ;
	* aoDestination = '\0' ;
	while ( ( pOccurence = strstr ( p , aOldSubStr ) ) != NULL )
	{
		strncat ( aoDestination , p , pOccurence - p ) ;
		strcat ( aoDestination , lNewSubStr ) ;
		p = pOccurence + lOldSubLen ;
	}
	strcat ( aoDestination , p ) ;
}


static int replaceChr ( char * const aString ,
						char const aOldChr ,
						char const aNewChr )
{
	char * p ;
	int lRes = 0 ;

	if ( ! aString )
	{
		return 0 ;
	}

	if ( aOldChr == aNewChr )
	{
		return 0 ;
	}

	p = aString ;
	while ( (p = strchr ( p , aOldChr )) )
	{
		* p = aNewChr ;
		p ++ ;
		lRes = 1 ;
	}
	return lRes ;
}


static int filenameValid( char const * const aFileNameWithoutPath )
{
	if ( ! aFileNameWithoutPath
	  || ! strlen(aFileNameWithoutPath)
	  || strpbrk(aFileNameWithoutPath , "\\/:*?\"<>|") )
	{
		return 0 ;
	}
	return 1 ;
}


static int fileExists( char const * const aFilePathAndName )
{
	FILE * lIn ;
	if ( ! aFilePathAndName || ! strlen(aFilePathAndName) )
	{
		return 0 ;
	}
	lIn = fopen( aFilePathAndName , "r" ) ;
	if ( ! lIn )
	{

		return 0 ;
	}
	fclose ( lIn ) ;
	return 1 ;
}


/* source and destination can be the same or ovelap*/
static char const * ensureFilesExist( char * const aDestination ,
									  char const * const aSourcePathsAndNames)
{
	char * lDestination = aDestination ;
	char const * p ;
	char const * p2 ;
	int lLen ;

	if ( ! aSourcePathsAndNames )
	{
		return NULL ;
	}
	lLen = strlen( aSourcePathsAndNames ) ;
	if ( ! lLen )
	{
		return NULL ;
	}

	p = aSourcePathsAndNames ;
	while ( (p2 = strchr(p, '|')) != NULL )
	{
		lLen = p2-p ;
		memmove(lDestination,p,lLen);
		lDestination[lLen] = '\0';
		if ( fileExists ( lDestination ) )
		{
			lDestination += lLen ;
			* lDestination = '|';
			lDestination ++ ;
		}
		p = p2 + 1 ;
	}
	if ( fileExists ( p ) )
	{
		lLen = strlen(p) ;
		memmove(lDestination,p,lLen);
		lDestination[lLen] = '\0';
	}
	else
	{
		* (lDestination-1) = '\0';
	}
	return aDestination ;
}

#ifdef _WIN32

static int dirExists ( char const * const aDirPath )
{
	struct stat lInfo;
	if ( ! aDirPath || ! strlen ( aDirPath ) )
		return 0 ;
	if ( stat ( aDirPath , & lInfo ) != 0 )
		return 0 ;
	else if ( lInfo.st_mode & S_IFDIR )
		return 1 ;
	else
		return 0 ;
}

static int detectPresence ( char const * const aExecutable )
{
    return 0;
}

#ifndef TINYFD_WIN_CONSOLE_ONLY

static int messageBoxWinGui (
	char const * const aTitle , /* NULL or "" */
	char const * const aMessage , /* NULL or ""  may contain \n and \t */
	char const * const aDialogType , /* "ok" "okcancel" "yesno" */
	char const * const aIconType , /* "info" "warning" "error" "question" */
	int const aDefaultButton ) /* 0 for cancel/no , 1 for ok/yes */
{
	int lBoxReturnValue;
	UINT aCode ;

	if ( aIconType && ! strcmp( "warning" , aIconType ) )
	{
		aCode = MB_ICONWARNING ;
	}
	else if ( aIconType && ! strcmp("error", aIconType))
	{
		aCode = MB_ICONERROR ;
	}
	else if ( aIconType && ! strcmp("question", aIconType))
	{
		aCode = MB_ICONQUESTION ;
	}
	else
	{
		aCode = MB_ICONINFORMATION ;
	}

	if ( aDialogType && ! strcmp( "okcancel" , aDialogType ) )
	{
		aCode += MB_OKCANCEL ;
		if ( ! aDefaultButton )
		{
			aCode += MB_DEFBUTTON2 ;
		}
	}
	else if ( aDialogType && ! strcmp( "yesno" , aDialogType ) )
	{
		aCode += MB_YESNO ;
		if ( ! aDefaultButton )
		{
			aCode += MB_DEFBUTTON2 ;
		}
	}
	else
	{
		aCode += MB_OK ;
	}

	lBoxReturnValue = MessageBox(NULL, aMessage, aTitle, aCode);
	if ( ( ( aDialogType
		  && strcmp("okcancel", aDialogType)
		  && strcmp("yesno", aDialogType) ) )
		|| (lBoxReturnValue == IDOK)
		|| (lBoxReturnValue == IDYES) )
	{
		return 1 ;
	}
	else
	{
		return 0 ;
	}
}


static char const * inputBoxWinGui(
	char * const aoBuff ,
	char const * const aTitle , /* NULL or "" */
	char const * const aMessage , /* NULL or "" may NOT contain \n nor \t */
	char const * const aDefaultInput ) /* "" , if NULL it's a passwordBox */
{
	char lDialogString[4*MAX_PATH_OR_CMD];
	FILE * lIn;
	int lResult;

	if (aDefaultInput)
	{
		sprintf(lDialogString, "%s\\AppData\\Local\\Temp\\tinyfd.vbs",
			getenv("USERPROFILE"));
	}
	else
	{
		sprintf(lDialogString, "%s\\AppData\\Local\\Temp\\tinyfd.hta",
			getenv("USERPROFILE"));
	}
	lIn = fopen(lDialogString, "w");
	if (!lIn)
	{
		return NULL;
	}

	if ( aDefaultInput )
	{
		strcpy(lDialogString, "Dim result:result=InputBox(\"");
		if (aMessage && strlen(aMessage))
		{
			strcat(lDialogString, aMessage);
		}
		strcat(lDialogString, "\",\"");
		if (aTitle && strlen(aTitle))
		{

			strcat(lDialogString, aTitle);
		}
		strcat(lDialogString, "\",\"");
		if (aDefaultInput && strlen(aDefaultInput))
		{
			strcat(lDialogString, aDefaultInput);
		}
		strcat(lDialogString, "\"):If IsEmpty(result) then:WScript.Echo 0");
		strcat(lDialogString, ":Else: WScript.Echo \"1\" & result : End If");
	}
	else
	{
		sprintf(lDialogString, "\n\
<html>\n\
<head>\n\
<title>%s</title>\n\
<HTA:APPLICATION\n\
ID = 'tinyfdHTA'\n\
APPLICATIONNAME = 'tinyfd_inputBox'\n\
BORDER = 'thin'\n\
SCROLL = 'no'\n\
SINGLEINSTANCE = 'yes'\n\
WINDOWSTATE = 'hidden'\n\
>\n\
\n\
<script language = 'VBScript'>\n\
\n\
'Dim arrCommands\n\
result = 0\n\
\n\
Sub Window_onLoad\n\
intWidth = 375\n\
intHeight = 165\n\
Me.ResizeTo intWidth, intHeight\n\
Me.MoveTo((Screen.Width/2)-(intWidth/2)),((Screen.Height/2)-(intHeight/2))\n\
txt_input.Focus\n\
' if the args are written each in ' ' \n\
'arrCommands = Split(tinyfdHTA.commandLine, chr(34)) \n\
'Msgbox arrCommands(0)\n\
'For i = 1 to (Ubound(arrCommands) - 1) Step 2\n\
'    Msgbox arrCommands(i)\n\
'Next\n\
End Sub\n\
\n\
Sub Window_onUnload\n\
Set objFSO = CreateObject(\"Scripting.FileSystemObject\")\n\
Set oShell = CreateObject(\"WScript.Shell\")\n\
strHomeFolder = oShell.ExpandEnvironmentStrings(\"%%USERPROFILE%%\")\n\
Set objFile = objFSO.CreateTextFile(strHomeFolder & \"\\AppData\\Local\\Temp\\tinyfd.txt\",True)\n\
If result = 1 Then\n\
objFile.Write 1 & txt_input.Value\n\
Else\n\
objFile.Write 0\n\
End If\n\
objFile.Close\n\
End Sub\n\
\n\
Sub Run_ProgramOK\n\
result = 1\n\
window.Close\n\
End Sub\n\
\n\
Sub Run_ProgramCancel\n\
window.Close\n\
End Sub\n\
\n\
Sub Default_Buttons\n\
If Window.Event.KeyCode = 13 Then\n\
btn_OK.Click\n\
ElseIf Window.Event.KeyCode = 27 Then\n\
btn_Cancel.Click\n\
End If\n\
End Sub\n\
\n\
</script>\n\
</head>\n\
<body style = 'background-color:#EEEEEE' onkeypress = 'vbs:Default_Buttons' align = 'top'>\n\
<table width = '100%%' height = '80%%' align = 'center' border = '0'>\n\
<tr border = '0'>\n\
<td align = 'left' style = 'font-family: arial; font-size: 11px;'>\n\
%s\n\
</td>\n\
<td align = 'right' style = 'margin-top: 0em;'>\n\
<table  align = 'right' style = 'margin-right: 0em;'>\n\
<tr align = 'right' 'margin-top: 5em;'>\n\
<input type = 'button' value = 'OK' name = 'btn_OK' onClick = 'vbs:Run_ProgramOK' style = 'font-size: 11px; width: 5em; margin-top: 2em;'><br>\n\
<input type = 'button' value = 'Cancel' name = 'btn_Cancel' onClick = 'vbs:Run_ProgramCancel' style = 'font-size: 11px; width: 5em;'><br><br>\n\
</tr>\n\
</table>\n\
</td>\n\
</tr>\n\
</table>\n\
<table width = '100%%' height = '100%%' align = 'center' border = '0'>\n\
<tr>\n\
<td align = 'left' style = 'font-family: arial; font-size: 16px; font-weight: bold;'>\n\
<input type = 'password' size = '61' id = 'txt_input'\n\
name = 'txt_input' style = 'font-size: 11px;' value = '' ><BR>\n\
</td>\n\
</tr>\n\
</table>\n\
</body>\n\
</html>\n\
"		, aTitle ? aTitle : "", aMessage ? aMessage : "") ;
	}
	fputs(lDialogString, lIn);
	fclose(lIn);

	if ( GetConsoleWindow() )
	{
		strcpy(lDialogString, "");
	}
	else
	{
		strcpy(lDialogString, "powershell -WindowStyle Hidden -Command \"");
	}
	if (aDefaultInput)
	{
		strcat(lDialogString,
			"cscript.exe %USERPROFILE%\\AppData\\Local\\Temp\\tinyfd.vbs");
	}
	else
	{
		strcat(lDialogString,
			"mshta.exe %USERPROFILE%\\AppData\\Local\\Temp\\tinyfd.hta");
	}
	if ( ! GetConsoleWindow() )
	{
		strcat(lDialogString, "\"");
	}
	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	if (!(lIn = _popen(lDialogString,"r")))
	{
		return NULL ;
	}
	while ( fgets ( aoBuff , MAX_PATH_OR_CMD , lIn ) != NULL )
	{}
	_pclose ( lIn ) ;
	if ( aoBuff[ strlen ( aoBuff ) -1 ] == '\n' )
	{
		aoBuff[ strlen ( aoBuff ) -1 ] = '\0' ;
	}
	if (aDefaultInput)
	{
		sprintf(lDialogString, "%s\\AppData\\Local\\Temp\\tinyfd.vbs",
			getenv("USERPROFILE"));
	}
	else
	{
		sprintf(lDialogString, "%s\\AppData\\Local\\Temp\\tinyfd.txt",
			getenv("USERPROFILE"));
		if (!(lIn = fopen(lDialogString, "r")))
		{
			remove(lDialogString);
			sprintf(lDialogString, "%s\\AppData\\Local\\Temp\\tinyfd.hta",
				getenv("USERPROFILE"));
			return NULL;
		}
		while (fgets(aoBuff, MAX_PATH_OR_CMD, lIn) != NULL)
		{}
		fclose(lIn);
		remove(lDialogString);
		sprintf(lDialogString, "%s\\AppData\\Local\\Temp\\tinyfd.hta",
			getenv("USERPROFILE"));
	}
	remove(lDialogString);
	/* printf ( "aoBuff: %s\n" , aoBuff ) ; //*/
	lResult = strncmp(aoBuff, "1", 1) ? 0 : 1;
	/* printf ( "lResult: %d \n" , lResult ) ; //*/
	if (!lResult)
	{
		return NULL ;
	}
	/* printf ( "aoBuff+1: %s\n" , aoBuff+1 ) ; //*/
	return aoBuff + 1;
}


static char const * saveFileDialogWinGui (
	char * const aoBuff ,
	char const * const aTitle , /* NULL or "" */
	char const * const aDefaultPathAndFile , /* NULL or "" */
	int const aNumOfFilterPatterns , /* 0 */
	char const * const * const aFilterPatterns , /* NULL or {"*.jpg","*.png"} */
	char const * const aSingleFilterDescription ) /* NULL or "image files" */
{
	char lDirname [ MAX_PATH_OR_CMD ] ;
	char lDialogString[MAX_PATH_OR_CMD];
	char lFilterPatterns[MAX_PATH_OR_CMD] = "";
	int i ;
	char * p;
	OPENFILENAME ofn ;
	char * lRetval;
	HRESULT lHResult;

	lHResult = CoInitializeEx(NULL,0);

	getPathWithoutFinalSlash(lDirname, aDefaultPathAndFile);
	getLastName(aoBuff, aDefaultPathAndFile);

	if (aNumOfFilterPatterns > 0)
	{
		if ( aSingleFilterDescription && strlen(aSingleFilterDescription) )
		{
			strcpy(lFilterPatterns, aSingleFilterDescription);
			strcat(lFilterPatterns, "\n");
		}
		strcat(lFilterPatterns, aFilterPatterns[0]);
		for (i = 1; i < aNumOfFilterPatterns; i++)
		{
			strcat(lFilterPatterns, ";");
			strcat(lFilterPatterns, aFilterPatterns[i]);
		}
		strcat(lFilterPatterns, "\n");
		if ( ! (aSingleFilterDescription && strlen(aSingleFilterDescription) ) )
		{
			strcpy(lDialogString, lFilterPatterns);
			strcat(lFilterPatterns, lDialogString);
		}
		strcat(lFilterPatterns, "All Files\n*.*\n");
		p = lFilterPatterns;
		while ((p = strchr(p, '\n')) != NULL)
		{
			*p = '\0';
			p ++ ;
		}
	}

	ofn.lStructSize     = sizeof(OPENFILENAME) ;
	ofn.hwndOwner       = 0 ;
	ofn.hInstance       = 0 ;
	ofn.lpstrFilter     = lFilterPatterns ;
	ofn.lpstrCustomFilter = NULL ;
	ofn.nMaxCustFilter  = 0 ;
	ofn.nFilterIndex    = 1 ;
	ofn.lpstrFile		= aoBuff;

	ofn.nMaxFile        = MAX_PATH_OR_CMD ;
	ofn.lpstrFileTitle  = NULL ;
	ofn.nMaxFileTitle   = _MAX_FNAME + _MAX_EXT ;
	ofn.lpstrInitialDir = lDirname;
	ofn.lpstrTitle      = aTitle ;
	ofn.Flags           = OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR ;
	ofn.nFileOffset     = 0 ;
	ofn.nFileExtension  = 0 ;
	ofn.lpstrDefExt     = NULL ;
	ofn.lCustData       = 0L ;
	ofn.lpfnHook        = NULL ;
	ofn.lpTemplateName  = NULL ;

	if ( GetSaveFileName ( & ofn ) == 0 )
	{
		lRetval = NULL ;
	}
	else
	{
		lRetval = aoBuff ;
	}

	if (lHResult==S_OK || lHResult==S_FALSE)
	{
		CoUninitialize();
	}
	return lRetval ;
}


static char const * openFileDialogWinGui (
	char * const aoBuff ,
	char const * const aTitle , /*  NULL or "" */
	char const * const aDefaultPathAndFile , /*  NULL or "" */
	int const aNumOfFilterPatterns , /* 0 */
	char const * const * const aFilterPatterns , /* NULL or {"*.jpg","*.png"} */
	char const * const aSingleFilterDescription , /* NULL or "image files" */
	int const aAllowMultipleSelects ) /* 0 or 1 */
{
	char lDirname [ MAX_PATH_OR_CMD ] ;
	char lFilterPatterns[MAX_PATH_OR_CMD] = "";
	char lDialogString[MAX_PATH_OR_CMD] ;
	char * lPointers[MAX_MULTIPLE];
	size_t lLengths[MAX_MULTIPLE];
	int i , j ;
	char * p;
	OPENFILENAME ofn;
  size_t lBuffLen ;
	char * lRetval;
	HRESULT lHResult;

	lHResult = CoInitializeEx(NULL,0);

	getPathWithoutFinalSlash(lDirname, aDefaultPathAndFile);
	getLastName(aoBuff, aDefaultPathAndFile);

	if (aNumOfFilterPatterns > 0)
	{
		if ( aSingleFilterDescription && strlen(aSingleFilterDescription) )
		{
			strcpy(lFilterPatterns, aSingleFilterDescription);
			strcat(lFilterPatterns, "\n");
		}
		strcat(lFilterPatterns, aFilterPatterns[0]);
		for (i = 1; i < aNumOfFilterPatterns; i++)
		{
			strcat(lFilterPatterns, ";");
			strcat(lFilterPatterns, aFilterPatterns[i]);
		}
		strcat(lFilterPatterns, "\n");
		if ( ! (aSingleFilterDescription && strlen(aSingleFilterDescription) ) )
		{
			strcpy(lDialogString, lFilterPatterns);
			strcat(lFilterPatterns, lDialogString);
		}
		strcat(lFilterPatterns, "All Files\n*.*\n");
		p = lFilterPatterns;
		while ((p = strchr(p, '\n')) != NULL)
		{
			*p = '\0';
			p ++ ;
		}
	}

	ofn.lStructSize     = sizeof ( OPENFILENAME ) ;
	ofn.hwndOwner       = 0 ;
	ofn.hInstance       = 0 ;
	ofn.lpstrFilter		= lFilterPatterns;
	ofn.lpstrCustomFilter = NULL ;
	ofn.nMaxCustFilter  = 0 ;
	ofn.nFilterIndex    = 1 ;
	ofn.lpstrFile		= aoBuff ;
	ofn.nMaxFile        = MAX_PATH_OR_CMD ;
	ofn.lpstrFileTitle  = NULL ;
	ofn.nMaxFileTitle   = _MAX_FNAME + _MAX_EXT ;
	ofn.lpstrInitialDir = lDirname ;
	ofn.lpstrTitle      = aTitle ;
	ofn.Flags			= OFN_EXPLORER  | OFN_NOCHANGEDIR ;
	ofn.nFileOffset     = 0 ;
	ofn.nFileExtension  = 0 ;
	ofn.lpstrDefExt     = NULL ;
	ofn.lCustData       = 0L ;
	ofn.lpfnHook        = NULL ;
	ofn.lpTemplateName  = NULL ;

	if ( aAllowMultipleSelects )
	{
		ofn.Flags |= OFN_ALLOWMULTISELECT;
	}

	if ( GetOpenFileName ( & ofn ) == 0 )
	{
		lRetval = NULL ;
	}
	else
	{
		lBuffLen = strlen(aoBuff) ;
		lPointers[0] = aoBuff + lBuffLen + 1 ;
		if ( !aAllowMultipleSelects || (lPointers[0][0] == '\0')  )
		{
			lRetval = aoBuff ;
		}
		else
		{
			i = 0 ;
			do
			{
				lLengths[i] = strlen(lPointers[i]);
				lPointers[i+1] = lPointers[i] + lLengths[i] + 1 ;
				i ++ ;
			}
			while ( lPointers[i][0] != '\0' );
			i--;
			p = aoBuff + MAX_MULTIPLE*MAX_PATH_OR_CMD - 1 ;
			* p = '\0';
			for ( j = i ; j >=0 ; j-- )
			{
				p -= lLengths[j];
				memmove(p, lPointers[j], lLengths[j]);
				p--;
				*p = '\\';
				p -= lBuffLen ;
				memmove(p, aoBuff, lBuffLen);
				p--;
				*p = '|';
			}
			p++;
			lRetval = p ;
		}
	}

	if (lHResult==S_OK || lHResult==S_FALSE)
	{
		CoUninitialize();
	}
	return lRetval;
}


static char const * selectFolderDialogWinGui (
	char * const aoBuff ,
	char const * const aTitle , /*  NULL or "" */
	char const * const aDefaultPath ) /* NULL or "" */
{
	BROWSEINFO bInfo ;
	LPITEMIDLIST lpItem ;
	HRESULT lHResult;

	lHResult = CoInitializeEx(NULL,0);

	/* we can't use aDefaultPath */
	bInfo.hwndOwner = 0 ;
	bInfo.pidlRoot = NULL ;
	bInfo.pszDisplayName = aoBuff ;
	bInfo.lpszTitle = aTitle ;
	bInfo.ulFlags = 0 ;
	bInfo.lpfn = NULL ;
	bInfo.lParam = 0 ;
	bInfo.iImage = -1 ;

	lpItem = SHBrowseForFolder ( & bInfo ) ;
	if ( lpItem )
	{
		SHGetPathFromIDList ( lpItem , aoBuff ) ;
	}

	if (lHResult==S_OK || lHResult==S_FALSE)
	{
		CoUninitialize();
	}
	return aoBuff ;
}


static char const * colorChooserWinGui(
	char const * const aTitle, /* NULL or "" */
	char const * const aDefaultHexRGB, /* NULL or "#FF0000"*/
	unsigned char const aDefaultRGB[3], /* { 0 , 255 , 255 } */
	unsigned char aoResultRGB[3]) /* { 0 , 0 , 0 } */
{
	static CHOOSECOLOR cc;
	static COLORREF crCustColors[16];
	static char lResultHexRGB[8];
	unsigned char lDefaultRGB[3];
	int lRet;

	if ( aDefaultHexRGB )
	{
		Hex2RGB(aDefaultHexRGB, lDefaultRGB);
	}
	else
	{
		lDefaultRGB[0]=aDefaultRGB[0];
		lDefaultRGB[1]=aDefaultRGB[1];
		lDefaultRGB[2]=aDefaultRGB[2];
	}

	/* we can't use aTitle */
	cc.lStructSize = sizeof ( CHOOSECOLOR ) ;
	cc.hwndOwner = NULL ;
	cc.hInstance = NULL ;
	cc.rgbResult = RGB(lDefaultRGB[0], lDefaultRGB[1], lDefaultRGB[2]);
	cc.lpCustColors = crCustColors;
	cc.Flags = CC_RGBINIT | CC_FULLOPEN;
	cc.lCustData = 0;
	cc.lpfnHook = NULL;
	cc.lpTemplateName = NULL;

	lRet = ChooseColor(&cc);

	if ( ! lRet )
	{
		return NULL;
	}

	aoResultRGB[0] = GetRValue(cc.rgbResult);
	aoResultRGB[1] = GetGValue(cc.rgbResult);
	aoResultRGB[2] = GetBValue(cc.rgbResult);

	RGB2Hex(aoResultRGB, lResultHexRGB);

	return lResultHexRGB;
}

#endif /* TINYFD_WIN_CONSOLE_ONLY */


static int dialogPresent ( )
{
	static int lDialogPresent = -1 ;
	char lBuff [ MAX_PATH_OR_CMD ] ;
	FILE * lIn ;
	char const * lString = "dialog.exe";
	if ( lDialogPresent < 0 )
	{
		if (!(lIn = _popen("where dialog.exe","r")))
		{
			lDialogPresent = 0 ;
			return 0 ;
		}
		while ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) != NULL )
		{}
		_pclose ( lIn ) ;
		if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
		{
			lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
		}
		if ( strcmp(lBuff+strlen(lBuff)-strlen(lString),lString) )
		{
			lDialogPresent = 0 ;
		}
		else
		{
			lDialogPresent = 1 ;
		}
	}
	return lDialogPresent ;
}


static int messageBoxWinConsole (
	char const * const aTitle , /* NULL or "" */
	char const * const aMessage , /* NULL or ""  may contain \n and \t */
	char const * const aDialogType , /* "ok" "okcancel" "yesno" */
	char const * const aIconType , /* "info" "warning" "error" "question" */
	int const aDefaultButton ) /* 0 for cancel/no , 1 for ok/yes */
{
	char lDialogString[MAX_PATH_OR_CMD];
	char lDialogFile[MAX_PATH_OR_CMD];
	FILE * lIn;
	char lBuff [ MAX_PATH_OR_CMD ] = "";

	strcpy ( lDialogString , "dialog " ) ;
	if ( aTitle && strlen(aTitle) )
	{
		strcat(lDialogString, "--title \"") ;
		strcat(lDialogString, aTitle) ;
		strcat(lDialogString, "\" ") ;
	}
	if ( aDialogType && ! strcmp( "okcancel" , aDialogType ) )
	{
		if ( ! aDefaultButton )
		{
			strcat ( lDialogString , "--defaultno " ) ;
		}
		strcat ( lDialogString ,
				"--yes-label \"Ok\" --no-label \"Cancel\" --yesno " ) ;
	}
	else if ( aDialogType && ! strcmp( "yesno" , aDialogType ) )
	{
		if ( ! aDefaultButton )
		{
			strcat ( lDialogString , "--defaultno " ) ;
		}
		strcat ( lDialogString , "--yesno " ) ;
	}
	else
	{
		strcat ( lDialogString , "--msgbox " ) ;

	}


	strcat ( lDialogString , "\"" ) ;
	if ( aMessage && strlen(aMessage) )
	{
		replaceSubStr ( aMessage , "\n" , "\\n" , lBuff ) ;
		strcat(lDialogString, lBuff) ;
		lBuff[0]='\0';
	}

	strcat(lDialogString, "\" 10 60");
	strcat(lDialogString, " && echo 1 > ");

	strcpy(lDialogFile, getenv("USERPROFILE"));
	strcat(lDialogFile, "\\AppData\\Local\\Temp\\tinyfd.txt");
	strcat(lDialogString, lDialogFile);

	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	system ( lDialogString ) ;

	if (!(lIn = fopen(lDialogFile, "r")))
	{
		remove(lDialogFile);
		return 0 ;
	}
	while (fgets(lBuff, sizeof(lBuff), lIn) != NULL)
	{}
	fclose(lIn);
	remove(lDialogFile);
	if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
	{
		lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
	}
	/* printf ( "lBuff: %s\n" , lBuff ) ; //*/
	if ( ! strlen(lBuff) )
	{
		return 0;
	}
	return 1;
}


static char const * inputBoxWinConsole(
	char * const aoBuff ,
	char const * const aTitle , /* NULL or "" */
	char const * const aMessage , /* NULL or "" may NOT contain \n nor \t */
	char const * const aDefaultInput ) /* "" , if NULL it's a passwordBox */
{
	char lDialogString[MAX_PATH_OR_CMD];
	char lDialogFile[MAX_PATH_OR_CMD];
	FILE * lIn;
	int lResult;

	strcpy(lDialogFile, getenv("USERPROFILE"));
	strcat(lDialogFile, "\\AppData\\Local\\Temp\\tinyfd.txt");
	strcpy(lDialogString , "echo|set /p=1 >" ) ;
	strcat(lDialogString, lDialogFile);
	strcat( lDialogString , " & " ) ;

	strcat ( lDialogString , "dialog " ) ;
	if ( aTitle && strlen(aTitle) )
	{
		strcat(lDialogString, "--title \"") ;
		strcat(lDialogString, aTitle) ;
		strcat(lDialogString, "\" ") ;
	}
	if ( ! aDefaultInput )
	{
		strcat ( lDialogString , "--passwordbox" ) ;
	}
	else
	{
		strcat ( lDialogString , "--inputbox" ) ;
	}
	strcat ( lDialogString , " \"" ) ;
	if ( aMessage && strlen(aMessage) )
	{
		strcat(lDialogString, aMessage) ;
	}
	strcat(lDialogString,"\" 10 60 ") ;
	if ( aDefaultInput && strlen(aDefaultInput) )
	{
		strcat(lDialogString, "\"") ;
		strcat(lDialogString, aDefaultInput) ;
		strcat(lDialogString, "\" ") ;
	}

	strcat(lDialogString, "2>>");
	strcpy(lDialogFile, getenv("USERPROFILE"));
	strcat(lDialogFile, "\\AppData\\Local\\Temp\\tinyfd.txt");
	strcat(lDialogString, lDialogFile);
	strcat(lDialogString, " || echo 0 > ");
	strcat(lDialogString, lDialogFile);

	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	system ( lDialogString ) ;

	if (!(lIn = fopen(lDialogFile, "r")))
	{
		remove(lDialogFile);
		return 0 ;
	}
	while (fgets(aoBuff, MAX_PATH_OR_CMD, lIn) != NULL)
	{}
	fclose(lIn);
	remove(lDialogFile);
	if ( aoBuff[ strlen ( aoBuff ) -1 ] == '\n' )
	{
		aoBuff[ strlen ( aoBuff ) -1 ] = '\0' ;
	}
	/* printf ( "aoBuff: %s\n" , aoBuff ) ; //*/

	/* printf ( "aoBuff: %s len: %lu \n" , aoBuff , strlen(aoBuff) ) ; //*/
	lResult =  strncmp ( aoBuff , "1" , 1) ? 0 : 1 ;
	/* printf ( "lResult: %d \n" , lResult ) ; //*/
	if ( ! lResult )
	{
		return NULL ;
	}
	/* printf ( "aoBuff+1: %s\n" , aoBuff+1 ) ; //*/
	return aoBuff+3 ;
}


static char const * saveFileDialogWinConsole (
	char * const aoBuff ,
	char const * const aTitle , /* NULL or "" */
	char const * const aDefaultPathAndFile ) /* NULL or "" */
{
	char lDialogString[MAX_PATH_OR_CMD];
	char lPathAndFile[MAX_PATH_OR_CMD] = "";
	FILE * lIn;

	strcpy ( lDialogString , "dialog " ) ;
	if ( aTitle && strlen(aTitle) )
	{
		strcat(lDialogString, "--title \"") ;
		/*strcat(lDialogString, aTitle) ;*/
		strcat(lDialogString, "tab =move focus | spacebar =select | add / =populate") ;
		strcat(lDialogString, "\" ") ;
	}
	strcat ( lDialogString , "--fselect \"" ) ;
	if ( aDefaultPathAndFile && strlen(aDefaultPathAndFile) )
	{
		/* dialog.exe uses unix separators even on windows */
		strcpy(lPathAndFile, aDefaultPathAndFile);
		replaceChr ( lPathAndFile , '\\' , '/' ) ;
	}

	/* dialog.exe needs at least one separator */
	if ( ! strchr(lPathAndFile, '/') )
	{
		strcat(lDialogString, "./") ;
	}
	strcat(lDialogString, lPathAndFile) ;
	strcat(lDialogString, "\" 0 60 2>");
	strcpy(lPathAndFile, getenv("USERPROFILE"));
	strcat(lPathAndFile, "\\AppData\\Local\\Temp\\tinyfd.txt");
	strcat(lDialogString, lPathAndFile);

	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	system ( lDialogString ) ;

	if (!(lIn = fopen(lPathAndFile, "r")))
	{
		remove(lPathAndFile);
		return NULL;
	}
	while (fgets(aoBuff, MAX_PATH_OR_CMD, lIn) != NULL)
	{}
	fclose(lIn);
	remove(lPathAndFile);
	replaceChr ( aoBuff , '/' , '\\' ) ;
	/* printf ( "aoBuff: %s\n" , aoBuff ) ; //*/
	getLastName(lDialogString,aoBuff);
	if ( ! strlen(lDialogString) )
	{
		return NULL;
	}
	return aoBuff;
}


static char const * openFileDialogWinConsole (
	char * const aoBuff ,
	char const * const aTitle , /*  NULL or "" */
	char const * const aDefaultPathAndFile , /*  NULL or "" */
	int const aAllowMultipleSelects ) /* 0 or 1 */
{
	char lFilterPatterns[MAX_PATH_OR_CMD] = "";
	char lDialogString[MAX_PATH_OR_CMD] ;
	FILE * lIn;


	strcpy ( lDialogString , "dialog " ) ;
	if ( aTitle && strlen(aTitle) )
	{
		strcat(lDialogString, "--title \"") ;
		/*strcat(lDialogString, aTitle) ;*/
		strcat(lDialogString, "tab =move focus | spacebar =select | add / =populate") ;
		strcat(lDialogString, "\" ") ;
	}
	strcat ( lDialogString , "--fselect \"" ) ;
	if ( aDefaultPathAndFile && strlen(aDefaultPathAndFile) )
	{
		/* dialog.exe uses unix separators even on windows */
		strcpy(lFilterPatterns, aDefaultPathAndFile);
		replaceChr ( lFilterPatterns , '\\' , '/' ) ;
	}

	/* dialog.exe needs at least one separator */
	if ( ! strchr(lFilterPatterns, '/') )
	{
		strcat(lDialogString, "./") ;
	}
	strcat(lDialogString, lFilterPatterns) ;
	strcat(lDialogString, "\" 0 60 2>");
	strcpy(lFilterPatterns, getenv("USERPROFILE"));
	strcat(lFilterPatterns, "\\AppData\\Local\\Temp\\tinyfd.txt");
	strcat(lDialogString, lFilterPatterns);

	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	system ( lDialogString ) ;

	if (!(lIn = fopen(lFilterPatterns, "r")))
	{
		remove(lFilterPatterns);
		return NULL;
	}
	while (fgets(aoBuff, MAX_PATH_OR_CMD, lIn) != NULL)
	{}
	fclose(lIn);
	remove(lFilterPatterns);
	replaceChr ( aoBuff , '/' , '\\' ) ;
	/* printf ( "aoBuff: %s\n" , aoBuff ) ; //*/
	return aoBuff;
}


static char const * selectFolderDialogWinConsole (
	char * const aoBuff ,
	char const * const aTitle , /*  NULL or "" */
	char const * const aDefaultPath ) /* NULL or "" */
{
	char lDialogString [ MAX_PATH_OR_CMD ] ;
	char lString [ MAX_PATH_OR_CMD ] ;
	FILE * lIn ;

	strcpy ( lDialogString , "dialog " ) ;
	if ( aTitle && strlen(aTitle) )
	{
		strcat(lDialogString, "--title \"") ;
		/*strcat(lDialogString, aTitle) ;*/
		strcat(lDialogString, "tab =move focus | spacebar =select | add / =populate") ;
		strcat(lDialogString, "\" ") ;
	}
	strcat ( lDialogString , "--dselect \"" ) ;
	if ( aDefaultPath && strlen(aDefaultPath) )
	{
		/* dialog.exe uses unix separators even on windows */
		strcpy(lString, aDefaultPath) ;
		ensureFinalSlash(lString);
		replaceChr ( lString , '\\' , '/' ) ;
		strcat(lDialogString, lString) ;
	}
	else
	{
		/* dialog.exe needs at least one separator */
		strcat(lDialogString, "./") ;
	}
	strcat(lDialogString, "\" 0 60 2>");
	strcpy(lString, getenv("USERPROFILE"));
	strcat(lString, "\\AppData\\Local\\Temp\\tinyfd.txt");
	strcat(lDialogString, lString);

	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	system ( lDialogString ) ;

	if (!(lIn = fopen(lString, "r")))
	{
		remove(lString);
		return NULL;
	}
	while (fgets(aoBuff, MAX_PATH_OR_CMD, lIn) != NULL)
	{}
	fclose(lIn);
	remove(lString);
	replaceChr ( aoBuff , '/' , '\\' ) ;
	/* printf ( "aoBuff: %s\n" , aoBuff ) ; //*/
	return aoBuff;
}


/* returns 0 for cancel/no , 1 for ok/yes */
int tinyfd_messageBox (
	char const * const aTitle , /* NULL or "" */
	char const * const aMessage , /* NULL or ""  may contain \n and \t */
	char const * const aDialogType , /* "ok" "okcancel" "yesno" */
	char const * const aIconType , /* "info" "warning" "error" "question" */
	int const aDefaultButton ) /* 0 for cancel/no , 1 for ok/yes */
{
	char lChar ;

#ifndef TINYFD_WIN_CONSOLE_ONLY
	if ( ( !tinyfd_forceConsole || !( GetConsoleWindow() || dialogPresent() ) )
	  && ( !getenv("SSH_CLIENT") || getenv("DISPLAY") ) )
	{
		return messageBoxWinGui(
					aTitle,aMessage,aDialogType,aIconType,aDefaultButton);
	}
	else
#endif /* TINYFD_WIN_CONSOLE_ONLY */
	if ( dialogPresent() )
	{
		return messageBoxWinConsole(
					aTitle,aMessage,aDialogType,aIconType,aDefaultButton);
	}
	else
	{
		if ( !gWarningDisplayed )
		{
			gWarningDisplayed = 1 ;
			printf ("\n\n%s\n", gTitle);
			printf ("%s\n\n\n", gMessageWin);
		}
		if ( aTitle && strlen(aTitle) )
		{
			printf ("%s\n\n", aTitle);
		}
		if ( aDialogType && !strcmp("yesno",aDialogType) )
		{
			do
			{
				if ( aMessage && strlen(aMessage) )
				{
					printf("%s\n",aMessage);
				}
				printf("y/n: ");
				lChar = (char) tolower ( _getch() ) ;
				printf("\n\n");
			}
			while ( lChar != 'y' && lChar != 'n' ) ;
			return lChar == 'y' ? 1 : 0 ;
		}
		else if ( aDialogType && !strcmp("okcancel",aDialogType) )
		{
			do
			{
				if ( aMessage && strlen(aMessage) )
				{
					printf("%s\n",aMessage);
				}
				printf("[O]kay/[C]ancel: ");
				lChar = (char) tolower ( _getch() ) ;
				printf("\n\n");
			}
			while ( lChar != 'o' && lChar != 'c' ) ;
			return lChar == 'o' ? 1 : 0 ;
		}
		else
		{
			if ( aMessage && strlen(aMessage) )
			{
				printf("%s\n\n",aMessage);
			}
			printf("press any key to continue ");
			lChar = (char) _getch() ;
			printf("\n\n");
			return 1 ;
		}
	}
}


/* returns NULL on cancel */
char const * tinyfd_inputBox(
	char const * const aTitle , /* NULL or "" */
	char const * const aMessage , /* NULL or "" may NOT contain \n nor \t */
	char const * const aDefaultInput ) /* "" , if NULL it's a passwordBox */
{
	static char lBuff [ MAX_PATH_OR_CMD ] ;

#ifndef TINYFD_WIN_CONSOLE_ONLY
	DWORD mode = 0;
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);;
	if ( ( !tinyfd_forceConsole || !( GetConsoleWindow() || dialogPresent() ) )
	  && ( !getenv("SSH_CLIENT") || getenv("DISPLAY") ) )
	{
		lBuff[0]='\0';
		return inputBoxWinGui(lBuff,aTitle,aMessage,aDefaultInput);
	}
	else
#endif /* TINYFD_WIN_CONSOLE_ONLY */
	if ( dialogPresent() )
	{
		lBuff[0]='\0';
		return inputBoxWinConsole(lBuff,aTitle,aMessage,aDefaultInput);
	}
	else
	{
		lBuff[0]='\0';
		if ( !gWarningDisplayed )
		{
			gWarningDisplayed = 1 ;
			printf ("\n\n%s\n", gTitle);
			printf ("%s\n\n\n", gMessageWin);
		}
		if ( aTitle && strlen(aTitle) )
		{
			printf ("%s\n\n", aTitle);
		}
		if ( aMessage && strlen(aMessage) )
		{
			printf("%s\n",aMessage);
		}
		printf("(esc+enter to cancel): ");
#ifndef TINYFD_WIN_CONSOLE_ONLY
		if ( ! aDefaultInput )
		{
			GetConsoleMode(hStdin,&mode);
			SetConsoleMode(hStdin,mode & (~ENABLE_ECHO_INPUT) );
		}
#endif /* TINYFD_WIN_CONSOLE_ONLY */
		fgets(lBuff, MAX_PATH_OR_CMD, stdin);
#ifndef TINYFD_WIN_CONSOLE_ONLY
		if ( ! aDefaultInput )
		{
			SetConsoleMode(hStdin,mode);
			printf ("\n");
		}
#endif /* TINYFD_WIN_CONSOLE_ONLY */
		printf ("\n");
		if ( strchr(lBuff,27) )
		{
			return NULL ;
		}
		if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
		{
			lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
		}
		return lBuff ;
	}
}


char const * tinyfd_saveFileDialog (
	char const * const aTitle , /* NULL or "" */
	char const * const aDefaultPathAndFile , /* NULL or "" */
	int const aNumOfFilterPatterns , /* 0 */
	char const * const * const aFilterPatterns , /* NULL or {"*.jpg","*.png"} */
	char const * const aSingleFilterDescription ) /* NULL or "image files" */
{
	static char lBuff [ MAX_PATH_OR_CMD ] ;
	char lString[MAX_PATH_OR_CMD] ;
	char const * p ;
	lBuff[0]='\0';
#ifndef TINYFD_WIN_CONSOLE_ONLY
	if ( ( !tinyfd_forceConsole || !( GetConsoleWindow() || dialogPresent() ) )
	  && ( !getenv("SSH_CLIENT") || getenv("DISPLAY") ) )
	{
		p = saveFileDialogWinGui(lBuff,
				aTitle,aDefaultPathAndFile,aNumOfFilterPatterns,aFilterPatterns,aSingleFilterDescription);
	}
	else
#endif /* TINYFD_WIN_CONSOLE_ONLY */
	if ( dialogPresent() )
	{
		p = saveFileDialogWinConsole(lBuff,aTitle,aDefaultPathAndFile);
	}
	else
	{
		p = tinyfd_inputBox(aTitle, "Save file","");
	}

	if ( ! p || ! strlen ( p )  )
	{
		return NULL;
	}
	getPathWithoutFinalSlash ( lString , p ) ;
	if ( strlen ( lString ) && ! dirExists ( lString ) )
	{
		return NULL ;
	}
	getLastName(lString,p);
	if ( ! filenameValid(lString) )
	{
		return NULL;
	}
	return p ;
}


/* in case of multiple files, the separator is | */
char const * tinyfd_openFileDialog (
	char const * const aTitle , /*  NULL or "" */
	char const * const aDefaultPathAndFile , /*  NULL or "" */
	int const aNumOfFilterPatterns , /* 0 */
	char const * const * const aFilterPatterns , /* NULL or {"*.jpg","*.png"} */
	char const * const aSingleFilterDescription , /* NULL or "image files" */
	int const aAllowMultipleSelects ) /* 0 or 1 */
{
	static char lBuff[MAX_MULTIPLE*MAX_PATH_OR_CMD];
	char const * p ;
#ifndef TINYFD_WIN_CONSOLE_ONLY
	if ( ( !tinyfd_forceConsole || !( GetConsoleWindow() || dialogPresent() ) )
	  && ( !getenv("SSH_CLIENT") || getenv("DISPLAY") ) )
	{
		p = openFileDialogWinGui(lBuff,
				aTitle,aDefaultPathAndFile,aNumOfFilterPatterns,
				aFilterPatterns,aSingleFilterDescription,aAllowMultipleSelects);
	}
	else
#endif /* TINYFD_WIN_CONSOLE_ONLY */
	if ( dialogPresent() )
	{
		p = openFileDialogWinConsole(lBuff,
				aTitle,aDefaultPathAndFile,aAllowMultipleSelects);
	}
	else
	{
		p = tinyfd_inputBox(aTitle, "Open file","");
	}

	if ( ! p || ! strlen ( p )  )
	{
		return NULL;
	}
	if ( aAllowMultipleSelects && strchr(p, '|') )
	{
		p = ensureFilesExist( lBuff , p ) ;
	}
	else if ( ! fileExists (p) )
	{
		return NULL ;
	}
	/* printf ( "lBuff3: %s\n" , p ) ; //*/
	return p ;
}


char const * tinyfd_selectFolderDialog (
	char const * const aTitle , /*  NULL or "" */
	char const * const aDefaultPath ) /* NULL or "" */
{
	static char lBuff [ MAX_PATH_OR_CMD ] ;
	char const * p ;
#ifndef TINYFD_WIN_CONSOLE_ONLY
	if ( ( !tinyfd_forceConsole || !( GetConsoleWindow() || dialogPresent() ) )
	  && ( !getenv("SSH_CLIENT") || getenv("DISPLAY") ) )
	{
		p = selectFolderDialogWinGui(lBuff,aTitle,aDefaultPath);
	}
	else
#endif /* TINYFD_WIN_CONSOLE_ONLY */
	if ( dialogPresent() )
	{
		p = selectFolderDialogWinConsole(lBuff,aTitle,aDefaultPath);
	}
	else
	{
		p = tinyfd_inputBox(aTitle, "Select folder","");
	}

	if ( ! p || ! strlen ( p ) || ! dirExists ( p ) )
	{
		return NULL ;
	}
	return p ;
}


/* returns the hexcolor as a string "#FF0000" */
/* aoResultRGB also contains the result */
/* aDefaultRGB is used only if aDefaultHexRGB is NULL */
/* aDefaultRGB and aoResultRGB can be the same array */
char const * tinyfd_colorChooser(
	char const * const aTitle, /* NULL or "" */
	char const * const aDefaultHexRGB, /* NULL or "#FF0000"*/
	unsigned char const aDefaultRGB[3], /* { 0 , 255 , 255 } */
	unsigned char aoResultRGB[3]) /* { 0 , 0 , 0 } */
{
	char lDefaultHexRGB[8];
	char * lpDefaultHexRGB;
	int i;
	char const * p ;

#ifndef TINYFD_WIN_CONSOLE_ONLY
	if ( (!tinyfd_forceConsole || !( GetConsoleWindow() || dialogPresent()) )
	  && (!getenv("SSH_CLIENT") || getenv("DISPLAY")) )
	{
		return colorChooserWinGui(
						aTitle,aDefaultHexRGB,aDefaultRGB,aoResultRGB);
	}
	else
#endif /* TINYFD_WIN_CONSOLE_ONLY */
	if ( aDefaultHexRGB )
	{
		lpDefaultHexRGB = (char *) aDefaultHexRGB ;
	}
	else
	{
		RGB2Hex( aDefaultRGB , lDefaultHexRGB ) ;
		lpDefaultHexRGB = (char *) lDefaultHexRGB ;
	}
	p = tinyfd_inputBox(aTitle,
			"Enter hex rgb color (i.e. #f5ca20)",lpDefaultHexRGB);
	if ( !p || (strlen(p) != 7) || (p[0] != '#') )
	{
		return NULL ;
	}
	for ( i = 1 ; i < 7 ; i ++ )
	{
		if ( ! isxdigit( p[i] ) )
		{
			return NULL ;
		}
	}
	Hex2RGB(p,aoResultRGB);
	return p ;
}

#else /* unix */

static char gPython2Name[16];

static int isDarwin ( )
{
	static int lsIsDarwin = -1 ;
	struct utsname lUtsname ;
	if ( lsIsDarwin < 0 )
	{
		lsIsDarwin = !uname(&lUtsname) && !strcmp(lUtsname.sysname,"Darwin") ;
	}
	return lsIsDarwin ;
}


static int dirExists ( char const * const aDirPath )
{
	DIR * lDir ;
	if ( ! aDirPath || ! strlen ( aDirPath ) )
		return 0 ;
	lDir = opendir ( aDirPath ) ;
	if ( ! lDir )
	{
		return 0 ;
	}
	closedir ( lDir ) ;
	return 1 ;
}


static int detectPresence ( char const * const aExecutable )
{
	char lBuff [ MAX_PATH_OR_CMD ] ;
	char lTestedString [ MAX_PATH_OR_CMD ] = "which " ;
	FILE * lIn ;

	strcat ( lTestedString , aExecutable ) ;
	lIn = popen ( lTestedString , "r" ) ;
	if ( ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) != NULL )
		&& ( ! strchr ( lBuff , ':' ) ) )
	{	/* present */
		pclose ( lIn ) ;
		return 1 ;
	}
	else
	{
		pclose ( lIn ) ;
		return 0 ;
	}
}


static int tryCommand ( char const * const aCommand )
{
	char lBuff [ MAX_PATH_OR_CMD ] ;
	FILE * lIn ;

	lIn = popen ( aCommand , "r" ) ;
	if ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) == NULL )
	{	/* present */
		pclose ( lIn ) ;
		return 1 ;
	}
	else
	{
		pclose ( lIn ) ;
		return 0 ;
	}

}


static char const * terminalName ( )
{
	static char lTerminalName[64] = "*" ;
	if ( lTerminalName[0] == '*' )
	{
		if ( isDarwin() )
		{
			if ( strcpy(lTerminalName , "/opt/X11/bin/xterm" )
			  && detectPresence ( lTerminalName ) )
			{
				strcat(lTerminalName , " -e bash -c " ) ;
			}
			else
			{
				strcpy(lTerminalName , "" ) ;
			}
		}
		else if ( strcpy(lTerminalName,"gnome-terminal")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " --disable-factory -x bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"konsole")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"xterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
			//strcat(lTerminalName , " -e " ) ;
		}
		else if ( strcpy(lTerminalName,"lxterminal")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"xfce4-terminal")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -x bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"Terminal")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -x bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"rxvt")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"urxvt")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"mrxvt")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"wterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"eterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"aterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"terminology")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"multi-gnome-terminal")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -x bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"hpterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"winterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -c bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"roxterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"st")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"sakura")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"mlterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"vte")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"terminator")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -x bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"lilyterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -x bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"dtterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"nxterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"pterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"xgterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"evilvte")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"kterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"xiterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"termit")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"xvt")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"vala-terminal")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else if ( strcpy(lTerminalName,"osso-xterm")
			  && detectPresence(lTerminalName) )
		{
			strcat(lTerminalName , " -e bash -c " ) ;
		}
		else
		{
			strcpy(lTerminalName , "" ) ;
		}
	}
	if ( strlen(lTerminalName) )
	{
		return lTerminalName ;
	}
	else
	{
		return NULL ;
	}
}


static char const * dialogName ( )
{
	static char lDialogName[64] = "*" ;
	if ( lDialogName[0] == '*' )
	{
		if ( isDarwin() && strcpy(lDialogName , "/opt/local/bin/dialog" )
		  && detectPresence ( lDialogName ) )
		{}
		else if ( strcpy(lDialogName , "dialog" )
			&& detectPresence ( lDialogName ) )
		{}
		else
		{
			strcpy(lDialogName , "" ) ;
		}
	}
	if ( strlen(lDialogName) && ( isatty(1) || terminalName() ) )
	{
		return lDialogName ;
	}
	else
	{
		return NULL ;
	}
}


static int whiptailPresent ( )
{
	static int lWhiptailPresent = -1 ;
	if ( lWhiptailPresent < 0 )
	{
		lWhiptailPresent = detectPresence ( "whiptail" ) ;
	}
	return lWhiptailPresent && ( isatty(1) || terminalName() ) ;
}


static int graphicMode()
{
	return !( tinyfd_forceConsole && (isatty(1) || terminalName()) )
			&& ( getenv ( "DISPLAY" ) || isDarwin() ) ;
}


static int xmessagePresent ( )
{
	static int lXmessagePresent = -1 ;
	if ( lXmessagePresent < 0 )
	{
	 lXmessagePresent = detectPresence("xmessage");/*if not tty,not on osxpath*/
	}
	return lXmessagePresent && graphicMode ( ) ;
}


static int gxmessagePresent ( )
{
	static int lGxmessagePresent = -1 ;
	if ( lGxmessagePresent < 0 )
	{
		lGxmessagePresent = detectPresence("gxmessage") ;
	}
	return lGxmessagePresent && graphicMode ( ) ;
}


static int notifysendPresent ( )
{
	static int lNotifysendPresent = -1 ;
	if ( lNotifysendPresent < 0 )
	{
		lNotifysendPresent = detectPresence("notify-send") ;
	}
	return lNotifysendPresent && graphicMode ( ) ;
}


static int xdialogPresent ( )
{
	static int lXdialogPresent = -1 ;
	if ( lXdialogPresent < 0 )
	{
		lXdialogPresent = detectPresence("Xdialog") ;
	}
	return lXdialogPresent && graphicMode ( ) ;
}


static int gdialogPresent ( )
{
	static int lGdialoglPresent = -1 ;
	if ( lGdialoglPresent < 0 )
	{
		lGdialoglPresent = detectPresence ( "gdialog" ) ;
	}
	return lGdialoglPresent && graphicMode ( ) ;
}


static int osascriptPresent ( )
{
	static int lOsascriptPresent = -1 ;
	if ( lOsascriptPresent < 0 )
	{
		lOsascriptPresent = detectPresence ( "osascript" ) ;
	}
	return lOsascriptPresent && graphicMode ( ) ;
}


static int kdialogPresent ( )
{
	static int lKdialogPresent = -1 ;
	if ( lKdialogPresent < 0 )
	{
		lKdialogPresent = detectPresence("kdialog") ;
	}
	return lKdialogPresent && graphicMode ( ) ;
}


static int zenityPresent ( )
{
	static int lZenityPresent = -1 ;
	if ( lZenityPresent < 0 )
	{
		lZenityPresent = detectPresence("zenity") ;
	}
	return lZenityPresent && graphicMode ( ) ;
}


static int zenity3Present ( )
{
	static int lZenity3Present = -1 ;
	char lBuff [ MAX_PATH_OR_CMD ] ;
	FILE * lIn ;


	if ( lZenity3Present < 0 )
	{
		if ( ! zenityPresent() )
		{
			lZenity3Present = 0 ;
		}
		else
		{
			lIn = popen ( "zenity --version" , "r" ) ;
			if ( ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) != NULL )
			  && ( atoi(lBuff) >= 3 )
			  && ( atoi(strtok(lBuff,".")+1) >= 0 ) )
			{
				lZenity3Present = 1 ;
			}
			else
			{
				lZenity3Present = 0 ;
			}
			pclose ( lIn ) ;
		}
	}
	return lZenity3Present && graphicMode ( ) ;
}


static int tkinter2Present ( )
{
	static int lTkinter2Present = -1 ;
	char lPythonCommand[256];
	char lPythonParams[256] =
"-c \"try:\n\timport Tkinter;\nexcept:\n\tprint(0);\"";
	int i;

	if ( lTkinter2Present < 0 )
	{
		strcpy(gPython2Name , "python" ) ;
		sprintf ( lPythonCommand , "%s %s" , gPython2Name , lPythonParams ) ;
		lTkinter2Present = tryCommand(lPythonCommand);
		if ( ! lTkinter2Present )
		{
			strcpy(gPython2Name , "python2" ) ;
			if ( detectPresence(gPython2Name) )
			{
sprintf ( lPythonCommand , "%s %s" , gPython2Name , lPythonParams ) ;
				lTkinter2Present = tryCommand(lPythonCommand);
			}
			else
			{
				for ( i = 9 ; i >= 0 ; i -- )
				{
					sprintf ( gPython2Name , "python2.%d" , i ) ;
					if ( detectPresence(gPython2Name) )
					{
sprintf ( lPythonCommand , "%s %s" , gPython2Name , lPythonParams ) ;
						lTkinter2Present = tryCommand(lPythonCommand);
						break ;
					}
				}
			}
		}
	}
	/* printf ("gPython2Name %s\n", gPython2Name) ; //*/
	return lTkinter2Present && graphicMode ( ) ;
}


/* returns 0 for cancel/no , 1 for ok/yes */
int tinyfd_messageBox (
	char const * const aTitle , /* NULL or "" */
	char const * const aMessage , /* NULL or ""  may contain \n and \t */
	char const * const aDialogType , /* "ok" "okcancel" "yesno"*/
	char const * const aIconType , /* "info" "warning" "error" "question" */
	int const aDefaultButton ) /* 0 for cancel/no , 1 for ok/yes */
{
	char lBuff [ MAX_PATH_OR_CMD ] ;
	char lDialogString [ MAX_PATH_OR_CMD ] ;
	FILE * lIn ;
	int lWasGraphicDialog = 0 ;
	int lWasXterm = 0 ;
	int lResult ;
	char lChar ;
	struct termios infoOri;
	struct termios info;
	lBuff[0]='\0';

	if ( osascriptPresent ( ) )
	{
		strcpy ( lDialogString , "osascript -e 'try' -e 'display dialog \"") ;
		if ( aMessage && strlen(aMessage) )
		{
			strcat(lDialogString, aMessage) ;
		}
		strcat(lDialogString, "\" ") ;
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "with title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\" ") ;
		}
		strcat(lDialogString, "with icon ") ;
		if ( aIconType && ! strcmp( "error" , aIconType ) )
		{
			strcat(lDialogString, "stop " ) ;
		}
		else if ( aIconType && ! strcmp( "warning" , aIconType ) )
		{
			strcat(lDialogString, "caution " ) ;
		}
		else /* question or info */
		{
			strcat(lDialogString, "note " ) ;
		}
		if ( aDialogType && ! strcmp( "okcancel" , aDialogType ) )
		{
			if ( ! aDefaultButton )
			{
				strcat ( lDialogString ,"default button \"Cancel\" " ) ;
			}
		}
		else if ( aDialogType && ! strcmp( "yesno" , aDialogType ) )
		{
			strcat ( lDialogString ,"buttons {\"No\", \"Yes\"} " ) ;
			if (aDefaultButton)
			{
				strcat ( lDialogString ,"default button \"Yes\" " ) ;
			}
			else
			{
				strcat ( lDialogString ,"default button \"No\" " ) ;
			}
			strcat ( lDialogString ,"cancel button \"No\"" ) ;
		}
		else
		{
			strcat ( lDialogString ,"buttons {\"OK\"} " ) ;
			strcat ( lDialogString ,"default button \"OK\" " ) ;

		}
		strcat(lDialogString, "' ") ;
		strcat(lDialogString, "-e '1' " );
		strcat(lDialogString, "-e 'on error number -128' " ) ;
		strcat(lDialogString, "-e '0' " );
		strcat(lDialogString, "-e 'end try'") ;
	}
	else if ( zenityPresent() )
	{
		strcpy ( lDialogString , "zenity --" ) ;
		if ( aDialogType && ! strcmp( "okcancel" , aDialogType ) )
		{
			strcat ( lDialogString ,
					"question --ok-label=Ok --cancel-label=Cancel" ) ;
		}
		else if ( aDialogType && ! strcmp( "yesno" , aDialogType ) )
		{
			strcat ( lDialogString , "question" ) ;
		}
		else if ( aIconType && ! strcmp( "error" , aIconType ) )
		{
			strcat ( lDialogString , "error" ) ;
		}
		else if ( aIconType && ! strcmp( "warning" , aIconType ) )
		{
			strcat ( lDialogString , "warning" ) ;
		}
		else
		{
			strcat ( lDialogString , "info" ) ;
		}
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, " --title=\"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
		if ( aMessage && strlen(aMessage) )
		{
			strcat(lDialogString, " --text=\"") ;
			strcat(lDialogString, aMessage) ;
			strcat(lDialogString, "\"") ;
		}
		if ( zenity3Present ( ) )
		{
			strcat ( lDialogString , " --icon-name=dialog-" ) ;
			if ( aIconType && (! strcmp( "question" , aIconType )
			  || ! strcmp( "error" , aIconType )
			  || ! strcmp( "warning" , aIconType ) ) )
			{
				strcat ( lDialogString , aIconType ) ;
			}
			else
			{
				strcat ( lDialogString , "info" ) ;
			}
		}
		strcat ( lDialogString , ";if [ $? = 0 ];then echo 1;else echo 0;fi");
	}
	else if ( kdialogPresent() )
	{
		strcpy ( lDialogString , "kdialog --" ) ;
		if ( aDialogType && ( ! strcmp( "okcancel" , aDialogType )
		  || ! strcmp( "yesno" , aDialogType ) ) )
		{
			if ( aIconType && ( ! strcmp( "warning" , aIconType )
			  || ! strcmp( "error" , aIconType ) ) )
			{
				strcat ( lDialogString , "warning" ) ;
			}
			strcat ( lDialogString , "yesno" ) ;
		}
		else if ( aIconType && ! strcmp( "error" , aIconType ) )
		{
			strcat ( lDialogString , "error" ) ;
		}
		else if ( aIconType && ! strcmp( "warning" , aIconType ) )
		{
			strcat ( lDialogString , "sorry" ) ;
		}
		else
		{
			strcat ( lDialogString , "msgbox" ) ;
		}
		strcat ( lDialogString , " \"" ) ;
		if ( aMessage )
		{
			strcat ( lDialogString , aMessage ) ;
		}
		strcat ( lDialogString , "\"" ) ;
		if ( aDialogType && ! strcmp( "okcancel" , aDialogType ) )
		{
			strcat ( lDialogString ,
				" --yes-label Ok --no-label Cancel" ) ;
		}
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, " --title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
		strcat ( lDialogString , ";if [ $? = 0 ];then echo 1;else echo 0;fi");
	}
	else if ( ! xdialogPresent() && tkinter2Present ( ) )
	{
		strcpy ( lDialogString , gPython2Name ) ;
		if ( ! isatty ( 1 ) && isDarwin ( ) )
		{
			strcat ( lDialogString , " -i" ) ;  /* for osx without console */
		}

		strcat ( lDialogString ,
" -c \"import Tkinter,tkMessageBox;root=Tkinter.Tk();root.withdraw();");

		if ( isDarwin ( ) )
		{
			strcat ( lDialogString ,
"import os;os.system('''/usr/bin/osascript -e 'tell app \\\"Finder\\\" to set \
frontmost of process \\\"Python\\\" to true' ''');");
		}

		strcat ( lDialogString ,"res=tkMessageBox." ) ;
		if ( aDialogType && ! strcmp( "okcancel" , aDialogType ) )
		{
			strcat ( lDialogString , "askokcancel(" ) ;
			if ( aDefaultButton )
			{
				strcat ( lDialogString , "default=tkMessageBox.OK," ) ;
			}
			else
			{
				strcat ( lDialogString , "default=tkMessageBox.CANCEL," ) ;
			}
		}
		else if ( aDialogType && ! strcmp( "yesno" , aDialogType ) )
		{
			strcat ( lDialogString , "askyesno(" ) ;
			if ( aDefaultButton )
			{
				strcat ( lDialogString , "default=tkMessageBox.YES," ) ;
			}
			else
			{
				strcat ( lDialogString , "default=tkMessageBox.NO," ) ;
			}
		}
		else
		{
			strcat ( lDialogString , "showinfo(" ) ;
		}
		strcat ( lDialogString , "icon='" ) ;
		if ( aIconType && (! strcmp( "question" , aIconType )
		  || ! strcmp( "error" , aIconType )
		  || ! strcmp( "warning" , aIconType ) ) )
		{
			strcat ( lDialogString , aIconType ) ;
		}
		else
		{
			strcat ( lDialogString , "info" ) ;
		}
		strcat(lDialogString, "',") ;
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "title='") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "',") ;
		}
		if ( aMessage && strlen(aMessage) )
		{
			replaceSubStr ( aMessage , "\n" , "\\n" , lBuff ) ;
			strcat(lDialogString, "message='") ;
			strcat(lDialogString, lBuff) ;
			strcat(lDialogString, "'") ;
			lBuff[0]='\0';
		}
		strcat(lDialogString, ");\n\
if res==False :\n\tprint 0\n\
else :\n\tprint 1\n\"" ) ;
	}
	else if (!xdialogPresent() && !gdialogPresent() && gxmessagePresent() )
	{
		strcpy ( lDialogString , "gxmessage");
		if ( aDialogType && ! strcmp("okcancel" , aDialogType) )
		{
			strcpy ( lDialogString , " -buttons Ok:1,Cancel:0");
		}
		else if ( aDialogType && ! strcmp("yesno" , aDialogType) )
		{
			strcpy ( lDialogString , " -buttons Yes:1,No:0");
		}

		strcpy ( lDialogString , " -center \"");
		if ( aMessage && strlen(aMessage) )
		{
			strcat ( lDialogString , aMessage ) ;
		}
		strcat(lDialogString, "\"" ) ;
		if ( aTitle && strlen(aTitle) )
		{
			strcat ( lDialogString , " -title  \"");
			strcat ( lDialogString , aTitle ) ;
			strcat(lDialogString, "\"" ) ;
		}
	}
	else if (!xdialogPresent() && !gdialogPresent() && notifysendPresent()
			 && strcmp("okcancel" , aDialogType)
			 && strcmp("yesno" , aDialogType) )
	{
		strcpy ( lDialogString , "notify-send \"" ) ;
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, aTitle) ;
			strcat ( lDialogString , " | " ) ;
		}
		if ( aMessage && strlen(aMessage) )
		{
			strcat(lDialogString, aMessage) ;
		}
		strcat ( lDialogString , "\"" ) ;
	}
	else if (!xdialogPresent() && !gdialogPresent() && xmessagePresent()
		&& strcmp("okcancel" , aDialogType)
		&& strcmp("yesno" , aDialogType) )
	{
		strcpy ( lDialogString , "xmessage -center \"");
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\n\n" ) ;
		}
		if ( aMessage && strlen(aMessage) )
		{
			strcat(lDialogString, aMessage) ;
		}
		strcat(lDialogString, "\"" ) ;
	}
	else if ( xdialogPresent() || gdialogPresent()
		   || dialogName() || whiptailPresent() )
	{
		if ( xdialogPresent ( ) )
		{
			lWasGraphicDialog = 1 ;
			strcpy ( lDialogString , "(Xdialog " ) ;
		}
		else if ( gdialogPresent ( ) )
		{
			lWasGraphicDialog = 1 ;
			strcpy ( lDialogString , "(gdialog " ) ;
		}
		else if ( dialogName ( ) )
		{
			if ( isatty ( 1 ) )
			{
				strcpy ( lDialogString , "(dialog " ) ;
			}
			else
			{
				lWasXterm = 1 ;
				strcpy ( lDialogString , terminalName() ) ;
				strcat ( lDialogString , "'(" ) ;
				strcat ( lDialogString , dialogName() ) ;
				strcat ( lDialogString , " " ) ;
			}
		}
		else if ( isatty ( 1 ) )
		{
			strcpy ( lDialogString , "(whiptail " ) ;
		}
		else
		{
			lWasXterm = 1 ;
			strcpy ( lDialogString , terminalName() ) ;
			strcat ( lDialogString , "'(whiptail " ) ;
		}

		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "--title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\" ") ;
		}
		if ( aDialogType && ! strcmp( "okcancel" , aDialogType ) )
		{
			if ( ! aDefaultButton )
			{
				strcat ( lDialogString , "--defaultno " ) ;
			}
			strcat ( lDialogString ,
					"--yes-label \"Ok\" --no-label \"Cancel\" --yesno " ) ;
		}
		else if ( aDialogType && ! strcmp( "yesno" , aDialogType ) )
		{
			if ( ! aDefaultButton )
			{
				strcat ( lDialogString , "--defaultno " ) ;
			}
			strcat ( lDialogString , "--yesno " ) ;
		}
		else
		{
			strcat ( lDialogString , "--msgbox " ) ;

		}
		strcat ( lDialogString , "\"" ) ;
		if ( aMessage && strlen(aMessage) )
		{
			strcat(lDialogString, aMessage) ;
		}

		if ( lWasGraphicDialog )
		{
			strcat(lDialogString,
				   "\" 10 60 ) 2>&1;if [ $? = 0 ];then echo 1;else echo 0;fi");
		}
		else
		{
			strcat(lDialogString, "\" 10 60 >/dev/tty) 2>&1;if [ $? = 0 ];");
			if ( lWasXterm )
			{
				strcat ( lDialogString ,
					"then\n\techo 1\nelse\n\techo 0\nfi >/tmp/tinyfd.txt';\
cat /tmp/tinyfd.txt;rm /tmp/tinyfd.txt");
			}
			else
			{
			   strcat(lDialogString,
					  "then echo 1;else echo 0;fi;clear >/dev/tty");
			}
		}
	}
	else if ( ! isatty ( 1 ) && terminalName() )
	{
		strcpy ( lDialogString , terminalName() ) ;
		strcat ( lDialogString , "'" ) ;
		if ( !gWarningDisplayed )
		{
			gWarningDisplayed = 1 ;
			strcat ( lDialogString , "echo \"" ) ;
			strcat ( lDialogString, gTitle) ;
			strcat ( lDialogString , "\";" ) ;
			strcat ( lDialogString , "echo \"" ) ;
			strcat ( lDialogString, gMessageUnix) ;
			strcat ( lDialogString , "\";echo;echo;" ) ;
		}
		if ( aTitle && strlen(aTitle) )
		{
			strcat ( lDialogString , "echo \"" ) ;
			strcat ( lDialogString, aTitle) ;
			strcat ( lDialogString , "\";echo;" ) ;
		}
		if ( aMessage && strlen(aMessage) )
		{
			strcat ( lDialogString , "echo \"" ) ;
			strcat ( lDialogString, aMessage) ;
			strcat ( lDialogString , "\"; " ) ;
		}
		if ( aDialogType && !strcmp("yesno",aDialogType) )
		{
			strcat ( lDialogString , "echo -n \"y/n: \"; " ) ;
			strcat ( lDialogString , "stty raw -echo;" ) ;
			strcat ( lDialogString ,
				"answer=$( while ! head -c 1 | grep -i [ny];do true ;done);");
			strcat ( lDialogString ,
				"if echo \"$answer\" | grep -iq \"^y\";then\n");
			strcat ( lDialogString , "\techo 1\nelse\n\techo 0\nfi" ) ;
		}
		else if ( aDialogType && !strcmp("okcancel",aDialogType) )
		{
			strcat ( lDialogString , "echo -n \"[O]kay/[C]ancel: \"; " ) ;
			strcat ( lDialogString , "stty raw -echo;" ) ;
			strcat ( lDialogString ,
				"answer=$( while ! head -c 1 | grep -i [oc];do true ;done);");
			strcat ( lDialogString ,
				"if echo \"$answer\" | grep -iq \"^o\";then\n");
			strcat ( lDialogString , "\techo 1\nelse\n\techo 0\nfi" ) ;
		}
		else
		{
			strcat(lDialogString , "echo -n \"press any key to continue \"; ");
			strcat ( lDialogString , "stty raw -echo;" ) ;
			strcat ( lDialogString ,
				"answer=$( while ! head -c 1;do true ;done);echo 1");
		}
		strcat ( lDialogString ,
			" >/tmp/tinyfd.txt';cat /tmp/tinyfd.txt;rm /tmp/tinyfd.txt");
	}
	else
	{
		if ( !gWarningDisplayed )
		{
			gWarningDisplayed = 1 ;
			printf ("\n\n%s\n", gTitle);
			printf ("%s\n\n\n", gMessageUnix);
		}
		if ( aTitle && strlen(aTitle) )
		{
			printf ("%s\n\n", aTitle);
		}

		tcgetattr(0, &infoOri);
		tcgetattr(0, &info);
		info.c_lflag &= ~ICANON;
		info.c_cc[VMIN] = 1;
		info.c_cc[VTIME] = 0;
		tcsetattr(0, TCSANOW, &info);
		if ( aDialogType && !strcmp("yesno",aDialogType) )
		{
			do
			{
				if ( aMessage && strlen(aMessage) )
				{
					printf("%s\n",aMessage);
				}
				printf("y/n: ");
				lChar = tolower ( getchar() ) ;
				printf("\n\n");
			}
			while ( lChar != 'y' && lChar != 'n' );
			lResult = lChar == 'y' ? 1 : 0 ;
		}
		else if ( aDialogType && !strcmp("okcancel",aDialogType) )
		{
			do
			{
				if ( aMessage && strlen(aMessage) )
				{
					printf("%s\n",aMessage);
				}
				printf("[O]kay/[C]ancel: ");
				lChar = tolower ( getchar() ) ;
				printf("\n\n");
			}
			while ( lChar != 'o' && lChar != 'c' );
			lResult = lChar == 'o' ? 1 : 0 ;
		}
		else
		{
			if ( aMessage && strlen(aMessage) )
			{
				printf("%s\n\n",aMessage);
			}
			printf("press any key to continue ");
			getchar() ;
			printf("\n\n");
			lResult = 1 ;
		}
		tcsetattr(0, TCSANOW, &infoOri);
		return lResult ;
	}

	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	if ( ! ( lIn = popen ( lDialogString , "r" ) ) )
	{
		return 0 ;
	}
	while ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) != NULL )
	{}
	pclose ( lIn ) ;
	/* printf ( "lBuff: %s len: %lu \n" , lBuff , strlen(lBuff) ) ; //*/
	if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
	{
		lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
	}
	/* printf ( "lBuff1: %s len: %lu \n" , lBuff , strlen(lBuff) ) ; //*/
	lResult =  strcmp ( lBuff , "1" ) ? 0 : 1 ;
	/* printf ( "lResult: %d\n" , lResult ) ; //*/
	return lResult ;
}


/* returns NULL on cancel */
char const * tinyfd_inputBox(
	char const * const aTitle , /* NULL or "" */
	char const * const aMessage , /* NULL or "" may NOT contain \n nor \t */
	char const * const aDefaultInput ) /* "" , if NULL it's a passwordBox */
{
	static char lBuff[MAX_PATH_OR_CMD];
	char lDialogString[MAX_PATH_OR_CMD];
	FILE * lIn ;
	int lResult ;
	int lWasGdialog = 0 ;
	int lWasGraphicDialog = 0 ;
	int lWasXterm = 0 ;
	int lWasBasicXterm = 0 ;
	struct termios oldt ;
	struct termios newt ;
	lBuff[0]='\0';

	if ( osascriptPresent ( ) )
	{
		strcpy ( lDialogString , "osascript -e 'try' -e 'display dialog \"") ;
		if ( aMessage && strlen(aMessage) )
		{
			strcat(lDialogString, aMessage) ;
		}
		strcat(lDialogString, "\" ") ;
		strcat(lDialogString, "default answer \"") ;
		if ( aDefaultInput && strlen(aDefaultInput) )
		{
			strcat(lDialogString, aDefaultInput) ;
		}
		strcat(lDialogString, "\" ") ;
		if ( ! aDefaultInput )
		{
			strcat(lDialogString, "hidden answer true ") ;
		}
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "with title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\" ") ;
		}
		strcat(lDialogString, "with icon note' ") ;
		strcat(lDialogString, "-e '\"1\" & text returned of result' " );
		strcat(lDialogString, "-e 'on error number -128' " ) ;
		strcat(lDialogString, "-e '0' " );
		strcat(lDialogString, "-e 'end try'") ;
	}
	else if ( zenityPresent() )
	{
		strcpy ( lDialogString , "szAnswer=$(zenity --entry" ) ;
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, " --title=\"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
		if ( aMessage && strlen(aMessage) )
		{
			strcat(lDialogString, " --text=\"") ;
			strcat(lDialogString, aMessage) ;
			strcat(lDialogString, "\"") ;
		}
		if ( aDefaultInput )
		{
			if ( strlen(aDefaultInput) )
			{
				strcat(lDialogString, " --entry-text=\"") ;
				strcat(lDialogString, aDefaultInput) ;
				strcat(lDialogString, "\"") ;
			}
		}
		else
		{
			strcat(lDialogString, " --hide-text") ;
		}
		strcat ( lDialogString ,
				");if [ $? = 0 ];then echo 1$szAnswer;else echo 0$szAnswer;fi");
	}
	else if ( kdialogPresent() )
	{
		strcpy ( lDialogString , "szAnswer=$(kdialog" ) ;
		if ( ! aDefaultInput )
		{
			strcat(lDialogString, " --password ") ;
		}
		else
		{
			strcat(lDialogString, " --inputbox ") ;

		}
		strcat(lDialogString, "\"") ;
		if ( aMessage && strlen(aMessage) )

		{
			strcat(lDialogString, aMessage ) ;
		}
		strcat(lDialogString , "\" \"" ) ;
		if ( aDefaultInput && strlen(aDefaultInput) )
		{
			strcat(lDialogString, aDefaultInput ) ;
		}
		strcat(lDialogString , "\"" ) ;
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, " --title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
		strcat ( lDialogString ,
				");if [ $? = 0 ];then echo 1$szAnswer;else echo 0$szAnswer;fi");
	}
	else if ( ! xdialogPresent() && tkinter2Present ( ) )
	{
		strcpy ( lDialogString , gPython2Name ) ;
		if ( ! isatty ( 1 ) && isDarwin ( ) )
		{
			strcat ( lDialogString , " -i" ) ;  /* for osx without console */
		}

		strcat ( lDialogString ,
" -c \"import Tkinter,tkSimpleDialog;root=Tkinter.Tk();root.withdraw();");

		if ( isDarwin ( ) )
		{
			strcat ( lDialogString ,
"import os;os.system('''/usr/bin/osascript -e 'tell app \\\"Finder\\\" to set \
frontmost of process \\\"Python\\\" to true' ''');");
		}

		strcat ( lDialogString ,"res=tkSimpleDialog.askstring(" ) ;
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "title='") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "',") ;
		}
		if ( aMessage && strlen(aMessage) )
		{
			replaceSubStr ( aMessage , "\n" , "\\n" , lBuff ) ;
			strcat(lDialogString, "prompt='") ;
			strcat(lDialogString, lBuff) ;
			strcat(lDialogString, "',") ;
			lBuff[0]='\0';
		}
		if ( aDefaultInput )
		{
			if ( strlen(aDefaultInput) )
			{
				strcat(lDialogString, "initialvalue='") ;
				strcat(lDialogString, aDefaultInput) ;
				strcat(lDialogString, "',") ;
			}
		}
		else
		{
			strcat(lDialogString, "show='*'") ;
		}
		strcat(lDialogString, ");\nif res is None :\n\tprint 0");
		strcat(lDialogString, "\nelse :\n\tprint '1'+res\n\"" ) ;
	}
	else if (!xdialogPresent() && !gdialogPresent() && gxmessagePresent() )
	{
		strcpy ( lDialogString , "gxmessage -buttons Ok:1,Cancel:0 -center \"");
		if ( aMessage && strlen(aMessage) )
		{
			strcat ( lDialogString , aMessage ) ;
		}
		strcat(lDialogString, "\"" ) ;
		if ( aTitle && strlen(aTitle) )
		{
			strcat ( lDialogString , " -title  \"");
			strcat ( lDialogString , aTitle ) ;
			strcat(lDialogString, "\" " ) ;
		}
		strcat(lDialogString, " -entrytext \"" ) ;
		if ( aDefaultInput && strlen(aDefaultInput) )
		{
			strcat ( lDialogString , aDefaultInput ) ;
		}
		strcat(lDialogString, "\"" ) ;
	}
	else if ( xdialogPresent() || gdialogPresent()
		   || dialogName() || whiptailPresent() )
	{
		if ( xdialogPresent ( ) )
		{
			lWasGraphicDialog = 1 ;
			strcpy ( lDialogString , "(Xdialog " ) ;
		}
		else if ( gdialogPresent ( ) )
		{
			lWasGraphicDialog = 1 ;
			lWasGdialog = 1 ;
			strcpy ( lDialogString , "(gdialog " ) ;
		}
		else if ( dialogName ( ) )
		{
			if ( isatty ( 1 ) )
			{
				strcpy ( lDialogString , "(dialog " ) ;
			}
			else
			{
				lWasXterm = 1 ;
				strcpy ( lDialogString , terminalName() ) ;
				strcat ( lDialogString , "'(" ) ;
				strcat ( lDialogString , dialogName() ) ;
				strcat ( lDialogString , " " ) ;
			}
		}
		else if ( isatty ( 1 ) )
		{
			strcpy ( lDialogString , "(whiptail " ) ;
		}
		else
		{
			lWasXterm = 1 ;
			strcpy ( lDialogString , terminalName() ) ;
			strcat ( lDialogString , "'(whiptail " ) ;
		}


		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "--title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\" ") ;
		}
		if ( aDefaultInput || lWasGdialog )
		{
			strcat ( lDialogString , "--inputbox" ) ;
		}
		else
		{
			strcat ( lDialogString , "--passwordbox" ) ;
		}
		strcat ( lDialogString , " \"" ) ;
		if ( aMessage && strlen(aMessage) )
		{
			strcat(lDialogString, aMessage) ;
		}
		strcat(lDialogString,"\" 10 60 ") ;
		if ( aDefaultInput && strlen(aDefaultInput) )
		{
			strcat(lDialogString, "\"") ;
			strcat(lDialogString, aDefaultInput) ;
			strcat(lDialogString, "\" ") ;
		}
		if ( lWasGraphicDialog )
		{
			strcat(lDialogString,") 2>/tmp/tinyfd.txt;\
	if [ $? = 0 ];then tinyfdBool=1;else tinyfdBool=0;fi;\
	tinyfdRes=$(cat /tmp/tinyfd.txt);\
	rm /tmp/tinyfd.txt;echo $tinyfdBool$tinyfdRes") ;
		}
		else
		{
			strcat(lDialogString,">/dev/tty ) 2>/tmp/tinyfd.txt;\
	if [ $? = 0 ];then tinyfdBool=1;else tinyfdBool=0;fi;\
	tinyfdRes=$(cat /tmp/tinyfd.txt);\
	rm /tmp/tinyfd.txt;echo $tinyfdBool$tinyfdRes") ;
			if ( lWasXterm )
			{
			  strcat ( lDialogString ,
				" >/tmp/tinyfd0.txt';cat /tmp/tinyfd0.txt;rm /tmp/tinyfd0.txt");
			}
			else
			{
				strcat(lDialogString, "; clear >/dev/tty") ;
			}
		}
	}
	else if ( ! isatty ( 1 ) && terminalName() )
	{
		lWasBasicXterm = 1 ;
		strcpy ( lDialogString , terminalName() ) ;
		strcat ( lDialogString , "'" ) ;
		if ( !gWarningDisplayed )
		{
			gWarningDisplayed = 1 ;
			strcat ( lDialogString , "echo \"" ) ;
			strcat ( lDialogString, gTitle) ;
			strcat ( lDialogString , "\";" ) ;
			strcat ( lDialogString , "echo \"" ) ;
			strcat ( lDialogString, gMessageUnix) ;
			strcat ( lDialogString , "\";echo;echo;" ) ;
		}
		if ( aTitle && strlen(aTitle) )
		{
			strcat ( lDialogString , "echo \"" ) ;
			strcat ( lDialogString, aTitle) ;
			strcat ( lDialogString , "\";echo;" ) ;
		}

		strcat ( lDialogString , "echo \"" ) ;
		if ( aMessage && strlen(aMessage) )
		{
			strcat ( lDialogString, aMessage) ;
		}
		strcat ( lDialogString , "\";read " ) ;
		if ( ! aDefaultInput )
		{
			strcat ( lDialogString , "-s " ) ;
		}
		strcat ( lDialogString , "-p \"" ) ;
		strcat(lDialogString , "(esc+enter to cancel): \" ANSWER " ) ;
		strcat(lDialogString , ";echo 1$ANSWER >/tmp/tinyfd.txt';" ) ;
		strcat(lDialogString , "cat -v /tmp/tinyfd.txt;rm /tmp/tinyfd.txt");
	}
	else if ( isatty ( 1 ) )
	{
		if ( !gWarningDisplayed )
		{
			gWarningDisplayed = 1 ;
			printf ("\n\n%s\n", gTitle);
			printf ("%s\n\n\n", gMessageUnix);
		}
		if ( aTitle && strlen(aTitle) )
		{
			printf ("%s\n\n", aTitle);
		}
		if ( aMessage && strlen(aMessage) )
		{
			printf("%s\n",aMessage);
		}
		printf("(esc+enter to cancel): ");
		if ( ! aDefaultInput )
		{
			tcgetattr(STDIN_FILENO, & oldt) ;
			newt = oldt ;
			newt.c_lflag &= ~ECHO ;
			tcsetattr(STDIN_FILENO, TCSANOW, & newt);
		}
		fgets(lBuff, MAX_PATH_OR_CMD, stdin);
		if ( ! aDefaultInput )
		{
			tcsetattr(STDIN_FILENO, TCSANOW, & oldt);
			printf ("\n");
		}
		printf ("\n");
		if ( strchr(lBuff,27) )
		{
			return NULL ;
		}
		if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
		{
			lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
		}
		return lBuff ;
	}
	else
	{
		if ( !gWarningDisplayed )
		{
			gWarningDisplayed = 1 ;
			tinyfd_messageBox ( gTitle , gMessageUnix , "ok", "error" , 1 ) ;
		}
		return NULL ;
	}

	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	if ( ! ( lIn = popen ( lDialogString , "r" ) ) )
	{
		return NULL ;
	}
	while ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) != NULL )
	{}
	pclose ( lIn ) ;
	/* printf ( "len Buff: %lu\n" , strlen(lBuff) ) ; //*/
	/* printf ( "lBuff0: %s\n" , lBuff ) ; //*/
	if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
	{
		lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
	}
	/* printf ( "lBuff1: %s len: %lu \n" , lBuff , strlen(lBuff) ) ; //*/
	if ( lWasBasicXterm )
	{
		if ( strstr(lBuff,"^[") ) /* esc was pressed */
		{
			return NULL ;
		}
	}
	lResult =  strncmp ( lBuff , "1" , 1) ? 0 : 1 ;
	/* printf ( "lResult: %d \n" , lResult ) ; //*/
	if ( ! lResult )
	{
		return NULL ;
	}
	/* printf ( "lBuff+1: %s\n" , lBuff+1 ) ; //*/
	return lBuff+1 ;
}


char const * tinyfd_saveFileDialog (
	char const * const aTitle , /* NULL or "" */
	char const * const aDefaultPathAndFile , /* NULL or "" */
	int const aNumOfFilterPatterns , /* 0 */
	char const * const * const aFilterPatterns , /* NULL or {"*.jpg","*.png"} */
	char const * const aSingleFilterDescription ) /* NULL or "image files" */
{
	static char lBuff [ MAX_PATH_OR_CMD ] ;
	char lDialogString [ MAX_PATH_OR_CMD ] ;
	char lString [ MAX_PATH_OR_CMD ] ;
	int i ;
	int lWasGraphicDialog = 0 ;
	int lWasXterm = 0 ;
	char const * p ;
	DIR * lDir ;
	FILE * lIn ;
	lBuff[0]='\0';

	if ( osascriptPresent ( ) )
	{
		strcpy ( lDialogString ,
				"osascript -e 'POSIX path of ( choose file name " );
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "with prompt \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\" ") ;
		}
		getPathWithoutFinalSlash ( lString , aDefaultPathAndFile ) ;
		if ( strlen(lString) )
		{
			strcat(lDialogString, "default location \"") ;
			strcat(lDialogString, lString ) ;
			strcat(lDialogString , "\" " ) ;
		}
		getLastName ( lString , aDefaultPathAndFile ) ;
		if ( strlen(lString) )
		{
			strcat(lDialogString, "default name \"") ;
			strcat(lDialogString, lString ) ;
			strcat(lDialogString , "\" " ) ;
		}
		strcat ( lDialogString , ")'" ) ;
	}
	else if ( zenityPresent() )
	{
		strcpy ( lDialogString ,
				"zenity --file-selection --save --confirm-overwrite" ) ;
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, " --title=\"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
		if ( aDefaultPathAndFile && strlen(aDefaultPathAndFile) )
		{
			strcat(lDialogString, " --filename=\"") ;
			strcat(lDialogString, aDefaultPathAndFile) ;
			strcat(lDialogString, "\"") ;
		}
		if ( aNumOfFilterPatterns > 0 )
		{
			strcat ( lDialogString , " --file-filter='" ) ;
			if ( aSingleFilterDescription && strlen(aSingleFilterDescription) )
			{
				strcat ( lDialogString , aSingleFilterDescription ) ;
				strcat ( lDialogString , " | " ) ;
			}
			for ( i = 0 ; i < aNumOfFilterPatterns ; i ++ )
			{
				strcat ( lDialogString , aFilterPatterns [ i ] ) ;
				strcat ( lDialogString , " " ) ;
			}
			strcat ( lDialogString , "' --file-filter='All files | *'" ) ;
		}
	}
	else if ( kdialogPresent() )
	{
		strcpy ( lDialogString , "kdialog --getsavefilename" ) ;
		if ( aDefaultPathAndFile && strlen(aDefaultPathAndFile) )
		{
			strcat(lDialogString, " \"") ;
			strcat(lDialogString, aDefaultPathAndFile ) ;
			strcat(lDialogString , "\"" ) ;
		}
		else
		{
			strcat(lDialogString, " :" ) ;
		}
		if ( aNumOfFilterPatterns > 0 )
		{
			strcat(lDialogString , " \"" ) ;
			for ( i = 0 ; i < aNumOfFilterPatterns ; i ++ )
			{
				strcat ( lDialogString , aFilterPatterns [ i ] ) ;
				strcat ( lDialogString , " " ) ;
			}
			if ( aSingleFilterDescription && strlen(aSingleFilterDescription) )
			{
				strcat ( lDialogString , " | " ) ;
				strcat ( lDialogString , aSingleFilterDescription ) ;
			}
			strcat ( lDialogString , "\"" ) ;
		}
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, " --title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
	}
	else if ( ! xdialogPresent() && tkinter2Present ( ) )
	{

		strcpy ( lDialogString , gPython2Name ) ;
		if ( ! isatty ( 1 ) && isDarwin ( ))
		{
			strcat ( lDialogString , " -i" ) ;  /* for osx without console */
		}
		strcat ( lDialogString ,
" -c \"import Tkinter,tkFileDialog;root=Tkinter.Tk();root.withdraw();");

		if ( isDarwin ( ) )
		{
			strcat ( lDialogString ,
"import os;os.system('''/usr/bin/osascript -e 'tell app \\\"Finder\\\" to set\
 frontmost of process \\\"Python\\\" to true' ''');");
		}

		strcat ( lDialogString , "print tkFileDialog.asksaveasfilename(");
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "title='") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "',") ;
		}
		if ( aDefaultPathAndFile && strlen(aDefaultPathAndFile) )
		{
			getPathWithoutFinalSlash ( lString , aDefaultPathAndFile ) ;
			if ( strlen(lString) )
			{
				strcat(lDialogString, "initialdir='") ;
				strcat(lDialogString, lString ) ;
				strcat(lDialogString , "'," ) ;
			}
			getLastName ( lString , aDefaultPathAndFile ) ;
			if ( strlen(lString) )
			{
				strcat(lDialogString, "initialfile='") ;
				strcat(lDialogString, lString ) ;
				strcat(lDialogString , "'," ) ;
			}
		}
		if ( ( aNumOfFilterPatterns > 1 )
		  || ( (aNumOfFilterPatterns == 1) /* test because poor osx behaviour */
			&& ( aFilterPatterns[0][strlen(aFilterPatterns[0])-1] != '*' ) ) )
		{
			strcat(lDialogString , "filetypes=(" ) ;
			strcat ( lDialogString , "('" ) ;
			if ( aSingleFilterDescription && strlen(aSingleFilterDescription) )
			{
				strcat ( lDialogString , aSingleFilterDescription ) ;
			}
			strcat ( lDialogString , "',(" ) ;
			for ( i = 0 ; i < aNumOfFilterPatterns ; i ++ )
			{
				strcat ( lDialogString , "'" ) ;
				strcat ( lDialogString , aFilterPatterns [ i ] ) ;
				strcat ( lDialogString , "'," ) ;
			}
			strcat ( lDialogString , "))," ) ;
			strcat ( lDialogString , "('All files','*'))" ) ;
		}
		strcat ( lDialogString , ")\"" ) ;
	}
	else if ( xdialogPresent() || dialogName() )
	{
		if ( xdialogPresent ( ) )
		{
			lWasGraphicDialog = 1 ;
			strcpy ( lDialogString , "(Xdialog " ) ;
		}
		else if ( isatty ( 1 ) )
		{
			strcpy ( lDialogString , "@echo lala;(dialog " ) ;
		}
		else
		{
			lWasXterm = 1 ;
			strcpy ( lDialogString , terminalName() ) ;
			strcat ( lDialogString , "'(" ) ;
			strcat ( lDialogString , dialogName() ) ;
			strcat ( lDialogString , " " ) ;
		}

		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "--title \"") ;
			/*strcat(lDialogString, aTitle) ;*/
			strcat(lDialogString, "tab =move focus | spacebar =select | add / =populate") ;
			strcat(lDialogString, "\" ") ;
		}
		strcat ( lDialogString , "--fselect \"" ) ;
		if ( aDefaultPathAndFile && strlen(aDefaultPathAndFile) )
		{
			if ( ! strchr(aDefaultPathAndFile, '/') )
			{
				strcat(lDialogString, "./") ;
			}
			strcat(lDialogString, aDefaultPathAndFile) ;
		}
		else if ( ! isatty ( 1 ) && !lWasGraphicDialog )
		{
			strcat(lDialogString, getenv("HOME")) ;
			strcat(lDialogString, "/") ;
		}
		else
		{
			strcat(lDialogString, "./") ;
		}

		if ( lWasGraphicDialog )
		{
			strcat(lDialogString, "\" 0 60 ) 2>&1 ") ;
		}
		else
		{
			strcat(lDialogString, "\" 0 60  >/dev/tty) ") ;
			if ( lWasXterm )
			{
			  strcat ( lDialogString ,
				"2>/tmp/tinyfd.txt';cat /tmp/tinyfd.txt;rm /tmp/tinyfd.txt");
			}
			else
			{
				strcat(lDialogString, "2>&1 ; clear >/dev/tty") ;
			}
		}
	}
	else
	{
		p = tinyfd_inputBox ( aTitle , "Save file" , "" ) ;
		getPathWithoutFinalSlash ( lString , p ) ;
		if ( strlen ( lString ) && ! dirExists ( lString ) )
		{
			return NULL ;
		}
		getLastName(lString,p);
		if ( ! strlen(lString) )
		{
			return NULL;
		}
		return p ;
	}

	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	if ( ! ( lIn = popen ( lDialogString , "r" ) ) )
	{
		return NULL ;
	}
	while ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) != NULL )
	{}
	pclose ( lIn ) ;
	if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
	{
		lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
	}
	/* printf ( "lBuff: %s\n" , lBuff ) ; //*/
	if ( ! strlen(lBuff) )
	{
		return NULL;
	}
	getPathWithoutFinalSlash ( lString , lBuff ) ;
	if ( strlen ( lString ) && ! dirExists ( lString ) )
	{
		return NULL ;
	}
	getLastName(lString,lBuff);
	if ( ! filenameValid(lString) )
	{
		return NULL;
	}
	return lBuff ;
}


/* in case of multiple files, the separator is | */
char const * tinyfd_openFileDialog (
	char const * const aTitle , /* NULL or "" */
	char const * const aDefaultPathAndFile , /* NULL or "" */
	int const aNumOfFilterPatterns , /* 0 */
	char const * const * const aFilterPatterns , /* NULL or {"*.jpg","*.png"} */
	char const * const aSingleFilterDescription , /* NULL or "image files" */
	int const aAllowMultipleSelects ) /* 0 or 1 */
{
	static char lBuff [ MAX_MULTIPLE*MAX_PATH_OR_CMD ] ;
	char lDialogString [ MAX_PATH_OR_CMD ] ;
	char lString [ MAX_PATH_OR_CMD ] ;
	int i ;
	FILE * lIn ;
	char * p ;
	char const * p2 ;
	int lWasKdialog = 0 ;
	int lWasGraphicDialog = 0 ;
	int lWasXterm = 0 ;
	lBuff[0]='\0';

	if ( osascriptPresent ( ) )
	{
		strcpy ( lDialogString , "osascript -e '" );
		if ( ! aAllowMultipleSelects )
		{
			strcat ( lDialogString , "POSIX path of ( " );
		}
		else
		{
			strcat ( lDialogString , "set mylist to " );
		}
		strcat ( lDialogString , "choose file " );
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "with prompt \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\" ") ;
		}
		getPathWithoutFinalSlash ( lString , aDefaultPathAndFile ) ;
		if ( strlen(lString) )
		{
			strcat(lDialogString, "default location \"") ;
			strcat(lDialogString, lString ) ;
			strcat(lDialogString , "\" " ) ;
		}
		if ( aNumOfFilterPatterns > 0 )
		{
			strcat(lDialogString , "of type {\"" );
			strcat ( lDialogString , aFilterPatterns [ 0 ] ) ;
			strcat ( lDialogString , "\"" ) ;
			for ( i = 1 ; i < aNumOfFilterPatterns ; i ++ )
			{
				strcat ( lDialogString , ",\"" ) ;
				strcat ( lDialogString , aFilterPatterns [ i ]) ;
				strcat ( lDialogString , "\"" ) ;
			}
			strcat ( lDialogString , "} " ) ;
		}
		if ( aAllowMultipleSelects )
		{
			strcat ( lDialogString , "multiple selections allowed true ' " ) ;
			strcat ( lDialogString ,
					"-e 'set mystring to POSIX path of item 1 of mylist' " );
			strcat ( lDialogString ,
					"-e 'repeat with  i from 2 to the count of mylist' " );
			strcat ( lDialogString , "-e 'set mystring to mystring & \"|\"' " );
			strcat ( lDialogString ,
			"-e 'set mystring to mystring & POSIX path of item i of mylist' " );
			strcat ( lDialogString , "-e 'end repeat' " );
			strcat ( lDialogString , "-e 'mystring'" );
		}
		else
		{
			strcat ( lDialogString , ")'" ) ;
		}
	}
	else if ( zenityPresent() )
	{
		strcpy ( lDialogString ,"zenity --file-selection" ) ;
		if ( aAllowMultipleSelects )
		{
			strcat ( lDialogString , " --multiple" ) ;
		}
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, " --title=\"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
		if ( aDefaultPathAndFile && strlen(aDefaultPathAndFile) )
		{
			strcat(lDialogString, " --filename=\"") ;
			strcat(lDialogString, aDefaultPathAndFile) ;
			strcat(lDialogString, "\"") ;
		}
		if ( aNumOfFilterPatterns > 0 )
		{
			strcat ( lDialogString , " --file-filter='" ) ;
			if ( aSingleFilterDescription && strlen(aSingleFilterDescription) )
			{
				strcat ( lDialogString , aSingleFilterDescription ) ;
				strcat ( lDialogString , " | " ) ;
			}
			for ( i = 0 ; i < aNumOfFilterPatterns ; i ++ )
			{
				strcat ( lDialogString , aFilterPatterns [ i ] ) ;
				strcat ( lDialogString , " " ) ;
			}
			strcat ( lDialogString , "' --file-filter='All files | *'" ) ;
		}
	}
	else if ( kdialogPresent() )
	{
		lWasKdialog = 1 ;
		strcpy ( lDialogString , "kdialog --getopenfilename" ) ;
		if ( aDefaultPathAndFile && strlen(aDefaultPathAndFile) )
		{
			strcat(lDialogString, " \"") ;
			strcat(lDialogString, aDefaultPathAndFile ) ;

			strcat(lDialogString , "\"" ) ;
		}
		else
		{
			strcat(lDialogString, " :" ) ;
		}
		if ( aNumOfFilterPatterns > 0 )
		{
			strcat(lDialogString , " \"" ) ;
			for ( i = 0 ; i < aNumOfFilterPatterns ; i ++ )
			{
				strcat ( lDialogString , aFilterPatterns [ i ] ) ;
				strcat ( lDialogString , " " ) ;
			}
			if ( aSingleFilterDescription && strlen(aSingleFilterDescription) )
			{
				strcat ( lDialogString , " | " ) ;
				strcat ( lDialogString , aSingleFilterDescription ) ;
			}
			strcat ( lDialogString , "\"" ) ;
		}
		if ( aAllowMultipleSelects )
		{
			strcat ( lDialogString , " --multiple --separate-output" ) ;
		}
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, " --title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
	}
	else if ( ! xdialogPresent() && tkinter2Present ( ) )
	{
		strcpy ( lDialogString , gPython2Name ) ;
		if ( ! isatty ( 1 ) && isDarwin ( ) )
		{
			strcat ( lDialogString , " -i" ) ;  /* for osx without console */
		}
		strcat ( lDialogString ,
" -c \"import Tkinter,tkFileDialog;root=Tkinter.Tk();root.withdraw();");

		if ( isDarwin ( ) )
		{
			strcat ( lDialogString ,
"import os;os.system('''/usr/bin/osascript -e 'tell app \\\"Finder\\\" to set \
frontmost of process \\\"Python\\\" to true' ''');");
		}
		strcat ( lDialogString , "lFiles=tkFileDialog.askopenfilename(");
		if ( aAllowMultipleSelects )
		{
			strcat ( lDialogString , "multiple=1," ) ;
		}
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "title='") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "',") ;
		}
		if ( aDefaultPathAndFile && strlen(aDefaultPathAndFile) )
		{
			getPathWithoutFinalSlash ( lString , aDefaultPathAndFile ) ;
			if ( strlen(lString) )
			{
				strcat(lDialogString, "initialdir='") ;
				strcat(lDialogString, lString ) ;
				strcat(lDialogString , "'," ) ;
			}
			getLastName ( lString , aDefaultPathAndFile ) ;
			if ( strlen(lString) )
			{
				strcat(lDialogString, "initialfile='") ;
				strcat(lDialogString, lString ) ;
				strcat(lDialogString , "'," ) ;
			}
		}
		if ( ( aNumOfFilterPatterns > 1 )
		  || ( ( aNumOfFilterPatterns == 1 ) /*test because poor osx behaviour*/
			&& ( aFilterPatterns[0][strlen(aFilterPatterns[0])-1] != '*' ) ) )
		{
			strcat(lDialogString , "filetypes=(" ) ;
			strcat ( lDialogString , "('" ) ;
			if ( aSingleFilterDescription && strlen(aSingleFilterDescription) )
			{
				strcat ( lDialogString , aSingleFilterDescription ) ;
			}
			strcat ( lDialogString , "',(" ) ;
			for ( i = 0 ; i < aNumOfFilterPatterns ; i ++ )
			{
				strcat ( lDialogString , "'" ) ;
				strcat ( lDialogString , aFilterPatterns [ i ] ) ;
				strcat ( lDialogString , "'," ) ;
			}
			strcat ( lDialogString , "))," ) ;
			strcat ( lDialogString , "('All files','*'))" ) ;
		}
		strcat ( lDialogString , ");\
\nif not isinstance(lFiles, tuple):\n\tprint lFiles\nelse:\
\n\tlFilesString=''\n\tfor lFile in lFiles:\n\t\tlFilesString+=str(lFile)+'|'\
\n\tprint lFilesString[:-1]\n\"" ) ;
	}
	else if ( xdialogPresent() || dialogName() )
	{
		if ( xdialogPresent ( ) )
		{
			lWasGraphicDialog = 1 ;
			strcpy ( lDialogString , "(Xdialog " ) ;
		}
		else if ( isatty ( 1 ) )
		{
			strcpy ( lDialogString , "(dialog " ) ;
		}
		else
		{
			lWasXterm = 1 ;
			strcpy ( lDialogString , terminalName() ) ;
			strcat ( lDialogString , "'(" ) ;
			strcat ( lDialogString , dialogName() ) ;
			strcat ( lDialogString , " " ) ;
		}

		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "--title \"") ;
			/*strcat(lDialogString, aTitle) ;*/
			strcat(lDialogString, "tab =move focus | spacebar =select | add / =populate") ;
			strcat(lDialogString, "\" ") ;
		}
		strcat ( lDialogString , "--fselect \"" ) ;
		if ( aDefaultPathAndFile && strlen(aDefaultPathAndFile) )
		{
			if ( ! strchr(aDefaultPathAndFile, '/') )
			{
				strcat(lDialogString, "./") ;
			}
			strcat(lDialogString, aDefaultPathAndFile) ;
		}
		else if ( ! isatty ( 1 ) && !lWasGraphicDialog )
		{
			strcat(lDialogString, getenv("HOME")) ;
			strcat(lDialogString, "/");
		}
		else
		{
			strcat(lDialogString, "./") ;
		}

		if ( lWasGraphicDialog )
		{
			strcat(lDialogString, "\" 0 60 ) 2>&1 ") ;
		}
		else
		{
			strcat(lDialogString, "\" 0 60  >/dev/tty) ") ;
			if ( lWasXterm )
			{
				strcat ( lDialogString ,
				"2>/tmp/tinyfd.txt';cat /tmp/tinyfd.txt;rm /tmp/tinyfd.txt");
			}
			else
			{
				strcat(lDialogString, "2>&1 ; clear >/dev/tty") ;
			}
		}
	}
	else
	{
		p2 = tinyfd_inputBox(aTitle, "Open file","");
		if ( ! fileExists (p2) )
		{
			return NULL ;
		}
		return p2 ;
	}

	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	if ( ! ( lIn = popen ( lDialogString , "r" ) ) )
	{
		return NULL ;
	}
	lBuff[0]='\0';
	p=lBuff;
	while ( fgets ( p , sizeof ( lBuff ) , lIn ) != NULL )
	{
		p += strlen ( p );
	}
	pclose ( lIn ) ;
	if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
	{
		lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
	}
	/* printf ( "lBuff: %s\n" , lBuff ) ; //*/
	if ( lWasKdialog && aAllowMultipleSelects )
	{
		p = lBuff ;
		while ( ( p = strchr ( p , '\n' ) ) )
			* p = '|' ;
	}
	/* printf ( "lBuff2: %s\n" , lBuff ) ; //*/
	if ( ! strlen ( lBuff )  )
	{
		return NULL;
	}
	if ( aAllowMultipleSelects && strchr(lBuff, '|') )
	{
		p2 = ensureFilesExist( lBuff , lBuff ) ;
	}
	else if ( fileExists (lBuff) )
	{
		p2 = lBuff ;
	}
	else
	{
		return NULL ;
	}
	/* printf ( "lBuff3: %s\n" , p2 ) ; //*/

	return p2 ;
}


char const * tinyfd_selectFolderDialog (
	char const * const aTitle , /* "" */

	char const * const aDefaultPath ) /* "" */
{
	static char lBuff [ MAX_PATH_OR_CMD ] ;
	char lDialogString [ MAX_PATH_OR_CMD ] ;
	DIR * lDir ;
	FILE * lIn ;
	char const * p ;
	int lWasGraphicDialog = 0 ;
	int lWasXterm = 0 ;
	lBuff[0]='\0';

	if ( osascriptPresent ( ))
	{
		strcpy(lDialogString ,"osascript -e 'POSIX path of ( choose folder ");
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "with prompt \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\" ") ;
		}
		if ( aDefaultPath && strlen(aDefaultPath) )
		{
			strcat(lDialogString, "default location \"") ;
			strcat(lDialogString, aDefaultPath ) ;
			strcat(lDialogString , "\" " ) ;
		}
		strcat ( lDialogString , ")'" ) ;
	}
	else if ( zenityPresent() )
	{
		strcpy ( lDialogString , "zenity --file-selection --directory" ) ;
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, " --title=\"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
		if ( aDefaultPath && strlen(aDefaultPath) )
		{
			strcat(lDialogString, " --filename=\"") ;
			strcat(lDialogString, aDefaultPath) ;
			strcat(lDialogString, "\"") ;
		}
	}
	else if ( kdialogPresent() )
	{
		strcpy ( lDialogString , "kdialog --getexistingdirectory" ) ;
		if ( aDefaultPath && strlen(aDefaultPath) )
		{
			strcat(lDialogString, " \"") ;
			strcat(lDialogString, aDefaultPath ) ;
			strcat(lDialogString , "\"" ) ;
		}
		else
		{
			strcat(lDialogString, " :" ) ;
		}
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, " --title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
	}
	else if ( ! xdialogPresent() && tkinter2Present ( ) )
	{
		strcpy ( lDialogString , gPython2Name ) ;
		if ( ! isatty ( 1 ) && isDarwin ( ) )
		{
			strcat ( lDialogString , " -i" ) ;  /* for osx without console */
		}
		strcat ( lDialogString ,
" -c \"import Tkinter,tkFileDialog;root=Tkinter.Tk();root.withdraw();");

		if ( isDarwin ( ) )
		{
			strcat ( lDialogString ,
"import os;os.system('''/usr/bin/osascript -e 'tell app \\\"Finder\\\" to set \
frontmost of process \\\"Python\\\" to true' ''');");
		}

		strcat ( lDialogString , "print tkFileDialog.askdirectory(");
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "title='") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "',") ;
		}
		if ( aDefaultPath && strlen(aDefaultPath) )
		{
				strcat(lDialogString, "initialdir='") ;
				strcat(lDialogString, aDefaultPath ) ;
				strcat(lDialogString , "'" ) ;
		}
		strcat ( lDialogString , ")\"" ) ;
	}
	else if ( xdialogPresent() || dialogName() )
	{
		if ( xdialogPresent ( ) )
		{
			lWasGraphicDialog = 1 ;
			strcpy ( lDialogString , "(Xdialog " ) ;
		}
		else if ( isatty ( 1 ) )
		{
			strcpy ( lDialogString , "(dialog " ) ;
		}
		else
		{
			lWasXterm = 1 ;
			strcpy ( lDialogString , terminalName() ) ;
			strcat ( lDialogString , "'(" ) ;
			strcat ( lDialogString , dialogName() ) ;
			strcat ( lDialogString , " " ) ;
		}

		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, "--title \"") ;
			/*strcat(lDialogString, aTitle) ;*/
			strcat(lDialogString, "tab =move focus | spacebar =select | add / =populate") ;
			strcat(lDialogString, "\" ") ;
		}
		strcat ( lDialogString , "--dselect \"" ) ;
		if ( aDefaultPath && strlen(aDefaultPath) )
		{
			strcat(lDialogString, aDefaultPath) ;
			ensureFinalSlash(lDialogString);
		}
		else if ( ! isatty ( 1 ) && !lWasGraphicDialog )
		{
			strcat(lDialogString, getenv("HOME")) ;
			strcat(lDialogString, "/");
		}
		else
		{
			strcat(lDialogString, "./") ;
		}

		if ( lWasGraphicDialog )
		{
			strcat(lDialogString, "\" 0 60 ) 2>&1 ") ;
		}
		else
		{
			strcat(lDialogString, "\" 0 60  >/dev/tty) ") ;
			if ( lWasXterm )
			{
			  strcat ( lDialogString ,
				"2>/tmp/tinyfd.txt';cat /tmp/tinyfd.txt;rm /tmp/tinyfd.txt");
			}
			else
			{
				strcat(lDialogString, "2>&1 ; clear >/dev/tty") ;
			}
		}
	}
	else
	{
		p = tinyfd_inputBox(aTitle, "Select folder","");
		if ( !p || ! strlen ( p ) || ! dirExists ( p ) )
		{
			return NULL ;
		}
		return p ;
	}
	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	if ( ! ( lIn = popen ( lDialogString , "r" ) ) )
	{
		return NULL ;
	}
	while ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) != NULL )
	{}
	pclose ( lIn ) ;
	if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
	{
		lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
	}
	/* printf ( "lBuff: %s\n" , lBuff ) ; //*/
	if ( ! strlen ( lBuff ) || ! dirExists ( lBuff ) )
	{
		return NULL ;
	}
	return lBuff ;
}


/* returns the hexcolor as a string "#FF0000" */
/* aoResultRGB also contains the result */
/* aDefaultRGB is used only if aDefaultHexRGB is NULL */
/* aDefaultRGB and aoResultRGB can be the same array */
char const * tinyfd_colorChooser(
	char const * const aTitle , /* NULL or "" */
	char const * const aDefaultHexRGB , /* NULL or "#FF0000"*/
	unsigned char const aDefaultRGB[3] , /* { 0 , 255 , 255 } */
	unsigned char aoResultRGB[3] ) /* { 0 , 0 , 0 } */
{
	static char lBuff [ 16 ] ;
	char lTmp [ 16 ] ;
	char lDialogString [ MAX_PATH_OR_CMD ] ;
	char lDefaultHexRGB[8];
	char * lpDefaultHexRGB;
	unsigned char lDefaultRGB[3];
	char const * p;
	FILE * lIn ;
	int i ;
	int lWasZenity3 = 0 ;
	int lWasOsascript = 0 ;
	int lWasXdialog = 0 ;
	lBuff[0]='\0';

	if ( aDefaultHexRGB )
	{
		Hex2RGB ( aDefaultHexRGB , lDefaultRGB ) ;
		lpDefaultHexRGB = (char *) aDefaultHexRGB ;
	}
	else
	{
		lDefaultRGB[0]=aDefaultRGB[0];
		lDefaultRGB[1]=aDefaultRGB[1];
		lDefaultRGB[2]=aDefaultRGB[2];
		RGB2Hex( aDefaultRGB , lDefaultHexRGB ) ;
		lpDefaultHexRGB = (char *) lDefaultHexRGB ;
	}

	if ( osascriptPresent ( ) )
	{
		lWasOsascript = 1 ;
		strcpy ( lDialogString , "osascript -e 'tell app (path to frontmost \
application as Unicode text) to set mycolor to choose color default color {");
		sprintf(lTmp, "%d", 256 * lDefaultRGB[0] ) ;
		strcat(lDialogString, lTmp ) ;
		strcat(lDialogString, "," ) ;
		sprintf(lTmp, "%d", 256 * lDefaultRGB[1] ) ;
		strcat(lDialogString, lTmp ) ;
		strcat(lDialogString, "," ) ;
		sprintf(lTmp, "%d", 256 * lDefaultRGB[2] ) ;
		strcat(lDialogString, lTmp ) ;
		strcat(lDialogString, "}' " ) ;
		strcat ( lDialogString ,
"-e 'set mystring to ((item 1 of mycolor)/256 as integer) as string' " );
		strcat ( lDialogString ,
"-e 'repeat with i from 2 to the count of mycolor' " );
		strcat ( lDialogString ,
"-e 'set mystring to mystring & \" \" & \
((item i of mycolor)/256 as integer) as string' " );
		strcat ( lDialogString , "-e 'end repeat' " );
		strcat ( lDialogString , "-e 'mystring'");
	}
	else if ( zenity3Present() )
	{
		lWasZenity3 = 1 ;
		sprintf ( lDialogString ,
"zenity --color-selection --show-palette --color=%s" , lpDefaultHexRGB ) ;
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, " --title=\"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
	}
	else if ( kdialogPresent() )
	{
		sprintf ( lDialogString ,
"kdialog --getcolor --default '%s'" , lpDefaultHexRGB ) ;
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, " --title \"") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "\"") ;
		}
	}
	else if ( xdialogPresent() )
	{
		lWasXdialog = 1 ;
		strcpy ( lDialogString , "Xdialog --colorsel \"" ) ;
		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, aTitle) ;
		}
		strcat(lDialogString, "\" 0 60 ") ;
		sprintf(lTmp,"%hhu %hhu %hhu",lDefaultRGB[0],
				lDefaultRGB[1],lDefaultRGB[2]);
		strcat(lDialogString, lTmp) ;
		strcat(lDialogString, " 2>&1");
	}
	else if ( tkinter2Present ( ) )
	{
		strcpy ( lDialogString , gPython2Name ) ;
		if ( ! isatty ( 1 ) && isDarwin ( ) )
		{
			strcat ( lDialogString , " -i" ) ;  /* for osx without console */
		}

		strcat ( lDialogString ,
" -c \"import Tkinter,tkColorChooser;root=Tkinter.Tk();root.withdraw();");

		if ( isDarwin ( ) )
		{
			strcat ( lDialogString ,
"import os;os.system('''osascript -e 'tell app \\\"Finder\\\" to set \
frontmost of process \\\"Python\\\" to true' ''');");
		}

		strcat ( lDialogString , "res=tkColorChooser.askcolor(color='" ) ;
		strcat(lDialogString, lpDefaultHexRGB ) ;
		strcat(lDialogString, "'") ;


		if ( aTitle && strlen(aTitle) )
		{
			strcat(lDialogString, ",title='") ;
			strcat(lDialogString, aTitle) ;
			strcat(lDialogString, "'") ;
		}
		strcat ( lDialogString , ");\
\nif res[1] is not None:\n\tprint res[1]\"" ) ;
	}
	else
	{
		p = tinyfd_inputBox(aTitle,
				"Enter hex rgb color (i.e. #f5ca20)",lpDefaultHexRGB);
		if ( !p || (strlen(p) != 7) || (p[0] != '#') )
		{
			return NULL ;
		}
		for ( i = 1 ; i < 7 ; i ++ )
		{
			if ( ! isxdigit( p[i] ) )
			{
				return NULL ;
			}
		}
		Hex2RGB(p,aoResultRGB);
		return p ;
	}

	/* printf ( "lDialogString: %s\n" , lDialogString ) ; //*/
	if ( ! ( lIn = popen ( lDialogString , "r" ) ) )
	{
		return NULL ;
	}
	while ( fgets ( lBuff , sizeof ( lBuff ) , lIn ) != NULL )
	{
	}
	pclose ( lIn ) ;
	if ( ! strlen ( lBuff ) )
	{
		return NULL ;
	}
	/* printf ( "len Buff: %lu\n" , strlen(lBuff) ) ; //*/
	/* printf ( "lBuff0: %s\n" , lBuff ) ; //*/
	if ( lBuff[ strlen ( lBuff ) -1 ] == '\n' )
	{
		lBuff[ strlen ( lBuff ) -1 ] = '\0' ;
	}
	if ( lWasZenity3 )
	{
		lBuff[3]=lBuff[5];
		lBuff[4]=lBuff[6];
		lBuff[5]=lBuff[9];
		lBuff[6]=lBuff[10];
		lBuff[7]='\0';
		Hex2RGB(lBuff,aoResultRGB);
	}
	else if ( lWasOsascript || lWasXdialog )
	{
		sscanf(lBuff,"%hhu %hhu %hhu",
			   & aoResultRGB[0], & aoResultRGB[1],& aoResultRGB[2]);
		RGB2Hex(aoResultRGB,lBuff);
	}
	else
	{
		Hex2RGB(lBuff,aoResultRGB);
	}
	/* printf("%d %d %d\n", aoResultRGB[0],aoResultRGB[1],aoResultRGB[2]); //*/
	/* printf ( "lBuff: %s\n" , lBuff ) ; //*/
	return lBuff ;
}


#endif /* _WIN32 */


/*// hello.c
int main()
{
	char const * lThePassword;
	char const * lTheSaveFileName;
	char const * lTheOpenFileName;
	FILE * lIn;
	char lBuffer[1024];

  tinyfd_forceConsole = tinyfd_messageBox("Hello World",
	"force dialogs into console mode?\
	\n\t(it is better if dialog is installed)",
	"yesno", "question", 0);

  lThePassword =  tinyfd_inputBox(
	"a password box","your password will be revealed",NULL);

  lTheSaveFileName = tinyfd_saveFileDialog (
	"let us save this password",
	"passwordFile.txt",
	0,
	NULL,
	NULL );

	lIn = fopen(lTheSaveFileName, "w");
	if (!lIn)
	{
		tinyfd_messageBox(
			"Error",
			"Can not open this file in writting mode",
			"ok",
			"error",
			1 );
		return(1);
	}
	fputs(lThePassword, lIn);
	fclose(lIn);

	lTheOpenFileName = tinyfd_openFileDialog (
		"let us read this password back",
		"",
		0,
		NULL,
		NULL,
		0);

	lIn = fopen(lTheOpenFileName, "r");
	if (!lIn)
	{
		tinyfd_messageBox(
			"Error",
			"Can not open this file in reading mode",
			"ok",
			"error",
			1 );
		return(1);
	}
	fgets(lBuffer, sizeof(lBuffer), lIn);
	fclose(lIn);

  if ( *lBuffer )
	tinyfd_messageBox("your password is", lBuffer, "ok", "info", 1);
}
//*/

#pragma warning(default:4996)

/*
OSX :
$ gcc -o hello.app hello.c tinyfiledialogs.c

UNIX :
$ gcc -o hello hello.c tinyfiledialogs.c

MinGW :
> gcc -o hello.exe hello.c tinyfiledialogs.c -LC:/mingw/lib -lcomdlg32 -lole32

VisualStudio :
  Create a console application project,
	it links against Comdlg32.lib & Ole32.lib.
	Right click on your Project, select Properties.
	Configuration Properties/General Character Set to Multi-Byte.
*/
