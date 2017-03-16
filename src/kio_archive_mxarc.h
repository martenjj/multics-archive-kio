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

#ifndef KIO_ARCHIVE_MXARC_H
#define KIO_ARCHIVE_MXARC_H

#include "kio_archivebase.h"

class MxarcArchiveProtocol : public ArchiveProtocolBase
{
public:
    MxarcArchiveProtocol(const QByteArray &proto, const QByteArray &pool, const QByteArray &app);
    virtual ~MxarcArchiveProtocol() = default;

    KArchive *createArchive(const QString &proto, const QString &archiveFile) Q_DECL_OVERRIDE;
};

#endif							// KIO_ARCHIVE_MXARC_H
