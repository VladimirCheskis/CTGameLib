#pragma once

void iterateFiles(const std::string& fileFilter, function<bool(const std::string&)> func);

class FileIndexChecker
{
public:
    FileIndexChecker(const std::string& fileNameStart);
    void add(const std::string& fileName);

    void build();
    const std::string& fileFilter() const {return m_fileFilter;}
    size_t fileFirstIndex() const  {return m_firstIndex;}
    size_t fileCount() const  {return m_lastIndex + 1 - m_firstIndex;}
private:
    std::string m_fileNameStart;
    std::string m_fileNameEnd;
    size_t m_start0Count = 0;
    size_t m_firstIndex = 0;
    size_t m_lastIndex = 0;

    std::string m_fileFilter;
};
