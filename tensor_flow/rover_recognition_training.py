import os
import glob
import sys
import tensorflow as tf

from scipy import misc
import numpy as np
from tensorflow import image

# Simple FCN, to used to determine the location of the Rover in the input image.
# FCN configuration will be as follows:
# Encoder Layer (Seperable Convolution)
# Encoder Layer (Seperable Convolution)
# 3 standard 1x1 convolutional layers
# Decoder Layer (Seperable)
# Decoder Layer (Seperable)
# Output Layer (Standard convolution).

# This Script is used to train the model based on the labeled data for the rover.
# Note: Labeled data is not provided in git as it contains many pictures of the interior
# of my house in which the Rover lives.  I'll provide guidance on how to construct labeled
# data for ones own Rover eventually.





