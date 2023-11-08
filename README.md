# Registry Access Library
[![windows-latest](https://github.com/DiggerMan-cpp/Registry-Access-Library/actions/workflows/cmake-single-platform.yml/badge.svg)](https://github.com/DiggerMan-cpp/Registry-Access-Library/actions/workflows/cmake-single-platform.yml)

Concept Idea: **Receiver**

This library provides a set of classes for accessing and manipulating the Windows Registry.

## Key class

### Description
Represents a handle to a registry key. Provides methods for key operations.

### Members
- **handle**: Private member variable representing the registry key handle (HKEY type)
- **path**: Private member variable representing the registry key path (string)
- **Key()**: Constructor - Initializes the key with the given HKEY and key path
- **~Key()**: Destructor - Closes the registry key handle
- **operator=()**: Assignment operator overload for assigning one key to another
- **keys_count()**: Method to get the count of subkeys
- **value()**: Method to get a specific value from the registry key
- **tree()**: Method to get the handle of the registry key
- **native_handle()**: Method to get the native handle of the registry key
- **rename_key()**: Method to rename a subkey
- **create_key()**: Method to create a new subkey
- **paths()**: Method to get the path of the registry key (getter)

## KeyIterator class

### Description
Represents an iterator for iterating through the subkeys of a registry key.

### Members
- **parrentKey**: Private member variable representing the parent registry key
- **index**: Private member variable representing the current index
- **name[]**: Private member variable representing the name of the subkey
  ### Methods
- **KeyIterator()**: Constructor - Initializes the iterator with the parent key
- **operator!=()**: Inequality operator overload to compare two iterators
- **operator++()**: Prefix increment operator overload to move to the next subkey
- **operator*()**: Dereference operator overload to return the handle of the current subkey

## Value class

### Description
Represents a value within a registry key.

### Members
- **valueName**: Private member variable representing the name of the registry value
- **parrentKey**: Private member variable representing the parent registry key
- Various methods for reading and writing different types of values (DWORD, binary, string)

## ValueIterator class

### Description
Represents an iterator for iterating through the values of a registry key.

### Members
- **parentKey**: Private member variable representing the parent registry key
- **index**: Private member variable representing the current index
- **valueNameBuffer**: Private member variable representing the buffer for value names

### Methods
- **ValueIterator()**: Constructor - Initializes the iterator with the parent key
- **next()**: Method to move to the next value
- **name()**: Method to get the name of the current value (getter)

### SHOWCASE
```cpp
#include <iostream>
#include "RegEditor.h" 

int main() {
    Key registryKey(HKEY_LOCAL_MACHINE, "Software\MyApp");

    int subkeyCount = registryKey.keys_count();
    std::cout << "Total subkeys: " << subkeyCount << std::endl;

    KeyIterator keyIterator(registryKey.tree());
    while (keyIterator != KeyIterator(nullptr)) {
        HKEY subKeyHandle = *keyIterator;
        // ...

        ++keyIterator; // Move to the next subkey
    }

 
    Value configValue = registryKey.value("Config");
    if (configValue.is_dword()) {
        DWORD configData = configValue.get_dword();
        std::cout << "Config value (DWORD): " << configData << std::endl;
    } else if (configValue.is_string()) {
        std::string configData = configValue.get_string();
        std::cout << "Config value (String): " << configData << std::endl;
    }

   
    ValueIterator valueIterator(registryKey.tree());
    while (valueIterator.next()) {
        std::string valueName = valueIterator.name();
        // ...
    }

  
    if (registryKey.create_key(HKEY_LOCAL_MACHINE, "Software\MyApp\NewKey")) {
        std::cout << "New key created successfully" << std::endl;
        if (registryKey.rename_key(HKEY_LOCAL_MACHINE, "Software\MyApp\NewKey", "Software\MyApp\RenamedKey")) {
            std::cout << "Key renamed successfully" << std::endl;
        }
    }

    return 0;
}
```
