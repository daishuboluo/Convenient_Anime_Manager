#include "playback_page.h"

Playback_Page::Playback_Page(QWidget* parent)
    : QWidget{ parent }
{
    Main_Video = new Video_Playback_Area(this);
    Overlay_Subtitles_And_Controls = new Video_Control_Area(this);
    Video_Info = new Video_Info_Bar(this);
    episode_bar_shell = new Video_Episode_Bar_Shell(this);
    back_button = new Back_Button(this);

    player = new QMediaPlayer(this);
    QAudioOutput* audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);
    player->setVideoOutput(Main_Video);

    Main_Video->setMediaPlayer(player);
    Overlay_Subtitles_And_Controls->setMediaPlayer(player);
}

void Playback_Page::resizeEvent(QResizeEvent* event)
{
    int height = this->height();
    int width = this->width();
    int left_margin = width * 0.03;
    int top_margin = height * 0.05;
    int video_height = height * 0.9;
    int video_width = width - Video_Info->width() - width * 0.06;

    Main_Video->setGeometry(left_margin, top_margin, video_width, video_height - 61);
    Overlay_Subtitles_And_Controls->setGeometry(left_margin, top_margin, video_width, height - height * 0.1);
    Video_Info->move(left_margin + video_width, top_margin);
    episode_bar_shell->move(left_margin + video_width, top_margin + Video_Info->height());
    episode_bar_shell->setFixedHeight(video_height - Video_Info->height());
    back_button->setGeometry(0, height * 0.2, left_margin, height * 0.60);
}

void Playback_Page::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(243, 246, 253, 255));
    painter.drawRect(this->rect());
}
