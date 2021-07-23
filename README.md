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
## fp分支实现智能指纹门锁项目
- 开机启动显示温度湿度
- 可用按键控制菜单选择，返回，确定
- 连续输入5次错误密码或指纹将锁住
- 管理员重置密码，可继续使用
- 管理员可以添加指纹、删除指纹（未实现，已留接口）
- 多次检测有人时警报（未实现，可通过超声波接口实现）
## 硬件
- [STM32F407ZE](https://s.taobao.com/search?q=STM32F407ZE&imgfile=&js=1&stats_click=search_radio_all%3A1&initiative_id=staobaoz_20210715&ie=utf8 "直达链接")
- [J-Link下载器](https://s.taobao.com/search?q=J-Link%E4%B8%8B%E8%BD%BD%E5%99%A8&imgfile=&js=1&stats_click=search_radio_all%3A1&initiative_id=staobaoz_20210715&ie=utf8 "直达链接")

# 蓝牙模块
## 硬件信息
- [ZS-040](https://s.taobao.com/search?q=ZS-040&imgfile=&js=1&stats_click=search_radio_all%3A1&initiative_id=staobaoz_20210715&ie=utf8 "直达链接")
## 使用说明
### 连接软件
- 蓝牙串口小程序

### 蓝牙AT指令
- AT  基本信息
- AT+NAME 名称
- AT+VERSION  版本

### 蓝牙接收端输入指令
- CloseLed+num	
- OpenLed+num	
- LedFast
- LedLow
- LedShan+num	
- LedNotShan+num	
# 超声波模块
## 硬件信息
- [HC-SR04](https://s.taobao.com/search?q=HC-SR04&imgfile=&js=1&stats_click=search_radio_all%3A1&initiative_id=staobaoz_20210715&ie=utf8 "直达链接")
## 使用说明
- key1  打开
- key2  关闭
- key3 调节等级（3级可调led2~4）
# 温湿度模块
## 硬件信息
- [DH T 1 1&DS18 B20](https://s.taobao.com/search?q=DH+T+1+1%26DS18+B20&imgfile=&js=1&stats_click=search_radio_all%3A1&initiative_id=staobaoz_20210715&ie=utf8 "直达链接")
# OLED模块
## 硬件信息
- 硬件型号：0.7寸OLED显示屏
- 分辨率：128*64
- 通信协议：IIC
## 软件信息
- 部分驱动代码移植于正点原子

# 指纹模块
## 硬件信息
- [AS608](https://s.taobao.com/search?q=as608&imgfile=&commend=all&ssid=s5-e&search_type=item&sourceId=tb.index&spm=&ie=utf8&initiative_id=tbindexz_20170306 "直达链接")
