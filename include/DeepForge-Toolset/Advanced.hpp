/*  GNU GENERAL PUBLIC LICENSE
    ============================================================================

    ██████╗ ███████╗███████╗██████╗ ███████╗ ██████╗ ██████╗  ██████╗ ███████╗
    ██╔══██╗██╔════╝██╔════╝██╔══██╗██╔════╝██╔═══██╗██╔══██╗██╔════╝ ██╔════╝
    ██║  ██║█████╗  █████╗  ██████╔╝█████╗  ██║   ██║██████╔╝██║  ███╗█████╗
    ██║  ██║██╔══╝  ██╔══╝  ██╔═══╝ ██╔══╝  ██║   ██║██╔══██╗██║   ██║██╔══╝
    ██████╔╝███████╗███████╗██║     ██║     ╚██████╔╝██║  ██║╚██████╔╝███████╗
    ╚═════╝ ╚══════╝╚══════╝╚═╝     ╚═╝      ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚══════╝

    ████████╗ ██████╗  ██████╗ ██╗     ███████╗███████╗████████╗
    ╚══██╔══╝██╔═══██╗██╔═══██╗██║     ██╔════╝██╔════╝╚══██╔══╝
       ██║   ██║   ██║██║   ██║██║     ███████╗█████╗     ██║
       ██║   ██║   ██║██║   ██║██║     ╚════██║██╔══╝     ██║
       ██║   ╚██████╔╝╚██████╔╝███████╗███████║███████╗   ██║
       ╚═╝    ╚═════╝  ╚═════╝ ╚══════╝╚══════╝╚══════╝   ╚═╝

    ============================================================================
    Copyright (c) 2023 DeepForge Technology
    ============================================================================
    Organization: DeepForge Technology
    ============================================================================
    Author: Blackflame576
    ============================================================================
    Created: 4 Juny 2023
    ============================================================================
*/
// Importing Libraries
#ifndef ADVANCED_HPP_
#define ADVANCED_HPP_

#include <iostream>
#include <cstdio>
#include <cstring>
#include <unordered_map>
#include <filesystem>
#include <sys/types.h>
#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
#include <curl/curl.h>
#include <Progressbar/Progressbar.hpp>
#include <cctype>
#include <fstream>
#include <functional>
#include <json/json.h>
#include <time.h>
#include <cstdint>
#include <chrono>
#include <vector>
#include <Database/DatabaseAPI.hpp>
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <Logger/Logger.hpp>
#include <miniz/miniz.h>
#include <sstream>
#include <algorithm>

// Checking the name of the operating system and importing the necessary libraries for this system
#if defined(__linux__)
#include <unistd.h>
#include <regex>

#elif __APPLE__
#include <unistd.h>

#elif _WIN32
#include <conio.h>
#include <Windows.h>
#include <tchar.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include "shlobj.h"
#endif

#define NAME_PROGRAM "DeepForge-Toolset"
#define __version__ 0.1
#define __channel__ "stable\\latest"
#define APPINSTALLER_DB_URL "https://github.com/DeepForge-Technology/DeepForge-Toolset/releases/download/InstallerUtils/AppInstaller.db"
#define RELEASE_MODE 1
#define DEBUG_MODE 0
#define MODE RELEASE_MODE

// Statuc codes
#define FAILED_STATUS_CODE 1
#define SUCCESS_STATUS_CODE 0
#define ALREADY_EXISTS_STATUS_CODE 2

#if defined(__linux__)
#define PATHMAN_AMD64_URL "https://github.com/DeepForge-Tech/DeepForge-Toolset-Packages/releases/download/Packages/pathman-v0.5.2-linux-amd64.zip"
#define PATHMAN_ARM64_URL "https://github.com/DeepForge-Tech/DeepForge-Toolset-Packages/releases/download/Packages/pathman-v0.5.2-linux-armv8.zip"
#define OS_NAME "Linux"
#elif __APPLE__
#define PATHMAN_AMD64_URL "https://github.com/DeepForge-Tech/DeepForge-Toolset-Packages/releases/download/Packages/pathman-v0.6.0-darwin-amd64_v2.zip"
#define PATHMAN_ARM64_URL "https://github.com/DeepForge-Tech/DeepForge-Toolset-Packages/releases/download/Packages/pathman-v0.6.0-darwin-arm64.zip"
#define OS_NAME "macOS"
#elif _WIN32
#define PATHMAN_AMD64_URL "https://github.com/DeepForge-Tech/DeepForge-Toolset-Packages/releases/download/Packages/pathman-v0.5.2-windows-amd64.zip"
#define PATHMAN_ARM64_URL "https://github.com/DeepForge-Tech/DeepForge-Toolset-Packages/releases/download/Packages/pathman-v0.5.2-windows-amd64.zip"
#define OS_NAME "Windows"
#endif

typedef std::unordered_map<std::string, std::string> StringHashMap;
typedef std::unordered_map<int, std::string> EnumStringHashMap;
typedef std::unique_ptr<std::string[]> SmartStringArray;

// Variables
// int type
int Percentage;
int TempPercentage;
// int result;
// enum classes
enum class LanguageChoices
{
    RUSSIAN,
    ENGLISH
};
// double type
double LastSize;
double LastTotalSize;
// map type
DB::DatabaseValues Packages;
DB::ArrayDatabaseValues DevelopmentPacks;
DB::ArrayDatabaseValues Languages;

/* The `replaceAll` function is a utility function that replaces all occurrences of a substring `from` with another substring `to` in a given string `str`. */
std::string ReplaceAll(std::string str, const std::string &from, const std::string &to)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}
// string type
const std::string TrueVarious[3] = {"yes", "y", "1"};
std::string ProjectFolder = std::filesystem::current_path().generic_string();
std::string haveString = "";
std::string LangReadySet;
std::string InstallDelimiter = "========================================================";
std::string Language;
// std::string SelectPackages;
std::string Answer;
std::string NumMenu;
// Boolean type
bool Install;
bool withProgress = true;

#if defined(__APPLE__)
std::string Architecture;
#if defined(_M_AMD64)
Architecture = "amd64";
#elif __arm__ || __aarch64__ || _M_ARM64
Architecture = "arm64";
#endif
std::string OrganizationFolder;
std::string DesktopPath;
std::string ApplicationFolder;
std::string TempFolder;
std::string LocaleFolder;
std::string UpdateManagerFolder;
std::string DatabasePath;
std::string LogPath;
std::string PackagesFolder;
std::string ArchivesFolder;

#elif __linux__
#if defined(__x86_64__)
std::string Architecture = "amd64";
#elif __arm__ || __aarch64__ || _M_ARM64
std::string Architecture = "arm64";
#endif
std::string NameDistribution;
std::string PackageManager;
char *UserFolder = getenv("USER");
const std::string DesktopPath = std::string(UserFolder) + "/Desktop";
const std::string OrganizationFolder = "/usr/bin/DeepForge";
const std::string ApplicationFolder = OrganizationFolder + "/DeepForge-Toolset";
const std::string UpdateManagerFolder = OrganizationFolder + "/UpdateManager";
const std::string TempFolder = ApplicationFolder + "/Temp";
const std::string PackagesFolder = "/usr/bin";
const std::string ArchivesFolder = ProjectFolder + "/Downloads";
std::string LocaleFolder = ProjectFolder == DesktopPath ? ApplicationFolder + "/locale" : ProjectFolder + "/locale";
std::string DatabasePath = ProjectFolder == DesktopPath ? ApplicationFolder + "/DB/AppInstaller.db" : ProjectFolder + "/DB/AppInstaller.db";
std::string LogPath = ProjectFolder + "/logs/DeepForge-Toolset.log";

#elif _WIN32
#if defined(_M_AMD64)
std::string Architecture = "amd64";
#elif __arm__ || __aarch64__ || _M_ARM64
std::string Architecture = "arm64";
#endif
char *UserFolder = getenv("USERPROFILE");
const std::string DesktopPath = std::string(UserFolder) + "/Desktop";
const std::string ApplicationFolder = "C:/ProgramData/DeepForge/DeepForge-Toolset";
const std::string TempFolder = ApplicationFolder + "/Temp";
const std::string PackagesFolder = "C:\\";
const std::string ArchivesFolder = ProjectFolder + "/Downloads";
std::string DatabasePath = ReplaceAll(ProjectFolder, "/", "\\") == DesktopPath ? ApplicationFolder + "/DB/AppInstaller.db" : ProjectFolder + "/DB/AppInstaller.db";
std::string LogPath = ReplaceAll(ProjectFolder, "/", "\\") == DesktopPath ? ApplicationFolder + "/logs/DeepForge-Toolset.log" : ProjectFolder + "/logs/DeepForge-Toolset.log";
std::string LocaleFolder = ReplaceAll(ProjectFolder, "/", "\\") == DesktopPath ? ApplicationFolder + "/locale" : ProjectFolder + "/locale";
#endif
// init classes
Logger::Logging logger(LogPath.c_str(), "10kb");
Bar::ProgressBar_v1 progressbar;
Json::Value translate;
DB::Database database;

/**
 * The function `CallbackProgress` is a callback function used to track the progress of a download
 * and update a progress bar accordingly.
 *
 * @param ptr The `ptr` parameter is a pointer to user-defined data that can be passed to the
 * callback function. It allows you to pass additional information or context to the callback
 * function if needed.
 * @param TotalToDownload The total size of the file to be downloaded in bytes.
 * @param NowDownloaded The amount of data that has been downloaded so far.
 * @param TotalToUpload The total size of the data to be uploaded in bytes.
 * @param NowUploaded The parameter "NowUploaded" represents the amount of data that has been
 * uploaded so far. It is a double data type.
 *
 * @return an integer value of 0.
 */
int CallbackProgress(void *ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded)
{
    if (TotalToDownload <= 0.0)
    {
        return 0;
    }
    // double DownloadSpeed;
    Percentage = static_cast<float>(NowDownloaded) / static_cast<float>(TotalToDownload) * 100;
    /* The bellow code is checking if the `TempPercentage` is not equal to `Percentage` and is less
    than or equal to 100. If this condition is true, it retrieves the download speed using
    `curl_easy_getinfo` and updates a progress bar using the `progressbar.Update` function. It
    also updates some variables (`LastDownloadSpeed`, `LastSize`, `LastTotalSize`, and
    `TempPercentage`) with the current values. */
    if (TempPercentage != Percentage && TempPercentage <= 100)
    {
        progressbar.update(NowDownloaded, TotalToDownload);
        LastSize = NowDownloaded;
        LastTotalSize = TotalToDownload;
        TempPercentage = Percentage;
    }
    return 0;
}
/**
 * The function "WriteData" writes data from a pointer to a file stream.
 *
 * @param ptr ptr is a pointer to the data that needs to be written to the file. It points to the
 * starting address of the data.
 * @param size The size parameter specifies the size of each element to be written.
 * @param nmemb The parameter "nmemb" stands for "number of members". It represents the number of
 * elements, each with a size of "size", that you want to write to the file.
 * @param stream The stream parameter is a pointer to a FILE object, which represents the file
 * stream that the data will be written to.
 *
 * @return the number of elements successfully written to the file stream.
 */
size_t WriteData(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    size_t WriteProcess = fwrite(ptr, size, nmemb, stream);
    return WriteProcess;
}

bool endsWith(const std::string &s, const std::string &suffix)
{
    return s.rfind(suffix) == (s.size() - suffix.size());
}

// Function to create a string with two application names
std::string NewString(std::string sentence)
{
    std::string new_sentence = "";
    // If the string is empty, then the first application name is added.
    if (haveString.empty())
    {
        haveString = sentence;
        return new_sentence;
    }
    else
    {
        // Formatting string with two columns
        /* If the string already contains the name of the application,
        then the second name of the application is added and the formatted string is returned */
        new_sentence = fmt::format("{:<40} {:<15}\n", haveString, sentence);
        haveString = "";
        return new_sentence;
    }
}
// Method of make string to lower
std::string to_lower(std::string sentence)
{
    std::string new_sentence = "";
    for (int i = 0; i < sentence.length(); i++)
    {
        char ch = sentence[i];
        // cout << ch << endl;
        ch = tolower(ch);
        new_sentence += ch;
    }
    return new_sentence;
}
// Function for check of answer
bool CheckAnswer(std::string &answer)
{
    bool status = false;
    for (int i = 0; i < TrueVarious->size(); i++)
    {
        answer = to_lower(answer);
        if (answer == TrueVarious[i] || answer.empty())
        {
            status = true;
            break;
        }
    }
    return status;
}

bool CheckStringInFile(const std::string &filename, const std::string &target)
{
    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!file.is_open())
    {
        std::cerr << fmt::format("Failed to open file: {}", filename) << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.find(target) != std::string::npos)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

constexpr std::uint32_t hashString(const char *value, size_t index = 0)
{
    return value[index] == '\0' ? 11 : hashString(value, index + 1) * 99 + static_cast<unsigned char>(value[index]);
}

template <class StringType>
StringType removeChar(StringType &str, char c)
{
    str.erase(std::remove(str.begin(), str.end(), c), str.end());
    return str;
}

template <class StringType>
StringType removeNonDigits(StringType str)
{
    std::string result;
    std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                 [](char c)
                 { return std::isdigit(c); });
    return result;
}

template <class StringType>
StringType removeDigits(StringType str)
{
    std::string result;
    std::copy_if(str.begin(), str.end(), std::back_inserter(result),
                 [](char c)
                 { return !std::isdigit(c); });
    return result;
}

void PrintFormatted(DB::ArrayDatabaseValues &array, int size)
{
    try
    {
        std::string Value_1;
        std::string Value_2;
        for (int i = 0; i < size; i += 2)
        {
            Value_1 = fmt::format("{}. {}", std::to_string(i + 1), array[i]);
            if (i + 1 < size)
            {
                Value_2 = fmt::format("{}. {}", std::to_string(i + 2), array[i + 1]);
                std::cout << fmt::format("{:<20} {:<20}\n", Value_1, Value_2);
            }
            else
            {
                std::cout << fmt::format("{}\n", Value_1);
            }
        }
    }
    catch (std::exception &error)
    {
        throw std::runtime_error(fmt::format("PrintFormatted.{}", error.what()));
    }
}

template <class T>
void PrintFormatted(T &object, int size)
{
    std::string Value_1;
    std::string Value_2;
    for (int i = 0; i < size; i += 2)
    {
        Value_1 = fmt::format("{}. {}", std::to_string(i + 1), object[i + 1]);
        if (i + 1 < size)
        {
            Value_2 = fmt::format("{}. {}", std::to_string(i + 2), object[i + 2]);
            std::cout << fmt::format("{:<40} {}\n", Value_1, Value_2);
        }
        else
        {
            std::cout << fmt::format("{}\n", Value_1);
        }
    }
}

template <class T, class U>
T Enumerate(U object)
{
    T new_object;
    for (int i = 1; const auto &element : object)
    {
        new_object.insert(std::pair<int, std::string>(i, element.first));
        i++;
    }
    return new_object;
}

void InstallIfFound(std::string &selectedPackages, DB::EnumColDatabaseValues &enumeratePackages, std::function<int(std::string)> MainInstaller)
{
    try
    {
        std::string NamePackage;
        std::string delimiter = ",";
        size_t pos = 0;
        std::string token;

        if (!selectedPackages.empty())
        {
            while ((pos = selectedPackages.find(delimiter)) != std::string::npos)
            {
                token = selectedPackages.substr(0, pos);
                std::cout << "hello" << token << std::endl;
                if (enumeratePackages.find(stoi(token)) != enumeratePackages.end())
                {
                    NamePackage = enumeratePackages[stoi(token)];
                    // Install application
                    MainInstaller(NamePackage);
                    selectedPackages.erase(0, pos + delimiter.length());
                }
            }
            if (enumeratePackages.find(stoi(selectedPackages)) != enumeratePackages.end())
            {
                NamePackage = enumeratePackages[stoi(selectedPackages)];
                if (NamePackage != "AllPackages")
                {
                    // Install application
                    MainInstaller(NamePackage);
                }
                else
                {
                    for (const auto &element : enumeratePackages)
                    {
                        if (element.second != "AllPackages")
                            MainInstaller(element.second);
                    }
                }
            }
        }
    }
    catch (std::exception &error)
    {
        throw std::runtime_error(fmt::format("InstallIfFound.{}", error.what()));
    }
}

#endif