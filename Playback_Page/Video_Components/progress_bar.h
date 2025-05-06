#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

#include <QSlider>
#include <QPainter>
#include <QStyleOptionSlider>
#include <QLabel>
#include <QMouseEvent>

class Progress_Bar : public QSlider
{
    Q_OBJECT
public:
    explicit Progress_Bar(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* ev) override;

private:
    QColor Slot_Color = QColor(38, 38, 38);
    QColor Path_Color = QColor(111, 111, 111);
    QColor Slider_Color = QColor(116, 222, 255);
};

#endif // PROGRESS_BAR_H
