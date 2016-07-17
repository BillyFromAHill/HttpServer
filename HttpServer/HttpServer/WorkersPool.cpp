#include "stdafx.h"
#include "WorkersPool.h"
#include <thread>
#include <functional>

using namespace std;
WorkersPool::WorkersPool(asio::io_service &ioService, int workerCount) : _ioService(ioService), _workersCount(workerCount)
{
}

void WorkersPool::run()
{
    for (int i = 0; i < _workersCount; i++)
    {
        shared_ptr<thread> thr = make_shared<thread>([this]()->void{_ioService.run(); });
        _threads.push_back(thr);
    }

    for_each(_threads.begin(), _threads.end(), [](shared_ptr<thread> & val){val->join(); });
}

WorkersPool::~WorkersPool()
{
}
