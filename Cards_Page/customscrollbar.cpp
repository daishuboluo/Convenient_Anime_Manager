#include "customscrollbar.h"

CustomScrollBar::CustomScrollBar(QWidget* parent)
    : QScrollBar(parent)
{
    setContextMenuPolicy(Qt::NoContextMenu);
    setOrientation(Qt::Vertical);

    animation = new QPropertyAnimation(this, "navWidth");
    animation->setDuration(500);
    animation->setStartValue(m_navWidth);
    animation->setEndValue(0);
    animation->setEasingCurve(QEasingCurve::OutCubic);

    animation2 = new QPropertyAnimation(this, "handleColor");
    animation2->setDuration(500);
    animation2->setStartValue(m_handleColor);
    animation2->setEndValue(QColor(255, 122, 198));
    animation2->setEasingCurve(QEasingCurve::OutCubic);

    connect(this, &QScrollBar::valueChanged, RELAY_SIGNALS, &Central_Bundle_Bridge::Send_Y_Axis);
}

void CustomScrollBar::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QStyleOptionSlider opt;
    initStyleOption(&opt);
    QRect handleRect = style()->subControlRect(QStyle::CC_ScrollBar, &opt, QStyle::SC_ScrollBarSlider, this);
    QRect grooveRect = handleRect.adjusted(m_navWidth, -12, -m_navWidth, 12);

    painter.setBrush(QBrush(m_handleColor));
    painter.drawRoundedRect(grooveRect, 5, 5);
}

bool CustomScrollBar::event(QEvent* event)
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

    return QScrollBar::event(event);
}

int CustomScrollBar::navWidth() const
{
    return m_navWidth;
}

void CustomScrollBar::setNavWidth(int newNavWidth)
{
    m_navWidth = newNavWidth;
    update();
}

QColor CustomScrollBar::handleColor() const
{
    return m_handleColor;
}

void CustomScrollBar::setHandleColor(const QColor& newHandleColor)
{
    m_handleColor = newHandleColor;
    update();
}
