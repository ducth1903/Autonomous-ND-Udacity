from sklearn.utils import shuffle
import matplotlib.image as mpimg
import numpy as np


# Helper function to read center/left/right images based on input argument 'pos'
# pos={0,1,2} -> {center, left, right}
def read_img(base_path, batch_sample, pos):
    name = base_path + r"IMG/" + batch_sample[pos].split('/')[-1]
    img = mpimg.imread(name)
    return img


# Helper function to read steering angles for center/left/right
# Arguments:
# batch_sample: current row
# counter_clockwise: car moves in counter clockwise or clockwise
# if counter clockwise -> steer more to the left
# if clockwise -> steer more to the right
def read_steer_angle(batch_sample, counter_clockwise=True):
    correction = 0.2        # parameter to tune!
    center_steer = float(batch_sample[3])
    if counter_clockwise:
        # steer more to LEFT
        left_steer = center_steer + correction
        right_steer = center_steer - correction
    else:
        # steer more to RIGHT
        center_steer = center_steer * (-1)
        left_steer = center_steer - correction
        right_steer = center_steer + correction

    return center_steer, left_steer, right_steer


# Generators (large amounts of data!)
# Pre-process data on the fly without storing in memory -> memory efficient
# Keyword: yield
def generator(base_path, samples, batch_size=32):
    num_samples = len(samples)
    while 1:        # loop forever so the generator never terminates
        shuffle(samples)
        for offset in range(0, num_samples, batch_size):
            batch_samples = samples[offset:offset+batch_size, :]
            images, angles = [], []
            for batch_sample in batch_samples:
                # Load images for center/left/right
                center_img = read_img(base_path, batch_sample, pos=0)
                left_img = read_img(base_path, batch_sample, pos=1)
                right_img = read_img(base_path, batch_sample, pos=2)

                # Load angles for center/left/right
                center_steer, left_steer, right_steer = read_steer_angle(
                    batch_sample, counter_clockwise=True)

                images.extend([center_img, left_img, right_img])
                angles.extend([center_steer, left_steer, right_steer])

            # trim images to only see section with road ???
            X = np.array(images)
            y = np.array(angles)
            yield shuffle(X, y)
