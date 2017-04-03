
import mcv
import cv2
import matplotlib.pyplot as plt
import numpy as np

# img = cv2.imread("/Users/Steven/tmp/DSC_0336.JPG")
img = cv2.imread("../test/images/H3224.jpg")
print(img.dtype, img.shape)
if img.dtype == np.uint8:
    img = img.astype(np.float32)
    img = img/255.0

img_g = mcv.gas_blur(img, 4)
plt.imshow(img_g)







