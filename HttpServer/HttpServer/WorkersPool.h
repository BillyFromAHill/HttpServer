#pragma once
#include "asio.hpp"
#include <list>
#include <thread>

class WorkersPool
{
public:

    WorkersPool(const WorkersPool&) = delete;
    WorkersPool& operator=(const WorkersPool&) = delete;
    WorkersPool() = delete;

    WorkersPool(asio::io_service &ioService, int workerCount);

    void run();

    ~WorkersPool();
private:
    asio::io_service &_ioService;
    int _workersCount;

    std::list<std::shared_ptr<std::thread>> _threads;
};

