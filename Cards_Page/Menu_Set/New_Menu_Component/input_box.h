#ifndef INPUT_BOX_H
#define INPUT_BOX_H

#include <QLineEdit>
#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QApplication>
#include <QPropertyAnimation>
#include "../../../Singleton_Set/image_processing.h"

class Input_Box : public QLineEdit
{
    Q_OBJECT
        Q_PROPERTY(int widinput READ widinput WRITE setWidinput FINAL)

public:
    explicit Input_Box(QString PlaceholderText, QWidget* parent = nullptr);
    QPropertyAnimation* animation;

    int widinput() const;
    void setWidinput(int newWidinput);
    void set_Input_Box_Focus();

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;

private:
    int m_widinput = 0;
};

#endif // INPUT_BOX_H
