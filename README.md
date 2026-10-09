# Data and Remote Control with ESP8266 and Arduino

Codes and libraries accompanying the book **Data and Remote Control with ESP8266 and Arduino** by Mihai Todică, Presa Universitară Clujeană (Cluj University Press).

## Contents

- [`codes/`](codes) — the 93 Arduino sketches presented in the book, grouped by chapter (see the [index of codes](codes/README.md) with the book section and the libraries each one needs).
- [`libraries/`](libraries) — the 18 libraries used by the author, in the tested versions (see [libraries/README.md](libraries/README.md)).

## Getting started

1. Install the Arduino IDE (1.8.13 or newer).
2. In *File → Preferences → Additional Boards Manager URLs* add `http://arduino.esp8266.com/stable/package_esp8266com_index.json`.
3. In *Tools → Board → Boards Manager* install **esp8266 by ESP8266 Community**.
4. Download this repository (*Code → Download ZIP*) and copy the needed folders from `libraries/` into `Documents/Arduino/libraries`.
5. Open a sketch from `codes/`, select *NodeMCU 1.0 (ESP-12E Module)* and upload.

Wi-Fi credentials (`ssid`, `password`) and Blynk tokens in the codes must be replaced with your own.

## Licence

The sketches in `codes/` are released under the [MIT License](LICENSE) (c) Mihai Todică: you may use, modify and share them, keeping the copyright notice. The libraries keep their own licences. Some sketches are adapted from public examples; their sources are credited in the comments and in the book.

## Chapters

1. [Server with ESP8266 and Arduino](codes/Chapter_1) — 13 codes
2. [Asynchronous and WebSocket servers](codes/Chapter_2) — 8 codes
3. [Servers with WebSerial library](codes/Chapter_3) — 9 codes
4. [Peer to Peer (P2P) connections](codes/Chapter_4) — 25 codes
5. [Gateway with ESP8266 and Arduino Uno Pro Mini](codes/Chapter_5) — 8 codes
6. [Transmission of data and orders trough the internet](codes/Chapter_6) — 13 codes
7. [Equivalent ESP8266 modules](codes/Chapter_7) — 17 codes
