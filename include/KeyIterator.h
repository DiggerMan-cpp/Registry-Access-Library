#include <iostream>
#include <vector>
#include <windows.h>
class KeyIterator{
private:
    HKEY parrentKey;
    DWORD index;            
    char name[MAX_PATH];                       


public:
    KeyIterator(HKEY key) : parrentKey(key), index(0){

    }

    bool operator!=(const KeyIterator& other) const{
        return index != other.index;
    }

    KeyIterator& operator++(){
        index++;
        return *this;
    }

    HKEY operator*() const{
        HKEY subKey;
        if(RegOpenKeyExA(parrentKey, name, 0, KEY_READ, &subKey) != ERROR_SUCCESS){
            std::cerr << "Failed To Topenm registry key" << std::endl;
        }
        return subKey;
    }

};

