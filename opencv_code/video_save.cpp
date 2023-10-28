#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{



 

    string sourceVideoPath = "F:/material/videos/tea_small.avi";
    string outputVideoPath = "small_write_test.avi";

    // 视频读入
    VideoCapture inputVideo("rtsp://192.168.3.66:554/user=admin&password=&channel=1&stream=0.sdp?");
    // 检测视频输入的有效性     
    if (!inputVideo.isOpened())
    {
        cout << "fail to open!" << endl;
        return -1;
    }

    // 获取视频分辨率
    int videoWidth = (int)inputVideo.get(CV_CAP_PROP_FRAME_WIDTH);
    int videoHeight = (int)inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT);
    cv::Size videoResolution = cv::Size(videoWidth, videoHeight);

    cout << "视频分辨率：" << videoResolution.width << " " << videoResolution.height << endl;


    // 获取视频总帧数  
    int videoCount = inputVideo.get(CV_CAP_PROP_FRAME_COUNT);
    cout << "总帧数：" << videoCount << endl;

    //获取视频帧率
    double fps = inputVideo.get(CV_CAP_PROP_FPS);

    //初始化一个VideoWriter对象
    VideoWriter outputVideo;


    //open方法相关设置
    int fourcc_1 = VideoWriter::fourcc('X', 'V', 'I', 'D'); //设置视频的编码方式
    outputVideo.open(outputVideoPath, fourcc_1, fps, videoResolution, true);

    if (!outputVideo.isOpened())
    {
        cout << "fail to open!" << endl;
        return -1;
    }

    cv::Mat frameImg, resultImg;

    int count = 0;

    while (true)
    {

        inputVideo >> frameImg;//获取当前帧图像


        // 显示当前帧
        if (!frameImg.empty())
        {
            outputVideo << frameImg;//将当前帧进行编码写入视频文件

            count++;
            cout << "一共" << videoCount << "帧,";
            cout << "第" << count << "帧处理完毕" << endl;
        }
        else
        {
            break;
        }
    }

    // 释放相关对象及资源
    inputVideo.release();
    outputVideo.release();

    return 0;

}