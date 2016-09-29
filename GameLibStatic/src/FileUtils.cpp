#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include "Common.h"
#include "FileUtils.h"
using namespace std;


void iterateFiles(const string& fileFilter, function<bool(const string&)> func)
{
   WIN32_FIND_DATA ffd;
   auto hFind = FindFirstFile(fileFilter.c_str(), &ffd);

   if (INVALID_HANDLE_VALUE == hFind)
   {
      return;
   }

   // List all the files in the directory with some info about them.
   do
   {
      if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
      {
         continue;
      }
      else
      {
          if (!func(ffd.cFileName))
            break;
      }
   }
   while (FindNextFile(hFind, &ffd) != 0);
}


FileIndexChecker::FileIndexChecker(const std::string& fileNameStart)
    : m_fileNameStart(fileNameStart)
{
    if (!m_fileNameStart.empty())
    {
        for (size_t i = m_fileNameStart.size() - 1; i > 0; --i)
        {
            if (m_fileNameStart[i] == '/' || m_fileNameStart[i] == '\\')
            {
                m_fileNameStart = m_fileNameStart.substr(i);
                break;
            }
        }
    }
}

void FileIndexChecker::build()
{
    //string frmt = "%s%03d.png";
    char buf[256];
    sprintf(buf, "%d", m_start0Count > 0 ? m_start0Count + 1 : 0);
    string s("%s%0");
    m_fileFilter = s + buf + "d" + m_fileNameEnd;

//    std::cout << "format = " << m_fileFilter << endl;
}

void FileIndexChecker::add(const std::string& fileName)
{
    if (fileName.size() <= m_fileNameStart.size())
        return;

    auto numStr = fileName.substr(m_fileNameStart.size());
    auto pos = numStr.rfind('.');
    string endStr;
    if (pos != numStr.npos)
    {
        if (m_fileNameEnd.empty())
        {
           endStr = numStr.substr(pos);
        }
        numStr = numStr.substr(0, pos);
    }

    size_t index = 0;
    size_t num0 = 0;
    for (size_t i = 0; i < numStr.size(); ++i)
    {
        if (index == 0 && numStr[i] == '0')
        {
            ++num0;
            continue;
        }
        if (numStr[i] < '0' || numStr[i] > '9')
            return;
        index = 10 * index + size_t(numStr[i] - '0');
    }

    m_firstIndex = min(m_firstIndex, index);
    m_lastIndex  = max(m_lastIndex, index);

    m_start0Count = max(m_start0Count, num0);
    if (m_fileNameEnd.empty())
    {
        m_fileNameEnd = endStr;
    }
}
