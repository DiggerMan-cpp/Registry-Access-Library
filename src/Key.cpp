#include <Key.h>
    
    
   
 int Key::keys_count(){
        DWORD numSubKeys = 0;
        if(RegQueryInfoKeyA(handle, nullptr, nullptr, nullptr, &numSubKeys, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr) != ERROR_SUCCESS) {
            std::cerr << "Failed to query info registry key";
        }
        return static_cast<int>(numSubKeys);
    }


    
    HKEY Key::tree() const{
        return handle;
    }


    HKEY Key::native_handle() const{
        return handle;
    }
     bool Key::rename_key(HKEY hkey, const std::string& oldPath, const std::string& newPath){
        if(RegRenameKey(hkey, (LPCWSTR)oldPath.c_str(), (LPCWSTR)newPath.c_str()) != ERROR_SUCCESS){
            std::cerr << "Failed to Rename Key";
            return false;
        }
        return true;
    }

    bool Key::create_key(HKEY hkey, const std::string& keypath){
        HKEY newKey;
        DWORD disposition;
        if(RegCreateKeyExA(hkey, keypath.c_str(), 0, nullptr, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, nullptr, &newKey, &disposition) != ERROR_SUCCESS){
            std::cerr << "Failed to rename registry key" << std::endl;
        }

    return false;
    }


Value Key::value(const std::string& valueName){
        return Value(handle, valueName);
    }
