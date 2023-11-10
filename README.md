![GitHub last commit](https://img.shields.io/github/last-commit/blacksheepinc/Haltech-wideband-emulator)
# <img src="https://github.com/blacksheepinc/Haltech-wideband-emulator/blob/main/logo.png" width="100"> Haltech Wideband Emulator

This example code simulates Haltech's wideband box (both single and dual channel), designed to run on any arduino compatible board with a MCP2515 CAN controller. However it the basic code could be ported or the Protocol could be used for porting to any other CAN compatible MCU eg.ESP32 with a CAN transreceiver.
For the Wideband controlling side, here are some examples:
* SLC 2 Free: https://www.14point7.com/pages/software-and-documentation
* Bosch CJ125: https://github.com/byrek/arduino-cj125
* Bylund Bosch CJ125: https://github.com/Bylund/Lambda-Shield-2-Example

## Haltech product
* https://www.haltech.com/product/ht-159986-wb2-bosch-dual-channel-can/

### The following functions are performed:
* Outputs lambda to CAN in Haltech's format

## Example schematics:
<img src="https://github.com/blacksheepinc/Haltech-wideband-emulator/blob/main/arduino_uno_example_schematics.png">

## Official CAN protocol from Haltech Support:
<table class="tg">
<thead>
  <tr>
    <th class="tg-c3ow">CAN I.D.</th>
    <th class="tg-c3ow">Rate (Hz)</th>
    <th class="tg-c3ow">Direction</th>
    <th class="tg-c3ow">Message Position</th>
    <th class="tg-c3ow">Sign</th>
    <th class="tg-c3ow">Channel</th>
    <th class="tg-c3ow">Units</th>
    <th class="tg-c3ow">Conversion from Raw</th>
  </tr>
</thead>
<tbody>
  <tr>
    <td class="tg-9wq8" rowspan="7">WB1: 0x2B1<br>WB2A: 0x2B0<br>WB2B: 0x2B4<br>WB2C: 0x2B6<br>WB2D: 0x2B8</td>
    <td class="tg-9wq8" rowspan="7">20</td>
    <td class="tg-9wq8" rowspan="7">TX</td>
    <td class="tg-9wq8">0 - 1</td>
    <td class="tg-9wq8">Unsigned</td>
    <td class="tg-9wq8">WBI1 Lambda</td>
    <td class="tg-9wq8">λ</td>
    <td class="tg-9wq8">32767=Free Air<br>Otherwise: y = x/1024</td>
  </tr>
  <tr>
    <td class="tg-9wq8">2 - 3</td>
    <td class="tg-9wq8">Unsigned</td>
    <td class="tg-9wq8">WBI2 Lambda *</td>
    <td class="tg-9wq8">λ</td>
    <td class="tg-9wq8">32767=Free Air<br>Otherwise: y = x/1024</td>
  </tr>
  <tr>
    <td class="tg-9wq8">4</td>
    <td class="tg-9wq8">Unsigned</td>
    <td class="tg-9wq8">WBI1 Sense Resistor</td>
    <td class="tg-9wq8">Ω</td>
    <td class="tg-9wq8">y = x</td>
  </tr>
  <tr>
    <td class="tg-9wq8">5</td>
    <td class="tg-9wq8">Unsigned</td>
    <td class="tg-9wq8">WBI2 Sense Resistor</td>
    <td class="tg-9wq8">Ω</td>
    <td class="tg-9wq8">y = x</td>
  </tr>
  <tr>
    <td class="tg-9wq8">6:3 - 6:0</td>
    <td class="tg-9wq8">Unsigned</td>
    <td class="tg-9wq8">WBI1 Diagnostic Codes</td>
    <td class="tg-9wq8">enum</td>
    <td class="tg-9wq8">1=Low Battery Voltage (&lt;9V)<br>     2=High Battery Voltage (&gt;18V)<br>     3=Sensor Short Circuit<br>     4=Sensor Open Circuit<br>     5=Sensor Cold</td>
  </tr>
  <tr>
    <td class="tg-9wq8">6:7 - 6:4</td>
    <td class="tg-9wq8">Unsigned</td>
    <td class="tg-9wq8">WBI2 Diagnostic Codes</td>
    <td class="tg-9wq8">enum</td>
    <td class="tg-9wq8">1=Low Battery Voltage (&lt;9V)<br>2=High Battery Voltage (&gt;18V)<br>3=Sensor Short Circuit<br>4=Sensor Open Circuit<br>5=Sensor Cold</td>
  </tr>
  <tr>
    <td class="tg-9wq8">7</td>
    <td class="tg-9wq8">Unsigned</td>
    <td class="tg-9wq8">Battery Voltage</td>
    <td class="tg-9wq8">V</td>
    <td class="tg-9wq8">y = x*20/255</td>
  </tr>
</tbody>
</table>

## Dependencies:
* https://github.com/coryjfowler/MCP_CAN_lib
