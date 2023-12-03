#### 0730 RAW格式图像原理简述

https://zhuanlan.zhihu.com/p/158088019

##### 概念

RAW格式的图片是数码相机采集到的最原始的图像数据信息。

**JPEG**来自于RAW格式图片进行图像后处理和压缩后得到的照片，**会丢到许多重要的信息**。

##### 数码相机传感器介绍

**Cavity Array、Light Cavity**

数码相机使用数百万个微小的感光元来记录图像。当按下相机的快门按钮并开始曝光时，每一个感光元都会收集光子并将其存储为电信号。

曝光结束后，相机将关闭这些（光点/感光元？）然后通过测量电信号的强度来评估有多少光子掉入感光元中。然后将信号量转化为数字值，其精度由图像位深确定。我们能看到的图像精度结果取决于图像的记录格式，比如8为的JPEG照片其像素值就有2^8 = 256，其每一个pixel值就为[0 - 255]。使用的位数越大，我们就可以将颜色表示得越精细。

#### CFA（彩色滤光片阵列）

相机的感光元并不能区分不同的颜色，因此只依靠感光元只能创建灰度图像。为了捕获彩色图像，必须在每个感光元上方放置一个滤镜，该滤镜仅允许特定颜色的光。

最常见的CFA为Bayer阵列（拜尔阵列）。

![img](https://pic1.zhimg.com/80/v2-068c33c003753c728e083a76edc03048_720w.webp)

- 以2*2的小方块来看，其是一个有规律的排列，遵循绿-红-蓝-绿的组合。专业点说，拜耳阵列由交替排列的绿红和蓝绿滤光片组成。

- ##### ==拜耳阵列包含的绿色传感器是红色或蓝色传感器的两倍==（这样设计的原因是人眼对绿色更为敏感，所以使用了更多的绿色滤光片采集绿色）。这样设计的另一个原因是与每种颜色均等相比，带有绿色像素的冗余所产生的图像看起来噪声更少，并且具有更好的细节。

#### Bayer去马赛克 - BAYER DEMOSAICING

相机传感器接收到的最原始的图会带有明显的马赛克感，色块很突出，所以要去马赛克。

Bayer去马赛克是将这种拜耳原色阵列转换为最终图像的过程，该最终图像的每个像素都是全色的。 一种简单的方法是将红色，绿色和蓝色的每个2x2阵列视为一个完整的彩色块。如图三，黑色圆圈表示的就是2x2阵列合并得到的全色信息。

![img](https://pic2.zhimg.com/80/v2-d3639f4a9606b8e894fda7b1663451e9_720w.webp)

**这种方法会导致图像的分辨率下降，长和宽各少了1/2，那么总体分辨率就少了1/4**

因此：==**一般将RGB分别拆开进行插值然后合并**==

![img](https://pic3.zhimg.com/80/v2-96a2df77ab5d40b3dad179c654885742_720w.webp)

- 从RAW图到JEPG有一系列复杂的图像信号处理过程，称作==ISP（Image Signal Processing）==







记得看图像色深：https://zhuanlan.zhihu.com/p/157833222



### 0902

#### ISP流程解析

![image-20230902123821905](C:\Users\LeeON\AppData\Roaming\Typora\typora-user-images\image-20230902123821905.png)

- 光电转换好比做水桶接雨水
  - 关键点：黑电平矫正（无光时coms芯片也会有电信号）
  - 去噪声
- 没有完美的矫正（进光量矫正LSC；镜头矫正）
- 没有完美的sensor（BPC坏点处理）
- 颜色的完美还原
  - 感光元件sensor无法直接感知到颜色，只能感知到的时强度；
  - 对Bayer CFA(color Filter Array)进行**Demosaicing**，使得单通道变3通道，得到彩色的CamRGB图像。
  - CamRGB--->sRGB：CCM（Color Correction Matrix）
  - WB（White Balance）：在让相机在不同的色温下拍摄图像中的白色都可呈现为白色。
  - Gamma(Gamma Correction）【人眼对暗区更加敏感，不是线性的过程）
- 记录视场中更多的信息
  - AF（自动对焦）Auto Focus
  - AES（自动曝光控制）Automatic Exposure Control
  - HDR（高动态范围）High Dynamic Range

<img src="C:\Users\LeeON\AppData\Roaming\Typora\typora-user-images\image-20230902131101707.png" alt="image-20230902131101707" style="zoom: 50%;" />

> 你好，你可以看看《image sensors and signal processing for digital still cameras》这本书。

