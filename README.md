# Airport Parking Vehicle Classifier

## Overview

Offline C++ application for automatic vehicle classification using an ONNX AI model and ONNX Runtime.

The application processes images sequentially, classifies the detected vehicle, generates logs, exports results to CSV, and saves annotated images.

Current implementation is a technical proof-of-concept intended to validate the complete processing pipeline before integration with the client's Oracle database.

---

## Features

* Native C++ executable
* 100% offline operation
* ONNX Runtime integration
* OpenCV image processing
* Sequential image processing
* Vehicle classification
* Confidence score calculation
* Confidence threshold handling
* CSV export
* Logging system
* Annotated output images
* Configuration through JSON file
* Oracle integration architecture prepared

---

## Supported Vehicle Categories

The final output categories are:

* auto
* moto
* camionette
* bus

The current prototype model uses 21 vehicle classes internally and maps them automatically to the client categories.

---

## Project Structure

airport_parking_classifier/

* build/
* config/
* include/
* input_images/
* logs/
* models/
* output/
* src/
* README.md

---

## Configuration

Configuration file:

config/config.json

Example:

{
"model_path": "../models/model.onnx",
"input_folder": "../input_images",
"output_csv": "../output/results.csv",
"output_folder": "../output",
"confidence_threshold": 0.50,
"image_size": 640
}

---

## Execution

From the build folder:

Release\airport_parking_classifier.exe

---

## Outputs

### CSV Results

output/results.csv

Contains:

* image name
* vehicle type
* confidence score
* processing time
* status

### Annotated Images

output/

Example:

* image1_result.jpg
* image2_result.jpg

### Logs

logs/app.log

Contains:

* application start
* processing information
* warnings
* errors

---

## Oracle Integration

The architecture already includes:

* OracleImageReader.hpp
* OracleImageReader.cpp

The final Oracle implementation will:

Oracle LONG RAW image
→ OpenCV Mat
→ ONNX inference
→ CSV export
→ Local database / API integration

Oracle connection details, table structure, and credentials are required before implementation.

---

## AI Model

The current model is used only for technical validation of the pipeline.

The final production model will be retrained or fine-tuned using real airport camera images provided by the client in order to maximize classification accuracy.
