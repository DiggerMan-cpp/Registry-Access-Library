#include <string>
#include <vector>
#include <windows.h>

class ValueIterator {
private:
    HKEY parentKey;
    DWORD index;
    std::vector<char> valueNameBuffer;

public:
    ValueIterator(HKEY key) : parentKey(key), index(0), valueNameBuffer(16383, 0) {}

    bool next();

    std::string name() const;
};