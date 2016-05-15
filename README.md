# ntpclient
Arduino library that implements an NTP client.
It requires the Arduino Time library (http://playground.arduino.cc/Code/Time).

## Installation
Place the contents of this repository into your library folder.
See https://www.arduino.cc/en/Guide/Libraries for more details.

## Usage
[This example](https://github.com/betabandido/ntpclient/blob/master/examples/ntpclient_test/ntpclient_test.ino) shows the usage of the library. The login credentials for the access point must be placed in a file named `ssid-info.h` for the example to work. For instance:

    #ifndef SSID_INFO_H
    #define SSID_INFO_H

    static const char* ssid = "put your SSID here";
    static const char* password = "put your password here";

    #endif // SSID_INFO_H
