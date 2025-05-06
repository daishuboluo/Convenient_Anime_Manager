#include "function_button.h"

Function_Button::Function_Button(QPixmap m_Function_Button_pixmap, QWidget* parent)
    : QPushButton{ parent }, m_Function_Button_pixmap(m_Function_Button_pixmap)
{
    this->resize(30, 30);
    this->setCursor(Qt::PointingHandCursor);

    animation = new QPropertyAnimation(this, "Bottom_Edge_Color");
    animation->setDuration(200);
    animation->setStartValue(m_Bottom_Edge_Color);
    animation->setEndValue(QColor(255, 190, 241, 255));
}

void Function_Button::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QPainterPath path;
    path.addRoundedRect(this->rect(), 10, 10);
    painter.setClipPath(path);

    painter.setPen(Qt::NoPen);
    painter.setBrush(m_Bottom_Edge_Color);
    painter.drawRoundedRect(this->rect(), 10, 10);

    QRect rect;
    rect.setHeight(this->height() * 0.90);
    rect.setWidth(this->height() * 0.90);
    rect.moveCenter(QPoint(this->rect().center().x(), this->rect().center().y()));
    painter.drawPixmap(rect, m_Function_Button_pixmap);

    QLinearGradient gradient(QPointF(width() * 0.290, height() * 0.350), QPointF(width() * 0.710, height() * 0.650));
    gradient.setColorAt(0, QColor(187, 198, 211, 255));
    gradient.setColorAt(0.5, QColor(241, 245, 249, 255));
    gradient.setColorAt(1.0, QColor(255, 255, 255, 255));

    QPen pen;
    pen.setWidth(6);
    pen.setBrush(gradient);

    QImage blur_image(this->size(), QImage::Format_ARGB32);
    blur_image.fill(QColor(0, 0, 0, 0));
    QPainter image_painter(&blur_image);
    image_painter.setRenderHint(QPainter::Antialiasing);
    image_painter.setBrush(Qt::NoBrush);
    image_painter.setPen(pen);
    image_painter.drawRoundedRect(this->rect(), 10, 10);
    image_painter.end();

    IMAGE_PROCESSING->qt_blurImage(blur_image, 9.0, false, false);
    painter.drawImage(this->rect(), blur_image);
}

bool Function_Button::event(QEvent* event)
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

QPixmap Function_Button::Function_Button_pixmap() const
{
    return m_Function_Button_pixmap;
}

void Function_Button::setFunction_Button_pixmap(const QPixmap& newFunction_Button_pixmap)
{
    m_Function_Button_pixmap = newFunction_Button_pixmap;
    update();
}

QColor Function_Button::Bottom_Edge_Color() const
{
    return m_Bottom_Edge_Color;
}

void Function_Button::setBottom_Edge_Color(const QColor& newBottom_Edge_Color)
{
    m_Bottom_Edge_Color = newBottom_Edge_Color;
    update();
}
