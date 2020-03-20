#include <ctime>
#include <string>
#include <cstdlib> //std::system
#include <iostream>

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/python.hpp>

class PythonSharedMemTest
{
public:
    PythonSharedMemTest(){}

    int get_number()
    {
        using namespace boost::interprocess;
        try
        {
            managed_shared_memory segment(open_only, "MySharedMemory");

            //Find the vector using the c-string name
            MyVector *myvector = segment.find<MyVector>("MyVector").first;

            if (myvector->size() > 10)
            {
                return myvector->at(10);
            }
            else
            {
                std::cout << "MyVector was empty :(" << std::endl;
                return -1;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }

        return -1;
        
    }

    //Define an STL compatible allocator of ints that allocates from the managed_shared_memory.
    //This allocator will allow placing containers in the segment
    using ShmemAllocator = boost::interprocess::allocator<int, boost::interprocess::managed_shared_memory::segment_manager>;

    //Alias a vector that uses the previous STL-like allocator so that allocates
    //its values from the segment
    using MyVector = boost::interprocess::vector<int, ShmemAllocator>;

};

BOOST_PYTHON_MODULE(python_shared_mem)
{
   using namespace boost::python;

   class_<PythonSharedMemTest>("shared_mem", init<>())
      .def("get_number", &PythonSharedMemTest::get_number)
      ;   

}