# 项目名称
利用hugin实现移动端图片拼接

## 简介
利用hugin实现移动端图片拼接，基于android平台，把hugin项目移植到安卓平台实现图片拼接成全景图

## 功能特点
素材采集采用鲲图手机全景云台对素材采集，然后把素材导入项目实现移动端完成全景图拼接
[![云台](pic/1.png)](https://kuntu720.taobao.com)
[![云台](pic/2.png)](https://kuntu720.taobao.com)
[![素材](pic/imgs.png)]
[![拼接结果](pic/result.jpg)]
## 安装与使用

### 结构
hugin-mobile/  
├── app/  
│   ├── src/  
│   │   ├── main/  
│   │   │   ├── java/com/example/phonestitch/  # Java/Kotlin 代码  
│   │   │   │   ├── MainActivity.kt           # 主界面  
│   │   │   │   └── NativeLib.kt              # JNI 调用类  
│   │   │   ├── cpp/                          # NDK 本地代码  
│   │   │   │   ├── native-lib.cpp            # 调用 Hugin 核心  
│   │   │   │   └── CMakeLists.txt            # NDK 编译配置  
│   │   │   ├── res/                          # Android UI 资源  
│   │   │   │   ├── layout/activity_main.xml  # 主界面布局  
│   │   │   │   └── drawable/                 # 图片资源  
│   │   │   ├── AndroidManifest.xml           # 应用配置  
│   │   │   └── build.gradle                  # 构建配置  
├── stitchlib/                                # hugin库 
└── README.md  


### 安装步骤
1. 克隆仓库：
   ```bash
   git clone https://github.com/som-lgtm/hugin-mobile.git
