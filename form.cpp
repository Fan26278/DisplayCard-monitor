#include "form.h"
#include "ui_form.h"
#include <nvml.h>
#include<QTimer>

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);
    ui->setupUi(this);

    // 初始化NVML库
    nvmlReturn_t result = nvmlInit();
    if (result != NVML_SUCCESS)
    {
        return;
    }

    // 设置计时器
    QTimer *timer = new QTimer(this);
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
    nvmlDevice_t device;
    nvmlReturn_t result;
    unsigned int device_count, i;

    device_count = -1;
    // First initialize NVML library
    result = nvmlInit();
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


    nvmlUtilization_t nvmUtil;
    nvmlMemory_t memory;


    // 获得显卡使用率
    nvmlDeviceGetUtilizationRates(device, &nvmUtil);
    // 设置文本为使用率
    ui->ratesLabel->setText(QString::number(nvmUtil.gpu)+"%");
    // 获得显存使用率
    result = nvmlDeviceGetMemoryInfo(device, &memory);
    //
    QString usedMemory = QString::number((float)(memory.used)/1024.0f/1024.0f/1024.0f,'f',2)+"GB";
    QString totalMemory =  QString::number((float)(memory.total)/1024.0f/1024.0f/1024.0f)+"GB";
    ui->memoryLabel->setText(usedMemory+"/"+totalMemory);


}

