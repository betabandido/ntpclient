#ifndef NTP_CLIENT_H
#define NTP_CLIENT_H

#include <Time.h>
#include <Udp.h>

/** NTP client.
 *  
 * See http://www.ietf.org/rfc/rfc5905.txt for details.
 */
class ntp_client {
public:
  /** Constructor.
   *  
   *  @param udp Initialized UDP object.
   */
  ntp_client(UDP& udp)
    : udp_(udp)
  {}

  /** Returns the current UTC time.
   *  
   *  @param timeout Time to wait for a server response (in ms).
   *  @returns The current UTC time; 0 if no response was received.
   */
  time_t get_time(unsigned timeout = 1000);

private:
  static constexpr char* server_name = "pool.ntp.org";
  static constexpr unsigned short server_port = 123;
  static constexpr unsigned short packet_size = 48;

  uint8 buffer[packet_size];
  
  UDP& udp_;
};

#endif // NTP_CLIENT_H

