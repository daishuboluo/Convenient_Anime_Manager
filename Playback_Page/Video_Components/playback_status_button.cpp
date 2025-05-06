#include "playback_status_button.h"

Playback_Status_Button::Playback_Status_Button(const QString& play_image_path, const QString& pause_image_path, QWidget* parent)
    : QRadioButton(parent)
{
    this->play_image_path = QPixmap(play_image_path);
    this->pause_image_path = QPixmap(pause_image_path);

    m_animation = new QPropertyAnimation(this, "hover_color");
    m_animation->setDuration(200);
    m_animation->setStartValue(m_hover_color);
    m_animation->setEndValue(QColor(255, 255, 255, 66));

    m_opacity_animation = new QPropertyAnimation(this, "opacity");
    m_opacity_animation->setDuration(200);
    m_opacity_animation->setStartValue(m_opacity);
    m_opacity_animation->setEndValue(1.0);

    m_opacity2_animation = new QPropertyAnimation(this, "opacity2");
    m_opacity2_animation->setDuration(200);
    m_opacity2_animation->setStartValue(m_opacity2);
    m_opacity2_animation->setEndValue(0.0);
}

void Playback_Status_Button::paintEvent(QPaintEvent* event)
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

    painter.setOpacity(m_opacity2);
    painter.drawPixmap(rect, this->play_image_path);

    painter.setOpacity(m_opacity);
    painter.drawPixmap(rect, this->pause_image_path);
}

bool Playback_Status_Button::event(QEvent* event)
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
    return QRadioButton::event(event);
}

void Playback_Status_Button::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (m_is_play)
        {
            set_play_status(false);
        }
        else
        {
            set_play_status(true);
        }
    }
}

void Playback_Status_Button::set_play_status(bool is_play)
{
    this->set_is_play(is_play);
    update();

    if (!this->m_is_play)
    {
        m_opacity_animation->setDirection(QAbstractAnimation::Forward);
        m_opacity_animation->start();
        m_opacity2_animation->setDirection(QAbstractAnimation::Forward);
        m_opacity2_animation->start();
    }
    else
    {
        m_opacity_animation->setDirection(QAbstractAnimation::Backward);
        m_opacity_animation->start();
        m_opacity2_animation->setDirection(QAbstractAnimation::Backward);
        m_opacity2_animation->start();
    }
}

bool Playback_Status_Button::is_play() const
{
    return m_is_play;
}

void Playback_Status_Button::set_is_play(bool is_play)
{
    m_is_play = is_play;
    update();
    emit play_status_changed(m_is_play);
}

QColor Playback_Status_Button::hover_color() const
{
    return m_hover_color;
}

void Playback_Status_Button::Sethover_color(const QColor& newHover_color)
{
    m_hover_color = newHover_color;
    update();
}

qreal Playback_Status_Button::opacity() const
{
    return m_opacity;
}

void Playback_Status_Button::Setopacity(qreal newOpacity)
{
    m_opacity = newOpacity;
    update();
}

qreal Playback_Status_Button::opacity2() const
{
    return m_opacity2;
}

void Playback_Status_Button::Setopacity2(qreal newOpacity2)
{
    m_opacity2 = newOpacity2;
    update();
}
