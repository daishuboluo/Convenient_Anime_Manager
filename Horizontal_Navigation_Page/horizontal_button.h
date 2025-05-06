#ifndef HORIZONTAL_BUTTON_H
#define HORIZONTAL_BUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QResizeEvent>
#include <QPropertyAnimation>
#include "../Singleton_Set/central_bundle_bridge.h"

class Horizontal_Button : public QPushButton
{
    Q_OBJECT
        Q_PROPERTY(QColor text_color READ text_color WRITE setText_color FINAL)
        Q_PROPERTY(bool Button_Clicked_Status READ Button_Clicked_Status WRITE setButton_Clicked_Status FINAL)

public:
    explicit Horizontal_Button(QWidget* parent = nullptr);
    QString Button_name;
    QRect Button_rect;
    QPropertyAnimation* animation;
    int text_size;
    bool Is_Dragging = true;

    void animation_start();
    QColor text_color() const;
    void setText_color(const QColor& newText_color);
    bool Button_Clicked_Status() const;
    void setButton_Clicked_Status(bool newButton_Clicked_Status);

signals:
    void Button_rect_signal(QPoint rect, Horizontal_Button* button);
    void Button_signal(Horizontal_Button* button);
    void Button_name_signal(QString name);
    void Button_Clicked_signal();

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    bool event(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private:
    QColor m_text_color = QColor(0, 0, 0, 255);
    bool m_Button_Clicked_Status = false;
};

#endif // HORIZONTAL_BUTTON_H
