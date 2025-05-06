#include "input_box.h"

Input_Box::Input_Box(QString PlaceholderText, QWidget* parent)
    : QLineEdit{ parent }
{
    this->setPlaceholderText(PlaceholderText);
    this->resize(180, 30);
    this->setTextMargins(15, 0, 15, 0);

    QFont font = this->font();
    font.setPointSize(11);
    font.setBold(true);
    setFont(font);

    QPalette palette = this->palette();
    palette.setColor(QPalette::PlaceholderText, Qt::gray);
    this->setPalette(palette);

    palette.setColor(QPalette::Text, Qt::black);
    this->setPalette(palette);

    palette.setColor(QPalette::Base, Qt::transparent);
    this->setPalette(palette);

    this->setFrame(QFrame::NoFrame);

    animation = new QPropertyAnimation(this, "widinput");
    animation->setDuration(300);
    animation->setStartValue(m_widinput);
    animation->setEndValue(10);
}

void Input_Box::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setViewport(0, 0, width(), height());
    painter.setWindow(0, 0, width(), height());

    QPainterPath path;
    path.addRoundedRect(0, 0, width(), height(), 10, 10);
    painter.setClipPath(path);
    painter.setPen(Qt::NoPen);
    QBrush Brush(QColor(241, 245, 249, 255));
    painter.setBrush(Brush);
    painter.drawRoundedRect(0, 0, width(), height(), 10, 10);

    QLinearGradient gradient(QPointF(width() * 0.490, height() * 0.10), QPointF(width() * 0.510, height() * 0.90));
    gradient.setColorAt(0, QColor(187, 198, 211, 255));
    gradient.setColorAt(0.5, QColor(241, 245, 249, 255));
    gradient.setColorAt(1.0, QColor(255, 255, 255, 255));

    QPen pen;
    pen.setWidth(m_widinput);
    pen.setBrush(gradient);

    QImage blur_image(this->size(), QImage::Format_ARGB32);
    blur_image.fill(QColor(0, 0, 0, 0));
    QPainter image_painter(&blur_image);
    image_painter.setRenderHint(QPainter::Antialiasing);
    image_painter.setBrush(Qt::NoBrush);
    image_painter.setPen(pen);
    image_painter.drawRoundedRect(this->rect(), 10, 10);
    image_painter.end();

    IMAGE_PROCESSING->qt_blurImage(blur_image, m_widinput * 3, false, false);
    painter.drawImage(this->rect(), blur_image);

    QLineEdit::paintEvent(event);
}

void Input_Box::set_Input_Box_Focus()
{
    this->setFocus();
    animation->setDirection(QPropertyAnimation::Forward);
    animation->start();
}

void Input_Box::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        animation->setDirection(QPropertyAnimation::Forward);
        animation->start();
    }
}

void Input_Box::focusOutEvent(QFocusEvent* event)
{
    animation->setDirection(QPropertyAnimation::Backward);
    animation->start();
    QLineEdit::focusOutEvent(event);
}

int Input_Box::widinput() const
{
    return m_widinput;
}

void Input_Box::setWidinput(int newWidinput)
{
    m_widinput = newWidinput;
    update();
}
