/*
 * Rem - Requirements and Entity Modeler = UML + AOP + Open Source + Cross Platform
 * Copyright (C) 2008 Adrian Kosmaczewski - http://remproject.org/
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

//! Contains the starting point of the GUI Rem application.
/*!
 * \file ui/Main.cpp
 *
 * Contains the starting point of the GUI Rem application.
 * 
 * $LastChangedDate$
 * $LastChangedBy$
 * $HeadURL$
 * 
 * \version   $LastChangedRevision$
 * \author    Adrian
 * \date      4/11/08
 */

#ifndef APPLICATION_H_
#include "Application.h"
#endif

#include "PlatformDefinitions.h"

START_JUCE_APPLICATION (ui::Application)

/*!
 * \mainpage Rem
 *
 * \author Adrian Kosmaczewski
 * \date August 28th, 2008
 *
 * The project aims to the creation of an UML tool suitable both for academia and the industry, 
 * including Ivar Jacobson's proposed extensions for Aspect-Oriented Software Development (AOSD).
 *
 * \li Creation of a cross-platform (Linux, Windows & Mac OS X) UML editor, using C++;
 * \li Allow users to create (in its first release) use case, sequence and class diagrams;
 * \li Include AOSD extensions to create models for aspects, pointcuts and advices;
 * \li Provide interoperability through the export of diagrams using the XMI standard;
 * \li Deliver a high-quality code base, thoroughly unit- and functionally tested;
 * \li Provide a usable, standard and easy-to-use user interface.
 *
 * The name "Rem" stands for "Requirements and Entity Modeler" but is also a reference to 
 * Rem Koolhaas, one of the greatest urbanists and architects of all time. 
 * The icon of the application is a stylized representation of one of Koolhaas’ major works, 
 * the building of the Seattle Public Library. 
 *
 * \section main_index Index
 *
 * More information about Rem can be found in the following pages:
 *
 * \li \subpage pageLicense "License"
 * \li \subpage pageBuildWindows "Build in Windows XP"
 * \li \subpage pageBuildLinux "Build in Kubuntu Linux"
 * \li \subpage pageBuildMac "Build in Mac OS X"
 * \li \subpage pageInstallation "Installation"
 * \li \subpage pageDocumentation "Documentation"
 */

/*!
 * \page pageLicense License
 *
\verbatim
 		    GNU GENERAL PUBLIC LICENSE
		       Version 2, June 1991

 Copyright (C) 1989, 1991 Free Software Foundation, Inc.,
 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 Everyone is permitted to copy and distribute verbatim copies
 of this license document, but changing it is not allowed.

			    Preamble

  The licenses for most software are designed to take away your
freedom to share and change it.  By contrast, the GNU General Public
License is intended to guarantee your freedom to share and change free
software--to make sure the software is free for all its users.  This
General Public License applies to most of the Free Software
Foundation's software and to any other program whose authors commit to
using it.  (Some other Free Software Foundation software is covered by
the GNU Lesser General Public License instead.)  You can apply it to
your programs, too.

  When we speak of free software, we are referring to freedom, not
price.  Our General Public Licenses are designed to make sure that you
have the freedom to distribute copies of free software (and charge for
this service if you wish), that you receive source code or can get it
if you want it, that you can change the software or use pieces of it
in new free programs; and that you know you can do these things.

  To protect your rights, we need to make restrictions that forbid
anyone to deny you these rights or to ask you to surrender the rights.
These restrictions translate to certain responsibilities for you if you
distribute copies of the software, or if you modify it.

  For example, if you distribute copies of such a program, whether
gratis or for a fee, you must give the recipients all the rights that
you have.  You must make sure that they, too, receive or can get the
source code.  And you must show them these terms so they know their
rights.

  We protect your rights with two steps: (1) copyright the software, and
(2) offer you this license which gives you legal permission to copy,
distribute and/or modify the software.

  Also, for each author's protection and ours, we want to make certain
that everyone understands that there is no warranty for this free
software.  If the software is modified by someone else and passed on, we
want its recipients to know that what they have is not the original, so
that any problems introduced by others will not reflect on the original
authors' reputations.

  Finally, any free program is threatened constantly by software
patents.  We wish to avoid the danger that redistributors of a free
program will individually obtain patent licenses, in effect making the
program proprietary.  To prevent this, we have made it clear that any
patent must be licensed for everyone's free use or not licensed at all.

  The precise terms and conditions for copying, distribution and
modification follow.

		    GNU GENERAL PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. This License applies to any program or other work which contains
a notice placed by the copyright holder saying it may be distributed
under the terms of this General Public License.  The "Program", below,
refers to any such program or work, and a "work based on the Program"
means either the Program or any derivative work under copyright law:
that is to say, a work containing the Program or a portion of it,
either verbatim or with modifications and/or translated into another
language.  (Hereinafter, translation is included without limitation in
the term "modification".)  Each licensee is addressed as "you".

Activities other than copying, distribution and modification are not
covered by this License; they are outside its scope.  The act of
running the Program is not restricted, and the output from the Program
is covered only if its contents constitute a work based on the
Program (independent of having been made by running the Program).
Whether that is true depends on what the Program does.

  1. You may copy and distribute verbatim copies of the Program's
source code as you receive it, in any medium, provided that you
conspicuously and appropriately publish on each copy an appropriate
copyright notice and disclaimer of warranty; keep intact all the
notices that refer to this License and to the absence of any warranty;
and give any other recipients of the Program a copy of this License
along with the Program.

You may charge a fee for the physical act of transferring a copy, and
you may at your option offer warranty protection in exchange for a fee.

  2. You may modify your copy or copies of the Program or any portion
of it, thus forming a work based on the Program, and copy and
distribute such modifications or work under the terms of Section 1
above, provided that you also meet all of these conditions:

    a) You must cause the modified files to carry prominent notices
    stating that you changed the files and the date of any change.

    b) You must cause any work that you distribute or publish, that in
    whole or in part contains or is derived from the Program or any
    part thereof, to be licensed as a whole at no charge to all third
    parties under the terms of this License.

    c) If the modified program normally reads commands interactively
    when run, you must cause it, when started running for such
    interactive use in the most ordinary way, to print or display an
    announcement including an appropriate copyright notice and a
    notice that there is no warranty (or else, saying that you provide
    a warranty) and that users may redistribute the program under
    these conditions, and telling the user how to view a copy of this
    License.  (Exception: if the Program itself is interactive but
    does not normally print such an announcement, your work based on
    the Program is not required to print an announcement.)

These requirements apply to the modified work as a whole.  If
identifiable sections of that work are not derived from the Program,
and can be reasonably considered independent and separate works in
themselves, then this License, and its terms, do not apply to those
sections when you distribute them as separate works.  But when you
distribute the same sections as part of a whole which is a work based
on the Program, the distribution of the whole must be on the terms of
this License, whose permissions for other licensees extend to the
entire whole, and thus to each and every part regardless of who wrote it.

Thus, it is not the intent of this section to claim rights or contest
your rights to work written entirely by you; rather, the intent is to
exercise the right to control the distribution of derivative or
collective works based on the Program.

In addition, mere aggregation of another work not based on the Program
with the Program (or with a work based on the Program) on a volume of
a storage or distribution medium does not bring the other work under
the scope of this License.

  3. You may copy and distribute the Program (or a work based on it,
under Section 2) in object code or executable form under the terms of
Sections 1 and 2 above provided that you also do one of the following:

    a) Accompany it with the complete corresponding machine-readable
    source code, which must be distributed under the terms of Sections
    1 and 2 above on a medium customarily used for software interchange; or,

    b) Accompany it with a written offer, valid for at least three
    years, to give any third party, for a charge no more than your
    cost of physically performing source distribution, a complete
    machine-readable copy of the corresponding source code, to be
    distributed under the terms of Sections 1 and 2 above on a medium
    customarily used for software interchange; or,

    c) Accompany it with the information you received as to the offer
    to distribute corresponding source code.  (This alternative is
    allowed only for noncommercial distribution and only if you
    received the program in object code or executable form with such
    an offer, in accord with Subsection b above.)

The source code for a work means the preferred form of the work for
making modifications to it.  For an executable work, complete source
code means all the source code for all modules it contains, plus any
associated interface definition files, plus the scripts used to
control compilation and installation of the executable.  However, as a
special exception, the source code distributed need not include
anything that is normally distributed (in either source or binary
form) with the major components (compiler, kernel, and so on) of the
operating system on which the executable runs, unless that component
itself accompanies the executable.

If distribution of executable or object code is made by offering
access to copy from a designated place, then offering equivalent
access to copy the source code from the same place counts as
distribution of the source code, even though third parties are not
compelled to copy the source along with the object code.

  4. You may not copy, modify, sublicense, or distribute the Program
except as expressly provided under this License.  Any attempt
otherwise to copy, modify, sublicense or distribute the Program is
void, and will automatically terminate your rights under this License.
However, parties who have received copies, or rights, from you under
this License will not have their licenses terminated so long as such
parties remain in full compliance.

  5. You are not required to accept this License, since you have not
signed it.  However, nothing else grants you permission to modify or
distribute the Program or its derivative works.  These actions are
prohibited by law if you do not accept this License.  Therefore, by
modifying or distributing the Program (or any work based on the
Program), you indicate your acceptance of this License to do so, and
all its terms and conditions for copying, distributing or modifying
the Program or works based on it.

  6. Each time you redistribute the Program (or any work based on the
Program), the recipient automatically receives a license from the
original licensor to copy, distribute or modify the Program subject to
these terms and conditions.  You may not impose any further
restrictions on the recipients' exercise of the rights granted herein.
You are not responsible for enforcing compliance by third parties to
this License.

  7. If, as a consequence of a court judgment or allegation of patent
infringement or for any other reason (not limited to patent issues),
conditions are imposed on you (whether by court order, agreement or
otherwise) that contradict the conditions of this License, they do not
excuse you from the conditions of this License.  If you cannot
distribute so as to satisfy simultaneously your obligations under this
License and any other pertinent obligations, then as a consequence you
may not distribute the Program at all.  For example, if a patent
license would not permit royalty-free redistribution of the Program by
all those who receive copies directly or indirectly through you, then
the only way you could satisfy both it and this License would be to
refrain entirely from distribution of the Program.

If any portion of this section is held invalid or unenforceable under
any particular circumstance, the balance of the section is intended to
apply and the section as a whole is intended to apply in other
circumstances.

It is not the purpose of this section to induce you to infringe any
patents or other property right claims or to contest validity of any
such claims; this section has the sole purpose of protecting the
integrity of the free software distribution system, which is
implemented by public license practices.  Many people have made
generous contributions to the wide range of software distributed
through that system in reliance on consistent application of that
system; it is up to the author/donor to decide if he or she is willing
to distribute software through any other system and a licensee cannot
impose that choice.

This section is intended to make thoroughly clear what is believed to
be a consequence of the rest of this License.

  8. If the distribution and/or use of the Program is restricted in
certain countries either by patents or by copyrighted interfaces, the
original copyright holder who places the Program under this License
may add an explicit geographical distribution limitation excluding
those countries, so that distribution is permitted only in or among
countries not thus excluded.  In such case, this License incorporates
the limitation as if written in the body of this License.

  9. The Free Software Foundation may publish revised and/or new versions
of the General Public License from time to time.  Such new versions will
be similar in spirit to the present version, but may differ in detail to
address new problems or concerns.

Each version is given a distinguishing version number.  If the Program
specifies a version number of this License which applies to it and "any
later version", you have the option of following the terms and conditions
either of that version or of any later version published by the Free
Software Foundation.  If the Program does not specify a version number of
this License, you may choose any version ever published by the Free Software
Foundation.

  10. If you wish to incorporate parts of the Program into other free
programs whose distribution conditions are different, write to the author
to ask for permission.  For software which is copyrighted by the Free
Software Foundation, write to the Free Software Foundation; we sometimes
make exceptions for this.  Our decision will be guided by the two goals
of preserving the free status of all derivatives of our free software and
of promoting the sharing and reuse of software generally.

			    NO WARRANTY

  11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY
FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN
OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES
PROVIDE THE PROGRAM "AS IS" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS
TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE
PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,
REPAIR OR CORRECTION.

  12. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR
REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,
INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING
OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED
TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY
YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER
PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE
POSSIBILITY OF SUCH DAMAGES.

		     END OF TERMS AND CONDITIONS

	    How to Apply These Terms to Your New Programs

  If you develop a new program, and you want it to be of the greatest
possible use to the public, the best way to achieve this is to make it
free software which everyone can redistribute and change under these terms.

  To do so, attach the following notices to the program.  It is safest
to attach them to the start of each source file to most effectively
convey the exclusion of warranty; and each file should have at least
the "copyright" line and a pointer to where the full notice is found.

    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) <year>  <name of author>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

Also add information on how to contact you by electronic and paper mail.

If the program is interactive, make it output a short notice like this
when it starts in an interactive mode:

    Gnomovision version 69, Copyright (C) year name of author
    Gnomovision comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
    This is free software, and you are welcome to redistribute it
    under certain conditions; type `show c' for details.

The hypothetical commands `show w' and `show c' should show the appropriate
parts of the General Public License.  Of course, the commands you use may
be called something other than `show w' and `show c'; they could even be
mouse-clicks or menu items--whatever suits your program.

You should also get your employer (if you work as a programmer) or your
school, if any, to sign a "copyright disclaimer" for the program, if
necessary.  Here is a sample; alter the names:

  Yoyodyne, Inc., hereby disclaims all copyright interest in the program
  `Gnomovision' (which makes passes at compilers) written by James Hacker.

  <signature of Ty Coon>, 1 April 1989
  Ty Coon, President of Vice

This General Public License does not permit incorporating your program into
proprietary programs.  If your program is a subroutine library, you may
consider it more useful to permit linking proprietary applications with the
library.  If this is what you want to do, use the GNU Lesser General
Public License instead of this License.
\endverbatim
 */

/*!
 * \page pageInstallation Installation
 *
 * \section install_win Windows
 * 
 * The Windows version of the application is bundled as an installer, which
 * also provides a desinstallation option.
 *
 * \section install_linux Linux
 *
 * The Linux tarball contains a script which copies a required library
 * to the /usr/lib directory. See the "install.sh" file for details.
 *
 * \section install_mac Mac OS X (10.4+, Intel or PowerPC)
 * 
 * The Mac version is available in two forms:
 * 
 * \li A simpler DMG file, with a Universal Binary of Rem ready to 
 * use, which can simply be dragged to the Applications folder;
 * \li A second DMG file with an installer, which will copy the application
 * to the Applications folder.
 */

/*!
 * \page pageBuildWindows Build in Windows XP Service Pack 2
 * 
 * \section sec_1 Install Microsoft Visual C++ 2008 Express Edition
 * 
 * Free download from here:
 * http://www.microsoft.com/express/download/
 * 
 * It is recommended to download the "Offline Install DVD", available at the bottom of the page. You only need to install the C++ IDE and libraries from that DVD.
 * 
 * \section sec_2 Download and install QuickTime for Windows
 * 
 * JUCE depends on the QuickTime libraries for displaying media files. You can download and install QuickTime from this address:
 * http://www.apple.com/quicktime/download/
 * 
 * \section sec_3 Install the ASIO SDK
 * 
 * Juce requires this SDK to be available. Follow the instructions in this forum post:
 * http://www.rawmaterialsoftware.com/juceforum/viewtopic.php?p=12107&highlight=&sid=1a6b77fdef10736f25f1dc05caecb4c9#12107
 * 
 * The ASIO drivers can be downloaded from here:
 * http://www.steinberg.net/324+M52087573ab0.html
 * 
 * In that page, follow the link at the bottom, agree to the end-user license agreement and fill the form to access the download link. Install the libraries in "C:\ASIOSDK2\".
 * 
 * \section sec_4 Checkout and build POCO
 * 
 * POCO is bundled with the file "lib\poco\Foundation\Foundation_vs80.sln" which can be opened with Visual C++ 2008 Express Edition (you will be asked to upgrade it to the Visual Studio 2008 format). Right click on the project and select "Build", in each of the four available configurations. The generated libraries will be generated in "lib\poco\lib" and the DLLs will be installed in "lib\poco\bin".
 * 
 * \section sec_5 Build JUCE
 * 
 * JUCE is bundled with a Visual Studio solution, that can be used to build the library. Open the "lib\juce\build\win32\vc8\JUCE.sln" file (you will be asked to upgrade it to the Visual Studio 2008 format) and right-click on the JUCE project inside. Go to "Configuration Properties - C/C++ - General" and modify the the "Additional Include Directories" to the value: 
 * "C:\Program Files\QuickTime";"C:\ASIOSDK2\common".
 * Right-click on the project and select "Build", in both Release and Debug configurations.
 * 
 * \section sec_6 Install CppUnit
 * 
 * Download http://downloads.sourceforge.net/cppunit/cppunit-1.12.1.tar.gz and unzip it into:
 * "C:\cppunit-1.12.1"
 * Open the "C:\cppunit-1.12.0\src\CppUnitLibraries.sln" file and build the "cppunit" project. The resulting libraries are stored at "C:\cppunit-1.12.0\lib".
 * 
 * \section sec_7 Install SQLite
 * 
 * Download the precompiled DLL for Windows here:
 * http://www.sqlite.org/sqlitedll-3_5_8.zip
 * Unzip it and install the files "sqlite3.dll" and "sqlite3.def" in "lib/sqlite".
 * 
 * \section sec_8 Generate the DEF from the SQLite DLL
 * 
 * In order to use the DLL from within Rem, you need to generate a DEF file out of it. To do this, follow the instructions at:
 * http://support.microsoft.com/kb/131313
 * 
 * \li "cd lib\sqlite"
 * \li "LIB /DEF:sqlite.def"
 * 
 * This will generate the "sqlite3.exp" file required by the Rem Visual Studio solution.
 * 
 * \section sec_9 Install CMake 2.4
 * 
 * There is an installer available here:
 * http://www.cmake.org/files/v2.4/cmake-2.4.8-win32-x86.exe
 * 
 * Do not use CMake 2.6 (the latest version available at the time of this writing) since there is a regression bug that affects the command-line script that builds Rem from scratch:
 * http://www.cmake.org/Bug/view.php?id=7222
 * 
 * \section sec_10 Install NSIS 2.37
 * 
 * NSIS (Nullsoft Scriptable Install System) is used by CMake to generate installers for Windows. You can download it from here:
 * http://prdownloads.sourceforge.net/nsis/nsis-2.37-setup.exe?download
 * 
 * \section sec_11 Build Rem in Visual Studio
 * 
 * Open the "build\windows\Rem.sln" file; select the "Release" configuration, click on the "Rem" project on the solution tree, and select "Build Rem" on the "Build" menu.
 * 
 * \section sec_12 Build Rem using CMake
 * 
 * Use the "build/windows/build.bat" file, which generates an NMake makefile from the CMake file, and then uses NMake (available with Visual C++ 2008 Express Edition) to build the application and the installer from the command line.
 * 
 */

/*!
 * \page pageBuildLinux Build in Kubuntu Linux 7.10 "Gutsy Gibbon"
 * 
 * Much of the explanations for building JUCE in Kubuntu are taken from this 
 * entry in Rem author's blog:
 * http://kosmaczewski.net/2007/11/16/building-juce-on-kubuntu-710/
 * 
 * \section sec_1 Note about processor architectures
 * 
 * JUCE cannot run on Linux on PowerPC processors, given that it relies on assembler code for dealing with endianness issues, as shown here:
 * http://www.koders.com/c/fid26F230513834417D1CC7BE6FDF5CE455DA49BE09.aspx
 * This rules out the possibility of running Rem on PowerPC systems, like G3, G4 and G5 Macs running Linux. For the moment, Rem can only be built with Linux running on processors supporting the i386 architecture.
 * 
 * \section sec_2 Lua
 * 
 * Make sure that you have the Lua programming language installed; you can use your favorite package manager to install it, or you can grab the source files from 
 * http://www.lua.org/
 * 
 * \section sec_3 SQLite 3 and CppUnit
 * 
 * Using Synaptic manager or any other package manager, install the "libsqlite3" and "libcppunit-dev" libraries.
 * 
 * \section sec_4 Libraries required by JUCE
 * 
 * Make sure that you have the following libraries installed in your Kubuntu installation using Synaptic or any other package manager, as specified in this JUCE forum post:
 * http://www.rawmaterialsoftware.com/juceforum/viewtopic.php?t=1312&highlight=audio+build
 * 
 * \li libx11-dev
 * \li libasound2-dev
 * \li libfreetype6-dev
 * \li libxinerama-dev
 * \li libglu1-mesa-dev
 * \li libglut3-dev (with its dependency freeglut3-dev too)
 * 
 * \section sec_5 Libraries required by POCO
 * 
 * Install "libssl-dev" using Synaptic or any other package manager.
 * 
 * \section sec_6 Download premake from Sourceforge
 * 
 * You can download premake http://premake.sourceforge.net/ from this link:
 * http://prdownloads.sf.net/premake/premake-linux-3.4.tar.gz
 * 
 * Unzip the file and install the binary where you want (typically /usr/bin). You have to do this manually, since premake is not available through the Synaptic package manager, in any repository.
 * 
 * You can also build it from source, downloading and extracting the following file:
 * http://prdownloads.sf.net/premake/premake-src-3.6.zip
 * 
 * \section sec_7 Install CMake 2.6
 * 
 * Download the source files for CMake and install it following the instructions:
 * http://www.cmake.org/files/v2.6/cmake-2.6.0.tar.gz
 * 
 * \section sec_8 Build JUCE
 * 
 * \li "cd" into the lib/juce/build/linux folder.
 * \li Run "sh runpremake" which will use premake and Lua to create a makefile
 * \li Run "make" (which is equal to "make CONFIG=Debug") or "make CONFIG=Release" to build the library; a couple of minutes later you’ll have a "juce/bin/libjuce_debug.a" and a "juce/bin/libjuce.a" library files ready to use.
 * 
 * \section sec_9 Build POCO
 * 
 * \li "cd" into the lib/poco folder.
 * \li Type "chmod 755 configure" to make the "configure" script executable.
 * \li Type "chmod 755 build/script/*" to make all build scripts executable.
 * \li Type "configure", "make" and "sudo make install" to build and install the POCO library. This operation might take several minutes.
 * 
 * \section sec_10 Build Rem
 * 
 * The "build.sh" shell script in this folder shows how to build Rem and the distribution package using CMake. The resulting binaries will be placed in a "bin" subfolder at the root of the current distribution of Rem.
 *
 */

/*!
 * \page pageBuildMac Build in Mac OS X 10.5 "Leopard" (PowerPC or Intel)
 * 
 * These instructions explain how to build Rem from source code in Leopard.
 * 
 * \section sec_1 Install Xcode
 * 
 * Install the Xcode developer tools (bundled with Mac OS X). Rem has been successfully built with both Xcode 3.0 (bundled with Leopard) and 3.1 (bundled with the iPhone developer tools).
 * 
 * \section sec_2 CMake 2.6
 * 
 * \li Download CMake 2.6 from http://www.cmake.org/files/v2.6/cmake-2.6.0-Darwin-universal.dmg 
 * \li Open the DMG file, and execute the installer in the disk image.
 * \li When prompted to install the command-line utilities in /usr/bin, answer "YES"
 * 
 * \section sec_3 CppUnit 1.12.1
 * 
 * Install CppUnit in the usual Unix paths, with the following commands:
 * \verbatim
 *     $ mkdir ~/Desktop/cppunit/
 *     $ cd ~/Desktop/cppunit/
 *     $ curl http://switch.dl.sourceforge.net/sourceforge/cppunit/cppunit-1.12.1.tar.gz > cppunit-1.12.1.tar.gz
 *     $ tar xvfpz cppunit-1.12.1.tar.gz
 *     $ cd cppunit-1.12.1
 * \endverbatim
 * 
 * To build Universal Binaries of the CppUnit library, follow these instructions taken from the CppUnit wiki,
 * http://cppunit.sourceforge.net/cgi-bin/moin.cgi/BuildingCppUnit1#head-606831052dc6f25163a5f79aec04dcdbd05a7329
 * 
 * When building on an Intel machine:
 * 
 * \verbatim
 *     $ ./configure --disable-dependency-tracking CXXFLAGS="-arch ppc -arch i386 -gdwarf-2 -O2"
 *     $ make AM_LDFLAGS="-XCClinker -arch -XCClinker ppc -XCClinker -arch -XCClinker i386"
 *     $ sudo make install
 * \endverbatim
 * 
 * When building on a PowerPC machine (with Universal SDK installed):
 * 
 * \verbatim
 *     $ ./configure --disable-dependency-tracking CXXFLAGS="-isysroot /Developer/SDKs/MacOSX10.5.sdk -arch ppc -arch i386 -gdwarf-2 -O2"
 *     $ make AM_LDFLAGS="-XCClinker -arch -XCClinker ppc -XCClinker -arch -XCClinker i386 -XCClinker -isysroot -XCClinker /Developer/SDKs/MacOSX10.5.sdk"
 *     $ sudo make install
 * \endverbatim
 * 
 * This last step will install the headers in /usr/local/include/cppunit and the libraries in /usr/local/lib.
 * 
 * \section sec_4 Fix an incompatibility in the 10.4u SDK
 * 
 * Type the following command in Terminal.app
 * 
 * \verbatim
 *    $ sudo ln -s /Developer/SDKs/MacOSX10.4u.sdk/usr/lib/crt1.o /Developer/SDKs/MacOSX10.4u.sdk/usr/lib/crt1.10.5.o
 * \endverbatim
 * 
 * \section sec_5 Get a Universal Binary version of POCO
 * 
 * The POCO libraries included in the Rem source distribution (as an "svn:externals") is not prepared to be built as a Universal Binary. You can use it to create platform-specific (i.e., only PowerPC or Intel) versions of Rem.
 * 
 * To download a precompiled version of POCO as Universal Binary, go to this forum post:
 * http://www.openframeworks.cc/forum/viewtopic.php?p=2371#2371
 * There is a link to download the lib there:
 * http://openframeworks.cc/files/poco/poco-universal.zip
 * Unzip the file and place it in the "lib" subfolder of this project, together with the "juce" folder.
 * 
 * \section sec_6 Build JUCE 1.45
 * 
 * Go to lib/juce/build/macosx and open the Juce.xcodeproj file with Xcode. 
 * 
 *     <ol>
 *     <li>In Xcode 2.5 the library compiles out of the box.</li>
 *     <li>In Xcode 3 (Leopard-only):
 *         <ol>
 *         <li>Select the "Juce" target and open the "Info" dialog box, "Build" tab.</li>
 *         <li>Remove the dependencies to GCC 3 and to the Mac OS X 10.2 SDK. Instead, specify GCC 4.0.</li>
 *         <li>In the "Base SDK Path" entry specify "$(DEVELOPER_SDK_DIR)/MacOSX10.4u.sdk" for Release and Debug</li>
 *         <li>In the "Architectures" entry specify "$(NATIVE_ARCH)" for Debug, and "ppc i386" for Release.</li>
 *         </ol>
 *     </li>
 *     <li>Build the solution using the "Build" button in the toolbar, in both Debug and Release modes.</li>
 *     </ol>
 * 
 * \section sec_7 Install Doxygen
 * 
 * Install Doxygen using MacPorts:
 * 
 * \verbatim
 *     $ sudo port install doxygen
 * \endverbatim
 * 
 * \section sec_8 Build Rem using Xcode
 * 
 * Open build/mac/rem.xcodeproj and click the "Build" button on the toolbar, either in Release or Debug mode. The solution should compile without problems now.
 * 
 * The Xcode project is configured to build a Universal Binary of Rem and remtest only in "Release" mode. In "Debug" configuration, the binaries built will only work in the same architecture in which Xcode is running (as specified by the "$(NATIVE_ARCH)" configuration value).
 * 
 * \section sec_9 Build Rem using CMake
 * 
 * The "build.sh" shell script in this folder shows how to use CMake, CPack and CTest to build the application from the command line.
 * 
 * \section sec_10 Build the documentation with Doxygen
 * 
 * Type the following command at the root of the project (where the Doxyfile file resides):
 * 
 * \verbatim
 *     $ /opt/local/bin/doxygen 
 * \endverbatim
 * 
 * \section sec_11 Note about PDF output with Doxygen
 * 
 * If you want to create a PDF output using Doxygen, you should install first the MacTex distribution, freely available from
 * http://www.tug.org/mactex/
 * 
 * Download the disk image file from
 * http://mirror.ctan.org/systems/mac/mactex/MacTeX.dmg
 * 
 * Open the image file and execute the installer inside. This will install all the required tools to generate PDF files from the Doxygen documentation.
 * 
 * \section sec_12 Note about dynamic libraries and Xcode
 * 
 * Xcode has a feature (bug?) when linking executables to static libraries: if both the dynamic and static version of the same library are available (which usually is the case, for example with CppUnit), Xcode will link to the dynamic version, and there is no configuration possible to change this behavior. The only possible solution to get a statically-linked executable is to delete the dynamic library, which forces Xcode to link to the static version. This way, the deployment of the application is easier (even if the resulting binary is obviously larger)
 * 
 */

/*!
 * \page pageDocumentation Documentation
 *
 * To generate the documentation, make sure that Doxygen 1.5.4 or later
 * (http://www.stack.nl/~dimitri/doxygen/) and dot (http://www.graphviz.org/) are
 * installed; type "doxygen" in the folder where the file "Doxyfile" is located.
 *
 * For Windows, the Doxyfile also assumes that the HTML Compiler (used to generate
 * this CHM file) is located in "C:\Program Files\HTML Help Workshop\hhc.exe".
 * CHM files can be viewed in the Macintosh using Chmox (http://chmox.sourceforge.net/)
 * and in Linux using GnoCHM (http://gnochm.sourceforge.net/)
 */
