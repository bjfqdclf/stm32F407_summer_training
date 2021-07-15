# stm32F407_summer_training
基于stm32F407的软件开发

```c
/**
 *　　　　　　　　┏┓　　　┏┓+ +
 *　　　　　　　┏┛┻━━━┛┻┓ + +
 *　　　　　　　┃　　　　　　　┃ 　
 *　　　　　　　┃　　　━　　　┃ ++ + + +
 *　　　　　　 ████━████ ┃+
 *　　　　　　　┃　　　　　　　┃ +
 *　　　　　　　┃　　　┻　　　┃
 *　　　　　　　┃　　　　　　　┃ + +
 *　　　　　　　┗━┓　　　┏━┛
 *　　　　　　　　　┃　　　┃　　　　　　　　　　　
 *　　　　　　　　　┃　　　┃ + + + +
 *　　　　　　　　　┃　　　┃　Code is far away from bug with the animal protecting　　　　　　　
 *　　　　　　　　　┃　　　┃ + 神兽保佑,永无bug　　
 *　　　　　　　　　┃　　　┃
 *　　　　　　　　　┃　　　┃　　+　　　　　　　　　
 *　　　　　　　　　┃　 　　┗━━━┓ + +
 *　　　　　　　　　┃ 　LiGoudan 　┣┓ + +
 *　　　　　　　　　┃ 　　　　　　　┏┛
 *　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
 *　　　　　　　　　　┃┫┫　┃┫┫
 *　　　　　　　　　　┗┻┛　┗┻┛+ + + +
 */
```

# 基本信息
### 硬件
- STM32F407ZE
- J-Link下载器

# 蓝牙模块
### 硬件信息
- ZS-040
### 使用说明
#### 连接软件
- 蓝牙串口小程序

#### 蓝牙AT指令
- AT  基本信息
- AT+NAME 名称
- AT+VERSION  版本

#### 输入指令
- CloseLed+num	
- OpenLed+num	
- LedFast
- LedLow
- LedShan+num	
- LedNotShan+num	
# 超声波模块
### 硬件信息
- HC-SR04
### 使用说明
- key1  打开
- key2  关闭
- key3 调节等级（3级可调led2~4）
# 温湿度模块
### 硬件信息

