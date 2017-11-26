/* grabs all the masks I've already created, converts them
 * to greyscale, then scales them down to 160x120 for use in 
 * V2 version of the rover locator network. */
 
/*
 * Compiler Command: 
 * g++ data_converter.cpp -o app `pkg-config --cflags --libs opencv` 
*/

#include<sstream>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>
#include<sys/types.h>
#include<dirent.h>
#include<errno.h>
#include<vector>

using namespace cv;
using namespace std;

/* 
 * Get a vector of filenames in the target directory.
 * This was taken from: https://www.linuxquestions.org/questions/programming-9/c-list-files-in-directory-379323/
*/
int getdir(string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}


void convertAndScaleImage(string filename) {
    Mat image;
    Mat scaled;
    
    image = imread(filename, CV_LOAD_IMAGE_COLOR);
    
    // convert color mask to greyscale mask
    Mat greyscaled;
    cvtColor(image, greyscaled, CV_BGR2GRAY);
    
    // scale the image down to 160x120 pixels
    Size size = Size(160, 120);
    resize(greyscaled, scaled, size);
    
    string needle = "img_";
    filename.replace(filename.find(needle), needle.length(),"img_scaled_");
    
    imwrite(filename, scaled);
}

void convertAndScaleImagesInDir(string dir) {
    vector<string> files = vector<string>();
    
    getdir(dir, files);
    
    for (unsigned int i = 0;i < files.size();i++) {
        if (files[i] == "." || files[i] == "..") {
            continue;
        }
        
        cout << files[i] << endl;
        string filename = dir + files[i];    
        convertAndScaleImage(filename);
    }
}

int main(int argc, char** argv) {
    convertAndScaleImagesInDir("masks/");
    return 0;
}