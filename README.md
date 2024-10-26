# About
This project displays a value on a double digit 7 segment display. You control the value of the displayed number with a rotary encoder and reset the counter pushing the encoder in. You can also go to negative values. Negative values are indicated with the two periods lighting up

# Components
1. Arduino of choice (I chose nano)
2. Rotary encoder
3. double digit 7 segment display
4. Breadboard + cables

# Connections
- 7 seg from pin D2 to pin D11
    - D2 and D3 is for digit control
    - D4-D10 is for segment control
    - D11 is for period control
- Rotary encoder:
    - CLK to A1
    - DT to A2
    - SW to D12
    - \+ to 5V
    - GND to GND