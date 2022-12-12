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

1.找到自己电脑 OpenCV安装的路径,找到bin目录进行 Copy（复制）D:\APP\OpenCV\opencv\build\x64\vc15\lib

![OpenCV的bin目录](https://user-images.githubusercontent.com/99727314/206951488-c0b3ca46-9eba-49dc-9cce-55901ab56d98.png)


2.找到系统属性点击环境变量

![系统属性](https://user-images.githubusercontent.com/99727314/206912887-ffa32da4-fa02-4ff2-9094-0e7627c0bdfd.png)

3.点击用户变量中的 Path

![环境变量](https://user-images.githubusercontent.com/99727314/206913061-95c120fd-80df-4052-9e51-61e907c195df.png)

4.点击新建，将OpenCV路径下的bin目录 Paste（粘贴）,之后点击确定，确定，确定即可！

![path](https://user-images.githubusercontent.com/99727314/206951555-760e1b22-3be3-43b4-af66-79ff6895bcde.png)


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

5.鼠标右击项目名称，找属性

![找到属性](https://user-images.githubusercontent.com/99727314/206949655-9be63826-e252-495f-98c8-ec8c8f6ce984.png)

6.点击属性，找到 VC++目录，右侧的包含目录和库目录

![属性界面](https://user-images.githubusercontent.com/99727314/206949780-7001c5c2-f518-43e0-ba7f-453370a92d69.png)

7.配置包含目录，新建一行，找OpenCV的以下目录进行添加

D:\APP\OpenCV\opencv\build\include

D:\APP\OpenCV\opencv\build\include\opencv2

![包含目录配置](https://user-images.githubusercontent.com/99727314/206950203-298b0527-70f0-4e59-b448-99346be35450.png)

8.配置库目录，同理，找OpenCV中的以下目录进行添加

D:\APP\OpenCV\opencv\build\x64\vc15\lib

![库目录配置](https://user-images.githubusercontent.com/99727314/206950553-26dd3cfc-0b59-4e9b-9f90-aaadad7ff9ce.png)

配置好的界面

![库和包含目录配置好的界面](https://user-images.githubusercontent.com/99727314/206950607-5f73dd1a-1e32-48a1-9df1-00436a98afd7.png)

9.找到链接器的输入，附加依赖项

![找到链接器](https://user-images.githubusercontent.com/99727314/206950749-8d2035e9-d1bc-44db-b197-afd9faa18ec1.png)

10.找到OpenCV目录 D:\APP\OpenCV\opencv\build\x64\vc15\lib 下的 opencv_world455d.lib 文件

![lib](https://user-images.githubusercontent.com/99727314/206950948-b1f2c6d0-799e-4ee9-9e36-8e099ee3184c.png)

11.复制 opencv_world455d.lib 的全名称，进行贴贴，之后确定，确定！

![链接器配置](https://user-images.githubusercontent.com/99727314/206951247-c0780172-4fb7-4d3f-946f-9749d1457def.png)

12.以上都配置好，恭喜你！！！，OpenCV 已配置好 ，请把你的电脑重新开机，🙂。



