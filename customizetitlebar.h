#ifndef CUSTOMIZETITLEBAR_H
#define CUSTOMIZETITLEBAR_H

#include <QWidget>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QGuiApplication>
#include <windows.h>

#include "titlebar.h"

class CustomizeTitleBar : public QWidget
{
    Q_OBJECT

public:
    CustomizeTitleBar(QWidget *parent = 0);
    ~CustomizeTitleBar();

signals:
    void changeBackground(bool bmaxSize);

private slots:
    void onButtonMinClicked();       //窗口最小化
    void onButtonMaxClicked();       //窗口最大化
    void onButtonCloseClicked();     //关闭窗口
    void onChangeDialogSize();       //双击标题栏,更改窗口大小
    void onMoveDialog(QPoint point); //点击标题栏,移动窗口

private:
    void initLayout();
    void initConnect();
    void changeDialogSize();

protected:
    virtual void resizeEvent(QResizeEvent * event) Q_DECL_OVERRIDE;

private:
    TitleBar* m_pTitleBar;      //自定义标题栏

    QPoint m_point;

    int m_nDefaultWidth;         //默认窗口宽度
    int m_nDefaultHeight;        //默认窗口高度
    int m_nCurrentWidth;         //当前窗口宽度
    int m_nCurrentHeight;        //当前窗口高度
    bool m_bShowMax;
};

#endif
