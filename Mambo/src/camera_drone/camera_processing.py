import cv2, time, webbrowser

#def getImgBarCode(ipAddress):
#    webbrowser.open(ipAddress)

#ipAddress = input("Ip address of camera:\n")

#while True:
#getImgBarCode(ipAddress)
#imgPath = input("Caminho da imagem do código de barras\n")

barCodeDetector = cv2.barcode_BarcodeDetector()
img = cv2.imread("/home/laser/Desktop/Mambo-Turtle-Warehouse/Mambo/src/camera_drone/Imgs_tests/como-os-codigos-de-barras-funcionam.mp4")

ok, decodedInfo, decodedType, corners = barCodeDetector.detectAndDecode(img)

print(ok)
print(f"Decoded barcode information: {decodedInfo}")

#time.sleep(2)