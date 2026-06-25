from ultralytics import YOLO

model = YOLO("models/model.onnx", task="detect")

results = model.predict(
    source="input_images",
    imgsz=640,
    conf=0.45,
    device="cpu",
    save=True
)

for r in results:
    print(f"Image: {r.path}")

print("Inference completed successfully.")