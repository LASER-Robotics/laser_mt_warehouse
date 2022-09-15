import cv2
import Api_drive_consume

i = 0

while True:
    drive = Api_drive_consume.Drive()
    status = drive.fileDownload("Bc_" + str(i) + ".jpg")

    if(status == 111):
        continue

    barCodeDetector = cv2.barcode_BarcodeDetector()
    img = cv2.imread("/home/laser/Desktop/Mambo-Turtle-Warehouse/Mambo/src/camera_drone/Imgs_tests/" + "Bc_" + str(i) + ".jpg")

    ok, decodedInfo, decodedType, corners = barCodeDetector.detectAndDecode(img)

    print(ok)
    print(f"Decoded barcode information: {decodedInfo}")
    
    i += 1

