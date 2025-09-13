
# 🌱 Soil Moisture Detector with Machine Learning & Arduino

An **IoT + Machine Learning project** that detects soil conditions (`Dry`, `Optimal`, `Wet`) using environmental sensors and a trained ML model. It automatically controls a **water pump** through a relay to maintain optimal soil moisture.

---

## 📌 Features
- ✅ Uses **ML model (Random Forest)** trained on real environmental data.  
- ✅ Reads **humidity + air temperature** (DHT22).  
- ✅ Reads **soil temperature** (DS18B20 waterproof probe).  
- ✅ Calculates **dew point** from humidity & temperature.  
- ✅ Runs the ML model **directly on Arduino** (TinyML).  
- ✅ Controls **water pump via relay** based on prediction.  
- ✅ Includes **LED + buzzer alerts** when pump is ON.  

---

## 🛠️ Hardware Requirements
- Arduino Uno (or compatible board)  
- DHT22 / DHT11 sensor (air humidity & temperature)  
- DS18B20 sensor (soil temperature)  
- 1-channel Relay module  
- Water pump + external power supply  
- Buzzer + LED (optional for alerts)  
- Jumper wires + breadboard  

---

## ⚡ Circuit Diagram
![Wiring Diagram](img\SoilMoistureConnection.png)

---

## 🧑‍💻 Software Requirements
- [Arduino IDE / Arduino Web Editor](https://create.arduino.cc/editor)  
- Libraries:
  - `DHT.h` (Adafruit DHT sensor library)  
  - `OneWire.h` + `DallasTemperature.h` (for DS18B20)  
- Exported ML model header file (`SoilMoistureModel.h`)  

---

## 🚀 How It Works
1. Sensors collect **humidity, air temp, soil temp**.  
2. Dew point is **calculated** from humidity & air temp.  
3. These 4 features → passed into ML model (`Random Forest`).  
4. Model predicts soil condition:  
   - 🌵 `Dry` → Relay turns pump ON.  
   - 🌿 `Optimal` → Pump stays OFF.  
   - 💧 `Wet` → Pump stays OFF.  
5. Results are shown in **Serial Monitor** and via LED/Buzzer.  

---

## 📊 Machine Learning
- Model: **Random Forest Classifier**  
- Training done in Python (scikit-learn).  
- Exported using **EloquentTinyML** to `SoilMoistureModel.h`.  

---

## 📜 License
This project is licensed under the MIT License.  