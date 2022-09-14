from __future__ import print_function
import pickle
import os.path
import io
import shutil
from unittest import result
import requests
from mimetypes import MimeTypes
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request
from googleapiclient.http import MediaIoBaseDownload;

class Drive:
    global results, scopes

    scopes = ["https://www.googleapis.com/auth/drive"]
    
    def __init__(self):
        self.creds = None

        if os.path.exists("token.pickle"):
            with open("token.pickle", "rb") as token:
                self.creds = pickle.load(token)
        
        if not self.creds or not self.creds.valid:
            if self.creds and self.creds.expired and self.creds.refresh_token:
                self.creds.refresh(Request())
            else:
                flow = InstalledAppFlow.from_client_secrets_file("Mambo/src/camera_drone/img_processing/credentials.json", scopes)
                self.creds = flow.run_local_server()
                
                with open("token.pickle", "wb") as token:
                        pickle.dump(self.creds, token)
                        self.service = build("drive", "v3", self.creds)
                        results = self.service.files().list(q="mimeType='image/jpeg'",fields="files(id, name)").execute()
                        items = results.get("files")
                        print(*items, "\n", "\n\n")

    #def fileDownload(self):
    #    request = self.service.files().get_media()

obj = Drive()