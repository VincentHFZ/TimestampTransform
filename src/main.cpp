#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

// gflag
#include <gflags/gflags.h>
// glog 
#include <glog/logging.h>
#include <glog/log_severity.h>
#include <glog/raw_logging.h>

DEFINE_uint64(unix_time, 0, "unix时间戳, 秒");
DEFINE_string(bj_time, "null", "北京时间, 格式: 2020-01-01-00-00-00");

// 初始化 glog
void InitGlog(std::string log_name, int32_t log_size) 
{
    std::string log_dir = "/home/eventec/logs/";
    log_dir = log_dir + log_name;
    google::InitGoogleLogging(log_name.c_str());
    google::SetLogDestination(google::GLOG_INFO, log_dir.c_str());
    google::SetStderrLogging(google::GLOG_INFO);
    fLB::FLAGS_colorlogtostderr = true;                 // 设置颜色
    fLB::FLAGS_stop_logging_if_full_disk = true;        // 磁盘满了则停止日志记录
    fLI::FLAGS_max_log_size = log_size;                 // M
    fLI::FLAGS_logbufsecs = 0;                          // 实时输出

    return;
}

// unix 时间戳转换成北京时间，格式：2020-01-01-00-00-00
std::string GetBeijingTime(uint64_t timestamp)
{
    time_t timep = timestamp;
    struct tm *p;
    p = gmtime(&timep);
    // 东八区 北京时间
    p->tm_hour += 8;

    char s[100];
    strftime(s, sizeof(s), "%Y-%m-%d-%H-%M-%S", p);
    return s;
}

// 北京时间转换成 unix 时间戳，格式：2020-01-01-00-00-00
uint64_t GetUnixTime(std::string bj_time)
{
    struct tm tm_;
    int year, month, day, hour, minute, second;
    sscanf(bj_time.c_str(), "%d-%d-%d-%d-%d-%d", &year, &month, &day, &hour, &minute, &second);
    tm_.tm_year = year - 1900;
    tm_.tm_mon = month - 1;
    tm_.tm_mday = day;
    tm_.tm_hour = hour;
    tm_.tm_min = minute;
    tm_.tm_sec = second;
    uint64_t unix_stamp = mktime(&tm_);
    return unix_stamp;
}

std::string PrintUsage(void)
{
    std::string usage("时间戳转换工具\n");
    usage += "Usage: \n";
    usage += "  ./timestamp_transform --unix_time=1577808000\n";
    usage += "  ./timestamp_transform -u=1577808000\n";
    usage += "  ./timestamp_transform --bj_time=2020-01-01-00-00-00\n";
    usage += "  ./timestamp_transfrom -b=2020-01-01-00-00-00";
    return usage;
}

int main(int argc, char **argv)
{
    InitGlog("TimeStampTransform", 10);
    FLAGS_stderrthreshold = google::INFO;
    FLAGS_colorlogtostderr = true;
    google::ParseCommandLineFlags(&argc, &argv, true);

    if(FLAGS_unix_time > 0)
    {
        LOG(INFO) << "北京时间: " << GetBeijingTime(FLAGS_unix_time);
    }
    else if(FLAGS_bj_time != "null")
    {
        LOG(INFO) << "unix时间: " << GetUnixTime(FLAGS_bj_time);
    }
    else
    {
        LOG(ERROR) << "参数错误";
        LOG(WARNING) << "\n" << PrintUsage();
    }
    return 0;
}