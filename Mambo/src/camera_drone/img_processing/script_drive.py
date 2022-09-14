import pickle
import os.path
from googleapiclient.discovery import build
from google_auth_oauthlib.flow import InstalledAppFlow
from google.auth.transport.requests import Request

scopes = ["https://www.googleapis.com/auth/drive"]

def getFileList():
    creds = None

    if os.path.exists("token.pickle"):
        with open("token.pickle", "rb") as token:
            creds = pickle.load(token)

    if not creds or not creds.valid:
        if creds and creds.expired and creds.refresh_token:
            creds.refresh(Request())
        else:
            flow = InstalledAppFlow.from_client_secrets_file("Mambo/src/camera_drone/img_processing/credentials.json", scopes)
            creds = flow.run_local_server(port=0)
        with open("token.pickle", "wb") as token:
            pickle.dump(creds, token)

    service = build("drive", "v3", credentials=creds)

    resource = service.files()
    result = resource.list(q="mimeType = 'image/jpeg'",fields="files(id, name)").execute()

    return result

result_dict = getFileList()

file_list = result_dict.get("files")

for file in file_list:
    print(file["name"])