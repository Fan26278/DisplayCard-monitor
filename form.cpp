#include "form.h"
#include "ui_form.h"
#include<QTimer>
#include<QSystemTrayIcon>
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
    this->setWindowFlags(Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint|Qt::Tool);
    // 设置控件透明化（0~1 0为透明，1为完全不透明）
    // this->setWindowOpacity(1);
    // 设置窗体透明化
    this->setAttribute(Qt::WA_TranslucentBackground);
    // this->setStyleSheet("QWidget { color: #FFA500; font-weight: bold;  }");

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
}
// 设置任务栏托盘函数
void Form::SetSysTrayIcon(){

    QIcon icon ("lib/icon.jpg");
    QSystemTrayIcon *sysTrayIcon = new QSystemTrayIcon(this);
    sysTrayIcon->setIcon(icon);
    sysTrayIcon->setToolTip("显卡监视");

    // 设置右键菜单
    QMenu *trayMenu = new QMenu(this); // 初始化右键菜单
    // 按钮绑定事件
    QAction *showAction = new QAction("显示窗口",this);
    QAction *exitAction = new QAction("退出程序",this);
    showAction->setCheckable(true);
    showAction->setChecked(true);
    connect(showAction,&QAction::toggled,this,&Form::ShowForm);


    connect(exitAction,&QAction::triggered,this,&Form::ExitApplication);

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

    }else{
        // 窗口隐藏
        this->setVisible(false);
        // 计时器暂停
        timer->stop();
        this->ui->memoryLabel->setText("-200");
    }

}
