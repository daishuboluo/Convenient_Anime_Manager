#include "video_playback_area.h"

Video_Playback_Area::Video_Playback_Area(QWidget* parent)
    : QVideoWidget(parent), m_player(nullptr)
{
    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::Forward_Full_Screen, this, &Video_Playback_Area::Full_Screen);
    connect(this, &Video_Playback_Area::resize_window, RELAY_SIGNALS, &Central_Bundle_Bridge::Re_Adjust_Window_Size);
    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::Forward_Reset_Playback_Window, this, &Video_Playback_Area::stop_play);
}

void Video_Playback_Area::setMediaPlayer(QMediaPlayer* player) {
    m_player = player;
}

void Video_Playback_Area::stop_play() {
    m_player->stop();
}

void Video_Playback_Area::Full_Screen() {
    setFullScreen(!isFullScreen());
}

bool Video_Playback_Area::event(QEvent* event) {
    if (event->type() == QEvent::MouseButtonDblClick) {
        Full_Screen();
        emit resize_window();
    }
    return QVideoWidget::event(event);
}
