#include "ValueIterator.h"

 bool ValueIterator::next() {
        DWORD bufferSize = static_cast<DWORD>(valueNameBuffer.size());
        LONG result = RegEnumValueA(parentKey, index, valueNameBuffer.data(), &bufferSize, NULL, NULL, NULL, NULL);
        if (result == ERROR_SUCCESS) {
            index++;
            return true;
        } else {
            return false;
        }
}

std::string ValueIterator::name() const {
        return std::string(valueNameBuffer.data());
}