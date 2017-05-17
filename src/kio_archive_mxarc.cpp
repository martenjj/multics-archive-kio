/////////////////////////////////////////////////// -*- mode:c++; -*- ////
//									//
//  Project:  KDE - Multics Archive Reader				//
//									//
//  Copyright (c) 2017 Jonathan Marten <jjm@keelhaul.me.uk>		//
//  Home & download:  http://github.com/martenjj/multics-archive-kio	//
//									//
//  This program is free software; you can redistribute it and/or	//
//  modify it under the terms of the GNU General Public License as	//
//  published by the Free Software Foundation; either version 3 of	//
//  the License, or (at your option) any later version.			//
//									//
//  It is distributed in the hope that it will be useful, but		//
//  WITHOUT ANY WARRANTY; without even the implied warranty of		//
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the	//
//  GNU General Public License for more details.			//
//									//
//  You should have received a copy of the GNU General Public		//
//  License along with this program; see the file LICENSE for further	//
//  details.  If not, see <http://www.gnu.org/licenses>.		//
//									//
//////////////////////////////////////////////////////////////////////////

#include "kio_archive_mxarc.h"

#include <qcoreapplication.h>
#include <qurl.h>

#include "kmulticsarchive.h"

//////////////////////////////////////////////////////////////////////////
//									//
//  This wrapper creates an instance of the archiver to act as a	//
//  KIOslave.								//
//									//
//////////////////////////////////////////////////////////////////////////

extern "C" { int Q_DECL_EXPORT kdemain(int argc, char **argv); }

int kdemain(int argc, char **argv)
{
  QCoreApplication app(argc, argv);
  app.setApplicationName(QLatin1String("kio_archive_mxarc"));

  if (argc!=4)
  {
     fprintf(stderr, "Usage: kio_archive_mxarc protocol domain-socket1 domain-socket2\n");
     exit(-1);
  }

  qDebug() << "Starting" << getpid();
  MxarcArchiveProtocol slave(argv[1], argv[2], argv[3]);
  slave.dispatchLoop();
  qDebug() << "done";
  return (0);
}


MxarcArchiveProtocol::MxarcArchiveProtocol(const QByteArray &proto, const QByteArray &pool, const QByteArray &app)
  : ArchiveProtocolBase(proto, pool, app)
{
  qDebug();
}


KArchive *MxarcArchiveProtocol::createArchive(const QString &proto, const QString &archiveFile)
{
  if (proto==QLatin1String("mxarc"))
  {
    qDebug() << "Opening KMulticsArchive on " << archiveFile;
    return (new KMulticsArchive(archiveFile));
  }
  else
  {
    qWarning() << "Protocol" << proto << "not supported by this IOSlave";
    return (NULL);
  }
}
