#include "form.h"
#include "ui_form.h"
#include <nvml.h>
#include<QTimer>
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

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
    this->ui->nameLabel->setText(QString::fromLocal8Bit(name,512));

    // 设置计时器
    QTimer *timer = new QTimer(this);
    nvmlUtilization_t nvmUtil;
    nvmlBAR1Memory_t memory;

    // connect(timer, &QTimer::timeout,this,

        // 获得显卡使用率
        nvmlDeviceGetUtilizationRates(device, &nvmUtil);
    // 设置文本为使用率
    this->ui->ratesLabel->setText(QString::number(nvmUtil.gpu)+"%");
    result = nvmlDeviceGetBAR1MemoryInfo(device, &memory);
    QString usedMemory = QString::number((float)(memory.bar1Used)/1024.0f/1024.0f/1024.0f,'f',0)+"GB";
    QString totalMemory =  QString::number((float)(memory.bar1Total)/1024.0f/1024.0f/1024.0f)+"GB";
    this->ui->memoryLabel->setText(usedMemory+"/"+totalMemory);

    // timer->start(1000);


}
Form::~Form()
{
    delete ui;
}
