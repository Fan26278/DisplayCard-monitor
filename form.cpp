#include "form.h"
#include "ui_form.h"
#include <nvml.h>
#include<QTimer>
#include<QSystemTrayIcon>
#include<QMenu>
#include<QAction>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    // 初始化NVML库
    result = nvmlInit();
    if (result != NVML_SUCCESS)
    {
        return;
    }

    // 设置主窗体去掉边框
    this->setWindowFlags(Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint|Qt::Tool);
    // 设置控件透明化（0~1 0为透明，1为完全不透明）
    // this->setWindowOpacity(1);
    // 设置窗体透明化
    this->setAttribute(Qt::WA_TranslucentBackground);
    // this->setStyleSheet("QWidget { color: #FFA500; font-weight: bold;  }");


    unsigned int device_count;

    device_count = -1;

    result = nvmlDeviceGetCount(&device_count);
    // 获取设备数量
    if(NVML_SUCCESS != result){

    }

    //获得设备操作句柄
    nvmlDeviceGetHandleByIndex(0,&device);

    // 获得名字
    char name[NVML_DEVICE_NAME_BUFFER_SIZE];

    result = nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_BUFFER_SIZE);

    // 设置标签为显卡名字
    ui->nameLabel->setText(QString::fromLocal8Bit(name,512));
    ui->nameLabel->adjustSize();
    this->move(0,0);

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
    nvmlReturn_t result = nvmlShutdown();
    if (result != NVML_SUCCESS)
    {
        // 处理关闭失败的情况
    }
}

void Form::updateGPUInfo(){


    // 获得显卡使用率
    nvmlDeviceGetUtilizationRates(device, &nvmUtil);
    // 设置文本为使用率
    ui->ratesLabel->setText(QString::number(nvmUtil.gpu)+"%");
    // 获得显存使用率
    result = nvmlDeviceGetMemoryInfo(device, &memory);

    QString usedMemory = QString::number((float)(memory.used)/1024.0f/1024.0f/1024.0f,'f',2)+"GB";
    QString totalMemory =  QString::number((float)(memory.total)/1024.0f/1024.0f/1024.0f)+"GB";
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
    }

}
