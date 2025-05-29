from fastapi.testclient import TestClient
from backend.app import app
from config import ROOM_ID

client = TestClient(app)

def test_filter_api():
    payload = {
        "image_data": [0, 0, 0, 255],  # RGBA
        "filter_name": "invert",
        "width": 1,
        "height": 1
    }
    res = client.post(f"/filter/{ROOM_ID}", json=payload)
    assert res.status_code == 200
    assert res.json()["image_data"] == [255, 255, 255, 255]
