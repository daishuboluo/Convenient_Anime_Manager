#ifndef BACK_BUTTON_H
#define BACK_BUTTON_H

#include <QPushButton>
#include <QPainter>
#include <QEvent>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include "../../Singleton_Set/central_bundle_bridge.h"
#include "../../Singleton_Set/status_group.h"

class Back_Button : public QPushButton
{
    Q_OBJECT
        Q_PROPERTY(QColor color READ get_color WRITE set_color)

public:
    explicit Back_Button(QWidget* parent = nullptr);
    void update_triangle();
    QColor get_color() const;
    void set_color(const QColor& newColor);

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    bool event(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void Back_clicked();
    void reset_playback_window();

public slots:
    void reset_status();

private:
    QPropertyAnimation* animation;
    QPoint p1, p2, p3;
    QColor m_color = QColor(0, 0, 0, 0);
};

#endif // BACK_BUTTON_H
