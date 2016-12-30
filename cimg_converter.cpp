// #define cimg_display 0
#include <iostream>
#include <sys/types.h> 
#include <dirent.h> 
#include "CImg.h"
#include <sstream>
#include <string>
#include <regex>

using namespace cimg_library;
class Point {};

int main(int argc, char * argv[]) 
{ 

  std::cout << argv[1] << std::endl;
  if(sizeof(argv[1]) / sizeof(char)  < 5) return 0;

  char * path = argv[1];

  DIR *dir = opendir(path); 
  if(dir) { 
    struct dirent *ent; 
    while((ent = readdir(dir)) != NULL) { 
      try {

        if(ent->d_name[0] == '.') continue;
        std::size_t length;

        std::stringstream filename;
        filename <<  ent->d_name;
        std::string fname = filename.str();

        if ( 
          ! std::regex_match(fname, std::regex(".*\\.png$") ) 
          && ! std::regex_match(fname, std::regex(".*\\.jpeg$") )
        ) continue;

        std::stringstream ss;
        ss << path;
        ss <<  ent->d_name;

        std::string target_file = ss.str();
        const char * c_path_to_target_file = target_file.c_str();

        // Open image
        CImg<unsigned char> image(c_path_to_target_file);
        ss << ".jpg";

        std::string new_file = ss.str();
        // Get extension
        std::size_t border_ext = new_file.find(".png");

        // If isn't end string
        if(border_ext != std::string::npos) {
          new_file = new_file.substr(0, border_ext);
        } else {
          border_ext = new_file.find(".jpeg");
          if(border_ext != std::string::npos) {
            new_file = new_file.substr(0, border_ext);
          } else continue;
        }

        new_file += ".jpg";
        const char * c_path_to_new_file = new_file.c_str();
        image.save_jpeg(c_path_to_new_file, 50);

        std::remove(c_path_to_target_file);

        std::cout << (ent->d_name) << std::endl; 
      } catch(const std::runtime_error& error) {
        std::cout << error.what() << std::endl;
      }
    } 
  } else { 
    std::cout << "Error opening directory" << std::endl; 
  } 
  return 0; 
} 
