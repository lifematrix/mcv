
import mcv
import cv2
import matplotlib as plt

img = cv2.imread("/Users/Steven/tmp/DSC_0336.JPG")
img_g = mcv.gas_blur(img, 4)
plt.imshow(img_g)





