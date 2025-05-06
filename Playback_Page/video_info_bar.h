#ifndef VIDEO_INFO_BAR_H
#define VIDEO_INFO_BAR_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include "../Singleton_Set/central_bundle_bridge.h"
#include "../Singleton_Set/status_group.h"

class Video_Info_Bar : public QWidget
{
    Q_OBJECT

public:
    explicit Video_Info_Bar(QWidget* parent = nullptr);

public slots:
    void updateVideoInfo(QString videoName, QString Film_Year);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QString videoName;
    QString Film_Year;
};

#endif // VIDEO_INFO_BAR_H
