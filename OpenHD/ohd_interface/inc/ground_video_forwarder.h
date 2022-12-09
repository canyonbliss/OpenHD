//
// Created by consti10 on 09.12.22.
//

#ifndef OPENHD_OPENHD_OHD_INTERFACE_INC_GROUND_VIDEO_FORWARDER_H_
#define OPENHD_OPENHD_OHD_INTERFACE_INC_GROUND_VIDEO_FORWARDER_H_

#include "../../lib/wifibroadcast/src/UdpWBReceiver.hpp"

class GroundVideoForwarder{
 public:
  GroundVideoForwarder();
  // Start forwarding to another ip::port
  void addForwarder(std::string client_addr, int client_udp_port);
  // safe to call if not already forwarding to ip::port
  // stop forwarding to ip::port
  void removeForwarder(std::string client_addr, int client_udp_port);
  // called by the wb receiver
  void forward_data(const uint8_t* data, int data_len);
 private:
   std::unique_ptr<SocketHelper::UDPMultiForwarder> udpMultiForwarder;
};

#endif  // OPENHD_OPENHD_OHD_INTERFACE_INC_GROUND_VIDEO_FORWARDER_H_
