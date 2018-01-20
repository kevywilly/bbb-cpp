
#ifndef SYNC_SERVER_H
#define SYNC_SERVER_H

#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

const int max_length = 256;

void session(tcp::socket sock, void (*callback) (const std::string&))
{
  try
  {
    for (;;)
    {
      char data[max_length];

      boost::system::error_code error;
      size_t length = sock.read_some(boost::asio::buffer(data), error);
      if (error == boost::asio::error::eof)
        break; // Connection closed cleanly by peer.
      else if (error)
        throw boost::system::system_error(error); // Some other error.
      
      if(callback) {
        std::string payload = std::string(data);
        //std::string(strcpy(data));
        callback(payload);
      }
      
      cout << data << endl;
      boost::asio::write(sock, boost::asio::buffer(data, length));
    }
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception in thread: " << e.what() << "\n";
  }
}

void server(boost::asio::io_service& io_service, unsigned short port, void (*callback) (const std::string&))
{
  tcp::acceptor a(io_service, tcp::endpoint(tcp::v4(), port));
  for (;;)
  {
    tcp::socket sock(io_service);
    a.accept(sock);
    std::thread(session, std::move(sock), callback).detach();
  }
}


#endif