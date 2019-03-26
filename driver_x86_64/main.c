#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <queue>
#include <linux/videodev2.h>
#include "DriverInterface.h"

//使能opencv 图像显示窗口, 需要安装opencv并修改Makefile
#define SHOW  0

#if SHOW
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#endif

using namespace indem;

void ImuCallBackFunction(IMUData* data) {
    char buf[1024];
    //打印imu数据  时间(ms)  ACC（g） GYR (d/s)
    sprintf(buf, "%-18f %-18f %-18f %-18f %-18f %-18f %-18f\n", data->_timeStamp, data->_acc[0], data->_acc[1], data->_acc[2], data->_gyr[0], data->_gyr[1], data->_gyr[2]);
    printf("%s", buf);
    return;
}

void CameraCallbackFunction(cameraData* data) {
    //打印每帧图像时间  
    //printf("%f\n", data->_timeStamp);
#if SHOW
    cv::Mat img(data->_height, data->_width, CV_8UC1, data->_image);
    cv::imshow( "camera", img );
    cv::waitKey(10);
    img.release();
#endif
    return;
}

void HMDHotplugCallback_func(bool bArrive) {
    if (bArrive) {
        printf("设备插入\n");
    } else {
        printf("设备移除\n");
    }
    return;
}

int main(int argc, char **argv) {
    int ret = 0;
    int width = 0;      //单图像宽度 640 1280
    int height = 0;     //单图像高  400 800
    int fps = 0;        //帧率 25 50 100 200
    int imufreq = 0;    //imu频率
    int version = 255;  //代码固件版本号，初始值任意
    size_t info_size = 0; //获取到的参数总长度
    unsigned char *module_info = new unsigned char[sizeof(struct ModuleParameters)];
    struct ModuleParameters moddule_param = {0}; //标定参数等信息等
    IDriverInterface *driver = DriverFactory();
    enum IMAGE_RESOLUTION plan = RESOLUTION_640;

    if (argc == 5) {
        width = atoi(argv[1]);
        height = atoi(argv[2]);
        fps = atoi(argv[3]);
        imufreq = atoi(argv[4]);
        if (width == 1280)
            plan = RESOLUTION_1280;
        else if (width == 640)
            plan = RESOLUTION_640;
        else {
            width = 640;
            plan = RESOLUTION_640;
        }

        if (fps != 25 && fps != 50 && fps != 100 && fps != 200) {
            fps = 25;
        }
        if (fps == 200 && plan != RESOLUTION_640) {
            fps = 100;
        }

        if (imufreq > 1000) {
            imufreq = 1000;
        }
    } else {
        width = 1280;
        height = 800;
        fps = 50;
        imufreq = 1000;
    }
    //获取标定参数等信息等
    ret = driver->GetModuleParams(version, module_info, info_size);
    if (ret != true) {
        printf("Get params faild\n");
    } else {
        memcpy(&moddule_param, module_info, sizeof(struct ModuleParameters));
    }
    //打开设备
    ret = driver->Open(imufreq, fps, plan);
    ret = 0;
    if (ret < 0) {
        printf("open err\n");
    } else {
        driver->SetCameraCallback(CameraCallbackFunction);
        driver->SetIMUCallback(ImuCallBackFunction);
        SetHotplugCallback(HMDHotplugCallback_func);
    }
    //	sleep(5);
    //关闭设备
    //	driver->Close();
    while (1) {
        sleep(3600);
    }
    return 0;
}
