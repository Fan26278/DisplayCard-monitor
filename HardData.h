#ifndef HARDDATA_H
#define HARDDATA_H
#include <nvml.h>
#include<QString>
class HardData{
    nvmlDevice_t device;
    nvmlMemory_t memory;
    nvmlReturn_t result ;
    unsigned int device_count;
    unsigned int * fanSpeed;
    unsigned int * cardTemp;


public:
    ~HardData(){
        nvmlShutdown();
        delete this;
    }
    void InitDisplayCard(){
        // 初始化NVML库
        result = nvmlInit();
        //获得设备操作句柄
        result = nvmlDeviceGetHandleByIndex(0,&device);
        // 获取设备数量
        if(NVML_SUCCESS != result){

        }

    }

    int GetDisplayCardCount(){
        device_count = -1;
        result = nvmlDeviceGetCount(&device_count);
        return device_count;
    }
    // 获取显卡名字函数
    QString GetDisplayCardName(){
        // 获得名字
        char name[NVML_DEVICE_NAME_BUFFER_SIZE];
        result = nvmlDeviceGetName(device, name, NVML_DEVICE_NAME_BUFFER_SIZE);
        return QString::fromLocal8Bit(name,512);
    }
    // 获取显卡使用率函数
    int GetDisplayCardUsage(){
        nvmlUtilization_t nvmUtil;
        // 获得显卡使用率
       result =  nvmlDeviceGetUtilizationRates(device, &nvmUtil);

            return nvmUtil.gpu;

    }
    // 获取总显存
    float GetDisplayCardMemoryTotal(){
        result = nvmlDeviceGetMemoryInfo(device, &memory);
        return ((float)(memory.total)/1024.0f/1024.0f/1024.0f);
    }
    // 获取已经用的显存
    float GetDisplayCardMemoryUsed(){
        result = nvmlDeviceGetMemoryInfo(device, &memory);
        //        return memory.used;
        return (float)(memory.used)/1024.0f/1024.0f/1024.0f;
    }

    // 获取风扇转速
    int GetFanSpeed(){
        return nvmlDeviceGetFanSpeed(device,fanSpeed);
    }

     // 获取温度
//    int GetCardTemp(){

//      //  return nvmlDeviceGetTemperature(device,tmpSensor,cardTemp);
//    }
};

#endif // HARDDATA_H
