#ifndef FISH_CAMERA_H
#define FISH_CAMERA_H

#include <opencv2/opencv.hpp>
#include <vector>
#include <tuple>
#include <string>
#include <vector>
#include <string>
#include <getopt.h>

class FishCamera {
public:
    double fov;     // 视场角
    double a, b, c; // 畸变校正系数
    double radius;  // 相机半径
    double u0, v0;  // 图像中心坐标
    cv::Mat R;      // 旋转矩阵

    FishCamera(double fov, double a, double b, double c, double radius, double u0, double v0, const cv::Mat& R)
        : fov(fov), a(a), b(b), c(c), radius(radius), u0(u0), v0(v0), R(R) {}
};
// 白平衡-灰度平衡
cv::Mat WhiteBalcane_Gray(cv::Mat src);

// 白平衡-完美反射
cv::Mat WhiteBalcane_PRA(cv::Mat src);

// 自动伽马校正
cv::Mat AutoGammaCorrection(const cv::Mat& src, cv::Mat& dst);
void run_command(const std::string& command, const std::string& description);
// 从球面坐标到图像坐标的映射
void mapS2I(const cv::Point3d& s_pt, const FishCamera& C, cv::Point2d& img_pt);
void printMatrices(const std::vector<cv::Mat>& matrices);

// 构建映射矩阵
void buildMap(cv::Rect roi, int sphere_height, const FishCamera& C, cv::Mat& map);

// 初始化扭曲
//void _initWarp(const std::vector<cv::Mat>& src_arr, const FishCamera& camera, const std::vector<cv::Mat>& matrices, const std::vector<int>& index, std::vector<cv::Mat>& blend_warpeds, int& canvas_height);
void _initWarp(const std::vector<cv::Mat>& src_arr, FishCamera& camera, const std::vector<cv::Mat>& matrices, const std::vector<int>& index, std::vector<cv::Mat>& blend_warpeds, int& canvas_height);


// 从PTO文件提取RPY值
void extractRPYFromPTO(const std::string& filename, std::vector<std::tuple<float, float, float>>& rpyValues);

// 角度转弧度
double degToRad(double deg);

// 将欧拉角转换为旋转矩阵
std::vector<std::vector<double>> angleToMat3(double pitch, double yaw, double roll);
int groundResult(std::string panoramapath, std::string groundPath, std::string resultPath);

#endif // FISH_CAMERA_H




