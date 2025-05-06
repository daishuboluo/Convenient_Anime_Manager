#include "button_slider_component.h"

Button_Slider_Component::Button_Slider_Component(QWidget* parent)
    : QWidget{ parent }
{
    this->resize(0, 59);
    this->Get_Button_Number();
    this->Ima_zen();

    m_animationTimer = new QTimer(this);
    connect(m_animationTimer, &QTimer::timeout, this, &Button_Slider_Component::updateAnimation);
    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::Show_All_Buttons, this, [this] {
        Set_Button_Color_Show(false);
        });
}

void Button_Slider_Component::Get_Button_Number()
{
    m_but_w = this->height() * 1.69;
    but_h = this->height() * 0.80;
}

void Button_Slider_Component::Ima_zen()
{
    int year = QDateTime::currentDateTime().date().year();
    int x = 0;
    year += 50;

    while (year != 1899)
    {
        Horizontal_Button* Button = new Horizontal_Button(this);
        Button->resize(m_but_w, but_h);
        Button->move(x, 0);
        Button->Button_name = QString::number(year);
        connect(Button, &Horizontal_Button::Button_rect_signal, this, &Button_Slider_Component::animation);
        connect(Button, &Horizontal_Button::Button_signal, this, &Button_Slider_Component::Set_Button_Pointer);
        Buttons_list.append(Button);
        x += Button->width() + Button->width() / 10;
        year--;
    }

    this->resize(x, 59);
    QString s = QString::number(QDateTime::currentDateTime().date().year());

    for (auto& i : Buttons_list)
    {
        if (i->Button_name == s)
        {
            m_But_pos = i->pos();
            this->move(-i->pos().x(), i->pos().y());
            return;
        }
    }
}

void Button_Slider_Component::animation(QPoint Pos, Horizontal_Button* button)
{
    if (m_isDraging) return;
    Set_Button_Color_Show(true);

    for (auto& i : Buttons_list) i->setText_color(QColor(0, 0, 0, 255));
    for (auto& i : Buttons_list)
    {
        if (i == button) i->setButton_Clicked_Status(true);
        else i->setButton_Clicked_Status(false);
    }

    QPropertyAnimation* animation = new QPropertyAnimation(this, "But_pos");
    animation->setDuration(Animation_Time * 2);
    animation->setStartValue(this->m_But_pos);
    animation->setEndValue(Pos);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    QPropertyAnimation* animation2 = new QPropertyAnimation(this, "pos");
    animation2->setDuration(Animation_Time);
    animation2->setStartValue(this->pos());
    animation2->setEndValue(QPoint(-Pos.x() + m_Bar_Moving_Point - Buttons_list[0]->width() / 2, Pos.y()));
    animation2->start(QAbstractAnimation::DeleteWhenStopped);
}

void Button_Slider_Component::Set_Button_Pointer(Horizontal_Button* button)
{
    m_Button_Pointer = button;
}

void Button_Slider_Component::Set_Button_Color_Show(bool isShow)
{
    m_isShow_Button_Color = isShow;
    for (auto& i : Buttons_list)
    {
        i->setButton_Clicked_Status(false);
    }
    update();
}

void Button_Slider_Component::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    if (m_isShow_Button_Color) painter.setBrush(QColor(255, 65, 129, 255));
    painter.drawRoundedRect(m_But_pos.x(), m_But_pos.y(), m_but_w, but_h, 10, 10);
}

void Button_Slider_Component::resizeEvent(QResizeEvent* event)
{
    this->Get_Button_Number();
    QWidget::resizeEvent(event);
}

void Button_Slider_Component::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragStartPosition = event->pos();
        m_isDragging = true;
        m_Mouse_Down_Time = QDateTime::currentMSecsSinceEpoch();
        m_Mouse_Down_Pos = event->globalPos();
        event->accept();
    }
    else
    {
        QWidget::mousePressEvent(event);
    }
}

void Button_Slider_Component::mouseMoveEvent(QMouseEvent* event)
{
    this->m_isDraging = true;

    if (m_isDragging && (event->buttons() & Qt::LeftButton))
    {
        QPoint delta = event->pos() - m_dragStartPosition;
        QPoint newPos = this->pos() + delta;

        int minX = qMin(0, parentWidget()->width() - width());
        newPos.setX(qBound(minX, newPos.x(), 0));
        newPos.setY(pos().y());

        move(newPos);
        event->accept();
    }
    else
    {
        QWidget::mouseMoveEvent(event);
    }
}

void Button_Slider_Component::mouseReleaseEvent(QMouseEvent* event)
{
    this->m_isDraging = false;

    if (event->button() == Qt::LeftButton && m_isDragging)
    {
        m_isDragging = false;
        m_Mouse_Up_Time = QDateTime::currentMSecsSinceEpoch();
        m_Mouse_Up_Pos = event->globalPos();
        m_velocity = Calculate_Speed();

        if (abs(m_velocity) > 2.0)
            m_animationTimer->start(16);
        event->accept();
    }
    else
    {
        QWidget::mouseReleaseEvent(event);
    }
}

void Button_Slider_Component::moveEvent(QMoveEvent* event)
{
    if (this->pos().x() > 0) move(0, 0);
    else if (this->parentWidget()->width() - this->width() > event->pos().x())
        move(this->parentWidget()->width() - this->width(), 0);

    QWidget::moveEvent(event);
}

qreal Button_Slider_Component::Calculate_Speed()
{
    int m_Move_Distance = m_Mouse_Up_Pos.x() - m_Mouse_Down_Pos.x();
    qint64 m_Move_Time = m_Mouse_Up_Time - m_Mouse_Down_Time;

    if (m_Move_Time == 0) return 0;

    if (m_Move_Distance > 0) m_isNegative = 15;
    else m_isNegative = -15;

    return abs(qreal(m_Move_Distance) / qreal(m_Move_Time));
}

void Button_Slider_Component::updateAnimation() {
    m_velocity *= m_friction;
    move(pos() + QPoint(m_velocity * m_isNegative, 0));

    if (qAbs(m_velocity) < m_minSpeed)
    {
        m_animationTimer->stop();
    }
}

QPoint Button_Slider_Component::But_pos() const
{
    return m_But_pos;
}

void Button_Slider_Component::setBut_pos(QPoint newBut_pos)
{
    if (m_But_pos == newBut_pos)
        return;
    m_But_pos = newBut_pos;
    update();
    emit But_posChanged();
}

int Button_Slider_Component::but_w() const
{
    return m_but_w;
}

void Button_Slider_Component::setBut_w(int newBut_w)
{
    m_but_w = newBut_w;
    update();
}
