#include <Value.h>
   std::string Value::name() const {
        return valueName;
    }


 bool Value::is_dword() const{
        DWORD valueType;
        DWORD bufferSize = sizeof(DWORD);
        if(RegQueryValueExA(parrentKey, valueName.c_str(), nullptr, &valueType, nullptr, nullptr) != ERROR_SUCCESS){
            std::cerr << "Failed to query registry value" << std::endl;
            return false;
        }
        return (valueType = REG_DWORD);
    }

        void Value::delete_value(const std::string& key, const std::string& valueName) {
        if (RegDeleteValueA(parrentKey, valueName.c_str()) != ERROR_SUCCESS) {
            std::cerr << "Failed to delete registry value" << std::endl;
        }
    }


    DWORD Value::get_dword() const{
        DWORD value;
        DWORD valueType;
        DWORD bufferSize = sizeof(DWORD);
        if(RegQueryValueExA(parrentKey, valueName.c_str(), nullptr, &valueType, reinterpret_cast<LPBYTE>(&value), &bufferSize) != ERROR_SUCCESS){
            std::cerr << "Failed to query registry value" << std::endl; 
        }
        return value;
    }
    void Value::set_dword(DWORD value){
        if(RegSetKeyValueA(parrentKey, valueName.c_str(), 0, REG_DWORD, reinterpret_cast<const BYTE*> (&value), sizeof(DWORD)) != ERROR_SUCCESS){
            std::cerr << "Failed to set registry value" << std::endl;
        }
    }



    void Value::set_binary(const std::vector<BYTE>& value) {
        if (RegSetValueExA(parrentKey, valueName.c_str(), 0, REG_BINARY, reinterpret_cast<const BYTE*>(&value[0]), static_cast<DWORD>(value.size())) != ERROR_SUCCESS) {
            std::cerr << "Failed to set registry value" << std::endl;
        }
    }

   std::string Value::get_string() const {
        std::string value;
        DWORD valueType;
        DWORD bufferSize = 0;

        if (RegQueryValueExA(parrentKey, valueName.c_str(), nullptr, &valueType, nullptr, &bufferSize) == ERROR_SUCCESS) {
            value.resize(bufferSize);

            if (RegQueryValueExA(parrentKey, valueName.c_str(), nullptr, &valueType, reinterpret_cast<LPBYTE>(&value[0]), &bufferSize) != ERROR_SUCCESS) {
                std::cerr << "Failed to query registry value" << std::endl;
            }
            else {
                value.resize(bufferSize - 1);
            }
        }
        else {
            std::cerr << "Failed to query registry value" << std::endl;
        }

        return value;
    }
    void Value::set_string(const std::string& value) {
        if (RegSetValueExA(parrentKey, valueName.c_str(), 0, REG_SZ, reinterpret_cast<const BYTE*>(value.c_str()), (static_cast<DWORD>(value.size())+1)) != ERROR_SUCCESS) {
            std::cerr << "Failed to set registry value" << std::endl;
        }
    }


        bool Value::is_binary() const {
        DWORD valueType;
        DWORD bufferSize = 0;

        if (RegQueryValueExA(parrentKey, valueName.c_str(), nullptr, &valueType, nullptr, &bufferSize) != ERROR_SUCCESS) {
            std::cerr << "Failed to query registry value" << std::endl;
            return false;
        }

        return (valueType == REG_BINARY);
    }

        std::vector<BYTE> Value::get_binary() const {
        std::vector<BYTE> value;
        DWORD valueType;
        DWORD bufferSize = 0;

        if (RegQueryValueExA(parrentKey, valueName.c_str(), nullptr, &valueType, nullptr, &bufferSize) == ERROR_SUCCESS) {
            value.resize(bufferSize);

            if (RegQueryValueExA(parrentKey, valueName.c_str(), nullptr, &valueType, reinterpret_cast<LPBYTE>(&value[0]), &bufferSize) != ERROR_SUCCESS) {
                std::cerr << "Failed to query registry value" << std::endl;
            }
        }
        else {
            std::cerr << "Failed to query registry value" << std::endl;
        }

        return value;
    }




