

#ifndef KIOMULTICS_H
#define KIOMULTICS_H

#include <karchive.h>

#include "kiomultics_export.h"

class QDateTime;

// /**
 // * KAr is a class for reading archives in ar format. Writing
 // * is not supported.
 // * @short A class for reading ar archives.
 // * @author Laurence Anderson <l.d.anderson@warwick.ac.uk>
 // */

class KIOMULTICS_EXPORT KIOMultics : public KArchive
{
    Q_DECLARE_TR_FUNCTIONS(KIOMultics)

public:
    /**
     * Creates an instance that operates on the given filename.
     *
     * @param filename is a local path (e.g. "/home/holger/myfile.archive")
     */
    explicit KIOMultics(const QString &filename);

    /**
     * Creates an instance that operates on the given device.
     * The device can be compressed (KFilterDev) or not (QFile, etc.).
     * @param dev the device to read from
     */
    explicit KIOMultics(QIODevice *dev);

    /**
     * If the ar file is still opened, then it will be
     * closed automatically by the destructor.
     */
    virtual ~KIOMultics();

protected:
    /*
     * Writing is not supported by this class, will always fail.
     * @return always false
     */
    bool doPrepareWriting(const QString &name, const QString &user, const QString &group, qint64 size,
                          mode_t perm, const QDateTime &atime, const QDateTime &mtime, const QDateTime &ctime) override;

    /*
     * Writing is not supported by this class, will always fail.
     * @return always false
     */
    bool doFinishWriting(qint64 size) override;

    /*
     * Writing is not supported by this class, will always fail.
     * @return always false
     */
    bool doWriteDir(const QString &name, const QString &user, const QString &group,
                    mode_t perm, const QDateTime &atime, const QDateTime &mtime, const QDateTime &ctime) override;

    bool doWriteSymLink(const QString &name, const QString &target,
                        const QString &user, const QString &group, mode_t perm,
                        const QDateTime &atime, const QDateTime &mtime, const QDateTime &ctime) override;

    /**
     * Opens the archive for reading.
     * Parses the directory listing of the archive
     * and creates the KArchiveDirectory/KArchiveFile entries.
     *
     */
    bool openArchive(QIODevice::OpenMode openMode) override;
    bool closeArchive() override;

protected:
    void virtual_hook(int id, void *data) override;

private:
    void setErrorString(const QString &msg);
};

#endif							// KIOMULTICS_H
