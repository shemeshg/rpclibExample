#include <pybind11/pybind11.h>
#include <clientBal.h>
#include <serverBal.h>

namespace py = pybind11;

PYBIND11_MODULE(pyclient, m)
{
    py::class_<ServerBal>(m, "ServerBal")
        .def(py::init<uint16_t>(),         
         py::arg("hostPort"))
        .def("run", &ServerBal::run, 
            py::call_guard<py::gil_scoped_release>(),
            "Run server");

    py::class_<ClientBal>(m, "ClientBal")
        .def(py::init<std::string, uint16_t>(),
         py::arg("hostName"), 
         py::arg("hostPort"))
        .def("add", &ClientBal::add, "Add two numbers through RPC");
}
