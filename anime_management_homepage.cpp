#include "anime_management_homepage.h"

Anime_Management_Homepage::Anime_Management_Homepage(QWidget* parent)
    : QWidget(parent) {
    QPalette pal(this->palette());
    pal.setColor(QPalette::Window, QColor(243, 246, 253));
    this->setPalette(pal);

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
    qApp->installEventFilter(this);
    this->setMinimumWidth(300);
    this->setMinimumHeight(100);
    this->resize(1200, 700);

    left_window_tip = new Left_Window_Tip(this);
    left_window_tip->show();
    //left_window_tip->hide();
    connect(left_window_tip->quit_button, &Function_Button::clicked, this, &Anime_Management_Homepage::Window_Close);
    connect(left_window_tip->min_button, &Function_Button::clicked, this, &Anime_Management_Homepage::Window_Minimize);
    connect(left_window_tip->max_button, &Function_Button::clicked, this, &Anime_Management_Homepage::Window_Maximize);

    show_all = new Show_All(this);
    show_all->show();
    //show_all->hide();

    Navigation_Page = new Horizontal_Navigation_Page(this);
    Navigation_Page->show();
    //Navigation_Page->hide(); //Navigation_Page->hide();

    cards_page = new Cards_Page(this);
    cards_page->show();
    //cards_page->hide();

    Play_Page = new Playback_Page(this);
    Play_Page->raise();
    Play_Page->show();
    //Play_Page->hide();   

    m_animation = new QPropertyAnimation(this, "Current_Position_Ratio");
    m_animation->setDuration(700);
    m_animation->setStartValue(m_Current_Position_Ratio);
    m_animation->setEndValue(0.0);
    m_animation->setEasingCurve(QEasingCurve::OutSine);
    connect(m_animation, &QPropertyAnimation::finished, this, [this] {
        STATUS_GROUPS->setIs_Video_Playback_Status(!STATUS_GROUPS->Is_Video_Playback_Status());
        });
    connect(m_animation, &QPropertyAnimation::valueChanged, this, [this] {
        Play_Page->move(this->width() * m_Current_Position_Ratio + m_borderWidth, m_borderWidth);
        Play_Page->raise();
        });

    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::Enter_Playback_Page, this, &Anime_Management_Homepage::Switch_Page);
    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::Exit_Playback_Page, this, &Anime_Management_Homepage::Switch_Page);

    m_animation_size = new QPropertyAnimation(this, "size");
    m_animation_size->setDuration(1);
    connect(RELAY_SIGNALS, &Central_Bundle_Bridge::Re_Adjust_Window_Size, this, &Anime_Management_Homepage::Window_Size_Plus_Minus);
}

Anime_Management_Homepage::~Anime_Management_Homepage() { }

void Anime_Management_Homepage::Switch_Page() {
    if (STATUS_GROUPS->Is_Video_Playback_Status()) {
        m_animation->setDirection(QAbstractAnimation::Backward);
        m_animation->start();
    }
    else {
        m_animation->setDirection(QAbstractAnimation::Forward);
        m_animation->start();
    }
}

void Anime_Management_Homepage::Window_Size_Plus_Minus() {
    resize(this->size() + QSize(1, 1));
}

void Anime_Management_Homepage::Window_Minimize() {
    this->showMinimized();
}

void Anime_Management_Homepage::Window_Maximize() {
    this->isMaximized() ? this->showNormal() : this->showMaximized();
}

void Anime_Management_Homepage::Window_Close() {
    this->close();
}

void Anime_Management_Homepage::resizeEvent(QResizeEvent* event) {
    const QSize newSize = event->size();
    const int borderWidth = m_borderWidth;
    const int newHeight = newSize.height();
    const int newWidth = newSize.width();
    const int leftWindowTipWidth = left_window_tip->width();
    const int showAllWidth = show_all->width();
    const int navigationPageHeight = Navigation_Page->height();
    const int leftOffset = borderWidth + leftWindowTipWidth + 10;

    left_window_tip->resize(leftWindowTipWidth, newHeight * 0.9);
    left_window_tip->move(borderWidth, newHeight * 0.05);
    show_all->move(leftOffset, borderWidth);
    Navigation_Page->resize(newWidth - borderWidth * 2 - leftWindowTipWidth - 50 - showAllWidth - 10, navigationPageHeight);
    Navigation_Page->move(leftOffset + showAllWidth + 10, borderWidth);
    cards_page->resize(newWidth - borderWidth * 2 - leftWindowTipWidth - 10, newHeight - navigationPageHeight - borderWidth * 2);
    cards_page->move(leftOffset, navigationPageHeight + borderWidth);
    Play_Page->move(newWidth * m_Current_Position_Ratio + borderWidth, borderWidth);
    Play_Page->resize(newWidth - borderWidth * 2, newHeight - borderWidth * 2);
    Play_Page->raise();
    this->updateMask();
}

void Anime_Management_Homepage::updateMask() {
    QBitmap bitmap(size());
    bitmap.clear();
    QPainter painter(&bitmap);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::color1);
    int padding = m_borderWidth / 8;
    QRectF roundedRect(padding, padding, width() - padding * 2, height() - padding * 2);
    painter.drawRoundedRect(roundedRect, 25, 25);
    setMask(bitmap);
}

void Anime_Management_Homepage::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);
    QPainter painter(this);
    QColor borderColor = m_bPressed ? QColor(50, 150, 255, 200) : QColor(100, 100, 255, 150);
    int borderWidth = m_borderWidth / 2;
    QPen pen(borderColor, borderWidth);
    painter.setPen(pen);
    int padding = m_borderWidth / 8;
    QRectF roundedRect(rect().adjusted(padding, padding, -padding, -padding));
    painter.drawRoundedRect(roundedRect, 25, 25);
}

void Anime_Management_Homepage::mousePressEvent(QMouseEvent* event) {
    QRect dragArea(m_borderWidth, m_borderWidth, width() - 2 * m_borderWidth, height() - 2 * m_borderWidth);
    if (event->button() == Qt::LeftButton && dragArea.contains(event->pos())) {
        m_isDragging = true;
        m_dragStartPosition = event->globalPos() - frameGeometry().topLeft();
    }
    else if (event->button() == Qt::LeftButton) {
        m_bPressed = true;
        m_ptPress = event->pos();
        m_ptDrag = event->globalPos();
        m_originalSize = this->size();
        m_bDragTop = (m_ptPress.y() < m_borderWidth);
        m_bDragLeft = (m_ptPress.x() < m_borderWidth);
        m_bDragRight = (m_ptPress.x() > width() - m_borderWidth);
        m_bDragBottom = (m_ptPress.y() > height() - m_borderWidth);
    }
    QWidget::mousePressEvent(event);
}

void Anime_Management_Homepage::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && m_isDragging) {
        m_isDragging = false;
        event->accept();
    }
    else if (event->button() == Qt::LeftButton && m_bPressed) {
        m_bPressed = false;
        m_bDragTop = m_bDragLeft = m_bDragRight = m_bDragBottom = false;
    }
    else {
        QWidget::mouseReleaseEvent(event);
    }
    update();
}

bool Anime_Management_Homepage::eventFilter(QObject* watched, QEvent* event) {
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent* mouseEvent = dynamic_cast<QMouseEvent*>(event);
        if (mouseEvent) {
            QPoint globalPos = QCursor::pos();
            if (m_isDragging && mouseEvent->buttons() & Qt::LeftButton) {
                STATUS_GROUPS->setWindow_Dragging_Status(true);
                move(mouseEvent->globalPos() - m_dragStartPosition);
                event->accept();
            }
            if (!m_bPressed) {
                updateCursorShape(globalPos - this->pos());
            }
            else if (mouseEvent->buttons() & Qt::LeftButton) {
                handleWindowResize(globalPos); 
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void Anime_Management_Homepage::updateCursorShape(const QPoint& pos) {
    bool left = pos.x() < m_borderWidth;
    bool right = pos.x() > this->width() - m_borderWidth;
    bool top = pos.y() < m_borderWidth;
    bool bottom = pos.y() > this->height() - m_borderWidth;

    if (left && top) this->setCursor(Qt::SizeFDiagCursor);
    else if (left && bottom) this->setCursor(Qt::SizeBDiagCursor);
    else if (right && top) this->setCursor(Qt::SizeBDiagCursor);
    else if (right && bottom) this->setCursor(Qt::SizeFDiagCursor);
    else if (left || right) this->setCursor(Qt::SizeHorCursor);
    else if (top || bottom) this->setCursor(Qt::SizeVerCursor);
    else this->setCursor(Qt::ArrowCursor);
}

void Anime_Management_Homepage::handleWindowResize(const QPoint& globalMousePos) {
    QPoint delta = globalMousePos - m_ptDrag;
    int addWidth = delta.x();
    int addHeight = delta.y();
    int newWidth = m_originalSize.width();
    int newHeight = m_originalSize.height();

    if (m_bDragLeft) {
        newWidth -= addWidth;
        this->move(globalMousePos.x(), pos().y());
    }
    if (m_bDragRight) newWidth += addWidth;
    if (m_bDragTop) {
        newHeight -= addHeight;
        this->move(pos().x(), globalMousePos.y());
    }
    if (m_bDragBottom) newHeight += addHeight;

    m_animation_size->setStartValue(this->size());
    m_animation_size->setEndValue(QSize(newWidth, newHeight));
    m_animation_size->start();
}

qreal Anime_Management_Homepage::Current_Position_Ratio() const {
    return m_Current_Position_Ratio;
}

void Anime_Management_Homepage::setCurrent_Position_Ratio(qreal newCurrent_Position_Ratio) {
    m_Current_Position_Ratio = newCurrent_Position_Ratio;
}
