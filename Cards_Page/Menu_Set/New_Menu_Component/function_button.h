#ifndef FUNCTION_BUTTON_H
#define FUNCTION_BUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QMouseEvent>
#include <QPainterPath>
#include <QPropertyAnimation>
#include <QEvent>
#include <QGraphicsDropShadowEffect>
#include "../../../Singleton_Set/image_processing.h"

class Function_Button : public QPushButton
{
    Q_OBJECT
        Q_PROPERTY(QPixmap Function_Button_pixmap READ Function_Button_pixmap WRITE setFunction_Button_pixmap FINAL)
        Q_PROPERTY(QColor Bottom_Edge_Color READ Bottom_Edge_Color WRITE setBottom_Edge_Color FINAL)

public:
    explicit Function_Button(QPixmap m_Function_Button_pixmap, QWidget* parent = nullptr);
    QPropertyAnimation* animation;

public:
    QPixmap Function_Button_pixmap() const;
    void setFunction_Button_pixmap(const QPixmap& newFunction_Button_pixmap);
    QColor Bottom_Edge_Color() const;
    void setBottom_Edge_Color(const QColor& newBottom_Edge_Color);

protected:
    void paintEvent(QPaintEvent* event) override;
    bool event(QEvent* event) override;

private:
    QPixmap m_Function_Button_pixmap;
    QColor m_Bottom_Edge_Color = QColor(241, 245, 249, 255);
};

#endif // FUNCTION_BUTTON_H
