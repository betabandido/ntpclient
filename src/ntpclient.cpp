#include "ntpclient.h"

#include <Arduino.h>

ntp_client::ntp_client(UDP_ptr udp, unsigned short local_port)
  : udp_(std::move(udp))
{
  udp_->begin(local_port);
}

time_t ntp_client::get_time(unsigned timeout) {  
  memset(buffer, 0, packet_size);
  buffer[0] = 0b00100011; // version 4, client
  if (!udp_->beginPacket(server_name, server_port)
    || udp_->write(buffer, packet_size) != packet_size
    || !udp_->endPacket())
    return 0;

  auto t0 = millis();
  while ((millis() - t0) < timeout) {
    if (udp_->parsePacket() == packet_size) {
      udp_->read(buffer, packet_size);
      auto seconds = static_cast<unsigned long>(buffer[40]) << 24;
      seconds |= static_cast<unsigned long>(buffer[41]) << 16;
      seconds |= static_cast<unsigned long>(buffer[42]) << 8;
      seconds |= static_cast<unsigned long>(buffer[43]);
      return seconds - 2208988800UL;
    }
    delay(100);
  }

  Serial.println("get_time(): no response received");
  return 0;
}

