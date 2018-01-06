#ifndef VISION_SESSION_HPP_
#define VISION_SESSION_HPP_


#include "camera.hpp"
#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

class VisionSession
{
public:
  VisionSession(boost::asio::io_service& io_service, Camera * c)
    : socket_(io_service)
  {
      camera = c;
  }

  
  tcp::socket& socket()
  {
    return socket_;
  }
  
  virtual void start()
  {
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&VisionSession::handle_read, this,
          boost::asio::placeholders::error,
          boost::asio::placeholders::bytes_transferred));
  }

  virtual void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred)
  {
    if (!error)
    {
      boost::asio::async_write(socket_,
          boost::asio::buffer(data_, bytes_transferred),
          boost::bind(&VisionSession::handle_write, this,
            boost::asio::placeholders::error));
    }
    else
    {
      delete this;
    }
  }
  
  virtual void handle_write(const boost::system::error_code& error)
  {
    if (!error)
    {
      std::string s(data_);
      handle_action(s);
      
      socket_.async_read_some(boost::asio::buffer(data_, max_length),
          boost::bind(&VisionSession::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
    }
    else
    {
      delete this;
    }
    
  }
  
  virtual void handle_action(const std::string& action) {
      cout << "Camera: " << action << "\n" << endl;
      if(action == "grab") {
          if(camera != 0) {
              camera->grab_bw();
          }
      }
  }
  
  Camera * camera;


private:
  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];

  
};


#endif /* VISION_SESSION_HPP_ */