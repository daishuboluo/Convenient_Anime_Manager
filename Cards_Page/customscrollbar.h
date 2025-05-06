#ifndef CUSTOMSCROLLBAR_H
#define CUSTOMSCROLLBAR_H

#include <QScrollBar>
#include <QPainter>
#include <QStyleOptionSlider>
#include <QEvent>
#include "../Singleton_Set/central_bundle_bridge.h"
#include <QPropertyAnimation>

class CustomScrollBar : public QScrollBar
{
    Q_OBJECT
        Q_PROPERTY(int navWidth READ navWidth WRITE setNavWidth FINAL)
        Q_PROPERTY(QColor handleColor READ handleColor WRITE setHandleColor FINAL)

public:
    explicit CustomScrollBar(QWidget* parent = nullptr);

    QPropertyAnimation* animation;
    QPropertyAnimation* animation2;

    int navWidth() const;
    void setNavWidth(int newNavWidth);

    QColor handleColor() const;
    void setHandleColor(const QColor& newHandleColor);

protected:
    void paintEvent(QPaintEvent* event) override;
    bool event(QEvent* event) override;

private:
    int m_navWidth = 5;
    QColor m_handleColor = QColor(255, 192, 228, 255);
};

#endif // CUSTOMSCROLLBAR_H
