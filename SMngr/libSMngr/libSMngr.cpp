#include "libSMngr.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

int add(int a, int b){
    return a+b;
}

std::string getUuid(){
    boost::uuids::uuid id = boost::uuids::random_generator()();
    return to_string(id);
}