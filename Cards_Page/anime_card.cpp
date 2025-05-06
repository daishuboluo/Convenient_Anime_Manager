#include "anime_card.h"

Anime_Card::Anime_Card(QWidget *parent)
    : QWidget{parent}
{
    this->setCursor(Qt::PointingHandCursor);


    this->resize(190,320);
    m_Card_Image = QImage("://img/F3k201vakAEUJBv.png");
    m_Card_Link_Address = "://img/F3k201vakAEUJBv.png";
    m_Theme_Text = "狂犬艾莉丝";

    this->animation_start();

    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0);
    shadow->setBlurRadius(0);
    shadow->setColor(QColor(243, 246, 253, 255));
    this->setGraphicsEffect(shadow);

    connect(this, &Anime_Card::Video_URL_And_Subtitle_URL_In_Card, RELAY_SIGNALS, &Central_Bundle_Bridge::File_URLs);
    connect(this, &Anime_Card::Card_Clicked, RELAY_SIGNALS, &Central_Bundle_Bridge::Enter_Playback_Page);
    connect(this, &Anime_Card::Theme_And_Year_In_Card, RELAY_SIGNALS, &Central_Bundle_Bridge::Forward_Card_Theme_And_Year_Info);
 
}

void Anime_Card::animation_start() 
{
    animation = new QPropertyAnimation(this, "Zoom_Ratio");
    animation->setDuration(Animation_Time);
    animation->setStartValue(m_Zoom_Ratio);
    animation->setEndValue(1.4);

    animation2 = new QPropertyAnimation(this, "text_color");
    animation2->setDuration(Animation_Time);
    animation2->setStartValue(m_text_color);
    animation2->setEndValue(QColor(255, 65, 129, 255));

    animation3 = new QPropertyAnimation(this, "Grey_Barrier");
    animation3->setDuration(Animation_Time);
    animation3->setStartValue(m_Grey_Barrier);
    animation3->setEndValue(QColor(0, 0, 0, 90));

    animation4 = new QPropertyAnimation(this, "Circle_Color");
    animation4->setDuration(Animation_Time);
    animation4->setStartValue(m_Circle_Color);
    animation4->setEndValue(QColor(255, 0, 0, 255));

    animation5 = new QPropertyAnimation(this, "Triangle_Color");
    animation5->setDuration(Animation_Time);
    animation5->setStartValue(m_Triangle_Color);
    animation5->setEndValue(QColor(255, 255, 255, 255));
}

void Anime_Card::Execute_Animation()
{
    animation->setDirection(QAbstractAnimation::Forward);
    animation->start();
    animation2->setDirection(QAbstractAnimation::Forward);
    animation2->start();
    animation3->setDirection(QAbstractAnimation::Forward);
    animation3->start();
    animation4->setDirection(QAbstractAnimation::Forward);
    animation4->start();
    animation5->setDirection(QAbstractAnimation::Forward);
    animation5->start();

}

void Anime_Card::Reset_Animation()
{

    animation->setDirection(QAbstractAnimation::Backward);
    animation->start();
    animation2->setDirection(QAbstractAnimation::Backward);
    animation2->start();
    animation3->setDirection(QAbstractAnimation::Backward);
    animation3->start();
    animation4->setDirection(QAbstractAnimation::Backward);
    animation4->start();
    animation5->setDirection(QAbstractAnimation::Backward);
    animation5->start();

}


void Anime_Card::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);

    QPainterPath path;
    path.addRoundedRect(0, 0, this->width(), this->height(), 10, 10);
    painter.setClipPath(path);

    this->Draw_Image();
    this->Draw_Theme_Text();
    this->Draw_Circle();
    this->Draw_Rounded_Triangle();
}
bool Anime_Card::event(QEvent* event)
{
    if (event->type() == QEvent::Enter)
    {
        this->Execute_Animation();
    }
    else if (event->type() == QEvent::Leave)
    {
        this->Reset_Animation();
    }
    return QWidget::event(event);
}

void Anime_Card::Draw_Image()
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    QPainterPath path;
    path.addRoundedRect(QRectF(0, 0, this->width(), this->height() - this->height() / 9.0), 10, 10);
    painter.setClipPath(path);

    qreal Image_Ratio = qreal(m_Card_Image.width()) / qreal(m_Card_Image.height());
    QRectF Image_Matrix;
    Image_Matrix.setSize(QSizeF(Image_Ratio * this->height() * m_Zoom_Ratio, this->height() * m_Zoom_Ratio));
    Image_Matrix.moveCenter(QPointF(this->rect().center().rx(), this->rect().center().ry() - this->height() / 9.0));

    painter.drawImage(Image_Matrix, m_Card_Image, m_Card_Image.rect());

    QBrush brush;
    brush.setColor(m_Grey_Barrier);
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(QRectF(0, 0, this->width(), this->height() - this->height() / 9.0), 10, 10);
}

void Anime_Card::Draw_Theme_Text()
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    painter.setPen(QPen(m_text_color));
    QFont font;
    font.setPixelSize(this->height() / 17);
    font.setBold(true);
    painter.setFont(font);

    QRect rect1(0, 0, 0, 0);
    QRect actualRect = painter.boundingRect(rect1, Qt::AlignLeft | Qt::AlignBottom, m_Theme_Text);
    painter.drawText(QRect(this->rect().x() + 2, this->rect().y(), actualRect.width(), this->rect().height()), Qt::AlignLeft | Qt::AlignBottom, m_Theme_Text);
}

void Anime_Card::Draw_Rounded_Triangle()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int width = this->width();
    int sideLength = width / 6;
    int centerX = width / 2;
    int centerY = this->height() / 2 - this->height() / 9.0;

    QPainterPath path;
    path.addEllipse(QPointF(centerX * 0.94, centerY), sideLength * 0.42, sideLength * 0.42);
    painter.setClipPath(path);

    double height = std::sqrt(3.0) / 2 * sideLength;

    QPointF originalPoints[3] = {
        QPointF(centerX, centerY - height / 2),
        QPointF(centerX - sideLength / 2, centerY + height / 2),
        QPointF(centerX + sideLength / 2, centerY + height / 2)
    };

    double angle = 90 * M_PI / 180;
    QPointF rotatedPoints[3];
    for (int i = 0; i < 3; ++i) {
        double dx = originalPoints[i].x() - centerX;
        double dy = originalPoints[i].y() - centerY;
        rotatedPoints[i].setX(centerX + dx * std::cos(angle) - dy * std::sin(angle));
        rotatedPoints[i].setY(centerY + dx * std::sin(angle) + dy * std::cos(angle));
    }

    painter.setBrush(m_Triangle_Color);
    painter.setPen(Qt::NoPen);
    painter.drawPolygon(rotatedPoints, 3);
}

void Anime_Card::Draw_Circle()
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(m_Circle_Color);
    painter.drawEllipse(QPointF(this->rect().center().rx() * 0.97, this->rect().center().ry() - this->height() / 9.0), this->height() / 11, this->height() / 11);
}

void Anime_Card::Update_Card()
{
    this->update();
}

void Anime_Card::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {}
    QWidget::mousePressEvent(event);
}

void Anime_Card::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton && !STATUS_GROUPS->Window_Dragging_Status())
    {
        emit Video_URL_And_Subtitle_URL_In_Card(m_Video_Path_List);
        emit Card_Clicked();
        emit Theme_And_Year_In_Card(m_Theme_Text, m_cardYear);
    }
    STATUS_GROUPS->setWindow_Dragging_Status(false);
    QWidget::mouseReleaseEvent(event);
}
 

QString Anime_Card::cardYear() const
{
    return m_cardYear;
}

void Anime_Card::setCardYear(const QString &newCardYear)  
{
    if (m_cardYear == newCardYear)
        return;
    m_cardYear = newCardYear;

}

qreal Anime_Card::Zoom_Ratio() const
{
    return m_Zoom_Ratio;
}

void Anime_Card::setZoom_Ratio(qreal newZoom_Ratio)
{
    if (qFuzzyCompare(m_Zoom_Ratio, newZoom_Ratio))
        return;
    m_Zoom_Ratio = newZoom_Ratio;
    update();
}

QColor Anime_Card::text_color() const
{
    return m_text_color;
}

void Anime_Card::setText_color(const QColor &newText_color)
{
    m_text_color = newText_color;
}

QColor Anime_Card::Grey_Barrier() const
{
    return m_Grey_Barrier;
}

void Anime_Card::setGrey_Barrier(const QColor &newGrey_Barrier)
{
    m_Grey_Barrier = newGrey_Barrier;
}

QColor Anime_Card::Circle_Color() const
{
    return m_Circle_Color;
}

void Anime_Card::setCircle_Color(const QColor &newCircle_Color)
{
    m_Circle_Color = newCircle_Color;
}

QColor Anime_Card::Triangle_Color() const
{
    return m_Triangle_Color;
}

void Anime_Card::setTriangle_Color(const QColor &newTriangle_Color)
{
    m_Triangle_Color = newTriangle_Color;
}

bool Anime_Card::Type_Is_Visible() const
{
    return m_Type_Is_Visible;
}

void Anime_Card::setType_Is_Visible(bool newType_Is_Visible)
{
    m_Type_Is_Visible = newType_Is_Visible;
}

int Anime_Card::Card_ID() const
{
    return m_Card_ID;
}

void Anime_Card::setCard_ID(int newCard_ID)
{
    m_Card_ID = newCard_ID;
}

QImage Anime_Card::Card_Image() const
{
    return m_Card_Image;
}

void Anime_Card::setCard_Image(const QImage &newCard_Image)
{
    m_Card_Image = newCard_Image;
}

QString Anime_Card::Theme_Text() const
{
    return m_Theme_Text;
}

void Anime_Card::setTheme_Text(const QString &newTheme_Text)
{
    m_Theme_Text = newTheme_Text;
}

QString Anime_Card::Card_Link_Address() const
{
    return m_Card_Link_Address;
}

void Anime_Card::setCard_Link_Address(const QString &newCard_Link_Address)
{
    m_Card_Link_Address = newCard_Link_Address;
}

QString Anime_Card::Video_Folder() const
{
    return m_Video_Folder;
}

void Anime_Card::setVideo_Folder(const QString &newVideo_Folder) // 设置视频文件夹
{
    m_Video_Folder = newVideo_Folder;
}


QList<QString> Anime_Card::Video_Path_List() const
{
    return m_Video_Path_List;
}

void Anime_Card::setVideo_Path_List(const QList<QString> &newVideo_Path_List)
{
    m_Video_Path_List = newVideo_Path_List;
}


