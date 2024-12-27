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
    double fov;     // �ӳ���
    double a, b, c; // ����У��ϵ��
    double radius;  // ����뾶
    double u0, v0;  // ͼ����������
    cv::Mat R;      // ��ת����

    FishCamera(double fov, double a, double b, double c, double radius, double u0, double v0, const cv::Mat& R)
        : fov(fov), a(a), b(b), c(c), radius(radius), u0(u0), v0(v0), R(R) {}
};
// ��ƽ��-�Ҷ�ƽ��
cv::Mat WhiteBalcane_Gray(cv::Mat src);

// ��ƽ��-��������
cv::Mat WhiteBalcane_PRA(cv::Mat src);

// �Զ�٤��У��
cv::Mat AutoGammaCorrection(const cv::Mat& src, cv::Mat& dst);
void run_command(const std::string& command, const std::string& description);
// ���������굽ͼ�������ӳ��
void mapS2I(const cv::Point3d& s_pt, const FishCamera& C, cv::Point2d& img_pt);
void printMatrices(const std::vector<cv::Mat>& matrices);

// ����ӳ�����
void buildMap(cv::Rect roi, int sphere_height, const FishCamera& C, cv::Mat& map);

// ��ʼ��Ť��
//void _initWarp(const std::vector<cv::Mat>& src_arr, const FishCamera& camera, const std::vector<cv::Mat>& matrices, const std::vector<int>& index, std::vector<cv::Mat>& blend_warpeds, int& canvas_height);
void _initWarp(const std::vector<cv::Mat>& src_arr, FishCamera& camera, const std::vector<cv::Mat>& matrices, const std::vector<int>& index, std::vector<cv::Mat>& blend_warpeds, int& canvas_height);


// ��PTO�ļ���ȡRPYֵ
void extractRPYFromPTO(const std::string& filename, std::vector<std::tuple<float, float, float>>& rpyValues);

// �Ƕ�ת����
double degToRad(double deg);

// ��ŷ����ת��Ϊ��ת����
std::vector<std::vector<double>> angleToMat3(double pitch, double yaw, double roll);
int groundResult(std::string panoramapath, std::string groundPath, std::string resultPath);

#endif // FISH_CAMERA_H




