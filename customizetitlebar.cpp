#include "customizetitlebar.h"

CustomizeTitleBar::CustomizeTitleBar(QWidget *parent)
    : QWidget(parent),m_bShowMax(true)
{
    initLayout();
    initConnect();
}

CustomizeTitleBar::~CustomizeTitleBar()
{

}

void CustomizeTitleBar::initLayout()
{
    m_nDefaultWidth = this->width();
    m_nDefaultHeight = this->height();

    this->setStyleSheet("QWidget{background-color: #6495ED;}");

    //获取可用桌面大小
    RECT rect;
    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);
    m_nCurrentWidth = rect.right - rect.left;
    m_nCurrentHeight = rect.bottom - rect.top;

    //整个桌面的大小
    int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
    int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);
    qDebug() << "nScreenWidth:" << nScreenWidth << "nScreenHeight:" << nScreenHeight;

    this->setMinimumSize(m_nDefaultWidth, m_nDefaultHeight);
    this->setMaximumSize(m_nCurrentWidth, m_nCurrentHeight);
    this->resize(m_nCurrentWidth, m_nCurrentHeight);
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint |Qt::WindowSystemMenuHint
                         |Qt::WindowMinimizeButtonHint|Qt::WindowMaximizeButtonHint);

    m_pTitleBar = new TitleBar(QStringLiteral("客户端"), m_nCurrentWidth, this);
}

void CustomizeTitleBar::initConnect()
{
    connect(this, &CustomizeTitleBar::changeBackground, m_pTitleBar, &TitleBar::onChangeButtonBackground);

    connect(m_pTitleBar, &TitleBar::buttonMinClicked, this, &CustomizeTitleBar::onButtonMinClicked);
    connect(m_pTitleBar, &TitleBar::buttonMaxClicked, this, &CustomizeTitleBar::onButtonMaxClicked);
    connect(m_pTitleBar, &TitleBar::buttonCloseClicked, this, &CustomizeTitleBar::onButtonCloseClicked);
    connect(m_pTitleBar, &TitleBar::changeDialogSize, this, &CustomizeTitleBar::onChangeDialogSize);
    connect(m_pTitleBar, &TitleBar::moveDialog, this, &CustomizeTitleBar::onMoveDialog);
}

void CustomizeTitleBar::changeDialogSize()
{
    if (m_bShowMax) {
        this->setGeometry((m_nCurrentWidth - m_nDefaultWidth) / 2, (m_nCurrentHeight - m_nDefaultHeight) / 2,
                          m_nDefaultWidth, m_nDefaultHeight);
        m_pTitleBar->setTitleWidth(m_nDefaultWidth);
        m_bShowMax = false;
    } else {
        this->setGeometry(0, 0, m_nCurrentWidth, m_nCurrentHeight);
        m_pTitleBar->setTitleWidth(m_nCurrentWidth);
        m_bShowMax = true;
    }
    emit changeBackground(m_bShowMax);
}

void CustomizeTitleBar::resizeEvent(QResizeEvent * event)
{


    QWidget::resizeEvent(event);
}

void CustomizeTitleBar::onButtonMinClicked()
{
    this->showMinimized();
}

void CustomizeTitleBar::onButtonMaxClicked()
{
    changeDialogSize();
}

void CustomizeTitleBar::onButtonCloseClicked()
{
    this->close();
}

void CustomizeTitleBar::onChangeDialogSize()
{
    changeDialogSize();
}

void CustomizeTitleBar::onMoveDialog(QPoint point)
{
    m_point = point;
    this->move(this->geometry().topLeft() + point);
}
