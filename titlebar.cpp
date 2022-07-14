#include "titlebar.h"

TitleBar::TitleBar(QString content, int Barwidth, QWidget *parent) : QWidget(parent)
        ,m_strContent(content),m_nBarWidth(Barwidth),m_bLeftBtnPressed(false)
{
    initTitleBarLayout();
    initTitleBarConnect();
}

TitleBar::~TitleBar()
{

}

void TitleBar::initTitleBarLayout()
{
    this->setFixedWidth(m_nBarWidth);
    this->setFixedHeight(BAR_HEIGHT);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("QWidget{border-image: url(:/images/top_bg.png)}");

    m_pTitleIcon = new QLabel(this);
    m_pTitleIcon->setFixedWidth(BAR_WIDTH);
    m_pTitleIcon->setFixedHeight(BAR_HEIGHT);
    m_pTitleIcon->setStyleSheet("QLabel{border-image: url(:/images/title_log.png)}");

    m_pTitleContent = new QLabel(m_strContent, this);
    m_pTitleContent->setFixedHeight(BAR_HEIGHT);
    m_pTitleContent->setContentsMargins(10, 0, 0, 0);
    m_pTitleContent->setStyleSheet("QLabel{font-family: Microsoft YaHei; font-size: 18px; color: white}");

    m_pButtonMin = new QPushButton(this);
    m_pButtonMin->setFixedSize(BAR_WIDTH, BAR_HEIGHT);
    m_pButtonMin->setToolTip(QStringLiteral("最小化"));
    m_pButtonMin->setStyleSheet("QPushButton{border-image: url(:/images/min.png); background-color:black}"
                                  "QPushButton:hover{border-image: url(:/images/min_hover.png); background-color:black}");

    m_pButtonMax = new QPushButton(this);
    m_pButtonMax->setFixedSize(BAR_WIDTH+2, BAR_HEIGHT);
    m_pButtonMax->setToolTip(QStringLiteral("向下还原"));
    m_pButtonMax->setStyleSheet("QPushButton{border-image: url(:/images/scaling_desktop.png); background-color:black}"
                                  "QPushButton:hover{border-image: url(:/images/scaling_desktop_hover.png); background-color:black}");

    m_pButtonClose = new QPushButton(this);
    m_pButtonClose->setFixedSize(BAR_WIDTH+2, BAR_HEIGHT);
    m_pButtonClose->setToolTip(QStringLiteral("关闭"));
    m_pButtonClose->setStyleSheet("QPushButton{border-image: url(:/images/close.png); background-color:black}"
                                  "QPushButton:hover{border-image: url(:/images/close_hover.png)}");

    m_hLayout = new QHBoxLayout(this);
    m_hLayout->setSpacing(0);
    m_hLayout->addWidget(m_pTitleIcon);
    m_hLayout->addWidget(m_pTitleContent);
    m_hLayout->addWidget(m_pButtonMin);
    m_hLayout->addWidget(m_pButtonMax);
    m_hLayout->addWidget(m_pButtonClose);
    m_hLayout->setContentsMargins(0, 0, 0, 0);
    m_hLayout->setSpacing(0);
    m_hLayout->setAlignment(Qt::AlignLeft);

    m_pTitleContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void TitleBar::initTitleBarConnect()
{
    connect(m_pButtonMin, &QPushButton::clicked, this, &TitleBar::onButtonMinClicked);
    connect(m_pButtonMax, &QPushButton::clicked, this, &TitleBar::onButtonMaxclicked);
    connect(m_pButtonClose, &QPushButton::clicked, this, &TitleBar::onButtonCloseClicked);
}

void TitleBar::onButtonMinClicked()
{
    emit buttonMinClicked();
}

void TitleBar::onButtonMaxclicked()
{
    emit buttonMaxClicked();
}

void TitleBar::onButtonCloseClicked()
{
    emit buttonCloseClicked();
}

void TitleBar::onChangeButtonBackground(bool bMaxSize)
{
    if (bMaxSize) {
        m_pButtonMax->setToolTip(QStringLiteral("向下还原"));
        m_pButtonMax->setStyleSheet("QPushButton{border-image: url(:/images/scaling_desktop.png); background-color:black}"
                                      "QPushButton:hover{border-image: url(:/images/scaling_desktop_hover.png); background-color:black}");

    } else {
        m_pButtonMax->setToolTip(QStringLiteral("最大化"));
        m_pButtonMax->setStyleSheet("QPushButton{border-image: url(:/images/max.png); background-color:black}"
                                      "QPushButton:hover{border-image: url(:/images/max_hover.png); background-color:black}");
    }
}

void TitleBar::mouseMoveEvent(QMouseEvent * event)
{
    if (m_bLeftBtnPressed) {
        emit moveDialog(event->globalPos() - m_mouseStartPos);
        m_mouseStartPos = event->globalPos();
    }

    QWidget::mouseMoveEvent(event);
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
    if (Qt::LeftButton == event->button()) {
        m_bLeftBtnPressed = true;

        m_mouseStartPos = event->globalPos();
    }

    QWidget::mouseMoveEvent(event);
}

void TitleBar::mouseDoubleClickEvent(QMouseEvent * event)
{
    if (Qt::LeftButton == event->button()) {
        emit changeDialogSize();
    }

    QWidget::mouseDoubleClickEvent(event);
}

void TitleBar::mouseReleaseEvent(QMouseEvent * event)
{
    if (Qt::LeftButton == event->button()) {
        m_bLeftBtnPressed = false;
    }

    QWidget::mouseReleaseEvent(event);
}

void TitleBar::setTitleContent(const QString strTitleContent)
{
    //设置标题内容
    m_pTitleContent->setText(strTitleContent);
    m_strContent = strTitleContent;
}

void TitleBar::setTitleWidth(int nWidth)
{
    this->setFixedWidth(nWidth);
}

