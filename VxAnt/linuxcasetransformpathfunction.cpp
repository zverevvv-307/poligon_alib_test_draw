#include "linuxcasetransformpathfunction.h"

#include "atools.h"
#include "utils.h"
#include <ostream>


std::map<std::string, fs::path> LinuxCaseTransformPathFunction::files;
fs::path LinuxCaseTransformPathFunction::root;
std::recursive_mutex LinuxCaseTransformPathFunction::mtx;


static std::string change_separators(const std::string &path){
  std::string tmp{path};
  alib::string_replace_all(tmp, "\\","/");
  alib::string_replace_all(tmp, "//","/");
  return tmp;
}


void LinuxCaseTransformPathFunction::set_root(const std::string &path)
{
  alib::tools::ProfilerTimer t(__FUNCTION__);

  std::lock_guard<std::recursive_mutex> guard(mtx);

  root = change_separators(path);
  root.make_preferred();

  std::string ex = alib::to_lower( root.extension() );
  if ( ex == ".ych"
      || ex == ".yce"
      || ex == ".sta"
      || ex == ".ste"
      ) {
    root  = (root.parent_path()/"..").lexically_normal();
  }

  files.clear();
  for (auto const& dir_entry : std::filesystem::recursive_directory_iterator{root}) {
    if( dir_entry.is_regular_file() ){
      std::string key = alib::to_lower( dir_entry.path().filename().u8string() );
      files.emplace( std::make_pair( key, dir_entry.path().lexically_normal() )  );
      std::cout << key <<" -> " << dir_entry << std::endl;
    }
  }

  alib::CaseInsensitiveFilePath::path_transform_function = LinuxCaseTransformPathFunction::linux_transform_function;
}

std::string LinuxCaseTransformPathFunction::linux_transform_function(const char *name)
{
  fs::path path = change_separators(name);
  path.make_preferred();
  if( fs::exists(path) )
    return name;

  std::lock_guard<std::recursive_mutex> guard(mtx);

  std::string key = alib::to_lower( path.filename().u8string() );
  auto f = files.find(key);
  if( f == files.end() ){
    std::clog<<__FUNCTION__<<" No requested file: "<< key <<" -> "<< path.u8string() << std::endl;
    return name;
  }

  std::clog<<__FUNCTION__
            //<<" file: "<< path.u8string() << std::endl
            <<" file: "<< name //<< std::endl
            <<" remapped to: "<< f->second.u8string() << std::endl
      ;

  return f->second.u8string();
}
