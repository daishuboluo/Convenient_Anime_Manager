#include "right_click_menu_button.h"

Right_Click_Menu_Button::Right_Click_Menu_Button(QPixmap m_image, QString m_text, QWidget* parent)
    : QPushButton{ parent }, m_image(m_image), m_text(m_text)
{
    this->setCursor(Qt::PointingHandCursor);
    this->resize(104, 36);
    this->animation_start();

    connect(this, &QPushButton::clicked, this, [this] {
        emit Clicked();
        });
}

void Right_Click_Menu_Button::Draw_Image()
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QRect rect;
    rect.setHeight(this->height() / 2);
    rect.setWidth(this->height() / 2);
    rect.moveCenter(QPoint(width() / 6, height() / 2));

    painter.drawPixmap(rect, m_image);
}

void Right_Click_Menu_Button::Draw_Theme_Text()
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    QFont font;
    font.setPixelSize(this->height() * 0.4);
    font.setWeight(QFont::Bold);
    font.setLetterSpacing(QFont::AbsoluteSpacing, 6);
    painter.setFont(font);
    painter.setPen(QPen(QColor(0, 0, 255, 255)));

    painter.drawText(QPointF(this->rect().center().rx() * 0.96, this->rect().center().ry() * 1.42), m_text);
}

void Right_Click_Menu_Button::Draw_Shadow()
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QPainterPath path;
    path.addRoundedRect(0, 0, this->width(), this->height(), 7, 7);
    painter.setClipPath(path);

    QLinearGradient gradient(QPointF(width() * 0.5, height() * 0.0), QPointF(width() * 0.5, height() * 1.0));
    gradient.setColorAt(0, QColor(255, 255, 255, 255));
    gradient.setColorAt(0.5, QColor(241, 245, 249, 255));
    gradient.setColorAt(1.0, QColor(255, 216, 251, 255));

    QPen pen;
    pen.setWidth(6);
    pen.setBrush(gradient);
    QImage blur_image(this->size(), QImage::Format_ARGB32);
    blur_image.fill(QColor(0, 0, 0, 0));

    QPainter image_painter(&blur_image);
    image_painter.setRenderHint(QPainter::Antialiasing);
    image_painter.setBrush(Qt::NoBrush);
    image_painter.setPen(pen);
    image_painter.drawRoundedRect(this->rect(), 7, 7);
    image_painter.end();

    IMAGE_PROCESSING->qt_blurImage(blur_image, 14.0, false, false);
    painter.drawImage(this->rect(), blur_image);
}

void Right_Click_Menu_Button::animation_start()
{
    Animation = new QPropertyAnimation(this, "Background_Color");
    Animation->setDuration(200);
    Animation->setStartValue(m_Background_Color);
    Animation->setEndValue(QColor(255, 158, 236, 255));
}

void Right_Click_Menu_Button::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QPainterPath path;
    path.addRoundedRect(0, 0, this->width(), this->height(), 7, 7);
    painter.setClipPath(path);
    painter.setPen(Qt::NoPen);

    painter.setBrush(m_Background_Color);
    painter.drawRoundedRect(0, 0, this->width(), this->height(), 7, 7);

    this->Draw_Image();
    this->Draw_Theme_Text();
    this->Draw_Shadow();
}

bool Right_Click_Menu_Button::event(QEvent* event)
{
    if (event->type() == QEvent::Enter)
    {
        Animation->setDirection(QAbstractAnimation::Forward);
        Animation->start();
    }
    else if (event->type() == QEvent::Leave)
    {
        Animation->setDirection(QAbstractAnimation::Backward);
        Animation->start();
    }

    return QPushButton::event(event);
}

QColor Right_Click_Menu_Button::Background_Color() const
{
    return m_Background_Color;
}

void Right_Click_Menu_Button::setBackground_Color(const QColor& newBackground_Color)
{
    m_Background_Color = newBackground_Color;
    update();
}
