#from Ponto import Ponto, notInRetangule
import cv2 as cv
import cv2
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image, ImageDraw

mapa_aux = cv.imread("../movimentacaotbt2/map.png", 0)  # Imagem em escala de cinza
# Mapa binario, todo valor maior que 0 vai ser levado a ser 255
ret, mapa_aux = cv.threshold(mapa_aux, 0, 255, cv.THRESH_BINARY_INV)
mapaBinario = mapa_aux  


# #cria a dilatação das bordas
kernel = np.ones((4, 4), np.uint8)
img_dilation = cv2.dilate(mapaBinario, kernel, iterations=5)  #numero de vezes que eh feita a convolucao

imgplot = plt.imshow(img_dilation)

cv.imwrite('../movimentacaotbt2/map-dilatado.png', img_dilation)

