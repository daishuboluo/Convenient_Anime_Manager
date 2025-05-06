#include "video_episode_bar_shell.h"

Video_Episode_Bar_Shell::Video_Episode_Bar_Shell(QWidget* parent)
    : QWidget{ parent }
{
    this->setFixedWidth(250);
    video_episode_bar = new Video_Episode_Bar(this);
    ratio_slider = new Ratio_Slider(this);
    ratio_slider->setWidget(video_episode_bar);
    ratio_slider->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ratio_slider->setWidgetResizable(true);
}

void Video_Episode_Bar_Shell::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 255, 255, 255));
    painter.drawRect(this->rect());
}

void Video_Episode_Bar_Shell::resizeEvent(QResizeEvent* event)
{
    ratio_slider->resize(event->size());
    QWidget::resizeEvent(event);
}
