#ifndef PLAYBACK_STATUS_BUTTON_H
#define PLAYBACK_STATUS_BUTTON_H

#include <QRadioButton>
#include <QPixmap>
#include <QPainter>
#include <QEvent>
#include <QPropertyAnimation>
#include <QMouseEvent>

class Playback_Status_Button : public QRadioButton
{
    Q_OBJECT
        Q_PROPERTY(QColor hover_color READ hover_color WRITE Sethover_color FINAL)
        Q_PROPERTY(qreal opacity READ opacity WRITE Setopacity FINAL)
        Q_PROPERTY(qreal opacity2 READ opacity2 WRITE Setopacity2 FINAL)

public:
    explicit Playback_Status_Button(const QString& play_image_path, const QString& pause_image_path, QWidget* parent = nullptr);
    QPropertyAnimation* m_animation;
    QPropertyAnimation* m_opacity_animation;
    QPropertyAnimation* m_opacity2_animation;

    void set_play_status(bool is_play);
    bool is_play() const;
    void set_is_play(bool is_play);
    QColor hover_color() const;
    void Sethover_color(const QColor& newHover_color);
    qreal opacity() const;
    void Setopacity(qreal newOpacity);
    qreal opacity2() const;
    void Setopacity2(qreal newOpacity2);

protected:
    void paintEvent(QPaintEvent* event) override;
    bool event(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void play_status_changed(bool is_play);

private:
    QPixmap play_image_path;
    QPixmap pause_image_path;
    QString m_hover_text;
    QColor m_hover_color = QColor(255, 255, 255, 0);
    qreal m_opacity = 0.0;
    qreal m_opacity2 = 1.0;
    bool m_is_play = true;
};

#endif // PLAYBACK_STATUS_BUTTON_H
