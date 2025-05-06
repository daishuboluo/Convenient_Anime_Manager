#include "Time_Button_Module.h"

Time_Button_Module::Time_Button_Module(QWidget* parent)
    : QPushButton{ parent }
{
    this->resize(40, 25);
    this->setCursor(Qt::PointingHandCursor);

    connect(this, &Time_Button_Module::clicked, this, [this] {
        emit emitButton_Text(m_Button_Text);
        emit clicked_A();
        });

    animation = new QPropertyAnimation(this, "Button_Color");
    animation->setDuration(250);
    animation->setStartValue(m_Button_Color);
    animation->setEndValue(QColor(255, 190, 241, 255));

    animation2 = new QPropertyAnimation(this, "Button_Text_Color");
    animation2->setDuration(250);
    animation2->setStartValue(m_Button_Text_Color);
    animation2->setEndValue(QColor(255, 255, 255, 255));
}

void Time_Button_Module::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_Button_Color);
    painter.drawRoundedRect(this->rect(), 10, 10);

    painter.setPen(QPen(m_Button_Text_Color));
    QFont font;
    font.setPixelSize(this->height() * 0.6);
    font.setBold(true);
    painter.setFont(font);
    painter.drawText(this->rect(), Qt::AlignCenter, m_Button_Text);
}

bool Time_Button_Module::event(QEvent* event)
{
    if (event->type() == QEvent::Enter)
    {
        animation->setDirection(QAbstractAnimation::Forward);
        animation->start();
        animation2->setDirection(QAbstractAnimation::Forward);
        animation2->start();
    }
    else if (event->type() == QEvent::Leave)
    {
        animation->setDirection(QAbstractAnimation::Backward);
        animation->start();
        animation2->setDirection(QAbstractAnimation::Backward);
        animation2->start();
    }

    return QWidget::event(event);
}

QColor Time_Button_Module::Button_Color() const
{
    return m_Button_Color;
}

void Time_Button_Module::setButton_Color(const QColor& newButton_Color)
{
    m_Button_Color = newButton_Color;
    update();
}

QString Time_Button_Module::Button_Text() const
{
    return m_Button_Text;
}

void Time_Button_Module::setButton_Text(const QString& newButton_Text)
{
    m_Button_Text = newButton_Text;
    update();
}

QColor Time_Button_Module::Button_Text_Color() const
{
    return m_Button_Text_Color;
}

void Time_Button_Module::setButton_Text_Color(const QColor& newButton_Text_Color)
{
    m_Button_Text_Color = newButton_Text_Color;
    update();
}
