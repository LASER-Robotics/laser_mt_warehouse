import cv2, time, webbrowser

def getImgBarCode(ipAddress):
    webbrowser.open(ipAddress)

ipAddress = input("Ip address of camera:\n")

while True:
    getImgBarCode(ipAddress)
    imgPath = input("Caminho da imagem do código de barras\n")

    barCodeDetector = cv2.barcode_BarcodeDetector()
    img = cv2.imread(imgPath)

    ok, decodedInfo, decodedType, corners = barCodeDetector.detectAndDecode(img)

    print(f"Decoded barcode information: {decodedInfo[0]}")

    time.sleep(2)