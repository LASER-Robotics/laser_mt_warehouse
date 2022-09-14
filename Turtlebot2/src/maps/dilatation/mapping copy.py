import cv2 as cv
import cv2
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image, ImageDraw

grayImage = cv.imread('/home/pedrolucas/pibiclaser/maps/dilatation/maze.png', 0) ## Open image and transformation to gray scale
ret, auxMap = cv.threshold(grayImage, 0, 255, cv.THRESH_BINARY_INV) ## binary
binaryMap = auxMap; 
