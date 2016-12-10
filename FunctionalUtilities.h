#ifndef FUTILITIES
#define FUTILITIES
#include <algorithm>
namespace futilities{
    //template<typename myArray>
    /**
        This function runs in parallel when compiled with openmp enabled
        @array std-style container
        @fn function to apply to every element in the array
        @returns new array with fn applied to original array
    */
    auto for_each_parallel(auto&& array, auto&& fn){ //reuse array
        #pragma omp parallel
        {//multithread using openmp
            #pragma omp for //multithread using openmp
            for(auto it = array.begin(); it < array.end(); ++it){
                 *it=fn(*it);   
            }
        }
        return std::move(array);
    }
    /**
        @array std-style container
        @fn function to apply to every element in the array
        @returns new array with fn applied to original array
    */
    auto for_each(auto&& array, auto&& fn){ //reuse array
        for(auto it = array.begin(); it < array.end(); ++it){
                *it=fn(*it);   
        }
        return std::move(array);
    }
}
#endif