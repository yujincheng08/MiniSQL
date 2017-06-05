#ifndef FILE_H
#define FILE_H

#include <QString>
#include <fstream>
#include <type_traits>
class File
{
public:
    template<bool T, class K = void>
    using enable_if = typename std::enable_if<T,K>::type;
    template<typename T>
    using valid = enable_if<!std::is_class<T>::value && !std::is_pointer<T>::value, T>;
private:
    QString FileName;
    size_t BlockCount;
    std::fstream Stream;
public:
    File(const QString &fileName);
};

#endif // FILE_H
