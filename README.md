API及测试程序使用手册
====  

## 一、注意事项：

1.运行环境x86_64,目前在Ubuntu 14.04、16.04、18.04, centos7.5测试可用，其它64位linux系统理论上来说可用。

2.aarch64 ubuntu16.04测试可用,其它64位linux系统理论上来说可用。

3.程序需要使用root权限去运行，arm架构和x86架构需使用不同的动态库文件。

4.模组需要插到usb3.0接口上使用。

5.各个函数参数定义及相关说明请参考include目录下头文件及其注释。

6.camera 支持分辨率 1280x800x2  640x400x2  帧率 25fps  50fps

7.imu数据频率(imuFreq) 目前只支持 <1000hz, 且需要满足相邻两帧imu数据时间间隔为 >0 整数

## 二、API调用
以下是基本函数调用说明，具体操作参考main.c
### 1）包含下indem 命名空间
~~~
using namespace indem;
~~~
### 2) 调用DriverFactory()函数返回api对象指针;
~~~
如：IDriverInterface *driver = DriverFactory();
~~~
### 3）设置回调函数
#### a)根据以下几个定义，实现三个回调函数，用于接收相关数据，回调函数参数定义可参考include/DriverInterface.h
~~~
    typedef void(*DriverCameraDataCallback)(cameraData* data);
    typedef void(*DriverIMUDataCallback)(IMUData* data);
    typedef void(*DriverHotplugCallback)(bool bArrive);
    
    如：
        void ImuCallBackFunction(IMUData* data)；
        void CameraCallbackFunction(cameraData* data)；
        void HMDHotplugCallback_func (bool bArrive)；
~~~
#### b)获取标定参数
~~~
    函数原型:
        bool GetModuleParams(int& version, unsigned char* params, size_t& len)
        version: 模组内部固件版本标记，备用
        params:    模组信息标定信息存放缓冲区
        len: 接收到数据的长度，单位:byte
        return: true 获取参数成功， false 获取参数失败
    调用如下:
        int version = 255;
        size_t info_size = 0;
        unsigned char *module_info = new unsigned char[(sizeof(struct ModuleParameters))];
        struct ModuleParameters moddule_param;//标定参数等信息
        driver->GetModuleParams(version, module_info, info_size);
        memcpy(&moddule_param, module_info, sizeof(struct ModuleParameters));
~~~
#### b)调用设备打开接口，打开模组
~~~
    函数原型:
        bool Open(int imuFreq=1000,int imgFreq=50, IMAGE_RESOLUTION resolution= RESOLUTION_DEFAULT)
            param1: imu数据频率(imuFreq) 目前只支持 <1000hz 且需要满足 1000/imuFreq 为>0 整数（imu寄存器中是以时间间隔为单位配置的）
            param2: 图像频率 目前支持 25、50
            param3: 图像分辨率 参数只支持 RESOLUTION_1280（1280x800x2）、RESOLUTION_640（640x400x2）
            return：false 设备打开失败
    调用如下:
        driver->Open(1000, 50, RESOLUTION_1280);
~~~
#### c)调用回调函数接口配置回调函数  
~~~
    如： 
        driver->SetCameraCallback(CameraCallbackFunction);
        driver->SetIMUCallback(ImuCallBackFunction);
        SetHotplugCallback(HMDHotplugCallback_func);
~~~
## 测试程序编译和使用
### aarch64:
~~~
    交叉编译工具下载:
        下载链接  https://releases.linaro.org/components/toolchain/binaries/7.3-2018.05/aarch64-linux-gnu/
        选择 gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz
    
    解压交叉编译工具， 可根据需要修改交叉编译工具(同时修改build.sh 中 ”CROSS_COMPILE“ 选项)：
        tar -xvJf gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu.tar.xz
    编译：
       ./build.sh
    运行：
      sudo ./main.sh width height camfps imufreq
      如：sudo ./main.sh 640 400 25 200
~~~
### x86_64:
~~~
    编译：
       ./build.sh
    运行：
      sudo ./main.sh width height camfps imufreq
      如：sudo ./main.sh 640 400 25 200
~~~
