#include "image_processing.h"

Q_GLOBAL_STATIC(Image_Processing, fileRelatedInstance)

Image_Processing::Image_Processing(QObject* parent)
    : QObject{ parent }
{ }

Image_Processing* Image_Processing::instance() {
    return fileRelatedInstance;
}

template <class T>
void Image_Processing::qt_memrotate270_tiled_unpacked(const T* src, int w, int h, int sstride, T* dest, int dstride) {
    const int numTilesX = (w + tileSize - 1) / tileSize;
    const int numTilesY = (h + tileSize - 1) / tileSize;

    for (int tx = 0; tx < numTilesX; ++tx) {
        const int startx = tx * tileSize;
        const int stopx = qMin(startx + tileSize, w);

        for (int ty = 0; ty < numTilesY; ++ty) {
            const int starty = h - 1 - ty * tileSize;
            const int stopy = qMax(starty - tileSize, 0);

            for (int x = startx; x < stopx; ++x) {
                T* d = (T*)((char*)dest + x * dstride) + h - 1 - starty;
                const char* s = (const char*)(src + x) + starty * sstride;
                for (int y = starty; y >= stopy; --y) {
                    *d++ = *(const T*)s;
                    s -= sstride;
                }
            }
        }
    }
}

template <class T>
void Image_Processing::qt_memrotate270_template(const T* src, int srcWidth, int srcHeight, int srcStride, T* dest, int dstStride) {
    qt_memrotate270_tiled_unpacked<T>(src, srcWidth, srcHeight, srcStride, dest, dstStride);
}

template <class T>
void Image_Processing::qt_memrotate90_tiled_unpacked(const T* src, int w, int h, int sstride, T* dest, int dstride) {
    const int numTilesX = (w + tileSize - 1) / tileSize;
    const int numTilesY = (h + tileSize - 1) / tileSize;

    for (int tx = 0; tx < numTilesX; ++tx) {
        const int startx = w - tx * tileSize - 1;
        const int stopx = qMax(startx - tileSize, 0);

        for (int ty = 0; ty < numTilesY; ++ty) {
            const int starty = ty * tileSize;
            const int stopy = qMin(starty + tileSize, h);

            for (int x = startx; x >= stopx; --x) {
                T* d = (T*)((char*)dest + (w - x - 1) * dstride) + starty;
                const char* s = (const char*)(src + x) + starty * sstride;
                for (int y = starty; y < stopy; ++y) {
                    *d++ = *(const T*)(s);
                    s += sstride;
                }
            }
        }
    }
}

template <class T>
void Image_Processing::qt_memrotate90_template(const T* src, int srcWidth, int srcHeight, int srcStride, T* dest, int dstStride) {
    qt_memrotate90_tiled_unpacked<T>(src, srcWidth, srcHeight, srcStride, dest, dstStride);
}

template <int shift>
inline int qt_static_shift(int value) {
    if (shift == 0)
        return value;
    else if (shift > 0)
        return value << (uint(shift) & 0x1f);
    else
        return value >> (uint(-shift) & 0x1f);
}

template <int aprec, int zprec>
void Image_Processing::qt_blurinner(uchar* bptr, int& zR, int& zG, int& zB, int& zA, int alpha) {
    QRgb* pixel = (QRgb*)bptr;

    const int A_zprec = qt_static_shift<zprec - 24>(*pixel) & (0xff << zprec);
    const int R_zprec = qt_static_shift<zprec - 16>(*pixel) & (0xff << zprec);
    const int G_zprec = qt_static_shift<zprec - 8>(*pixel) & (0xff << zprec);
    const int B_zprec = qt_static_shift<zprec>(*pixel) & (0xff << zprec);

    const int zR_zprec = zR >> aprec;
    const int zG_zprec = zG >> aprec;
    const int zB_zprec = zB >> aprec;
    const int zA_zprec = zA >> aprec;

    zR += alpha * (R_zprec - zR_zprec);
    zG += alpha * (G_zprec - zG_zprec);
    zB += alpha * (B_zprec - zB_zprec);
    zA += alpha * (A_zprec - zA_zprec);

    *pixel = qt_static_shift<24 - zprec - aprec>(zA & (0xff << (zprec + aprec))) |
        qt_static_shift<16 - zprec - aprec>(zR & (0xff << (zprec + aprec))) |
        qt_static_shift<8 - zprec - aprec>(zG & (0xff << (zprec + aprec))) |
        qt_static_shift<-zprec - aprec>(zB & (0xff << (zprec + aprec)));
}

const int alphaIndex = (QSysInfo::ByteOrder == QSysInfo::BigEndian ? 0 : 3);

template <int aprec, int zprec>
void Image_Processing::qt_blurinner_alphaOnly(uchar* bptr, int& z, int alpha) {
    const int A_zprec = int(*(bptr)) << zprec;
    const int z_zprec = z >> aprec;
    z += alpha * (A_zprec - z_zprec);
    *(bptr) = z >> (zprec + aprec);
}

template <int aprec, int zprec, bool alphaOnly>
void Image_Processing::qt_blurrow(QImage& im, int line, int alpha) {
    uchar* bptr = im.scanLine(line);
    int zR = 0, zG = 0, zB = 0, zA = 0;

    if (alphaOnly && im.format() != QImage::Format_Indexed8)
        bptr += alphaIndex;

    const int stride = im.depth() >> 3;
    const int im_width = im.width();
    for (int index = 0; index < im_width; ++index) {
        if (alphaOnly)
            qt_blurinner_alphaOnly<aprec, zprec>(bptr, zA, alpha);
        else
            qt_blurinner<aprec, zprec>(bptr, zR, zG, zB, zA, alpha);
        bptr += stride;
    }

    bptr -= stride;
    for (int index = im_width - 2; index >= 0; --index) {
        bptr -= stride;
        if (alphaOnly)
            qt_blurinner_alphaOnly<aprec, zprec>(bptr, zA, alpha);
        else
            qt_blurinner<aprec, zprec>(bptr, zR, zG, zB, zA, alpha);
    }
}

template <int aprec, int zprec, bool alphaOnly>
void Image_Processing::expblur(QImage& img, qreal radius, bool improvedQuality, int transposed) {
    if (improvedQuality)
        radius *= qreal(0.5);

    Q_ASSERT(img.format() == QImage::Format_ARGB32_Premultiplied || img.format() == QImage::Format_RGB32 ||
        img.format() == QImage::Format_Indexed8 || img.format() == QImage::Format_Grayscale8);

    const qreal cutOffIntensity = 2;
    int alpha = radius <= qreal(1e-5)
        ? ((1 << aprec) - 1) : qRound((1 << aprec) * (1 - qPow(cutOffIntensity * (1 / qreal(255)), 1 / radius)));

    int img_height = img.height();
    for (int row = 0; row < img_height; ++row) {
        for (int i = 0; i <= int(improvedQuality); ++i)
            qt_blurrow<aprec, zprec, alphaOnly>(img, row, alpha);
    }

    QImage temp(img.height(), img.width(), img.format());
    temp.setDevicePixelRatio(img.devicePixelRatioF());
    if (transposed >= 0) {
        if (img.depth() == 8) {
            qt_memrotate270_template(reinterpret_cast<const quint8*>(img.bits()),
                img.width(),
                img.height(),
                img.bytesPerLine(),
                reinterpret_cast<quint8*>(temp.bits()),
                temp.bytesPerLine());
        }
        else {
            qt_memrotate270_template(reinterpret_cast<const quint32*>(img.bits()),
                img.width(),
                img.height(),
                img.bytesPerLine(),
                reinterpret_cast<quint32*>(temp.bits()),
                temp.bytesPerLine());
        }
    }
    else {
        if (img.depth() == 8) {
            qt_memrotate90_template(reinterpret_cast<const quint8*>(img.bits()),
                img.width(),
                img.height(),
                img.bytesPerLine(),
                reinterpret_cast<quint8*>(temp.bits()),
                temp.bytesPerLine());
        }
        else {
            qt_memrotate90_template(reinterpret_cast<const quint32*>(img.bits()),
                img.width(),
                img.height(),
                img.bytesPerLine(),
                reinterpret_cast<quint32*>(temp.bits()),
                temp.bytesPerLine());
        }
    }

    img_height = temp.height();
    for (int row = 0; row < img_height; ++row) {
        for (int i = 0; i <= int(improvedQuality); ++i)
            qt_blurrow<aprec, zprec, alphaOnly>(temp, row, alpha);
    }

    if (transposed == 0) {
        if (img.depth() == 8) {
            qt_memrotate90_template(reinterpret_cast<const quint8*>(temp.bits()),
                temp.width(),
                temp.height(),
                temp.bytesPerLine(),
                reinterpret_cast<quint8*>(img.bits()),
                img.bytesPerLine());
        }
        else {
            qt_memrotate90_template(reinterpret_cast<const quint32*>(temp.bits()),
                temp.width(),
                temp.height(),
                temp.bytesPerLine(),
                reinterpret_cast<quint32*>(img.bits()),
                img.bytesPerLine());
        }
    }
    else {
        img = temp;
    }
}

QImage Image_Processing::qt_halfScaled(const QImage& source) {
    if (source.width() < 2 || source.height() < 2)
        return QImage();

    QImage srcImage = source;

    if (source.format() == QImage::Format_Indexed8 || source.format() == QImage::Format_Grayscale8) {
        QImage dest(source.width() / 2, source.height() / 2, srcImage.format());
        dest.setDevicePixelRatio(source.devicePixelRatioF());

        const uchar* src = reinterpret_cast<const uchar*>(const_cast<const QImage&>(srcImage).bits());
        int sx = srcImage.bytesPerLine();
        int sx2 = sx << 1;

        uchar* dst = reinterpret_cast<uchar*>(dest.bits());
        int dx = dest.bytesPerLine();
        int ww = dest.width();
        int hh = dest.height();

        for (int y = hh; y; --y, dst += dx, src += sx2) {
            const uchar* p1 = src;
            const uchar* p2 = src + sx;
            uchar* q = dst;
            for (int x = ww; x; --x, ++q, p1 += 2, p2 += 2)
                *q = ((int(p1[0]) + int(p1[1]) + int(p2[0]) + int(p2[1])) + 2) >> 2;
        }

        return dest;
    }
    else if (source.format() == QImage::Format_ARGB8565_Premultiplied) {
        QImage dest(source.width() / 2, source.height() / 2, srcImage.format());
        dest.setDevicePixelRatio(source.devicePixelRatioF());

        const uchar* src = reinterpret_cast<const uchar*>(const_cast<const QImage&>(srcImage).bits());
        int sx = srcImage.bytesPerLine();
        int sx2 = sx << 1;

        uchar* dst = reinterpret_cast<uchar*>(dest.bits());
        int dx = dest.bytesPerLine();
        int ww = dest.width();
        int hh = dest.height();

        for (int y = hh; y; --y, dst += dx, src += sx2) {
            const uchar* p1 = src;
            const uchar* p2 = src + sx;
            uchar* q = dst;
            for (int x = ww; x; --x, q += 3, p1 += 6, p2 += 6) {
                q[0] = AVG(AVG(p1[0], p1[3]), AVG(p2[0], p2[3]));
                const quint16 p16_1 = (p1[2] << 8) | p1[1];
                const quint16 p16_2 = (p1[5] << 8) | p1[4];
                const quint16 p16_3 = (p2[2] << 8) | p2[1];
                const quint16 p16_4 = (p2[5] << 8) | p2[4];
                const quint16 result = AVG16(AVG16(p16_1, p16_2), AVG16(p16_3, p16_4));
                q[1] = result & 0xff;
                q[2] = result >> 8;
            }
        }

        return dest;
    }
    else if (source.format() != QImage::Format_ARGB32_Premultiplied && source.format() != QImage::Format_RGB32) {
        srcImage = source.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    }

    QImage dest(source.width() / 2, source.height() / 2, srcImage.format());
    dest.setDevicePixelRatio(source.devicePixelRatioF());

    const quint32* src = reinterpret_cast<const quint32*>(const_cast<const QImage&>(srcImage).bits());
    int sx = srcImage.bytesPerLine() >> 2;
    int sx2 = sx << 1;

    quint32* dst = reinterpret_cast<quint32*>(dest.bits());
    int dx = dest.bytesPerLine() >> 2;
    int ww = dest.width();
    int hh = dest.height();

    for (int y = hh; y; --y, dst += dx, src += sx2) {
        const quint32* p1 = src;
        const quint32* p2 = src + sx;
        quint32* q = dst;
        for (int x = ww; x; --x, q++, p1 += 2, p2 += 2)
            *q = AVG(AVG(p1[0], p1[1]), AVG(p2[0], p2[1]));
    }

    return dest;
}

void Image_Processing::qt_blurImage(QImage& blurImage, qreal radius, bool quality, bool alphaOnly, int transposed) {
    if (blurImage.format() != QImage::Format_ARGB32_Premultiplied && blurImage.format() != QImage::Format_RGB32) {
        blurImage = blurImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
    }

    qreal scale = 1;
    if (radius >= 4 && blurImage.width() >= 2 && blurImage.height() >= 2) {
        blurImage = qt_halfScaled(blurImage);
        scale = 2;
        radius *= qreal(0.5);
    }

    if (alphaOnly)
        expblur<12, 10, true>(blurImage, radius, quality, transposed);
    else
        expblur<12, 10, false>(blurImage, radius, quality, transposed);
}
