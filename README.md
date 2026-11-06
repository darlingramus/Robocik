# WeatherGirl
**Complete dog-like robot** built on clean **ATmega328P**.

**Project includes:**
- code wrote with **arduino framework** in **ArduinoIDE**
- projects pcb in **KiCad**

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

<img width="560" height="382" alt="image" src="https://github.com/user-attachments/assets/4a23ca75-055c-4cc5-aebb-794d470adc07" />

## Back PCB

<img width="559" height="381" alt="image" src="https://github.com/user-attachments/assets/074c4e8e-3d16-4a63-aee0-e572b2a34240" />


<img width="915" height="544" alt="image" src="https://github.com/user-attachments/assets/f3166503-4372-4b39-8bc8-c83a0b612fbe" />

## How to open in KiCad
Install KiCad
Open hardware/kicad/WeatherGirl.kicad_pro
