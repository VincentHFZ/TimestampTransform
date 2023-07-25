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
DEFINE_uint64(u, 0, "unix时间戳, 秒");
DEFINE_string(bj_time, "null", "北京时间, 格式: 2020-01-01-00-00-00");
DEFINE_string(bj, "null", "北京时间, 格式: 2020-01-01-00-00-00");

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
    usage += "  ./timestamp_transfrom -bj=2020-01-01-00-00-00";
    return usage;
}

int main(int argc, char **argv)
{
    FLAGS_stderrthreshold = google::INFO;
    FLAGS_colorlogtostderr = true;
    google::ParseCommandLineFlags(&argc, &argv, true);

    if(FLAGS_unix_time > 0)
    {
        std::cout << "北京时间: " << GetBeijingTime(FLAGS_unix_time) << std::endl;
    }
    else if(FLAGS_u > 0)
    {
        std::cout << "北京时间: " << GetBeijingTime(FLAGS_u) << std::endl;
    }
    else if(FLAGS_bj_time != "null")
    {
        std::cout << "unix时间: " << GetUnixTime(FLAGS_bj_time) << std::endl;
    }
    else if(FLAGS_bj != "null")
    {
        std::cout << "unix时间: " << GetUnixTime(FLAGS_bj) << std::endl;
    }
    else
    {
        std::cout << "参数错误" << std::endl;
        std::cout << "\n" << PrintUsage() << std::endl;
    }
    return 0;
}