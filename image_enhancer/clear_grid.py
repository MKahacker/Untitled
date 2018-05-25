import cv2
import numpy as np

img = cv2.imread('other.png')


# ret,thresh2 = cv2.threshold(img,127,255,cv2.THRESH_BINARY_INV)
kernel = np.ones((5,5),np.uint8)
# cv2.imshow('opening', opening)
dilate = cv2.morphologyEx(img, cv2.MORPH_DILATE, kernel)
# kernel = np.ones((8,8),np.uint8)
# opening = cv2.morphologyEx(dilate, cv2.MORPH_OPEN, kernel)
kernel = np.ones((5,5),np.uint8)
erosion = cv2.erode(dilate,kernel,iterations = 1)
cv2.imshow('image', erosion)
cv2.waitKey(0)
cv2.destroyAllWindows()
cv2.imwrite('out.png', erosion)
# # image = cv2.imread('other.jpg')
# # w = np.array([255, 255, 255])
# # wIndex = np.where(np.equal(image, w))
# # image[wIndex] = np.array([0, 0, 255])

# # im[im >= 128]= 255
# # im[im < 128] = 0
# # cv2.imwrite('out.jpg', image)

# im = cv2.imread('other.png')
# im[np.where((im == [237,237,237]).all(axis = 2))] = [255,255,255]
# cv2.imwrite('out.jpg', im)
# im[np.where((im == [249,249,249]).all(axis = 2))] = [255,255,255]
# cv2.imwrite('out.jpg', im)
# im[np.where((im == [235,235,235]).all(axis = 2))] = [255,255,255]
# cv2.imwrite('out.jpg', im)
# im[np.where((im == [240,240,240]).all(axis = 2))] = [255,255,255]
# cv2.imwrite('out.jpg', im)
# im[np.where((im == [238,238,238]).all(axis = 2))] = [255,255,255]
# cv2.imwrite('out.jpg', im)
# im[np.where((im == [240,240,240]).all(axis = 2))] = [255,255,255]
# cv2.imwrite('out.jpg', im)
# # print(im)
# # im[im >= 128]= 255
# # im[im < 128] = 0