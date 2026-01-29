#include <pybind11/pybind11.h>
#include "sharedConst.h"
#include <clientBal.h>
#include <serverBal.h>

namespace py = pybind11;

PYBIND11_MODULE(pyclient, m)
{
     py::class_<SvrRpc::ServerBal>(m, "ServerBal")
         .def(py::init<uint16_t>(),
              py::arg("hostPort"))
         .def("start", &SvrRpc::ServerBal::start,
              py::call_guard<py::gil_scoped_release>(),
              "Run server")
         .def("startAsync", &SvrRpc::ServerBal::startAsync,
              "Run server async");

     py::class_<ClntRpc::AsyncData<double>>(m, "AsyncDataDouble")
         .def("get", &ClntRpc::AsyncData<double>::get);

     py::class_<ClntRpc::CounterExample>(m, "CounterExample")
         .def(rpcConsts::CounterExample::add, &ClntRpc::CounterExample::get)
         .def(rpcConsts::CounterExample::get, &ClntRpc::CounterExample::add)
         .def(rpcConsts::CounterExample::setExpiredAt, &ClntRpc::CounterExample::setExpiredAt)         
         ;

     py::class_<ClntRpc::ClientBal>(m, "ClientBal")
         .def(py::init<std::string, uint16_t>(),
              py::arg("hostName"),
              py::arg("hostPort"))
         .def(rpcConsts::asyncAdd, &ClntRpc::ClientBal::add<double>, "Add two numbers through RPC")
         .def(rpcConsts::serverStop, &ClntRpc::ClientBal::serverStop, "Stop server")
         .def(rpcConsts::setClientTimeout, &ClntRpc::ClientBal::setClientTimeout, "Set client timeout in ms")         
         .def(rpcConsts::sessionStateCleanup, &ClntRpc::ClientBal::sessionStateCleanup, "sessionStateCleanup for stream interrupted")
         //stream objects
         .def(rpcConsts::getCounterExample, &ClntRpc::ClientBal::getCounterExample, "get CounterExample")

         ;
}
