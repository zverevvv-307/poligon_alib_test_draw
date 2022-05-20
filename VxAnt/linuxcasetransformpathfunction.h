#pragma once

#include <memory>
#include <map>
#include <filesystem>
#include <mutex>
namespace fs = std::filesystem;


class LinuxCaseTransformPathFunction
{
  static std::map<std::string, fs::path> files;
  static fs::path root;
  static std::recursive_mutex mtx;

public:

  static void set_root(const std::string& path);
  static std::string linux_transform_function(const char* name);

};

