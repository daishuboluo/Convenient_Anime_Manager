#ifndef NEW_MENU_SET_H
#define NEW_MENU_SET_H

#include <QWidget>
#include <QPainter>
#include <QPainterPath>
#include <QFileDialog>
#include <QSettings>
#include <QStandardPaths>
#include <QClipboard>
#include <QApplication>
#include <QMimeData>
#include <QMessageBox>
#include "./New_Menu_Component/function_button.h"
#include "./New_Menu_Component/input_box.h"
#include "./New_Menu_Component/Time_Selection_Module.h"
#include "../../Singleton_Set/file_related.h"
#include "../../Singleton_Set/Database_Related.h"
#include "../../Singleton_Set/image_processing.h"
#include "../anime_card.h"

class New_Menu_Set : public QWidget
{
    Q_OBJECT
        Q_PROPERTY(int id READ id WRITE setId FINAL)
        Q_PROPERTY(int Offset_Position1 READ Offset_Position1 WRITE setOffset_Position1 FINAL)
        Q_PROPERTY(int Offset_Position2 READ Offset_Position2 WRITE setOffset_Position2 FINAL)
        Q_PROPERTY(int Offset_Position3 READ Offset_Position3 WRITE setOffset_Position3 FINAL)
        Q_PROPERTY(int Offset_Position4 READ Offset_Position4 WRITE setOffset_Position4 FINAL)
        Q_PROPERTY(int Offset_Position5 READ Offset_Position5 WRITE setOffset_Position5 FINAL)
        Q_PROPERTY(int Offset_Position6 READ Offset_Position6 WRITE setOffset_Position6 FINAL)
        Q_PROPERTY(int Offset_Position7 READ Offset_Position7 WRITE setOffset_Position7 FINAL)
        Q_PROPERTY(int Offset_Position8 READ Offset_Position8 WRITE setOffset_Position8 FINAL)
        Q_PROPERTY(int Offset_Position9 READ Offset_Position9 WRITE setOffset_Position9 FINAL)
        Q_PROPERTY(int Offset_Position10 READ Offset_Position10 WRITE setOffset_Position10 FINAL)
        Q_PROPERTY(int Offset_Position11 READ Offset_Position11 WRITE setOffset_Position11 FINAL)
        Q_PROPERTY(int Offset_Position12 READ Offset_Position12 WRITE setOffset_Position12 FINAL)
        Q_PROPERTY(int Offset_Position13 READ Offset_Position13 WRITE setOffset_Position13 FINAL)

public:
    explicit New_Menu_Set(QWidget* parent = nullptr);

    enum SubmitStatus {
        New,
        Modify,
    };

    Input_Box* input_box1;
    Input_Box* input_box2;
    Input_Box* input_box3;
    Input_Box* input_box5;

    Function_Button* function_button1;
    Function_Button* function_button2;
    Function_Button* function_button3;
    Function_Button* function_button5;
    Function_Button* function_button6;

    Time_Selection_Module* time_selection_module1;

    int id() const;
    void setId(int newId);
    void setAnime_card(int newAnime_card);
    void Initial_Modification_Value(Anime_Card* anime_card);

    int Offset_Position1() const;
    void setOffset_Position1(int newOffset_Position1);
    int Offset_Position2() const;
    void setOffset_Position2(int newOffset_Position2);
    int Offset_Position3() const;
    void setOffset_Position3(int newOffset_Position3);
    int Offset_Position4() const;
    void setOffset_Position4(int newOffset_Position4);
    int Offset_Position5() const;
    void setOffset_Position5(int newOffset_Position5);
    int Offset_Position6() const;
    void setOffset_Position6(int newOffset_Position6);
    int Offset_Position7() const;
    void setOffset_Position7(int newOffset_Position7);
    int Offset_Position8() const;
    void setOffset_Position8(int newOffset_Position8);
    int Offset_Position9() const;
    void setOffset_Position9(int newOffset_Position9);
    int Offset_Position10() const;
    void setOffset_Position10(int newOffset_Position10);
    int Offset_Position11() const;
    void setOffset_Position11(int newOffset_Position11);
    int Offset_Position12() const;
    void setOffset_Position12(int newOffset_Position12);
    int Offset_Position13() const;
    void setOffset_Position13(int newOffset_Position13);

public slots:
    void Close_Window();
    void Confirm();
    void Open_File_Dialog2();
    void Open_File_Dialog3();
    void Paste_Clipboard();

signals:
    void Window_Close_Signal();
    void New_Window_Creation(int Create_Location_Card, Anime_Card* anime_card);

protected:
    void paintEvent(QPaintEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    Q_DISABLE_COPY_MOVE(New_Menu_Set)

        QPoint m_dragStartPosition;
    QPoint m_startWindowPosition;
    QSettings settings;

    int m_id;
    int m_anime_card;
    Anime_Card* anime_card;
    SubmitStatus submitStatus;

    int m_Offset_Position1;
    int m_Offset_Position2;
    int m_Offset_Position3;
    int m_Offset_Position4;
    int m_Offset_Position5;
    int m_Offset_Position6;
    int m_Offset_Position7;
    int m_Offset_Position8;
    int m_Offset_Position9;
    int m_Offset_Position10;
    int m_Offset_Position11;
    int m_Offset_Position12;
    int m_Offset_Position13;
};

#endif // NEW_MENU_SET_H
