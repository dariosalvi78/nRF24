nRF24
=====

This library implements the functionalities of the [NRF24L01+ chip](http://www.nordicsemi.com/eng/Products/2.4GHz-RF/nRF24LU1P) without (almost) any further abstraction.

Author: Dario Salvi (dariosalvi78 at gmail dot com)

Based on the work of Mike McCauley (mikem at airspayce dot com)
Original code Id: NRF24.h,v 1.1 2012/12/12 11:17:16 mikem Exp mikem
Available at http://www.airspayce.com/mikem/arduino/NRF24/

Differences with the original library:
* uses javadoc documentation style
* adds reliability: almost every command is checked after being executed
* supports all pipes (not only 0 and 1)
* adds support for interrupts (still provisional)

Still unsupported:
* acks with payload

Licensed under the GPL license http://www.gnu.org/copyleft/gpl.html