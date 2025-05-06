#include "new_menu_set.h"

New_Menu_Set::New_Menu_Set(QWidget* parent)
    : QWidget{ parent }
{
    this->resize(280, 460);

    input_box1 = new Input_Box(QString("标题"), this);
    input_box1->move(30, 40);
    input_box1->set_Input_Box_Focus();

    input_box2 = new Input_Box(QString("标题图片"), this);
    input_box2->move(30, 90);

    input_box3 = new Input_Box(QString("视频文件夹"), this);
    input_box3->move(30, 140);

    input_box5 = new Input_Box(QString("时间"), this);
    input_box5->setReadOnly(true);
    input_box5->move(30, 190);

    function_button1 = new Function_Button(QPixmap("://img/粘贴.png"), this);
    connect(function_button1, &Function_Button::clicked, this, &New_Menu_Set::Paste_Clipboard);
    function_button1->move(222, 42);

    function_button2 = new Function_Button(QPixmap("://img/文件夹.png"), this);
    connect(function_button2, &Function_Button::clicked, this, &New_Menu_Set::Open_File_Dialog3);
    function_button2->move(222, 92);

    function_button3 = new Function_Button(QPixmap("://img/文件夹.png"), this);
    connect(function_button3, &Function_Button::clicked, this, &New_Menu_Set::Open_File_Dialog2);
    function_button3->move(222, 142);

    time_selection_module1 = new Time_Selection_Module(this);
    time_selection_module1->move(15, 250);
    connect(time_selection_module1, &Time_Selection_Module::Launch_Selected_Year_Text, input_box5, &Input_Box::setText);

    function_button5 = new Function_Button(QPixmap("://img/取消.png"), this);
    function_button5->move(40, 400);
    connect(function_button5, &Function_Button::clicked, this, &New_Menu_Set::Close_Window);

    function_button6 = new Function_Button(QPixmap("://img/对号.png"), this);
    connect(function_button6, &Function_Button::clicked, this, &New_Menu_Set::Confirm);
    function_button6->move(210, 400);
}

void New_Menu_Set::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QColor(236, 240, 244, 255));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(0, 0, width(), height(), 30, 30);

    QImage blur_image(this->size(), QImage::Format_ARGB32);
    blur_image.fill(QColor(0, 0, 0, 0));
    QPainter image_painter(&blur_image);
    image_painter.setRenderHint(QPainter::Antialiasing);
    image_painter.setPen(Qt::NoPen);

    auto drawRoundedRect = [&](QWidget* widget) {
        image_painter.setBrush(QColor(255, 255, 255, 255));
        image_painter.drawRoundedRect(QRect(widget->geometry().x() - 10, widget->geometry().y() - 10, widget->width(), widget->height()), 5, 5);
        image_painter.setBrush(QColor(187, 198, 211, 230));
        image_painter.drawRoundedRect(QRect(widget->geometry().x() + 10, widget->geometry().y() + 10, widget->width(), widget->height()), 5, 5);
        };

    drawRoundedRect(input_box1);
    drawRoundedRect(input_box2);
    drawRoundedRect(input_box3);
    drawRoundedRect(input_box5);
    drawRoundedRect(function_button1);
    drawRoundedRect(function_button2);
    drawRoundedRect(function_button3);
    drawRoundedRect(function_button5);
    drawRoundedRect(function_button6);

    image_painter.end();
    IMAGE_PROCESSING->qt_blurImage(blur_image, 35.0, true, false);
    painter.drawImage(this->rect(), blur_image);
}

void New_Menu_Set::closeEvent(QCloseEvent* event)
{
    emit Window_Close_Signal();
    event->accept();
}

void New_Menu_Set::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);
    QPainterPath path;
    path.addRoundedRect(0, 0, width(), height(), 35, 35);
    path.closeSubpath();
    QRegion region = QRegion(path.toFillPolygon().toPolygon());
    setMask(region);
}

void New_Menu_Set::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragStartPosition = event->globalPos();
        m_startWindowPosition = this->pos();
        event->accept();
    }
    else
    {
        QWidget::mousePressEvent(event);
    }
}

void New_Menu_Set::mouseMoveEvent(QMouseEvent* event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        QPoint delta = event->globalPos() - m_dragStartPosition;
        this->move(m_startWindowPosition + delta);
        event->accept();
    }
    else
    {
        QWidget::mouseMoveEvent(event);
    }
}

void New_Menu_Set::Initial_Modification_Value(Anime_Card* anime_card)
{
    this->anime_card = anime_card;
    input_box1->setText(anime_card->Theme_Text());
    input_box2->setText(anime_card->Card_Link_Address());
    input_box3->setText(anime_card->Video_Folder());
    input_box5->setText(anime_card->cardYear());
    submitStatus = SubmitStatus::Modify;
}

void New_Menu_Set::Close_Window()
{
    this->close();
}

void New_Menu_Set::Confirm()
{
    if (submitStatus == SubmitStatus::New)
    {
        Anime_Card* anime_card = new Anime_Card();
        anime_card->setCard_ID(m_id);
        anime_card->setCardYear(input_box5->text());

        QStringList VideoFiles = FILE_RELATEDS->getSortedVideoFiles(input_box3->text());
        if (!VideoFiles.isEmpty() && FILE_RELATEDS->hasVideoFiles(input_box3->text()))
        {
            DATABASE_RELATEDS->insertVideo(VideoFiles, anime_card->Card_ID());
            anime_card->setVideo_Folder(input_box3->text());
            anime_card->setVideo_Path_List(VideoFiles);
        }
        else
        {
            QMessageBox::warning(this, "警告", "新建失败：视频文件夹中没有视频文件");
            return;
        }

        if (QFile::exists(input_box2->text()))
        {
            QByteArray data = FILE_RELATEDS->processAndCropImageToByteArray(input_box2->text());
            DATABASE_RELATEDS->insertImage(data, anime_card->Card_ID());
            anime_card->setCard_Image(QImage::fromData(data));
            anime_card->setCard_Link_Address(input_box2->text());
        }
        else
        {
            QByteArray data = FILE_RELATEDS->convertImageToByteArray(anime_card->Card_Link_Address());
            DATABASE_RELATEDS->insertImage(data, anime_card->Card_ID());
        }

        if (!input_box1->text().isEmpty())
        {
            anime_card->setTheme_Text(input_box1->text());
        }

        anime_card->Update_Card();
        int count = 0 + m_anime_card;
        emit New_Window_Creation(count, anime_card);
        this->close();
    }
    else if (submitStatus == SubmitStatus::Modify)
    {
        QStringList VideoFiles = FILE_RELATEDS->getSortedVideoFiles(input_box3->text());
        if (!VideoFiles.isEmpty() && FILE_RELATEDS->hasVideoFiles(input_box3->text()))
        {
            DATABASE_RELATEDS->insertVideo(VideoFiles, anime_card->Card_ID());
            anime_card->setVideo_Folder(input_box3->text());
            anime_card->setVideo_Path_List(VideoFiles);
        }
        else
        {
            QMessageBox::warning(this, "警告", "修改失败：视频文件夹中没有视频文件");
            return;
        }

        if (QFile::exists(input_box2->text()))
        {
            QByteArray data = FILE_RELATEDS->processAndCropImageToByteArray(input_box2->text());
            DATABASE_RELATEDS->insertImage(data, anime_card->Card_ID());
            anime_card->setCard_Image(QImage::fromData(data));
            anime_card->setCard_Link_Address(input_box2->text());
        }
        else
        {
            QByteArray data = FILE_RELATEDS->convertImageToByteArray(anime_card->Card_Link_Address());
            DATABASE_RELATEDS->insertImage(data, anime_card->Card_ID());
        }

        if (!input_box1->text().isEmpty())
        {
            anime_card->setTheme_Text(input_box1->text());
        }
        anime_card->setCardYear(input_box5->text());

        DATABASE_RELATEDS->insertComprehensive(
            anime_card->Theme_Text(),
            anime_card->cardYear().toInt(),
            anime_card->Card_Link_Address(),
            anime_card->Video_Folder(),
            DATABASE_RELATEDS->getComprehensive(anime_card->Card_ID())["Location_Data"].toInt(),
            anime_card->Card_ID()
        );

        anime_card->Update_Card();
        this->close();
    }
}

void New_Menu_Set::Open_File_Dialog2()
{
    QString lastPath = settings.value("Video_Path", QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation).first()).toString();
    QString selectedPath = QFileDialog::getExistingDirectory(
        this,
        tr("选择视频文件夹"),
        lastPath,
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );

    if (!selectedPath.isEmpty())
    {
        settings.setValue("Video_Path", selectedPath);
        input_box3->setText(selectedPath);
    }
}

void New_Menu_Set::Open_File_Dialog3()
{
    QString lastPath = settings.value("Title_Image_Path", QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).first()).toString();
    QString filePath = QFileDialog::getOpenFileName(
        this,
        tr("选择图片"),
        lastPath,
        tr("Image Files (*.jpg *.png *.jpeg *.webp);;JPEG (*.jpg);;PNG (*.png);;JPEG (*.jpeg);;WEBP (*.webp)")
    );

    if (!filePath.isEmpty())
    {
        QDir dir = QFileInfo(filePath).absoluteDir();
        settings.setValue("Title_Image_Path", dir.path());
        input_box2->setText(filePath);
    }
}

void New_Menu_Set::Paste_Clipboard()
{
    QClipboard* clipboard = QApplication::clipboard();

    if (!clipboard) {
        qWarning() << "无法访问剪贴板";
        return;
    }

    const QMimeData* mimeData = clipboard->mimeData();

    if (mimeData && mimeData->hasText()) {
        QString text = mimeData->text();
        input_box1->setText(text);
    }
}








int New_Menu_Set::id() const
{
    return m_id;
}

void New_Menu_Set::setId(int newId)
{
    m_id = newId;
    submitStatus = SubmitStatus::New;
}


void New_Menu_Set::setAnime_card(int newAnime_card)
{
    m_anime_card = newAnime_card;
    submitStatus = SubmitStatus::New;
}




int New_Menu_Set::Offset_Position1() const
{
    return m_Offset_Position1;
}

void New_Menu_Set::setOffset_Position1(int newOffset_Position1)
{
    m_Offset_Position1 = newOffset_Position1;
}

int New_Menu_Set::Offset_Position2() const
{
    return m_Offset_Position2;
}

void New_Menu_Set::setOffset_Position2(int newOffset_Position2)
{
    m_Offset_Position2 = newOffset_Position2;
}

int New_Menu_Set::Offset_Position3() const
{
    return m_Offset_Position3;
}

void New_Menu_Set::setOffset_Position3(int newOffset_Position3)
{
    m_Offset_Position3 = newOffset_Position3;
}

int New_Menu_Set::Offset_Position4() const
{
    return m_Offset_Position4;
}

void New_Menu_Set::setOffset_Position4(int newOffset_Position4)
{
    m_Offset_Position4 = newOffset_Position4;
}

int New_Menu_Set::Offset_Position5() const
{
    return m_Offset_Position5;
}

void New_Menu_Set::setOffset_Position5(int newOffset_Position5)
{
    m_Offset_Position5 = newOffset_Position5;
}

int New_Menu_Set::Offset_Position6() const
{
    return m_Offset_Position6;
}

void New_Menu_Set::setOffset_Position6(int newOffset_Position6)
{
    m_Offset_Position6 = newOffset_Position6;
}

int New_Menu_Set::Offset_Position7() const
{
    return m_Offset_Position7;
}

void New_Menu_Set::setOffset_Position7(int newOffset_Position7)
{
    m_Offset_Position7 = newOffset_Position7;
}

int New_Menu_Set::Offset_Position8() const
{
    return m_Offset_Position8;
}

void New_Menu_Set::setOffset_Position8(int newOffset_Position8)
{
    m_Offset_Position8 = newOffset_Position8;
}

int New_Menu_Set::Offset_Position9() const
{
    return m_Offset_Position9;
}

void New_Menu_Set::setOffset_Position9(int newOffset_Position9)
{
    m_Offset_Position9 = newOffset_Position9;
}

int New_Menu_Set::Offset_Position10() const
{
    return m_Offset_Position10;
}

void New_Menu_Set::setOffset_Position10(int newOffset_Position10)
{
    m_Offset_Position10 = newOffset_Position10;
}

int New_Menu_Set::Offset_Position11() const
{
    return m_Offset_Position11;
}

void New_Menu_Set::setOffset_Position11(int newOffset_Position11)
{
    m_Offset_Position11 = newOffset_Position11;
}

int New_Menu_Set::Offset_Position12() const
{
    return m_Offset_Position12;
}

void New_Menu_Set::setOffset_Position12(int newOffset_Position12)
{
    m_Offset_Position12 = newOffset_Position12;
}

int New_Menu_Set::Offset_Position13() const
{
    return m_Offset_Position13;
}

void New_Menu_Set::setOffset_Position13(int newOffset_Position13)
{
    m_Offset_Position13 = newOffset_Position13;
}
