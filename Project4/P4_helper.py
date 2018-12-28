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
def read_steer_angle(batch_sample, side_cameras, counter_clockwise=True):
    correction = 0.1        # parameter to tune!
    center_steer = float(batch_sample[3])
    if side_cameras:
        if counter_clockwise:
            # steer more to LEFT
            left_steer = center_steer + correction
            right_steer = center_steer - correction
        else:
            # steer more to RIGHT
            center_steer = center_steer * (-1)
            left_steer = center_steer - correction
            right_steer = center_steer + correction
        
        return (center_steer, left_steer, right_steer)
    else:
        return center_steer


# Generators (large amounts of data!)
# Pre-process data on the fly without storing in memory -> memory efficient
# Keyword: yield
def generator(base_path, samples, batch_size=32):
    # Flag to decide if using side images and steer angles
    # if not, only use center image and center steer angle
    side_cameras = False

    num_samples = len(samples)
    while 1:        # loop forever so the generator never terminates
        shuffle(samples)
        for offset in range(0, num_samples, batch_size):
            batch_samples = samples[offset:offset+batch_size, :]
            images, angles = [], []
            for batch_sample in batch_samples:
                # Load images for center/left/right
                center_img = read_img(base_path, batch_sample, pos=0)
                if side_cameras:
                    left_img = read_img(base_path, batch_sample, pos=1)
                    right_img = read_img(base_path, batch_sample, pos=2)

                # Load angles for center/left/right
                steer_angles = read_steer_angle(batch_sample, side_cameras, counter_clockwise=True)

                if side_cameras:
                    images.extend([center_img, left_img, right_img])
                    angles.extend([steer_angles[0], steer_angles[1], steer_angles[2]])
                else:
                    images.append(center_img)
                    angles.append(steer_angles)
            print(len(images))
            # trim images to only see section with road ???
            X = np.array(images)
            y = np.array(angles)
            yield shuffle(X, y)
