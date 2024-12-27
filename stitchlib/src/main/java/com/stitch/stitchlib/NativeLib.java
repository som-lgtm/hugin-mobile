package com.stitch.stitchlib;

public class NativeLib {

    // Used to load the 'stitchlib' library on application startup.
    static {
        System.loadLibrary("c++_shared");
        System.loadLibrary("stitchlib");
    }

    public native String stringFromJNI();

    public native int processPanorama(String workDir,
                                      String outputPath,
                                      String xmlFilePath,
                                      int canvasWidth,
                                      double exposureValue,
                                      int sieve,
                                      String mode,
                                      boolean fineComposition,
                                      String groundImagePath);

    // 新增获取用户应用数据目录的本地方法
    public native String getUserAppDataDir();

    // 新增一个处理全景图的封装方法，使用默认值
    public int processPanoramaWithDefaults(String workDir, String outputPath, String xmlFilePath) {
        // 设置默认参数
        int canvasWidth = 8192; // 默认全景图宽度
        double exposureValue = 0.3; // 默认曝光值
        int sieve = 6; // 默认重叠宽度
        String mode = ""; // 默认模式为空
        boolean fineComposition = false; // 默认不开启精细合成
        String groundImagePath = ""; // 默认空补地图片路径

        // 调用本地方法
        return processPanorama(workDir, outputPath, xmlFilePath, canvasWidth, exposureValue, sieve, mode, fineComposition, groundImagePath);
    }
}
