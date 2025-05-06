#ifndef EPISODE_BUTTON_H
#define EPISODE_BUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QPainterPath>
#include <QMouseEvent>
#include <QEvent>
#include <QPropertyAnimation>
#include "../../Singleton_Set/central_bundle_bridge.h"

class Episode_Button : public QPushButton
{
    Q_OBJECT
        Q_PROPERTY(int Button_ID READ Button_ID WRITE setButton_ID NOTIFY Button_IDChanged FINAL)
        Q_PROPERTY(QColor hoverColor READ hoverColor WRITE setHoverColor FINAL)
        Q_PROPERTY(bool doubleClicked READ doubleClicked WRITE setDoubleClicked FINAL)
        Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor FINAL)

public:
    explicit Episode_Button(QString Button_Theme, QWidget* parent = nullptr);
    void Send_videoPath_Playback_Path_Info();
    void setVideoPath(QString videoPath);

    QPropertyAnimation* m_ani;
    QPropertyAnimation* m_ani2;

    int Button_ID() const;
    void setButton_ID(int newButton_ID);
    QColor hoverColor() const;
    void setHoverColor(const QColor& newHoverColor);
    bool doubleClicked() const;
    void setDoubleClicked(bool newDoubleClicked);
    QColor textColor() const;
    void setTextColor(const QColor& newTextColor);

signals:
    void But_Send_videoPath_Playback_Path_Info(QString videoPath);
    void Button_IDChanged(int newButton_ID);

protected:
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    bool event(QEvent* event) override;

private:
    QString m_Button_Theme;
    QString m_VideoPath;
    int m_Button_ID;
    QColor m_hoverColor = QColor(239, 239, 239, 255);
    bool m_doubleClicked = false;
    QColor m_textColor = QColor(0, 0, 0, 255);
};

#endif // EPISODE_BUTTON_H
