#include <pybind11/pybind11.h>
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
         .def("get", &ClntRpc::CounterExample::get)
         .def("add", &ClntRpc::CounterExample::add)
         .def("setExpiredAt", &ClntRpc::CounterExample::setExpiredAt)         
         ;

     py::class_<ClntRpc::ClientBal>(m, "ClientBal")
         .def(py::init<std::string, uint16_t>(),
              py::arg("hostName"),
              py::arg("hostPort"))
         .def("add", &ClntRpc::ClientBal::add<double>, "Add two numbers through RPC")
         .def("serverStop", &ClntRpc::ClientBal::serverStop, "Stop server")
         .def("setClientTimeout", &ClntRpc::ClientBal::setClientTimeout, "Set client timeout in ms")         
         .def("sessionStateCleanup", &ClntRpc::ClientBal::sessionStateCleanup, "sessionStateCleanup for stream interrupted")
         //stream objects
         .def("getCounterExample", &ClntRpc::ClientBal::getCounterExample, "getCounterExample")

         ;
}
