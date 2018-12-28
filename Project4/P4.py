import pandas as pd 
import numpy as np 
import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import cv2

from sklearn.model_selection import train_test_split
from sklearn.utils import shuffle

from keras.models import Sequential, Model
from keras.layers import Lambda, Cropping2D, Convolution2D, Flatten, Dense, Dropout, Activation
from keras.layers.pooling import MaxPooling2D

from P4_helper import *

# Load dataset
base_path = r"/Users/dhtran/Documents/Code/Udacity/Self-Driving-Car-Nanodegree/P4-Behavioral-Cloning/data1/"
dataset_orig = pd.read_csv(base_path + r"driving_log.csv")
dataset = dataset_orig.iloc[:,:4].values

# Split dataset to training and validation sets
train_dataset, valid_dataset = train_test_split(dataset, test_size=0.2, shuffle=True)

train_generator = generator(base_path, train_dataset, batch_size=32)
valid_generator = generator(base_path, valid_dataset, batch_size=32)

# ================================== NVDIA Model ==================================
model = Sequential()
model.add(Lambda(lambda x: (x/255.0)-0.5, input_shape=(160,320,3)))       # Normalization and mean centered
model.add(Cropping2D(cropping=((65,20),(0,0))))    # crops 65 rows pixels from top and 20 rows pixels from bottom

model.add(Convolution2D(filters=24, kernel_size=(5,5), strides=(2,2), activation='relu'))
model.add(MaxPooling2D(pool_size=(1, 1)))
model.add(Dropout(rate=0.2))

model.add(Convolution2D(filters=36, kernel_size=(5, 5), strides=(2, 2), activation='relu'))
model.add(MaxPooling2D(pool_size=(1, 1)))
model.add(Dropout(rate=0.2))

model.add(Convolution2D(filters=48, kernel_size=(5,5), strides=(2,2), activation='relu'))
model.add(MaxPooling2D(pool_size=(1, 1)))
model.add(Dropout(rate=0.2))

model.add(Convolution2D(filters=64, kernel_size=(3,3), activation='relu'))
model.add(MaxPooling2D(pool_size=(1, 1)))
model.add(Dropout(rate=0.2))

model.add(Convolution2D(filters=64, kernel_size=(3, 3), activation='relu'))
model.add(MaxPooling2D(pool_size=(1, 1)))
model.add(Dropout(rate=0.2))

model.add(Flatten())
model.add(Dropout(rate=0.2))

model.add(Dense(100))
model.add(Activation('relu'))
model.add(Dropout(rate=0.2))

model.add(Dense(50))
model.add(Activation('relu'))
model.add(Dropout(rate=0.2))

model.add(Dense(10))
model.add(Activation('relu'))
model.add(Dropout(rate=0.2))

model.add(Dense(1))
# ================================================================================

model.compile(optimizer='adam', loss='mean_squared_error', metrics=['accuracy'])
# Use fit_generator() in order to use generator for input data
history_obj = model.fit_generator(train_generator, steps_per_epoch=len(train_dataset), 
                                validation_data=valid_generator, validation_steps=len(valid_dataset), epochs=3, verbose=1)

# Visualizing Losses
plt.plot(history_obj.history['loss'])
plt.plot(history_obj.history['val_loss'])
plt.title('MSE Losses')
plt.xlabel('Epoch')
plt.ylabel('MSE Loss')
plt.legend(['Training Loss', 'Validation Loss'])
plt.show()

# Save model
model.save('P4_model.h5')

'''
del model

from keras.models import load_model
# Reload model
model = load_model('P4_model.h5')

# Continue training
model.fit(...)
'''