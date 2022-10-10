import socket
import base64
import io
from PIL.Image import Image
import cv2


def barCodeProcessor(path):
        barCodeDetector = cv2.barcode_BarcodeDetector()
        image = cv2.imread(path) 
        ok, decodedInfo, _, _ = barCodeDetector.detectAndDecode(image)
        
        print(f"Read Status: {ok}")
        if ok:
            print(f"Decoded Information: {decodedInfo}")
        
HOST = "192.168.0.109"  
PORT = 4000

imgNumber = 0
path = "Camera_drone/img_processing/imgs_processeds/Bc_"
imageCodificada = bytes()

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as socket_server:
    socket_server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    socket_server.bind((HOST, PORT))
    socket_server.listen()
    conn, addr = socket_server.accept()
    
    with conn:
        print(f"Connected by {addr}")

        while True:
            data = conn.recv(4096)
            
            if not data:
                imageDecodificada = base64.b64decode(imageCodificada)
                imageDecodificada = Image.open(io.BytesIO(imageDecodificada))
                imageDecodificada.save(path + imgNumber + ".jpg", "JPEG")
                
                path += imgNumber + ".jpg"
                barCodeProcessor(path)
                
                imgNumber += 1
                imageCodificada = bytes()
            else:
                imageCodificada = imageCodificada + data