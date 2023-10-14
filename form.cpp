#include "form.h"
#include "ui_form.h"
#include<QTimer>
#include<QMenu>
#include<QAction>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    InitPage();
    // 初始化显卡信息
    displayCard =  new HardData();
    displayCard->InitDisplayCard();

    // 设置标签为显卡名字
    ui->nameLabel->setText(displayCard->GetDisplayCardName());
    ui->nameLabel->adjustSize();

    SetSysTrayIcon();
    // 设置计时器
    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this, &Form::updateGPUInfo);
    timer->start(1000);







}
// 析构函数
Form::~Form()
{
    delete ui;

}
// 初始化界面函数
void Form::InitPage(){
    // 设置主窗体去掉边框
    this->setWindowFlags( Qt::WindowStaysOnTopHint|Qt::Tool|Qt::FramelessWindowHint);

    // 设置控件透明化（0~1 0为透明，1为完全不透明）
    // this->setWindowOpacity(1);

    // this->setStyleSheet("QWidget { color: #FFA500; font-weight: bold;  }");
    // 设置窗体透明化
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->move(0,0);


}
void Form::updateGPUInfo(){

    // 设置显卡使用率
  ui->ratesLabel->setText(QString::number(displayCard->GetDisplayCardUsage())+"%");
    // 获得显存使用情况
    QString usedMemory = QString::number((displayCard->GetDisplayCardMemoryUsed()),'f',2)+"GB";
    // 获得总显存
    QString totalMemory = QString::number(displayCard->GetDisplayCardMemoryTotal(),'f',0)+"GB";
    ui->memoryLabel->setText(usedMemory+"/"+totalMemory);
    this->adjustSize();
    this->show();

}
// 设置任务栏托盘函数
void Form::SetSysTrayIcon(){

    QIcon icon ("lib/icon.jpg");
    sysTrayIcon = new QSystemTrayIcon(this);
    sysTrayIcon->setIcon(icon);
    sysTrayIcon->setToolTip("显卡监视");

    // 设置右键菜单
    QMenu *trayMenu = new QMenu(this); // 初始化右键菜单
    // 按钮绑定事件
    showAction = new QAction("显示窗口",this);
    QAction *exitAction = new QAction("退出程序",this);
    QAction *dragModeAction = new QAction("拖拽模式",this);

    showAction->setCheckable(true);
    showAction->setChecked(true);
    dragModeAction->setCheckable(true);
    dragModeAction->setChecked(false);


    connect(dragModeAction,&QAction::toggled,this,&Form::DragMode);

    // 拖拽模式启动后，退出隐藏模式（打开显示模式）
   // connect(dragModeAction,&QAction,showAction,&QAction::);

    connect(showAction,&QAction::toggled,this,&Form::ShowForm);
  // emit showAction->toggled(true);

    connect(exitAction,&QAction::triggered,this,&Form::ExitApplication);
    trayMenu->addAction(dragModeAction);
    trayMenu->addAction(showAction);    //菜单添加按钮
    trayMenu->addAction(exitAction);

    sysTrayIcon->setContextMenu(trayMenu); //将菜单加入到系统托盘中
    sysTrayIcon->show();
}
void Form::ExitApplication(){
    qApp->exit();
}
void Form::ShowForm(bool checked){

    if(checked){
        // 显示窗口
        this->setVisible(true);
        // 计时器继续
        timer->start();
        isShow = true;
    }else{
        // 窗口隐藏
        this->setVisible(false);
        // 计时器暂停
        timer->stop();
        this->ui->memoryLabel->setText("-200");
        isShow = false;
    }

}

// 设置允许用户拖拽窗体 移动位置
void Form::DragMode(bool checked){

    // 获取当前窗口标志
    Qt::WindowFlags flags = this->windowFlags();

    if (checked) {
        // 打开边框并允许拖拽
        flags |= Qt::WindowStaysOnTopHint | Qt::Tool;
        flags &= ~Qt::FramelessWindowHint; // 移除无边框标志
    } else {
        // 关闭边框并不允许拖拽
        flags |= Qt::WindowStaysOnTopHint | Qt::Tool | Qt::FramelessWindowHint;
    }

    // 设置新的窗口标志
    this->setWindowFlags(flags);
    this->show(); // 显示窗口（可能需要重新显示窗口）
    emit showAction->toggled(true);
}
