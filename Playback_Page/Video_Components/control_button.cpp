#include "control_button.h"

Control_Button::Control_Button(QString Button_pixmap, QString hover_text, QWidget* parent)
    : QPushButton(parent)
{
    this->m_Button_pixmap = QPixmap(Button_pixmap);
    this->m_hover_text = hover_text;
    this->setToolTip(m_hover_text);
    this->setCursor(Qt::PointingHandCursor);

    m_animation = new QPropertyAnimation(this, "hover_color");
    m_animation->setDuration(200);
    m_animation->setStartValue(m_hover_color);
    m_animation->setEndValue(QColor(255, 255, 255, 66));

    update();
}

void Control_Button::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_hover_color);
    painter.drawRect(this->rect());

    QRect rect;
    rect.setHeight(this->height() * 0.80);
    rect.setWidth(this->height() * 0.80);
    rect.moveCenter(QPoint(this->rect().center().x(), this->rect().center().y()));

    painter.drawPixmap(rect, m_Button_pixmap);
}

bool Control_Button::event(QEvent* event)
{
    if (event->type() == QEvent::Enter)
    {
        m_animation->setDirection(QAbstractAnimation::Forward);
        m_animation->start();
    }
    else if (event->type() == QEvent::Leave)
    {
        m_animation->setDirection(QAbstractAnimation::Backward);
        m_animation->start();
    }
    return QPushButton::event(event);
}

void Control_Button::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        update();
    }
}

void Control_Button::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit Control_Button_clicked();
    }
}

QColor Control_Button::hover_color() const
{
    return m_hover_color;
}

void Control_Button::Sethover_color(const QColor& newHover_color)
{
    m_hover_color = newHover_color;
    update();
}
