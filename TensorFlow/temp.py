### Define your architecture here.
### Feel free to use as many code cells as needed
import numpy as np
EPOCHS = 50
BATCH_SIZE = 64
dropout = 0.80  # Dropout, probability to keep units

x = range(4410)
num_batches = len(x) / BATCH_SIZE
print(num_batches, np.int32(np.ceil(num_batches)))
# for i in range(0, 4410, BATCH_SIZE):
#     print('{} -> {}'.format(x[i], x[min(i+BATCH_SIZE-1, len(x)-i)]))
