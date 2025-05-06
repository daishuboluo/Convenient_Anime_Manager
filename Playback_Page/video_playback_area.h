#ifndef VIDEO_PLAYBACK_AREA_H
#define VIDEO_PLAYBACK_AREA_H

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QWidget>
#include <QMouseEvent>
#include <QEvent>
#include "../Singleton_Set/central_bundle_bridge.h"

class Video_Playback_Area : public QVideoWidget
{
    Q_OBJECT

public:
    explicit Video_Playback_Area(QWidget* parent = nullptr);
    void setMediaPlayer(QMediaPlayer* player);

public slots:
    void Full_Screen();
    void stop_play();

signals:
    void resize_window();

protected:
    bool event(QEvent* event) override;

private:
    QMediaPlayer* m_player = nullptr;
};

#endif // VIDEO_PLAYBACK_AREA_H
