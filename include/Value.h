#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
class Value{
private:
    std::string valueName;
    HKEY parrentKey;
public:

    Value(HKEY hkey, const std::string& valueName) : parrentKey(hkey), valueName(valueName){}
    std::string name() const;
    bool is_dword() const;
    void delete_value(const std::string& key, const std::string& valueName);
    DWORD get_dword() const;
    void set_dword(DWORD value);
    operator DWORD() const{
        return get_dword();
    }
    void set_binary(const std::vector<BYTE>& value);
    std::string get_string() const ;
    void set_string(const std::string& value) ;
    operator std::string() const {
        return get_string();
    }
    Value& operator=(const std::string& value) {
        set_string(value);
        return *this;
    }
    bool is_binary() const;
    std::vector<BYTE> get_binary() const;
    Value& operator=(DWORD value){
        set_dword(value);
        return *this;
    }
    operator std::vector<BYTE>() const {
        return get_binary();
    }
    Value& operator=(const std::vector<BYTE>& value) {
        set_binary(value);
        return *this;
    }
};

