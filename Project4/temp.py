import matplotlib.pyplot as plt 
import matplotlib.image as mpimg
import pandas as pd 
import numpy as np 

file = r"/Users/dhtran/Documents/Code/Udacity/Self-Driving-Car-Nanodegree/P4-Behavioral-Cloning/data/IMG/center_2016_12_01_13_30_48_287.jpg"
print(file)
img = mpimg.imread(file)
imshape = img.shape
print('Initial...', imshape)
crop_img = img[65:(imshape[0]-20), :, :]
print(crop_img.shape)
plt.imshow(crop_img)
plt.show()

# Load dataset
base_path = r"/Users/dhtran/Documents/Code/Udacity/Self-Driving-Car-Nanodegree/P4-Behavioral-Cloning/data/"
dataset_orig = pd.read_csv(base_path + r"driving_log.csv")
dataset = dataset_orig.iloc[:, :4].values
print(dataset[:,3])