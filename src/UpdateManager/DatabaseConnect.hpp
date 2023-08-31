/*  The MIT License (MIT)
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
#ifndef DATABASECONNECT_HPP_
#define DATABASECONNECT_HPP_
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <map>
#include <filesystem>

using namespace std;

namespace DB
{
    int ArraySize;
    sqlite3 *db;
    sqlite3_stmt *statement;
    int RESULT_SQL;
    string SQL_COMMAND;
    string* AnswerDB;
    string DefaultDatabesePath = std::filesystem::current_path().generic_string() + "/DB/AppInstaller.db";

    class Database
    {
    public:
        Database(string *DB_Path = nullptr)
        {
            RESULT_SQL = sqlite3_open(DB_Path != nullptr ? DB_Path->c_str() : DefaultDatabesePath.c_str(), &db);

            // if result of open database != SQLITE_OK, that send error
            if (RESULT_SQL != SQLITE_OK)
            {
                throw runtime_error("Failed to connect to database");
            }
        }
        ~Database()
        {
            sqlite3_close(db);
        }
        string GetValueFromDB(string NameTable, string NameApp, string NameColumn);
        string GetVersionFromDB(string NameTable,string Status,string NameColumn,string Architecture);
        string GetApplicationURL(string NameTable,string Status,string NameColumn,string Architecture,string Version);
        map<string, string> GetAllValuesFromDB(string NameTable, string NameColumn);
        map<string, string> GetDevPackFromDB(string NameTable, string NameColumn);
        int InsertValuesToTable(string NameTable, string NameApp, string WindowsCommand, string macOSCommand, string LinuxCommand);
        int RemoveValuesFromTable(string NameTable,string NameApp);
        int AddValues(string Tables[]);
        int RemoveValues(string Tables[]);

    private:
        int GetArraySize(string NameTable, string NameColumn);
        static int callback(void *data, int argc, char **argv, char **azColName)
        {
            int i;
            fprintf(stderr, "%s: ", (const char *)data);

            for (i = 0; i < argc; i++)
            {
                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
            }

            printf("\n");
            return 0;
        }
    };
}

#endif