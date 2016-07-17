#include "stdafx.h"
#include "Server.h"
#include <signal.h>
#include <utility>
#include "connection.hpp"

using namespace http::server;

server::server(const std::string& address, const std::string& port,
    const std::string& doc_root)
  : _ioService(),
    _signals(_ioService),
    _acceptor(_ioService),
    _requestHandler(doc_root),
    _workers(_ioService, 10)
{
  _signals.add(SIGINT);
  _signals.add(SIGTERM);

  Stop();

  asio::ip::tcp::resolver resolver(_ioService);
  asio::ip::tcp::endpoint endpoint = *resolver.resolve({address, port});
  _acceptor.open(endpoint.protocol());
  _acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));
  _acceptor.bind(endpoint);
  _acceptor.listen();

  Accept();
}

void server::run()
{
  _workers.run();
}

void server::Accept()
{
    http::server::connection_ptr connection(new http::server::connection(_ioService, _requestHandler));
   _acceptor.async_accept(connection->GetSocket(),
      [=](std::error_code ec)
      {
        if (!_acceptor.is_open())
        {
          return;
        }

        if (!ec)
        {
            connection->start();
        }

        Accept();
      });
}

void server::Stop()
{
  _signals.async_wait(
      [this](std::error_code ec, int signo)
      {
        _acceptor.close();
        _ioService.stop();
      });
}


