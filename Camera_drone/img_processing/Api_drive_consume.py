from __future__ import print_function
import pickle
import os.path
import io
import shutil
import requests
from mimetypes import MimeTypes
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from googleapiclient.http import MediaIoBaseDownload;

class Drive:
    global SCOPES

    SCOPES = ["https://www.googleapis.com/auth/drive"]
    
    def __init__(self):
        self.creds = None

        if os.path.exists("/home/laser/Desktop/Mambo-Turtle-Warehouse/Mambo/src/camera_drone/img_processing/token.pickle"):
            with open("/home/laser/Desktop/Mambo-Turtle-Warehouse/Mambo/src/camera_drone/img_processing/token.pickle", "rb") as token:
                self.creds = pickle.load(token)
        
        if not self.creds or not self.creds.valid:
            if self.creds and self.creds.expired and self.creds.refresh_token:
                self.creds.refresh(Request())
            else:
                flow = InstalledAppFlow.from_client_secrets_file("Mambo/src/camera_drone/img_processing/credentials.json", SCOPES)
                self.creds = flow.run_local_server(port=0)
            with open("/home/laser/Desktop/Mambo-Turtle-Warehouse/Mambo/src/camera_drone/img_processing/token.pickle", "wb") as token:
                pickle.dump(self.creds, token)
        
        self.service = build("drive", "v3", credentials=self.creds)
        self.results = self.service.files().list(q="mimeType = 'image/jpeg'",fields="files(id, name)").execute()

    def fileDownload(self, nameFile):
        idFile = ""
        
        for file in self.results.get("files"):
            if(file["name"] == nameFile):
                idFile = file["id"]
                break
        
        if(idFile == ""):
            return 111

        request = self.service.files().get_media(fileId=idFile)
        fh = io.BytesIO()

        downloader = MediaIoBaseDownload(fh, request, chunksize=204800)
        done = False

        try:
            while not done:
                    status, done = downloader.next_chunk()
                    fh.seek(0)
                    
                    with open("/home/laser/Desktop/Mambo-Turtle-Warehouse/Mambo/src/camera_drone/Imgs_tests/" + nameFile, "wb") as f:
                        shutil.copyfileobj(fh, f)
            
            return True
        except:
            return False