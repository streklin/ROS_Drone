/*
 * Grabs all the images (and their respective masks) and creates "flipped"
 * versions of them all - effectively doubling the size of the training set.
 * For bookkeeping purposes flipped images will have the "_flipped" postfix.
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

void flipAndSaveImage(string filename) {
    Mat image;
    Mat flipped;
    
    image = imread(filename, CV_LOAD_IMAGE_COLOR);
    flip(image, flipped, 1);
    
    string needle = "img_";
    filename.replace(filename.find(needle), needle.length(),"img_flipped_");
    
    imwrite(filename, flipped);
}

void flipImagesInDir(string dir) {
    vector<string> files = vector<string>();
    
    getdir(dir, files);
    
    for (unsigned int i = 0;i < files.size();i++) {
        if (files[i] == "." || files[i] == "..") {
            continue;
        }
        
        cout << files[i] << endl;
        string filename = dir + files[i];    
        flipAndSaveImage(filename);
    }
}

int main(int argc, char** argv) {
    flipImagesInDir("images/");
    flipImagesInDir("masks/");
    return 0;
}