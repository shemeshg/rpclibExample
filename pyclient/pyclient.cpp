#include <pybind11/pybind11.h>
#include <clientBal.h>
#include <serverBal.h>

namespace py = pybind11;

PYBIND11_MODULE(pyclient, m)
{
     py::class_<ServerBal>(m, "ServerBal")
         .def(py::init<uint16_t>(),
              py::arg("hostPort"))
         .def("start", &ServerBal::start,
              py::call_guard<py::gil_scoped_release>(),
              "Run server")
         .def("startAsync", &ServerBal::startAsync,
              "Run server async");

     py::class_<AsyncData<double>>(m, "AsyncDataDouble")
         .def("get", &AsyncData<double>::get);

     py::class_<CounterExample>(m, "CounterExample") 
         .def("get", &CounterExample::get)
         .def("add", &CounterExample::add)
         ;

     py::class_<ClientBal>(m, "ClientBal")
         .def(py::init<std::string, uint16_t>(),
              py::arg("hostName"),
              py::arg("hostPort"))
         .def("add", &ClientBal::add<double>, "Add two numbers through RPC")
         .def("serverStop", &ClientBal::serverStop, "Stop server")
         .def("setClientTimeout", &ClientBal::setClientTimeout, "Set client timeout in ms")
         .def("getCounterExample", &ClientBal::getCounterExample, "getCounterExample")
         ;
}
