Multics Archive KIO Support
===========================

This package allows Multics (see http://www.multicians.org) archive
files to be opened within the Plasma desktop file managers Konqueror
or Dolphin, or by any other application that supports KIO.

See the images within the 'screenshots' subdirectory for examples of
it in action.

The package and all the files contained in it is licensed under the
GNU GPL V3+; see the file LICENSE for more information.


Requirements
------------

To build the plugin the KDE Frameworks 5 libraries and Plasma 5
desktop are required.  It requires the base archive support to be
available as a shared library, which means that commits 785d85f3 and
50bf2bf2 need to be incorporated in the 'kio-extras' package of
Plasma.  This is a fairly new change which your distro may not yet
incorporate; in case of any problems please check with your distro's
version control tracker that https://phabricator.kde.org/D5112 is
included.  If this isn't possible or is not recorded, check that your
library directory contains a 'libkioarchive.so.5' file; if it does
then all should be well.

CMake is also required to build the package.  Autotools are not required.

MIME type definitions are required at runtime in order that the file
manager can identify the Multics archive file type. See
http://github.com/martenjj/multics-mimetypes for suitable MIME type
definitions and icons, and install that first if necessary.

Despite the protocol name, it does not require the Multics archive tools
(http://sourceforge.net/p/dps8m/dps8m_devel_tools/ci/master/tree/src/tapeUtils/)
to be installed on the system;  the package implements the Multics
archive format internally.  It assumes that the files are already in
8-bit format; those downloaded from the source archive at
http://web.mit.edu/multics-history/source/Multics_Internet_Server/Multics_sources.html
are suitable.


Building and installing
-----------------------

Assuming that you have the requirements as above installed or already
provided by your distro, go to a suitable build location (e.g. your
home directory) and do:

     git clone https://github.com/martenjj/multics-archive-kio.git
     cd multics-archive-kio
     mkdir build
     cd build
     cmake ..
     make
     sudo make install


Running
-------

No configuration or setup is required.  Simply browse to a directory
containing a Multics archive file with the Konqueror or Dolphin file
manager and click on it.  Assuming that you have the "Open archives as
folder" option turned on ("Settings" - "Configure Konqueror" - "File
Management" - "Navigation" in Konqueror or "Settings" - "Configure
Dolphin" - "Navigation" in Dolphin), the archive should be opened as a
directory and you will be able to browse, view or copy the files
contained within.  You can also open a file within a Multics archive
from the command line or within an application using the "mxarc"
protocol.

If you use Konqueror as a file manager then you can configure what
happens when you click on a file identified as Multics source (PL/1,
ALM or related).  The default action will be the same as for any other
text file, either opening it in Kate or KWrite, or showing it in an
embedded editor part.  To configure this, use System Settings
("Personalisation" - "Applications" - "File Associations" -
"Embedding") to change the actions for the MIME types "text/x-pl1src"
and "text/x-almsrc".


Problems?
---------

Please raise an issue on GitHub (at
http://github.com/martenjj/multics-archive-kio) if there are any
problems with installing or using this package.


Thanks for your interest!
-------------------------

Jonathan Marten, http://github.com/martenjj
