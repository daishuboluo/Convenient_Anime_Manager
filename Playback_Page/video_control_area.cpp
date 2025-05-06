#include "video_control_area.h"

Video_Control_Area::Video_Control_Area(QWidget* parent)
    : QWidget{ parent }
{
    this->setMinimumWidth(240);
    m_control_area = new Control_Area(this);
    m_control_area->move(0, this->height() - m_control_area->height());
    m_control_area->show();

    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::Send_Playback_videoPath_Path_Info, this, &Video_Control_Area::setMedia);
    connect(this, &Video_Control_Area::fullScreen, RELAY_SIGNALS, &Central_Bundle_Bridge::Forward_Full_Screen);
}

void Video_Control_Area::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 255));
    painter.drawRect(0, 0, this->width(), this->height());
}

void Video_Control_Area::resizeEvent(QResizeEvent* event)
{
    m_control_area->move(0, this->height() - m_control_area->height());
    m_control_area->setFixedWidth(this->width());
}

bool Video_Control_Area::event(QEvent* event)
{
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        emit fullScreen();
    }
    return QWidget::event(event);
}

void Video_Control_Area::setMediaPlayer(QMediaPlayer* player)
{
    this->m_player = player;
    connect(m_player, &QMediaPlayer::durationChanged, this, &Video_Control_Area::setMaxDuration);
    connect(m_player, &QMediaPlayer::positionChanged, this, &Video_Control_Area::positionChanged);
    connect(m_control_area->progress_bar, &Progress_Bar::sliderMoved, this, &Video_Control_Area::seek);
    connect(m_control_area->playback_status_button, &Playback_Status_Button::play_status_changed, this, &Video_Control_Area::togglePlay);
    connect(m_control_area->mute_button, &Playback_Status_Button::play_status_changed, this, &Video_Control_Area::Is_Prohibited);
    connect(m_control_area->volume_bar, &Progress_Bar::sliderMoved, this, &Video_Control_Area::setVolume);

    connect(m_control_area->previous_button, &Control_Button::Control_Button_clicked, this, [this] {
        emit Next_Episode_Signal(-1);
        qDebug() << "减少一集";
        });
    connect(m_control_area->next_button, &Control_Button::Control_Button_clicked, this, [this] {
        emit Next_Episode_Signal(1);
        qDebug() << "增加一集";
        });
    connect(this, &Video_Control_Area::Next_Episode_Signal, RELAY_SIGNALS, &Central_Bundle_Bridge::Episode_Jump);
}

void Video_Control_Area::setMedia(QString path)
{
    m_player->setSource(QUrl::fromLocalFile(path));
    m_player->play();
    m_control_area->playback_status_button->set_play_status(false);
}

void Video_Control_Area::setMaxDuration(qint64 duration)
{
    m_control_area->progress_bar->setMaximum(duration);
}

void Video_Control_Area::positionChanged(qint64 position)
{
    if (m_control_area->progress_bar->isSliderDown()) return;
    m_control_area->progress_bar->setValue(position);
}

void Video_Control_Area::setVolume(int volume)
{
    m_player->audioOutput()->setVolume(volume / 100.0);
}

void Video_Control_Area::seek(int position)
{
    m_player->setPosition(position);
    m_control_area->progress_bar->setToolTip(durationTime);
}

void Video_Control_Area::togglePlay(bool play)
{
    if (play)
    {
        m_player->pause();
    }
    else
    {
        m_player->play();
    }
}

void Video_Control_Area::Is_Prohibited(bool prohibited)
{
    bool mute = m_player->audioOutput()->isMuted();
    m_player->audioOutput()->setMuted(!mute);
}
