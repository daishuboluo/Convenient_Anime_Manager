#ifndef TIME_SELECTION_MODULE_H
#define TIME_SELECTION_MODULE_H

#include <QWidget>
#include <QPainterPath>
#include <QPainter>
#include <QTime>
#include <QTimer>
#include "Time_Button_Module.h"

class Time_Selection_Module : public QWidget
{
    Q_OBJECT

public:
    explicit Time_Selection_Module(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;

public slots:
    void Time_Increase_Adjustment();
    void Time_Decrease_Adjustment();

signals:
    void Launch_Selected_Year_Text(QString text);

private:
    QList<Time_Button_Module*> time_button_list;
    int Time_Adjustment;
    int Time_Counting = 9;
    QTimer timer;
    QTimer timer2;
};

#endif // TIME_SELECTION_MODULE_H
