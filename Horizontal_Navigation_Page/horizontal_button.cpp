#include "horizontal_button.h"

Horizontal_Button::Horizontal_Button(QWidget* parent)
    : QPushButton{ parent }
{
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, Qt::transparent);
    this->setPalette(palette);

    this->setCursor(Qt::PointingHandCursor);
    text_size = this->height() / 3;
    this->resize(100, 59);
    this->animation_start();

    connect(this, &Horizontal_Button::Button_name_signal, RELAY_SIGNALS, &Central_Bundle_Bridge::Forward_Self_Button_Name);
    connect(this, &Horizontal_Button::Button_Clicked_signal, RELAY_SIGNALS, &Central_Bundle_Bridge::Set_Button_ColorVisible);
}

void Horizontal_Button::animation_start()
{
    animation = new QPropertyAnimation(this, "text_color");
    animation->setDuration(222);
    animation->setStartValue(m_text_color);
    animation->setEndValue(QColor(255, 65, 129, 255));
}

void Horizontal_Button::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(m_text_color);

    QFont font;
    font.setPixelSize(text_size);
    font.setBold(true);
    painter.setFont(font);

    if (m_Button_Clicked_Status)
        painter.setPen(QColor(255, 255, 255, 255));
    else
        painter.setPen(QColor(0, 0, 0, 255));

    painter.drawText(rect(), Qt::AlignCenter, Button_name);
}

void Horizontal_Button::resizeEvent(QResizeEvent* event)
{
    text_size = this->height() / 3;
    QPushButton::resizeEvent(event);
}

bool Horizontal_Button::event(QEvent* event)
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
    return QPushButton::event(event);
}

void Horizontal_Button::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        Is_Dragging = true;
        emit Button_signal(this);
    }
    QWidget::mousePressEvent(event);
}

void Horizontal_Button::mouseMoveEvent(QMouseEvent* event)
{
    if (Is_Dragging)
    {
        this->Is_Dragging = false;
    }
    QWidget::mouseMoveEvent(event);
}

void Horizontal_Button::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (Is_Dragging)
        {
            emit Button_rect_signal(this->pos(), this);
            emit Button_name_signal(Button_name);
            emit Button_Clicked_signal();
        }
    }
    QWidget::mouseReleaseEvent(event);
}

QColor Horizontal_Button::text_color() const
{
    return m_text_color;
}

void Horizontal_Button::setText_color(const QColor& newText_color)
{
    if (m_text_color == newText_color)
        return;
    m_text_color = newText_color;
    update();
}

bool Horizontal_Button::Button_Clicked_Status() const
{
    return m_Button_Clicked_Status;
}

void Horizontal_Button::setButton_Clicked_Status(bool newButton_Clicked_Status)
{
    m_Button_Clicked_Status = newButton_Clicked_Status;
    update();
}
