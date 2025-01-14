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
// Importing a Header File
#ifndef MACOS_HPP_
#define MACOS_HPP_
#include <DeepForge-Toolset/Advanced.hpp>

#define OS_NAME "macOS"

namespace macOS
{
    class Installer
    {
    public:
        /**
         * The MainInstaller function checks if an application requires manual installation or if it
         * can be installed automatically, and then installs it accordingly.
         *
         * @param Name The parameter "Name" is a string that represents the name of an application.
         *
         * @return an integer value.
         */
        int MainInstaller(std::string Name);
        // Function for update information from database about packages and development packs
        void UpdateData();
        // Function for install of DevelopmentPack(ready pack for certain programming language
        void InstallDevelopmentPack(std::string n);
        Installer()
        {
            try
            {
                char *UserFolder = getenv("HOME");
                ProjectFolder = std::filesystem::current_path().generic_string();
                DatabasePath = ProjectFolder + "/DB/AppInstaller.db";
                LogPath = ProjectFolder + "/logs/DeepForgeToolset.log";
                DesktopPath = std::string(UserFolder) + "/Desktop";
                OrganizationFolder = std::string(UserFolder) + "/Library/Containers/DeepForge";
                ApplicationFolder = OrganizationFolder + "/DeepForge-Toolset";
                TempFolder = ApplicationFolder + "/Temp";
                UpdateManagerFolder = OrganizationFolder + "/UpdateManager";
                LocaleFolder = ProjectFolder == DesktopPath ? ApplicationFolder + "/locale" : ProjectFolder + "/locale";
                PackagesFolder = OrganizationFolder;
                ArchivesFolder = ProjectFolder + "/Downloads"
                DownloadDatabase();
                UpdateData();
                InstallBrew();
            }
            catch (std::exception &error)
            {
                logger.writeLog("Error", error.what());
                logger.sendError(NAME_PROGRAM, Architecture, __channel__, OS_NAME, "AppInstaller-Constructor", error.what());
                std::cout << error.what() << std::endl;
            }
        }
        ~Installer()
        {
        }

    protected:
        void InstallBrew();
        /*  The `unpackArchive` function takes two parameters: `path_from` and `path_to`.
            It uses the `Unzipper` class to extract the contents of an archive file located at `path_from` and saves them to the directory specified by `path_to`.
            After extracting the contents, the function closes the `Unzipper` object.
        */
        void UnpackArchive(std::string path_from, std::string path_to);
        /* The 'MakeDirectory' function is used to create a directory (folder) in the file system.*/
        void MakeDirectory(std::string dir);

        void DownloadDatabase();

        int Download(std::string url, std::string dir,bool Progress);
    };
    /* The above code is defining two function pointer types: `AppInstaller_funct_t` and
        `map_funct_t`. `AppInstaller_funct_t` is a function pointer type that points to a member
        function of the `AppInstaller` class that takes no arguments and returns an `int`.
        `map_funct_t` is a function pointer type that points to a function that takes no arguments
        and returns `void`. */
    using Installer_funct_t = int (Installer::*)(void);
    using map_funct_t = void (*)(void);

    std::unordered_map<std::string, Installer_funct_t> PackagesFromSource{};
}

#endif