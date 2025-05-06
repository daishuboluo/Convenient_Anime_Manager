#include "control_area.h"

Control_Area::Control_Area(QWidget* parent)
    : QWidget{ parent }
{
    this->setFixedHeight(61);
    this->setMinimumWidth(200);

    progress_bar = new Progress_Bar(this);
    progress_bar->move(0, 0);
    progress_bar->resize(width(), 21);

    volume_bar = new Progress_Bar(this);
    volume_bar->setMaximum(100);
    volume_bar->setValue(20);
    volume_bar->resize(80, 10);

    playback_status_button = new Playback_Status_Button("://img/播放.png", "://img/暂停.png", this);
    playback_status_button->setFixedSize(40, 40);
    playback_status_button->move(40, 21);

    previous_button = new Control_Button("://img/上.png", "上一集", this);
    previous_button->setFixedSize(40, 40);
    previous_button->move(0, 21);

    next_button = new Control_Button("://img/下.png", "下一集", this);
    next_button->setFixedSize(40, 40);
    next_button->move(80, 21);

    mute_button = new Playback_Status_Button("://img/音量.png", "://img/静音.png", this);
    mute_button->setFixedSize(40, 40);
}

void Control_Area::resizeEvent(QResizeEvent* event)
{
    progress_bar->resize(width(), 21);
    volume_bar->move(width() - volume_bar->width() - 10, 36);
    mute_button->move(width() - volume_bar->width() - mute_button->width() - 10, 21);
}
