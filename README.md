# OpenCVLearning
基于C++语言的OpenCV入门学习


一、下载Visual Studio
进入网址:https://learn.microsoft.com/en-us/visualstudio/releases/2019/release-notes
下载Visual Studio Community 2019
![VS2019下载](https://user-images.githubusercontent.com/99727314/206912007-b710db93-6090-4ce0-9403-8685f28bcab8.png)

二、下载OpenCV
进入官网：https://opencv.org/releases/
选择 OpenCV – 4.5.4 版本下载
![opencv下载](https://user-images.githubusercontent.com/99727314/206912221-10f56325-744b-4b23-ace4-addab5dd56bd.png)
下载后安装即可，下载时速度可能比较慢。

三、配置OpenCV环境

1.找到自己电脑 OpenCV安装的路径,找到bin目录进行 Copy（复制）D:\APP\OpenCV\opencv\build\bin

![OpenCV的bin目录](https://user-images.githubusercontent.com/99727314/206912837-89ace0fc-12bc-4716-9c29-b80b02f6315a.png)

2.找到系统属性点击环境变量

![系统属性](https://user-images.githubusercontent.com/99727314/206912887-ffa32da4-fa02-4ff2-9094-0e7627c0bdfd.png)

3.点击用户变量中的 Path

![环境变量](https://user-images.githubusercontent.com/99727314/206913061-95c120fd-80df-4052-9e51-61e907c195df.png)

4.点击新建，将OpenCV路径下的bin目录 Paste（粘贴）,之后点击确定，确定，确定即可！

![path](https://user-images.githubusercontent.com/99727314/206913235-dfee4543-00f8-4f9b-ab8a-2ea507ae82be.png)

四、Visual Studio配置OpenCV

1.在 Visual Studio Installer 点击修改

![VSinstaller](https://user-images.githubusercontent.com/99727314/206946341-8abc8009-b694-46d2-9ab6-7f96b3a30916.png)


2.选择工作负载，✔ 上使用 C++ 的桌面开发，点击修改

![工作负载](https://user-images.githubusercontent.com/99727314/206946377-37240b1a-e980-4abc-bef9-8c9991985cd1.png)

3.创建一个新项目OpenCVLearning

![配置新项目](https://user-images.githubusercontent.com/99727314/206946528-ea914d27-47cd-45f9-8df7-a09391c7a0b5.png)


项目模板为：Windows 桌面向导

![创建新项目](https://user-images.githubusercontent.com/99727314/206946512-5637039c-d219-4080-9b13-10e878b7dd19.png)

4.项目创建好，将x86改为x64，找到项目名称

![项目创建好的界面](https://user-images.githubusercontent.com/99727314/206946619-d7464194-d753-4063-b9cc-01967ebd213f.png)

