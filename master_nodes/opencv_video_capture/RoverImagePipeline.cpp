#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

/*
 * Given: Raw image (from Web Cam)
 *        Segmented image (from tensor flow or some other model)
 * 
 *  Output:
 *      Perspective transformed image with the segented part
 *      highlighted in green, the drivable part in white,
 *      and everything else in black.
*/

class RoverImagePipeline {
public:
    RoverImagePipeline() {}
    
    Mat transform(Mat raw_image, Mat mask) {
        // get the green channel of the mask and raw image
        vector<Mat> bgr_raw(3);
        split(raw_image, bgr_raw);
        
        vector<Mat> bgr_mask(3);
        split(mask, bgr_mask);
        
        // update the green channel of the raw image to max(raw_image, mask)
        // zero out the other channels where the mask is green.
        for (int r = 0; r < bgr_raw[1].rows; r++) {
            for (int c = 0; c < bgr_raw[1].cols; c++) {
                
                int index = bgr_raw[1].cols * r + c;
                
                if (bgr_mask[1].data[index] > 0) {
                    bgr_raw[0].data[index] = 0;
                    bgr_raw[1].data[index] = bgr_mask[1].data[index];
                    bgr_raw[2].data[index] = 0;
                }
                
            }
        }
        
        // merge things back together
        Mat result;
        merge(bgr_raw, result);
        
        
        // perform perspective transform on the result
        
        
        return result;
    }
};


// Test code
int main(int argc, char** argv) {
    Mat raw_image = imread("img_0.jpg", CV_LOAD_IMAGE_COLOR);
    Mat mask_image = imread("img_mask_0.jpg", CV_LOAD_IMAGE_COLOR);
    
    RoverImagePipeline pipeline = RoverImagePipeline();
    Mat result = pipeline.transform(raw_image, mask_image);
    
    imwrite("img_result.jpg", result);
    
    return 0;
}