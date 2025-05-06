#ifndef VIDEO_CONTROL_AREA_H
#define VIDEO_CONTROL_AREA_H

#include <QWidget>
#include <QPainter>
#include <QtMultimedia>
#include "../Singleton_Set/central_bundle_bridge.h"
#include "Video_Components/control_area.h"

class Video_Control_Area : public QWidget
{
    Q_OBJECT
public:
    explicit Video_Control_Area(QWidget* parent = nullptr);
    void setMediaPlayer(QMediaPlayer* player);

public slots:
    void setMedia(QString path);
    void setMaxDuration(qint64 duration);
    void positionChanged(qint64 position);
    void setVolume(int volume);
    void seek(int position);
    void togglePlay(bool play);
    void Is_Prohibited(bool prohibited);

signals:
    void fullScreen();
    void Next_Episode_Signal(int episode_num);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    bool event(QEvent* event) override;

private:
    QMediaPlayer* m_player;
    Control_Area* m_control_area;
    QString durationTime;
};

#endif // VIDEO_CONTROL_AREA_H
