#ifndef COLOR_DETECTION
#define COLOR_DETECTION

#include <opencv2/opencv.hpp>
#include <fstream>
#include <regex>
#include "../include/fingertip_detection.hpp"

using namespace cv;

class ColorDetectionModule {

    int iLowH, iHighH, iLowS, iHighS, iLowV, iHighV;
    Mat& frame;
    Mat color;
    FingertipDetectionModule ftdm;

    int thresh = 100;
    int max_thresh = 255;
    RNG rng = RNG(12345);
    
    public:
    bool color_set=false;

    ColorDetectionModule(Mat &a) : iLowH(0), iHighH(179), iLowS(0),iHighS(255),iLowV(0),iHighV(255),frame(a),color(),ftdm(color) {
        std::map<char,std::pair<int,int>> hsv_values;
        std::ifstream config;
        config.open("./config.txt");
        std::string setting;
        std::smatch m;
        while(getline(config, setting)){

            char f = setting[0];

            setting=setting.substr(2);
            int low;
            std::stringstream(setting)>>low;

            int i=1,tmp=low;
            while(tmp>9){
            tmp=tmp/10;
            i++;
            }

            setting = setting.substr(i+1);
            int high;
            std::stringstream(setting)>>high;
            hsv_values[f] = std::pair<int,int>(low,high);
            // std::cout<<f<<":"<<low<<":"<<high<<std::endl;
        }
        config.close();
        iLowH = hsv_values['h'].first;
        iHighH = hsv_values['h'].second;

        iLowS = hsv_values['s'].first;
        iHighS = hsv_values['s'].second;

        iLowV = hsv_values['v'].first;
        iHighV = hsv_values['v'].second;

        std::cout<<iLowH<<" "<<iHighH<<"\n"<<iLowS<<" "<<iHighS<<"\n"<<iLowV<<" "<<iHighV<<"\n";
    }
    void setHSVColors(Mat image);
    void colorSelect(Mat image);
    void showTrackbars();
    void getColor();
};

#endif