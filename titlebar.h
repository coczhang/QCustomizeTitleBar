#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPoint>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMouseEvent>
#include <QDebug>

#define  BAR_WIDTH   40   //宽度
#define  BAR_HEIGHT  40   //高度

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QString content, int bar_width, QWidget *parent = 0);
    ~TitleBar();

signals:
    void buttonMinClicked();
    void buttonMaxClicked();
    void buttonCloseClicked();

    void changeDialogSize();
    void moveDialog(QPoint point);

public slots:
    void onButtonMinClicked();
    void onButtonMaxclicked();
    void onButtonCloseClicked();
    void onChangeButtonBackground(bool bMaxSize);

protected:
    virtual void mouseMoveEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void mouseDoubleClickEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    virtual void mouseReleaseEvent(QMouseEvent * event) Q_DECL_OVERRIDE;

private:
    void initTitleBarLayout(); //初始化控件
    void initTitleBarConnect(); //信号与槽的绑定

public:
    void setTitleContent(const QString strTitleContent); //设置标题内容
    void setTitleWidth(int nWidth);  //设置标题栏长度

private:
    QLabel* m_pTitleIcon;             //标题栏图标
    QLabel* m_pTitleContent;          //标题栏内容
    QPushButton* m_pButtonMin;        //最小化按钮
    QPushButton* m_pButtonMax;        //最大化按钮
    QPushButton* m_pButtonClose;      //关闭按钮
    QHBoxLayout* m_hLayout;

    QPoint m_mouseStartPos;
    QString m_strContent;             //标题栏内容
    int m_nBarWidth;
    bool m_bLeftBtnPressed;
};

#endif
