/*
 * Used for collecting training data - particularly for collecting
 * test images of the rover and its goals so they can be located in
 * the scene. 
*/

#include<sstream>
#include<iostream>
#include<opencv2/opencv.hpp>
#include<string>

using namespace cv;

static const std::string OPENCV_WINDOW = "Image";

class RoverImageCapture {
private:
    VideoCapture cap;
    int counter;
    Mat image;
    
public:
    RoverImageCapture(int start_counter) {
        this->counter = start_counter;
        
        if (!this->cap.open(0)) {
            throw "Error: Unable to access camera.";
        }
        
        this->cap >> this->image;
    }
    
    void updateImage() {
        this->cap >> this->image;
    }
    
    void captureAndSaveImage() {
        this->cap >> this->image;
        
        std::string counter_string;
        std::stringstream out;
        out << this->counter;
        counter_string = out.str();
        
        std::string filename = "images/img_" + counter_string + ".jpg";
        imwrite(filename, this->image);
        
        this->counter++;
    }
    
    Mat getImage() {
        return this->image;
    }
    
    void setCounter(int counter) {
        this->counter = counter;
    }
    
};


RoverImageCapture g_rover_image_capture(0);

void onMouse(int event, int x, int y, int, void*) {
    if( event != EVENT_LBUTTONDOWN )
        return;

    std::cout << "Saving image." << std::endl;

    g_rover_image_capture.captureAndSaveImage();
}

int main(int argc, char** argv) {
    
    if (argc > 1) {
        std::string counter_string(argv[0]);
        std::stringstream out(counter_string);
        
        int counter = 0;
        out >> counter;
        
        g_rover_image_capture.setCounter(counter);
    }
    
    namedWindow(OPENCV_WINDOW);
    
    setMouseCallback( OPENCV_WINDOW, onMouse, 0 );
    
    for (;;) {
        g_rover_image_capture.updateImage();
        imshow("image", g_rover_image_capture.getImage());
        waitKey(1);
    }
    
    return 0;
    
}