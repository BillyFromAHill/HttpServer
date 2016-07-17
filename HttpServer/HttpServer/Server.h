#pragma once
#include "stdafx.h"
#include "asio.hpp"
#include <string>
#include "connection.hpp"
#include "request_handler.hpp"
#include "asio/ip/tcp.hpp"
#include "asio/signal_set.hpp"
#include "WorkersPool.h"


/// The top-level class of the HTTP server.
class server
{
public:
  server(const server&) = delete;
  server& operator=(const server&) = delete;

  
  server(const std::string& address, const std::string& port,
      const std::string& doc_root);

  void run();

private:

  void Accept();
  void Stop();


  asio::io_service _ioService;
  asio::signal_set _signals;
  asio::ip::tcp::acceptor _acceptor;
  http::server::request_handler _requestHandler;
  WorkersPool _workers;
};

