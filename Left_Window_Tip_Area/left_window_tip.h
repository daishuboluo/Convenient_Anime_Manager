#ifndef LEFT_WINDOW_TIP_H
#define LEFT_WINDOW_TIP_H

#include <QWidget>
#include "../Cards_Page/Menu_Set/New_Menu_Component/function_button.h"

class Left_Window_Tip : public QWidget
{
    Q_OBJECT

public:
    explicit Left_Window_Tip(QWidget* parent = nullptr);
    Function_Button* quit_button;
    Function_Button* min_button;
    Function_Button* max_button;

signals:

protected:
    void paintEvent(QPaintEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:

};

#endif // LEFT_WINDOW_TIP_H
