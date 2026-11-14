# Robot
**Complete dog-like robot** built on clean **ATmega328P**.

**Project includes:**
- code wrote with **arduino framework** in **ArduinoIDE**
- projects pcb in **KiCad**

## Video
https://youtube.com/shorts/nso789CsX9U

## Used components
`| Microcontroler | ATmega328P`

`| 4 servos | sg90 180*`

`| OLED display | OLED SSD1106`

`| Pull-up resistors | 10kΩ`

`| Capacitors | 100nF | 100uF`

`| Coil | 10uF |`

`| ISP programmer | 6-pin (2x3) `

`| Power supply | Screw terminal | 8.5V` 

`| Stabilizer | AMS1117 5V`

`| Button | TTP223`

`| Buzzer controlled by transistor |`

`| Voltage divider | 10k and 1,5k`


## Software requirements

- **ArduinoIDE**
- **ISP Programmer**
- **KiCad 10.0** – if you want to check/add something

# Software

## Install and boot

### Step 1: clone repo
```bash


git clone https://github.com/darlingramus/Robocik.git
cd Robocik
```
### Step 2: 
- Open ArduinoIDE
- Install libraries
- Open folder Robocik and click on .ino file

- install Avrdudess and remember to set fuse bits
   
### Step 3:
- Click compile and find .hex file created by arduino

### Step 4: Connect ISP programmer
  
### Step 5: Upload code
- Click "program" in Avrdudess and wait till its done

# Hardware - KiCad
PCB designed in KiCad 10.0

## Schematic

<img width="1140" height="783" alt="image" src="https://github.com/user-attachments/assets/d95dd363-1f5c-44d6-a44a-ae0777a0bde0" />

## Front PCB

<img width="1536" height="2048" alt="c45ad85c-8333-4e9d-967d-a3e53d081956 (1)" src="https://github.com/user-attachments/assets/67d69a16-2b87-4e74-a672-20e2c2f57fa2" />


## Back PCB

<img width="1536" height="2048" alt="7141d11f-a660-4029-a978-41caf6e4aabc (1)" src="https://github.com/user-attachments/assets/7efbff41-8dd4-4c7e-ae20-fe873e76175b" />


## How to open in KiCad
Install KiCad
Open hardware/kicad/ProjektNaElektronike.kicad_pro
