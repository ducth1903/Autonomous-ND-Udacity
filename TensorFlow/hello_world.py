import tensorflow as tf 

# In Tensorflow, all values are encapsulated in a tensor object
hello_constant = tf.constant('Hello World!')            # # 0-dim string tensor
A = tf.constant(1234)                                   # 0-dim int32 tensor
B = tf.constant([123, 456, 789])                        # 1-dim int32 tensor
C = tf.constant([[123, 456, 789], [222,333,444]])       # 2-dim int32 tensor

# TensorFlow's API is built around a computational graph
# It is an environment for running a graph that is in charge of allocating GPU and/or CPU
with tf.Session() as sess:
    output = sess.run(hello_constant)
    print(output)
