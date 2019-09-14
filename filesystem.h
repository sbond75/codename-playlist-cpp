// https://stackoverflow.com/questions/11140483/how-to-get-list-of-files-with-a-specific-extension-in-a-given-folder

#include <string>
#include <vector>

#include <filesystem>
namespace fs = ::std::filesystem;

// return the filenames of all files that have the specified extension
// in the specified directory and all subdirectories
void get_all(const fs::path& root, const std::string& ext, 
    std::vector<fs::path>&
ret)
{
  if(!fs::exists(root) || !fs::is_directory(root)) return;

  fs::recursive_directory_iterator it(root);
  fs::recursive_directory_iterator endit;

  while(it != endit)
  {
    if(fs::is_regular_file(*it) && it->path().extension() == ext) ret.push_back(it->path());
    ++it;

  }

}
