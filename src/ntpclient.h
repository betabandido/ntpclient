#ifndef NTP_CLIENT_H
#define NTP_CLIENT_H

#include <memory>

#include <Time.h>
#include <Udp.h>

/** NTP client.
 *  
 * See http://www.ietf.org/rfc/rfc5905.txt for details.
 */
class ntp_client {
public:
  typedef std::unique_ptr<UDP> UDP_ptr;

  /** Constructor.
   *  
   *  @param udp pointer to UDP object. 
   */
  ntp_client(UDP_ptr udp, unsigned short local_port = 8888);

  /** Returns the current UTC time.
   *  
   *  @param timeout Time to wait for a server response (in ms).
   *  @returns The current UTC time; 0 if no response was received.
   */
  time_t get_time(unsigned timeout = 1000);

private:
  static constexpr char const* server_name = "pool.ntp.org";
  static constexpr unsigned short server_port = 123;
  static constexpr unsigned short packet_size = 48;

  uint8 buffer[packet_size];
  
  UDP_ptr udp_;
};

#endif // NTP_CLIENT_H

