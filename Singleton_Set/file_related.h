#ifndef FILE_RELATED_H
#define FILE_RELATED_H

#include <QObject>
#include <QString>
#include <QStringList>
#include <QCollator>
#include <QDir>
#include <QImageReader>
#include <QBuffer>
#include <QFileInfo>
#include <QImage>

#define FILE_RELATEDS File_Related::instance()

class File_Related : public QObject
{
    Q_OBJECT

public:
    explicit File_Related(QObject* parent = nullptr);
    static File_Related* instance();

    bool hasVideoFiles(const QString& directoryPath) const;
    QStringList getSortedVideoFiles(const QString& directoryPath) const;
    QByteArray convertImageToByteArray(const QString& imagePath) const;
    QByteArray processAndCropImageToByteArray(const QString& imagePath) const;

private:
    Q_DISABLE_COPY_MOVE(File_Related)
        QStringList sortFilesNumerically(const QStringList& files) const;

    const QStringList m_videoExtensions = { ".mkv", ".mp4", ".avi", ".mov", ".wmv", ".flv", ".m4v" };
    const QStringList m_imageExtensions = { ".png", ".jpg", ".jpeg", ".webp" };
};

#endif // FILE_RELATED_H
