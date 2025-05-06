#include "video_info_bar.h"

Video_Info_Bar::Video_Info_Bar(QWidget* parent)
    : QWidget{ parent }
{
    this->setFixedSize(250, 80);
    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::Forward_Card_Theme_And_Year_Info, this, &Video_Info_Bar::updateVideoInfo);
}

void Video_Info_Bar::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 246, 253, 255));
    painter.drawRect(this->rect());

    QPen pen;
    pen.setColor(Qt::black);
    painter.setPen(pen);

    QFont font;
    font.setPixelSize(30);
    painter.setFont(font);
    painter.drawText(QRect(15, 0, 250, 60), Qt::AlignVCenter | Qt::AlignLeft, videoName);

    font.setPixelSize(12);
    painter.setFont(font);
    painter.drawText(QRect(15, 50, 250, 20), Qt::AlignVCenter | Qt::AlignLeft, Film_Year + " 年 ");
}

void Video_Info_Bar::updateVideoInfo(QString videoName, QString Film_Year)
{
    if (!STATUS_GROUPS->Is_Accepting_Anime_Info()) return;
    STATUS_GROUPS->setIs_Accepting_Anime_Info(false);

    this->videoName = videoName;
    this->Film_Year = Film_Year;
    this->update();
}
