#ifndef OPENHD_OPENHD_OHD_COMMON_OPENHD_UTIL_FILESYSTEM_H_
#define OPENHD_OPENHD_OHD_COMMON_OPENHD_UTIL_FILESYSTEM_H_

#include <vector>

#include <boost/filesystem.hpp>

// boost::filesystem or std::filesystem, what a pain
// If possible, one should not use boost::filesystem or anything from boost::
// inside the project, but quickly write a wrapper here.
// We want to get rid of boost at some time.
// which should reduce build time and dependency issues on all the platforms.
// However, for std::filesystem we need c++17 AND support from the compiler for std::filesystem
// which is lagging behind immensely.

namespace OHDFilesystemUtil{

/**
 * Quite common during the discovery step, find all directory entries in a directory.
 * @param directory
 * @return the full paths of each entry in the directory.
 */
static std::vector<std::string> getAllEntriesFullPathInDirectory(const char* directory){
  boost::filesystem::path dev(directory);
  std::vector<std::string> ret;
  for (auto &entry: boost::filesystem::directory_iterator(dev)) {
	auto device_file = entry.path().string();
	ret.push_back(device_file);
  }
  return ret;
}

// Same as above, but returns the filenames only.
static std::vector<std::string> getAllEntriesFilenameOnlyInDirectory(const char* directory){
  boost::filesystem::path net(directory);
  std::vector<std::string> ret;
  for (auto &entry: boost::filesystem::directory_iterator(net)) {
	const auto interface_name = entry.path().filename().string();
	ret.push_back(interface_name);
  }
  return ret;
}

// same as boost::filesystem::exists
static bool exists(const char* file){
  return boost::filesystem::exists(file);
}

// These don't create top level directories recursively
static void create_directory(const char* directory){
  boost::filesystem::create_directory(directory);
}
static void create_directory(const std::string& directory){
  create_directory(directory.c_str());
}

// creates top level directories recursively
static void create_directories(const char* directory){
  boost::filesystem::create_directories(directory);
  assert(exists(directory));
}

static void safe_delete_directory(const char* directory){
  if(exists(directory)){
    boost::filesystem::remove_all(directory);
  }
}

}

#endif //OPENHD_OPENHD_OHD_COMMON_OPENHD_UTIL_FILESYSTEM_H_