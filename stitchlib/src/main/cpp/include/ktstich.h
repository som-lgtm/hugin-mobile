#ifndef libktstitch_H
#define libktstitch_H

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include <filesystem>
#include "multiblend.h"
#include "imageCTR.h"
namespace fs = std::filesystem;
namespace mb = multiblend;
namespace MButils = mb::utils;
namespace io = mb::io;
namespace memory = mb::memory;


    void DeleteFilesWithExtension(const fs::path& dir, const std::string& extension);
    void PrintImageVector(const std::vector<multiblend::io::Image>& images);
    std::vector<io::Image> LoadImagesFromFiles(const std::vector<std::string>& filenames, const std::string& basePath);
    cv::Mat ConvertToMat(const multiblend::Result& result);
    std::vector<std::string> getFileList(const fs::path& directory, const std::string& extension);
    std::vector<cv::Mat> convertRPYToMatrices(const std::vector<std::tuple<float, float, float>>& rpyValues);
    FishCamera processPtoFile(const std::string& filename);
    std::string getAttributeValue(const std::string& element, const std::string& attribute);
    std::string generateString(const std::string& xmlContent);
    std::string processXMLFile(const std::string& filePath);
    void collectJpgFiles(const fs::path& work_dir, std::vector<cv::Mat>& src_arr);
    void process_panorama(const fs::path& work_dir, const fs::path& output_path,const fs::path& xml_file_path,
                          int canvas_width, double exposure_value, int sieve, const std::string& mode,
    bool fine_composition, const fs::path& ground_image_path);


#endif 
