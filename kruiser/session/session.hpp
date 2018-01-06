#ifndef SESSION_H_
#define SESSION_H_

#include <boost/bind.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;


class Session
{
public:
  
  Session() {
    
  }
  tcp::socket& socket()
  {
    return socket_;
  }

  virtual void start() = 0;
  

  virtual void handle_read(const boost::system::error_code& error,
      size_t bytes_transferred) = 0;

  
  virtual void handle_write(const boost::system::error_code& error) = 0;
  
  
  virtual void handle_action(const std::string& action) = 0;

//protected:
  tcp::socket socket_;
  enum { max_length = 1024 };
  char data_[max_length];
  
};


#endif /* CAMERA_SESSION_HPP_ */