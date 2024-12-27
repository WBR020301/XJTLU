# HMI Gateway


![](doc/connector.png)

J6-4 for OrinX
J7-4 for J6E

## 以太网固件修改
参考： https://inside-docupedia.bosch.com/confluence/display/wave3/Flash+Methods+for+Switch+Firmware


## 网络配置
ADCC使用了802.1Q虚拟子网，因此，要配置虚拟子网。在树莓派bookwarm中，在 /etc/systemd/network/中，增加如下配置文件：
### Step 1: Install VLAN package
First, you need to install the vlan package that allows VLAN tagging in Linux.
```bash
sudo apt update
sudo apt install vlan
```
In Raspberry Pi Bookworm, the systemd-networkd package isn't a separate package because it is part of the core systemd package. This means you don't need to install systemd-networkd separately—it's already included in the system.

```bash
sudo systemctl enable systemd-networkd
sudo systemctl start systemd-networkd
```

### Step 2: Load 802.1q module
Make sure the 802.1q module, which is responsible for VLAN tagging, is loaded.
```bash
sudo modprobe 8021q
```
To make sure this module loads on boot, add it to /etc/modules.
```bash
echo "8021q" | sudo tee -a /etc/modules
```
### Step 3: Create a VLAN Interface
Use the ip command to create a VLAN interface:
```bash
sudo ip link add link eth0 name vlan62 type vlan id 62
```
Replace eth0 with your primary network interface, vlan62 with your vlan virutal network interface name and 62 with your VLAN ID.
注意： 有的树莓派不能自动创建vlan 网卡，可以用vlan62.server 创建一个自启动服务。

### Step 3: Create a VLAN interface
/etc/systemd/network/下：
* 10-vlan62.network
```console
[Match]
Name=eth0

[Network]
VLAN=vlan62

[Link]
Description=Eth0 with VLAN 62
```

* 20-vlan62.netdev

```console
[NetDev]
Name=vlan62
Kind=vlan

[VLAN]
Id=62
```

* 30-vlan62.network

```console
[Match]
Name=vlan62

[Network]
Address=192.168.62.33/24 # 这里24 是表示subnetmast中1位数
Gateway=192.168.62.1
DNS=8.8.8.8

[Link]
MACAddress=xx:xx:xx:xx:xx:xx
```

关于文件名的命名，没有强制，但是建议用 priority-lanid.xxx，方便文件list显示。
有可能遇到： "potentially unpredictable interface name" issue, let's try a few troubleshooting steps:“

Disable Predictable Network Interface Names
Although your interface is eth0, predictable network interface naming might still be enabled, and it can sometimes cause conflicts. You can disable predictable naming by adding a boot parameter.
```bash
sudo nano /boot/firmware/cmdline.txt
# Add net.ifnames=0 to the end of the line (all parameters in cmdline.txt should be on a single line):
```
### ADCC 板端操作
动态ARP是关掉的，所以你们配置的IP地址和MAC不能随意配。因此需要在master上，使用

```console
SOCK=/sock4 ifconfig vlan62 arp
```




上电都要执行下这个，把动态ARP学习打开。


## 以太网接口

* 泰科接口
* 罗森博格
* 安费诺

# 配置文件信息

| Key    | Value                                  | Comment                                                                      |
|--------|----------------------------------------|------------------------------------------------------------------------------|
| router | String枚举，可取值 zmq, websocket, composite | 启动router的类型 zmq: ZMQ, websocket, composite 复合类型则会启动CompositeRouter，它是组合设计模式。 |
| ttl    | 整数，单位毫秒                                | 表示一个消息的生存时间，如果超出这个时间，则任务消息延迟，将被丢弃                                            |
| device | 字符串，someip消息路出去的网卡名，可以ifconfig获取       | 字段被具体的Router的实现类读取，zmq或websocket类型router依赖此配置                                |
| port   | 整数，someip消息路出去占用的端口号                   | 字段被具体的Router的实现类读取，zmq或websocket类型router依赖此配置                                |
| poolSize | 整数，buffer缓冲池大小                         | ByteBufferPool 使用                                                            |
| bufferSize | 整数，缓冲池中每个bytearray数组缓冲区的大小             | ByteBufferPool 使用                                                            |
| queueSize       | 整数，路由缓冲共享队列缓冲区大小                       | 字段被具体的Router的实现类读取                                                           |
| discoveryMulticastAddress       | 字符串，ip或服务地址                            | 系统有UDP组播用于播报路由信息的IP地址                                                        |
| discoveryMulticastPort       | 整数，端口号                                 | 系统有UDP组播用于播报路由信息的端口                                                          |
|discoveryCycle| 整数，单位毫秒                                | 组播的周期                                                                        |


## 缩减计划

```console
sudo nano /etc/systemd/journald.conf set:
Storage=none
ForwardToConsole=no
```

## FAQ

```bash
ERROR: 
create_event_group_entry: Cannot create subscription as unreliable endpoint is zero: [ab05.0001.0001]
create_event_group_entry: Didn't insert subscription as subscription doesn't match reliablility type: [ab05.0001.0001]

一般可能是TCP/UDP配置不对，也就是 is_reliable等。或者service没有定义.
```
