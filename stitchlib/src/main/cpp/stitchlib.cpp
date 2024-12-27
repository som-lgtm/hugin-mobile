#include <jni.h>
#include <string>
#include "ktstich.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_stitch_stitchlib_NativeLib_stringFromJNI(JNIEnv* env, jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" JNIEXPORT jint JNICALL
Java_com_stitch_stitchlib_NativeLib_processPanorama(
        JNIEnv* env,
        jobject obj,
        jstring workDir,
        jstring outputPath,
        jstring xmlFilePath,
        jint canvasWidth,
        jdouble exposureValue,
        jint sieve,
        jstring mode,
        jboolean fineComposition,
        jstring groundImagePath) {

    const char* workDirCStr = env->GetStringUTFChars(workDir, nullptr);
    const char* outputPathCStr = env->GetStringUTFChars(outputPath, nullptr);
    const char* xmlFilePathCStr = env->GetStringUTFChars(xmlFilePath, nullptr);
    const char* modeCStr = env->GetStringUTFChars(mode, nullptr);
    const char* groundImagePathCStr = env->GetStringUTFChars(groundImagePath, nullptr);

    // 确保每个参数在使用前都已经处理空值
    std::string workDirStr = (workDirCStr != nullptr) ? workDirCStr : "";
    std::string outputPathStr = (outputPathCStr != nullptr) ? outputPathCStr : "";
    std::string xmlFilePathStr = (xmlFilePathCStr != nullptr) ? xmlFilePathCStr : "";
    std::string modeStr = (modeCStr != nullptr) ? modeCStr : "";
    std::string groundImagePathStr = (groundImagePathCStr != nullptr) ? groundImagePathCStr : "";

    // 使用默认值
    if (canvasWidth <= 0) canvasWidth = 8192; // 默认宽度
    if (exposureValue < 0.0) exposureValue = 0.3; // 默认曝光值
    if (sieve <= 0) sieve = 6; // 默认重叠宽度

    try {
        // 调用处理函数
        process_panorama(workDirStr.c_str(), xmlFilePathStr.c_str(), outputPathStr.c_str(),
                         canvasWidth, exposureValue, sieve,
                         modeStr.c_str(), fineComposition, groundImagePathStr.c_str());
    } catch (const std::exception& ex) {
        // 处理异常并释放资源
        env->ReleaseStringUTFChars(workDir, workDirCStr);
        env->ReleaseStringUTFChars(outputPath, outputPathCStr);
        env->ReleaseStringUTFChars(xmlFilePath, xmlFilePathCStr);
        env->ReleaseStringUTFChars(mode, modeCStr);
        env->ReleaseStringUTFChars(groundImagePath, groundImagePathCStr);
        return -1; // 返回错误代码
    }

    // 释放资源
    env->ReleaseStringUTFChars(workDir, workDirCStr);
    env->ReleaseStringUTFChars(outputPath, outputPathCStr);
    env->ReleaseStringUTFChars(xmlFilePath, xmlFilePathCStr);
    env->ReleaseStringUTFChars(mode, modeCStr);
    env->ReleaseStringUTFChars(groundImagePath, groundImagePathCStr);

    return 0; // 返回成功
}

// 新增方法获取用户应用数据目录
extern "C" JNIEXPORT jstring JNICALL
Java_com_stitch_stitchlib_NativeLib_getUserAppDataDir(JNIEnv* env, jobject /* this */) {
    // 假设返回的是一个示例路径，实际情况应根据需要获取
    const char* path = "/data/data/com.example.phonestitch/app_data";
    return env->NewStringUTF(path);
}
