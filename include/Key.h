#include <iostream>
#include <string>
#include <windows.h>
#include "Value.h"
class Key
{
private:
    HKEY handle;
    std::string path;
public:
    Key(HKEY hkey, const std::string& keyPath) : handle(nullptr), path(keyPath){
        if(RegOpenKeyExA(hkey, keyPath.c_str(), 0, KEY_ALL_ACCESS, &handle) != ERROR_SUCCESS){
            std::cerr << "Failed to open registry key" << std::endl;
        }
    }
    ~Key(){
        if(handle != nullptr){
            RegCloseKey(handle);
        }
    }
    Key& operator = (const Key& other){
        if(this != &other){
            if(handle != nullptr){
                RegCloseKey(handle);
            }
            if(RegOpenKeyExA(other.handle, other.path.c_str(), 0, KEY_ALL_ACCESS, &handle) != ERROR_SUCCESS){
                std::cerr << "Faled to open Registry Key";
            }
        }
        return *this;
    }
    int keys_count();
    Value value(const std::string& valueName);
    HKEY tree() const;
    HKEY native_handle() const;
    bool rename_key(HKEY hkey, const std::string& oldPath, const std::string& newPath);
    bool create_key(HKEY hkey, const std::string& keypath);
    std::string paths() const{
        return path;
    }


};


