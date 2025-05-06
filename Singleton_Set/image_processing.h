#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include <QObject>
#include <QImage>

#define IMAGE_PROCESSING Image_Processing::instance()
#define AVG(a, b) (((((a) ^ (b)) & 0xfefefefeUL) >> 1) + ((a) & (b)))
#define AVG16(a, b) (((((a) ^ (b)) & 0xf7deUL) >> 1) + ((a) & (b)))

class Image_Processing : public QObject
{
    Q_OBJECT
public:
    explicit Image_Processing(QObject* parent = nullptr);
    static Image_Processing* instance();

    void qt_blurImage(QImage& blurImage, qreal radius, bool quality, bool alphaOnly, int transposed = 0);

    template<class T>
    void qt_memrotate270_tiled_unpacked(const T* src, int w, int h, int sstride, T* dest, int dstride);

    template<class T>
    void qt_memrotate270_template(const T* src, int srcWidth, int srcHeight, int srcStride, T* dest, int dstStride);

    template<class T>
    void qt_memrotate90_tiled_unpacked(const T* src, int w, int h, int sstride, T* dest, int dstride);

    template<class T>
    void qt_memrotate90_template(const T* src, int srcWidth, int srcHeight, int srcStride, T* dest, int dstStride);

    template<int aprec, int zprec>
    void qt_blurinner(uchar* bptr, int& zR, int& zG, int& zB, int& zA, int alpha);

    template<int aprec, int zprec>
    void qt_blurinner_alphaOnly(uchar* bptr, int& z, int alpha);

    template<int aprec, int zprec, bool alphaOnly>
    void qt_blurrow(QImage& im, int line, int alpha);

    template<int aprec, int zprec, bool alphaOnly>
    void expblur(QImage& img, qreal radius, bool improvedQuality = false, int transposed = 0);

    QImage qt_halfScaled(const QImage& source);

private:
    Q_DISABLE_COPY_MOVE(Image_Processing)
        const int tileSize = 32;
};

#endif // IMAGE_PROCESSING_H
