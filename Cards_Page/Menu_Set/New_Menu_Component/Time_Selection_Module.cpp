#include "Time_Selection_Module.h"

Time_Selection_Module::Time_Selection_Module(QWidget* parent)
    : QWidget{ parent }
{
    this->resize(250, 130);
    connect(&timer, &QTimer::timeout, this, &Time_Selection_Module::Time_Increase_Adjustment);
    connect(&timer2, &QTimer::timeout, this, &Time_Selection_Module::Time_Decrease_Adjustment);

    Time_Button_Module* time_button = new Time_Button_Module(this);
    time_button->setButton_Text(QString("来年"));
    connect(time_button, &Time_Button_Module::clicked_A, this, [this] {
        timer.start(40);
        timer2.stop();
        Time_Counting = 9;
        });
    time_button->move(0, 0);

    Time_Button_Module* time_button2 = new Time_Button_Module(this);
    time_button2->move(68, 0);

    Time_Button_Module* time_button3 = new Time_Button_Module(this);
    time_button3->move(137, 0);

    Time_Button_Module* time_button4 = new Time_Button_Module(this);
    time_button4->move(210, 0);

    Time_Button_Module* time_button5 = new Time_Button_Module(this);
    time_button5->move(0, 44);

    Time_Button_Module* time_button6 = new Time_Button_Module(this);
    time_button6->move(68, 44);

    Time_Button_Module* time_button7 = new Time_Button_Module(this);
    time_button7->move(137, 44);

    Time_Button_Module* time_button8 = new Time_Button_Module(this);
    time_button8->move(210, 44);

    Time_Button_Module* time_button9 = new Time_Button_Module(this);
    time_button9->move(0, 90);

    Time_Button_Module* time_button10 = new Time_Button_Module(this);
    time_button10->move(68, 90);

    Time_Button_Module* time_button11 = new Time_Button_Module(this);
    time_button11->move(137, 90);

    Time_Button_Module* time_button12 = new Time_Button_Module(this);
    time_button12->setButton_Text(QString("往年"));
    connect(time_button12, &Time_Button_Module::clicked_A, this, [this] {
        timer2.start(40);
        timer.stop();
        Time_Counting = 9;
        });
    time_button12->move(210, 90);

    time_button_list.append(time_button2);
    time_button_list.append(time_button3);
    time_button_list.append(time_button4);
    time_button_list.append(time_button5);
    time_button_list.append(time_button6);
    time_button_list.append(time_button7);
    time_button_list.append(time_button8);
    time_button_list.append(time_button9);
    time_button_list.append(time_button10);
    time_button_list.append(time_button11);

    Time_Adjustment = QDateTime::currentDateTime().date().year();
    int x = Time_Adjustment;

    for (auto& time_button : time_button_list)
    {
        connect(time_button, &Time_Button_Module::emitButton_Text, this, &Time_Selection_Module::Launch_Selected_Year_Text);
        time_button->setButton_Text(QString::number(x));
        x--;
    }
}

void Time_Selection_Module::paintEvent(QPaintEvent* event)
{
}

void Time_Selection_Module::Time_Increase_Adjustment()
{
    Time_Adjustment += 1;
    if (Time_Adjustment > QDateTime::currentDateTime().date().year() + 50)
    {
        Time_Counting = 10;
        Time_Adjustment = QDateTime::currentDateTime().date().year() + 50;
        timer.stop();
        return;
    }

    Time_Counting -= 1;

    if (Time_Counting < 0)
    {
        Time_Counting = 9;
        timer.stop();
        return;
    }

    int x = Time_Adjustment;
    for (auto& time_button : time_button_list)
    {
        time_button->setButton_Text(QString::number(x));
        x--;
    }
}

void Time_Selection_Module::Time_Decrease_Adjustment()
{
    Time_Adjustment -= 1;
    if (Time_Adjustment < 1899)
    {
        Time_Counting = 9;
        Time_Adjustment = 1910;
        timer2.stop();
        return;
    }

    Time_Counting -= 1;

    if (Time_Counting < 0)
    {
        Time_Counting = 9;
        timer2.stop();
        return;
    }

    int x = Time_Adjustment;
    for (auto& time_button : time_button_list)
    {
        time_button->setButton_Text(QString::number(x));
        x--;
    }
}
