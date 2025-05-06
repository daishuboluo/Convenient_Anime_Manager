#include "back_button.h"

Back_Button::Back_Button(QWidget* parent) : QPushButton(parent)
{
    this->setCursor(Qt::PointingHandCursor);
    this->update_triangle();
    animation = new QPropertyAnimation(this, "color");
    animation->setDuration(600);
    animation->setStartValue(m_color);
    animation->setEndValue(QColor(0, 0, 0, 255));
    animation->setEasingCurve(QEasingCurve::Linear);

    connect(this, &Back_Button::Back_clicked, RELAY_SIGNALS, &Central_Bundle_Bridge::Exit_Playback_Page);
    connect(this, &Back_Button::Back_clicked, this, &Back_Button::reset_status);
    connect(this, &Back_Button::reset_playback_window, RELAY_SIGNALS, &Central_Bundle_Bridge::Forward_Reset_Playback_Window);
}

void Back_Button::update_triangle()
{
    p1 = QPoint(width() * 0.1, 0);
    p2 = QPoint(width() * 0.8, height() * 0.5);
    p3 = QPoint(width() * 0.1, height());
}

void Back_Button::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(m_color);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);

    QBrush brush;
    brush.setColor(m_color);
    brush.setStyle(Qt::Dense2Pattern);
    painter.setBrush(brush);

    QPolygon polygon;
    polygon.append(p1);
    polygon.append(p2);
    polygon.append(p3);
    painter.drawPolygon(polygon);
}

void Back_Button::reset_status()
{
    STATUS_GROUPS->setIs_Accepting_Anime_Info(true);
    STATUS_GROUPS->setIs_Accepting_Create_Episodes(true);
    emit reset_playback_window();
}

bool Back_Button::event(QEvent* event)
{
    if (event->type() == QEvent::Enter)
    {
        animation->setDirection(QAbstractAnimation::Forward);
        animation->start();
    }
    else if (event->type() == QEvent::Leave)
    {
        animation->setDirection(QAbstractAnimation::Backward);
        animation->start();
    }
    return QWidget::event(event);
}

void Back_Button::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit Back_clicked();
    }
    QWidget::mousePressEvent(event);
}

void Back_Button::resizeEvent(QResizeEvent* event)
{
    this->update_triangle();
}

QColor Back_Button::get_color() const
{
    return m_color;
}

void Back_Button::set_color(const QColor& newColor)
{
    m_color = newColor;
    update();
}
