//
//  main.cpp
//  DuplicateFileFinder
//
//  Copyright © 2018 SIDDHARTH. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include "stb_image.h"
#include <stdio.h>
#include <cstdio>
#include <dirent.h>
#include <string>
#include <vector>


std::vector< std::string > fileList;
std::vector < std::string > deleteFiles;
std::vector < std::string > tempData;

/*char* loadImage( std::vector < std:: string > fileList, int x, int y, int n, unsigned char* data )
{
    if( fileList.size() )
    {
        std::cout << fileList.size() << " image files" << std::endl;
        for( unsigned int i = 0; i < fileList.size(); ++i )
        {
            unsigned char* data = stbi_load(fileList[i].c_str(), &x, &y, &n, 0 );
        }
    }
    return (char*) data;
}*/

void searchFolder( std::string curr_folder, std::string extension )
{
    DIR* dir_point = opendir( curr_folder.c_str() );
    dirent* entry = readdir( dir_point );
    while( entry )
    {
        if( entry->d_type == DT_DIR )
        {
            std::string filename = entry->d_name;
            if (filename != "." && filename != "..")
                searchFolder(entry->d_name, extension);
        }
        else if( entry->d_type == DT_REG )
        {
            std::string filename = entry->d_name;
            if( filename.find( extension, ( filename.length() - extension.length() ) ) != std::string::npos )
            {
                fileList.push_back(filename);
            }
        }
        entry = readdir(dir_point);
    }
    return;
}

int main(int argc, char* argv[])
{
    std::string extension = ".png";
    std::string curr_directory = "../resource";
    searchFolder(curr_directory, extension);
    int remove( const char* fileName );
    
    if( fileList.size() )
    {
        std::cout << fileList.size() << " image files" << std::endl;
        for( unsigned int i = 0; i < fileList.size(); ++i )
        {
            int x, y, n, alpha;
            alpha = 0;
            unsigned char* data = stbi_load(fileList[i].c_str(), &x, &y, &n, alpha );
            if( data != NULL )
            {
                std::cout << data << std::endl;
            }
            
            int tempx = x;
            int tempy = y;
            int tempn = n;
            int tempalpha = alpha;
            
            std::cout << "data = " << fileList[i] << std::endl;
            if( !data )
            {
                std::cout << "Cound't load image\n" << std::endl;
                return -1;
            }
            for( unsigned int j = i+1; j < fileList.size(); ++j )
            {
                int x1, y1, n1, alpha1;
                alpha1 =0;
                unsigned char* data1 = stbi_load(fileList[j].c_str(), &x1, &y1, &n1, alpha1 );
                int tempx1 = x1;
                int tempy1 = y1;
                int tempn1 = n1;
                int tempalpha1 = alpha1;
                
                std::cout << "data1 = " << fileList[j] << std::endl;
                
                if( (tempx == tempx1) && (tempy == tempy1) && (tempn == tempn1) && (tempalpha == tempalpha1) )
                {
                    std::cout << "same file" << std::endl;
                    deleteFiles.push_back( fileList[j].c_str());
                }
                else
                {
                    std::cout << "different file" << std::endl;
                }
                stbi_image_free( data1 );
            }
            stbi_image_free( data );
        }
    }
    else
    {
        std::cout << "No files ending in '" << extension << "' were found." << std::endl;
    }
    for( unsigned n = 0; n < deleteFiles.size(); ++n )
    {
        remove( deleteFiles[n].c_str());
    }
    return 0;
}

