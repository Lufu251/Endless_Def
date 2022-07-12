#pragma once
#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include <filesystem>
#include <string>

class PathSearcher
{

private:
    // data
public:
    PathSearcher(){}
    ~PathSearcher(){}

    // returns the directory of the executable
    std::string getExecutableDirPath() {
        TCHAR dest[MAX_PATH];
        GetModuleFileName(NULL, dest, MAX_PATH); // returns executable path
        PathRemoveFileSpec(dest); // removes executable name from path
        return dest;
    }
    
    // returns the folder path if it was found
    // dir = folder name you want to search
    // searchDepth = the amount of layer to search going down from executable path
    std::filesystem::path getDirPath(std::string dir, int searchDepth) {
        std::filesystem::path curSP = getExecutableDirPath(); // get executable directory
    
        for(int i=0; i< searchDepth; i++) {


            if(!std::filesystem::exists(curSP / dir)){
                // path doesn't exist
                curSP = curSP.parent_path(); // go down one layer
            }
            else{
                // path exists return the current path
                return curSP / dir;
            }
        }
        return curSP;
    }
};