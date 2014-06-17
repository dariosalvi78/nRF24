nRF24
=====

This library implements the functionalities of the [NRF24L01+ chip](http://www.nordicsemi.com/eng/Products/2.4GHz-RF/nRF24LU1P) without (almost) any further abstraction. This code is based on the work of Mike McCauley (mikem at airspayce dot com), original code Id: NRF24.h,v 1.1 2012/12/12 11:17:16 mikem Exp mikem, available at http://www.airspayce.com/mikem/arduino/NRF24/

Differences with the original library:
* uses javadoc documentation style
* adds reliability: almost every command is checked after being executed
* supports all pipes (not only 0 and 1)
* adds support for interrupts (still provisional)


Alternatives:
-------------

*  [mirf](https://github.com/aaronds/arduino-nrf24l01) the official one in the Arduino playground
*  [RF24](http://maniacbug.github.io/RF24/) by [maniacbug](http://maniacbug.wordpress.com/find-me-on/)
*  [NRF24](http://www.airspayce.com/mikem/arduino/NRF24/) by Mike
*  [Greg Copeland's fork of RF24](https://github.com/gcopeland/RF24)
*  [Stanley Seow's fork of RF24](https://github.com/stanleyseow/RF24), includes support for RaspberryPi
*  [Arco van Geest's fork of RF24](https://github.com/gnulnulf/RF24), includes support for RaspberryPi
*  [Charles-Henri Hallard's fork of RF24](https://github.com/hallard/RF24), with support for RaspberryPi
*  [Trey Keown's fork of RF24](https://github.com/jfktrey/RF24), with support for RaspberryPi


Known issues and todos:
------------------

* acks with payload are not supported yet
* interrupts not tested well yet
