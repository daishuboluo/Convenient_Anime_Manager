#ifndef BUTTON_SLIDER_COMPONENT_H
#define BUTTON_SLIDER_COMPONENT_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QPropertyAnimation>
#include <QResizeEvent>
#include "horizontal_button.h"
#include "../Singleton_Set/central_bundle_bridge.h"

class Button_Slider_Component : public QWidget
{
    Q_OBJECT
        Q_PROPERTY(QPoint But_pos READ But_pos WRITE setBut_pos NOTIFY But_posChanged FINAL)
        Q_PROPERTY(int but_w READ but_w WRITE setBut_w FINAL)

public:
    explicit Button_Slider_Component(QWidget* parent = nullptr);
    QList<Horizontal_Button*> Buttons_list;
    void Get_Button_Number();
    int but_h;
    int m_but_w;
    QPropertyAnimation* animation3;
    void Ima_zen();
    int Animation_Time = 160;
    int m_Bar_Moving_Point;
    Horizontal_Button* m_Button_Pointer;

public slots:
    void animation(QPoint Pos, Horizontal_Button* button);
    void Set_Button_Pointer(Horizontal_Button* button);

public:
    QPoint But_pos() const;
    void setBut_pos(QPoint newBut_pos);
    int but_w() const;
    void setBut_w(int newBut_w);
    void Set_Button_Color_Show(bool isShow);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void moveEvent(QMoveEvent* event) override;

signals:
    void posChanged();
    void But_posChanged();

private:
    QPoint dragPos;
    QPoint m_But_pos;
    bool m_isDraging = false;
    QPoint m_dragStartPosition;
    bool m_isDragging = false;
    bool m_isShow_Button_Color = false;
    QPoint m_Mouse_Down_Pos;
    QPoint m_Mouse_Up_Pos;
    qint64 m_Mouse_Down_Time;
    qint64 m_Mouse_Up_Time;
    qreal Calculate_Speed();
    qreal m_velocity;
    qreal m_friction = 0.95;
    qreal m_minSpeed = 0.1;
    QTimer* m_animationTimer;
    void updateAnimation();
    qreal m_isNegative = 0;
};

#endif // BUTTON_SLIDER_COMPONENT_H
