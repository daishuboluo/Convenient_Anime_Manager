#include "File_Related.h"
#include <QDir>
#include <QFileInfo>

Q_GLOBAL_STATIC(File_Related, fileRelatedInstance)

File_Related::File_Related(QObject* parent)
    : QObject(parent)
{
}

File_Related* File_Related::instance()
{
    return fileRelatedInstance;
}

bool File_Related::hasVideoFiles(const QString& directoryPath) const
{
    QDir directory(directoryPath);
    if (!directory.exists()) {
        qWarning() << "目录不存在:" << directoryPath;
        return false;
    }

    QStringList files = directory.entryList(QDir::Files);
    for (const QString& file : files) {
        for (const QString& ext : m_videoExtensions) {
            if (file.endsWith(ext, Qt::CaseInsensitive)) {
                return true;
            }
        }
    }

    return false;
}

QByteArray File_Related::processAndCropImageToByteArray(const QString& imagePath) const
{
    QFileInfo fileInfo(imagePath);
    QString suffix = fileInfo.suffix().toLower();
    if (!m_imageExtensions.contains("." + suffix)) {
        return QByteArray();
    }

    QImage image;
    if (imagePath.startsWith(":/")) {
        image.load(imagePath);
    }
    else {
        image.load(imagePath);
    }

    if (image.isNull()) {
        return QByteArray();
    }

    int targetWidth = 283;
    int targetHeight = 409;
    QSize scaledSize;

    if (image.height() < targetHeight) {
        scaledSize = QSize(image.width() * targetHeight / image.height(), targetHeight);
    }
    else {
        scaledSize = QSize(targetWidth, image.height() * targetWidth / image.width());
    }

    QImage scaledImage = image.scaled(scaledSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    int x = (scaledImage.width() - targetWidth) / 2;
    int y = (scaledImage.height() - targetHeight) / 2;

    x = qMax(0, x);
    y = qMax(0, y);
    targetWidth = qMin(targetWidth, scaledImage.width());
    targetHeight = qMin(targetHeight, scaledImage.height());

    QImage croppedImage = scaledImage.copy(x, y, targetWidth, targetHeight);
    croppedImage.setDotsPerMeterX(300 * 100 / 2.54);
    croppedImage.setDotsPerMeterY(300 * 100 / 2.54);

    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);
    croppedImage.save(&buffer, "PNG");
    buffer.close();

    return imageData;
}

QStringList File_Related::getSortedVideoFiles(const QString& directoryPath) const
{
    QDir directory(directoryPath);
    if (!directory.exists()) {
        qWarning() << "目录不存在:" << directoryPath;
        return QStringList();
    }

    QStringList filters;
    for (const QString& ext : m_videoExtensions) {
        filters << "*" + ext;
    }

    QStringList files = directory.entryList(filters, QDir::Files);
    files = sortFilesNumerically(files);

    QStringList absolutePaths;
    for (const QString& file : files) {
        absolutePaths.append(directory.absoluteFilePath(file));
    }

    return absolutePaths;
}

QByteArray File_Related::convertImageToByteArray(const QString& imagePath) const
{
    QFileInfo fileInfo(imagePath);
    QString suffix = fileInfo.suffix().toLower();
    if (!m_imageExtensions.contains("." + suffix)) {
        return QByteArray();
    }

    QImage image;
    if (imagePath.startsWith(":/")) {
        if (!image.load(imagePath)) {
            return QByteArray();
        }
    }
    else {
        if (!image.load(imagePath)) {
            return QByteArray();
        }
    }

    if (image.isNull()) {
        return QByteArray();
    }

    QByteArray imageData;
    QBuffer buffer(&imageData);
    buffer.open(QIODevice::WriteOnly);

    if (suffix == "png") {
        image.save(&buffer, "PNG");
    }
    else if (suffix == "jpg" || suffix == "jpeg") {
        image.save(&buffer, "JPG");
    }

    buffer.close();
    return imageData;
}

QStringList File_Related::sortFilesNumerically(const QStringList& files) const
{
    QStringList sortedFiles = files;
    QCollator collator;
    collator.setNumericMode(true);

    std::sort(sortedFiles.begin(), sortedFiles.end(), [&collator](const QString& a, const QString& b) {
        return collator.compare(a, b) < 0;
        });

    return sortedFiles;
}
