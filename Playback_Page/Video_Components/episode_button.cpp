#include "episode_button.h"

Episode_Button::Episode_Button(QString Button_Theme, QWidget* parent)
    : QPushButton(parent)
{
    this->m_Button_Theme = Button_Theme;
    this->setCursor(Qt::PointingHandCursor);

    m_ani = new QPropertyAnimation(this, "hoverColor");
    m_ani->setDuration(300);
    m_ani->setStartValue(m_hoverColor);
    m_ani->setEndValue(QColor(254, 220, 255, 255));

    m_ani2 = new QPropertyAnimation(this, "textColor");
    m_ani2->setDuration(300);
    m_ani2->setStartValue(m_textColor);
    m_ani2->setEndValue(QColor(255, 255, 255, 255));

    connect(this, &Episode_Button::But_Send_videoPath_Playback_Path_Info, RELAY_SIGNALS, &Central_Bundle_Bridge::Send_Playback_videoPath_Path_Info);
    connect(this, &Episode_Button::Button_IDChanged, RELAY_SIGNALS, &Central_Bundle_Bridge::Button_Collection_Arrangement);
}

void Episode_Button::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QPainterPath path;
    path.addRoundedRect(rect(), 10, 10);
    painter.setClipPath(path);

    if (m_doubleClicked) painter.setBrush(QColor(251, 143, 210, 255));
    else painter.setBrush(m_hoverColor);

    painter.drawRoundedRect(rect(), 10, 10);

    QFont font;
    font.setPixelSize(this->width() * 0.2);
    font.setBold(true);
    painter.setFont(font);

    if (m_doubleClicked) painter.setPen(QColor(255, 255, 255, 255));
    else painter.setPen(m_textColor);
    painter.drawText(rect(), Qt::AlignCenter, m_Button_Theme);
}

void Episode_Button::Send_videoPath_Playback_Path_Info()
{
    emit Button_IDChanged(m_Button_ID);
    emit But_Send_videoPath_Playback_Path_Info(m_VideoPath);
}

void Episode_Button::mousePressEvent(QMouseEvent* event)
{
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        emit Button_IDChanged(m_Button_ID);
        emit But_Send_videoPath_Playback_Path_Info(m_VideoPath);
    }

    QWidget::mousePressEvent(event);
}

bool Episode_Button::event(QEvent* event)
{
    if (event->type() == QEvent::Enter)
    {
        m_ani->setDirection(QPropertyAnimation::Forward);
        m_ani->start();
        m_ani2->setDirection(QPropertyAnimation::Forward);
        m_ani2->start();
    }
    else if (event->type() == QEvent::Leave)
    {
        m_ani->setDirection(QPropertyAnimation::Backward);
        m_ani->start();
        m_ani2->setDirection(QPropertyAnimation::Backward);
        m_ani2->start();
    }

    return QWidget::event(event);
}

void Episode_Button::setVideoPath(QString videoPath)
{
    this->m_VideoPath = videoPath;
    update();
}

int Episode_Button::Button_ID() const
{
    return m_Button_ID;
}

void Episode_Button::setButton_ID(int newButton_ID)
{
    if (m_Button_ID == newButton_ID)
        return;
    m_Button_ID = newButton_ID;
}

QColor Episode_Button::hoverColor() const
{
    return m_hoverColor;
}

void Episode_Button::setHoverColor(const QColor& newHoverColor)
{
    m_hoverColor = newHoverColor;
    update();
}

bool Episode_Button::doubleClicked() const
{
    return m_doubleClicked;
}

void Episode_Button::setDoubleClicked(bool newDoubleClicked)
{
    m_doubleClicked = newDoubleClicked;
    update();
}

QColor Episode_Button::textColor() const
{
    return m_textColor;
}

void Episode_Button::setTextColor(const QColor& newTextColor)
{
    m_textColor = newTextColor;
    update();
}
