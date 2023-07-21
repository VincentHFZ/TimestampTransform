# TimestampTransform 时间戳转换工具

## Compile & Install 编译和安装
```
cmake ..
make -j2
sudo make install
```

## Usage 使用方法

### 将 Unix 时间戳转换为北京时间
```
./TimeStampTransform --unix_time=1577808000
# 或者
./TimeStampTransform -u=1577808000
```

### 将 北京时间转换为 Unix 时间戳
```
./TimeStampTransform --bj_time=2020-01-01-00-00-00
# 或者
./TimeStampTransform -bj=2020-01-01-00-00-00
```
