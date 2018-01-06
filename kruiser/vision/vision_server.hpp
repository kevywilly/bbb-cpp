#ifndef VISION_SERVER_HPP_
#define VISION_SERVER_HPP_

#include "vision_session.hpp"


#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

class VisionServer {

public:

  VisionServer(boost::asio::io_service& io_service, short port, Camera * c) : io_service_(io_service), 
    acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) {
    VisionSession* new_session = new VisionSession(io_service_, c);
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&VisionServer::handle_accept, this, new_session,
          boost::asio::placeholders::error));
  }

  void handle_accept(VisionSession* new_session, const boost::system::error_code& error) {
      if (!error)
      {
        new_session->start();
        new_session = new VisionSession(io_service_, new_session->camera);
        acceptor_.async_accept(new_session->socket(),
        boost::bind(&VisionServer::handle_accept, this, new_session,
        boost::asio::placeholders::error));
      }
      else
      {
        delete new_session;
      }
  }
  
private:
  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;

};

#endif /* CAMERA_SERVER_HPP_ */