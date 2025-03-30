#pragma once

#include <iostream>
#include <string>
#include <ctime>

#define INFO    1
#define WARNING 2
#define ERROR   3
#define FATAL   4

#define LOG(level, message) Log(#level, message, __FILE__, __LINE__)//后面两个参数会自动获取

//引用LOG函数时候只需要填充前两个参数
void Log(std::string level, std::string message, std::string file_name, int line)
{
    std::cout << "[" << level << "]" << "[" << time(nullptr) << "]" << "[" << message << "]" << "[" << file_name << "]" << "[" << line << "]" << std::endl;
}
