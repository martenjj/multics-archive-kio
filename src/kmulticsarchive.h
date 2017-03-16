/////////////////////////////////////////////////// -*- mode:c++; -*- ////
//									//
//  Project:	KDE - Multics Archive Reader				//
//  Edit:	16-Mar-17						//
//									//
//////////////////////////////////////////////////////////////////////////
//									//
//  Copyright (c) 2017 Jonathan Marten <jjm@keelhaul.me.uk>		//
//  Home and download page:  http://github.com/martenjj/kiomultics	//
//									//
//  This program is free software; you can redistribute it and/or	//
//  modify it under the terms of the GNU General Public License as	//
//  published by the Free Software Foundation; either version 2 of	//
//  the License, or (at your option) any later version.			//
//									//
//  It is distributed in the hope that it will be useful, but		//
//  WITHOUT ANY WARRANTY; without even the implied warranty of		//
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	//
//  GNU General Public License for more details.			//
//									//
//  You should have received a copy of the GNU General Public		//
//  License along with this program; see the file COPYING for further	//
//  details.  If not, see <http://www.gnu.org/licenses>.		//
//									//
//////////////////////////////////////////////////////////////////////////

#ifndef KMULTICSARCHIVE_H
#define KMULTICSARCHIVE_H

#include <karchive.h>

#include "kmulticsarchive_export.h"

class QDateTime;

/**
 * @short An archive reader for the Multics archive format.
 *
 * This is a KIO plugin that implements the "mxarc" protocol,
 * allowing Multics archives to be listed and files extracted
 * in Konqueror or any application that supports KIO.
 *
 * @author Jonathan Marten
 **/
class KMULTICSARCHIVE_EXPORT KMulticsArchive : public KArchive
{
public:
    /**
     * Create an instance that operates on the given filename.
     *
     * @param filename Local Multics archive file path
     **/
    explicit KMulticsArchive(const QString &filename);

    /**
     * Create an instance that operates on the given device.
     * The device can be compressed (KFilterDev) or not (QFile, etc.).
     * @param dev The device to read from
     **/
    explicit KMulticsArchive(QIODevice *dev);

    /**
     * Destructor.  If the archive file is still open,
     * then it will be closed automatically.
     **/
    virtual ~KMulticsArchive();

protected:
    /**
     * Opens the archive for reading.  Parses the directory
     * listing of the archive, and creates a KArchiveEntry
     * for each file contained within.
     *
     * @param openMode The file or device open mode
     * @return @c true if the archive was opened and listed successfully,
     * or @c false if there was a problem.
     **/
    bool openArchive(QIODevice::OpenMode openMode) override;

    /**
     * Close the archive.
     *
     * @return @c true always
     **/
    bool closeArchive() override;

    /**
     * @return Always false, to indicate that writing is not supported.
     **/
    bool doPrepareWriting(const QString &name, const QString &user, const QString &group, qint64 size,
                          mode_t perm, const QDateTime &atime, const QDateTime &mtime, const QDateTime &ctime) override;

    /**
     * @return Always false, to indicate that writing is not supported.
     **/
    bool doFinishWriting(qint64 size) override;

    /**
     * @return Always false, to indicate that writing is not supported.
     **/
    bool doWriteDir(const QString &name, const QString &user, const QString &group,
                    mode_t perm, const QDateTime &atime, const QDateTime &mtime, const QDateTime &ctime) override;
    /**
     * @return Always false, to indicate that writing is not supported.
     **/
    bool doWriteSymLink(const QString &name, const QString &target,
                        const QString &user, const QString &group, mode_t perm,
                        const QDateTime &atime, const QDateTime &mtime, const QDateTime &ctime) override;

private:
    /**
     * Set an error message to be returned to the caller.
     *
     * @param msg The error message
     * @note The message may not always be shown to the user,
     * so it is printed as a debug/warning message also.
    **/
    void setErrorString(const QString &msg);
};

#endif							// KMULTICSARCHIVE_H
