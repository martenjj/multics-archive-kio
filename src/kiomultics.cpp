/* This file is part of the KDE libraries
   Copyright (C) 2002 Laurence Anderson <l.d.anderson@warwick.ac.uk>

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#include "kiomultics.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

#include <qfile.h>
#include <qdebug.h>

#include <klocalizedstring.h>

#include "loggingcategory.h"




// ldd/system_library_standard/source/bound_archive_.s.archive
//  from archive.pl1:
// 
// dcl 1 archive based (p1) aligned,
    // 2 hbgn char (8),
    // 2 pad1 char (4),
    // 2 name char (32),
    // 2 timeup char (16),
    // 2 mode char (4),
    // 2 time char (16),
    // 2 pad char (4),
    // 2 bcnt char (8),
    // 2 hend char (8),
    // 2 begin fixed bin;

struct ArchiveHeader
{
    char hbgn[8];
    char pad1[4];
    char name[32];
    char timeup[16];
    char mode[4];
    char time[16];
    char pad[4];
    char bcnt[8];
    char hend[8];
};

// from archive_data_.alm:
//
// hbgn = ident
	// oct	014012012012
	// oct	017012011011
static const char ARCHIVE_HBGN[] = { '\014', '\012', '\012', '\012', 
                                     '\017', '\012', '\011', '\011' };
// hend = fence
	// oct	017017017017
	// oct	012012012012
static const char ARCHIVE_HEND[] = { '\017', '\017', '\017', '\017',
                                     '\012', '\012', '\012', '\012' };

// just appended to some archives
static const char ARCHIVE_CHDR[] = { '\015', '\012', '\015', '\012',
                                     '\052', '\057', '\015', '\012' };


////////////////////////////////////////////////////////////////////////
/////////////////////////// KIOMultics ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////





KIOMultics::KIOMultics(const QString &filename)
    : KArchive(filename)
{
}


KIOMultics::KIOMultics(QIODevice *dev)
    : KArchive(dev)
{
}


KIOMultics::~KIOMultics()
{
    if (isOpen()) close();
}


static QDateTime decodeDate(const QByteArray &mdate)
{
    //  0000000000111111
    //  0123456789012345
    //
    // "11/04/82  1938.1"

    int year = mdate.mid(6, 2).toInt();
    year += (year<30 ? 2000 : 1900);
    QDate dt(year, mdate.mid(0, 2).toInt(), mdate.mid(3, 2).toInt());
    QTime tm(mdate.mid(10, 2).toInt(), mdate.mid(12, 2).toInt(), qRound(mdate.mid(14, 2).toDouble()*60));
    return (QDateTime(dt, tm, Qt::LocalTime));
}


static QString formatMagic(const QByteArray &data)
{
    QString result;

    for (int i = 0; i<data.size(); ++i)
    {
        char c = data.at(i);
        result += QString(QLatin1String("\\%1")).arg(static_cast<int>(c), 3, 8, QLatin1Char('0'));
    }
    return (result);
}


bool KIOMultics::doPrepareWriting(const QString &, const QString &, const QString &,
                           qint64, mode_t, const QDateTime &, const QDateTime &, const QDateTime &)
{
    qCWarning(KIOMulticsLog) << "doPrepareWriting not implemented";
    setErrorString(i18n("No write support for Multics archives"));
    return (false);
}


bool KIOMultics::doFinishWriting(qint64)
{
    qCWarning(KIOMulticsLog) << "doFinishWriting not implemented";
    setErrorString(i18n("No write support for Multics archives"));
    return (false);
}


bool KIOMultics::doWriteDir(const QString &, const QString &, const QString &,
                     mode_t, const QDateTime &, const QDateTime &, const QDateTime &)
{
    qCWarning(KIOMulticsLog) << "doWriteDir not implemented";
    setErrorString(i18n("No write support for Multics archives"));
    return (false);
}


bool KIOMultics::doWriteSymLink(const QString &, const QString &, const QString &,
                         const QString &, mode_t, const QDateTime &, const QDateTime &, const QDateTime &)
{
    qCWarning(KIOMulticsLog) << "doWriteSymLink not implemented";
    setErrorString(i18n("No write support for Multics archives"));
    return (false);
}

bool KIOMultics::openArchive(QIODevice::OpenMode openMode)
{
    if (openMode==QIODevice::WriteOnly) return (true);
    if (openMode!=QIODevice::ReadOnly && openMode!=QIODevice::ReadWrite)
    {
        setErrorString(i18n("Unsupported open mode %1", openMode));
        return (false);
    }

    QIODevice *dev = device();
    if (dev==NULL) return (false);

    const QByteArray hbgn = QByteArray::fromRawData(ARCHIVE_HBGN, 8);
    const QByteArray hend = QByteArray::fromRawData(ARCHIVE_HEND, 8);
    const QByteArray chdr = QByteArray::fromRawData(ARCHIVE_CHDR, 8);

    struct passwd *pwd = getpwuid(getuid());
    Q_ASSERT(pwd!=NULL);
    const QString username = QString::fromLocal8Bit(pwd->pw_name);

    struct group *grp = getgrgid(getgid());
    Q_ASSERT(grp!=NULL);
    const QString usergroup = QString::fromLocal8Bit(grp->gr_name);

    QByteArray magic = dev->read(8);
    if (magic!=hbgn)
    {
        setErrorString(i18n("Invalid magic file header '%1', expected '%2'", formatMagic(magic), formatMagic(hbgn)));
        return (false);
    }
    dev->seek(0);					// reset to start of archive

    while (!dev->atEnd())
    {
        struct ArchiveHeader header;
    
        dev->seek(dev->pos()+(4-(dev->pos() % 4)) % 4);	// headers are padded to word boundary

        qDebug() << "at file offset" << dev->pos();


        if (dev->read(((char *) &header), sizeof(struct ArchiveHeader))!=sizeof(struct ArchiveHeader))
        {						// read header
            qDebug() << "Couldn't read header";
            return (true);				// probably EOF/trailing junk
        }

        QByteArray data = QByteArray::fromRawData(header.name, sizeof(header.name));
        QString name = QString::fromLocal8Bit(data);
        name = name.trimmed();				// sanitise filename
        name.replace(QLatin1Char('/'), QLatin1String("_"));
        qDebug() << "  name" << name;

        if (name==QLatin1String("bull_copyright_notice.txt"))
        {						// just appended to archive
            qDebug() << "Exiting at end of archive";	// so don't check header magic
            break;
        }

        data = QByteArray::fromRawData(header.hbgn, sizeof(header.hbgn));
        if (data!=hbgn)
        {
            if (data==chdr)
            {
                qDebug() << "Exiting at start of copyright";
                break;
            }
            else
            {
                setErrorString(i18n("Invalid magic archive header '%1', expected '%2'", formatMagic(data), formatMagic(hbgn)));
                return (false);
            }
        }

        QByteArray timeup = QByteArray::fromRawData(header.timeup, sizeof(header.timeup));
        qDebug() << "  timeup" << timeup;

        QByteArray timecr = QByteArray::fromRawData(header.time, sizeof(header.time));
        qDebug() << "  timecr" << timecr;

        data = QByteArray::fromRawData(header.mode, sizeof(header.mode));
        QString modestr = QString::fromLocal8Bit(data).trimmed();
        int unixmask = umask(0); umask(unixmask);

        int unixmode = 0;
        if (modestr.contains(QLatin1Char('r'))) unixmode |= S_IRUSR|S_IRGRP|S_IROTH;
        if (modestr.contains(QLatin1Char('e'))) unixmode |= S_IXUSR|S_IXGRP|S_IXOTH;
        if (modestr.contains(QLatin1Char('w'))) unixmode |= S_IWUSR|S_IWGRP|S_IWOTH;
        unixmode &= ~unixmask;
        qDebug() << "  mode" << modestr << "->" << QString(QLatin1String("%1")).arg(unixmode, 4, 8, QLatin1Char('0'));

        data = QByteArray::fromRawData(header.bcnt, sizeof(header.bcnt));
        uint size = QString::fromLocal8Bit(data).toUInt()/9;
        qDebug() << "  size" << size;

        data = QByteArray::fromRawData(header.hend, sizeof(header.hend));
        if (data!=hend)
        {
            setErrorString(i18n("Invalid magic archive trailer '%1', expected '%2'", formatMagic(data), formatMagic(hend)));
            return (false);
        }

        KArchiveEntry *entry = new KArchiveFile(this,
                                                name,
                                                unixmode,
                                                decodeDate(timeup),
                                                username,
                                                usergroup,
                                                QString::null, // symlink
                                                dev->pos(),
                                                size);
        rootDir()->addEntry(entry);			// no directories, so everything in root
        dev->seek(dev->pos()+size);			// skip contents
    }

    return (true);
}


bool KIOMultics::closeArchive()
{
    return (true);
}


void KIOMultics::setErrorString(const QString &msg)
{
    qWarning() << msg;
    KArchive::setErrorString(msg);
}


void KIOMultics::virtual_hook(int id, void *data)
{
    KArchive::virtual_hook(id, data);
}
