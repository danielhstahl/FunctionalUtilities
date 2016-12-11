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
    auto for_each_parallel(const auto&& array, auto&& fn){ //reuse array
        #pragma omp parallel
        {//multithread using openmp
            #pragma omp for //multithread using openmp
            for(auto it = array.begin(); it < array.end(); ++it){
                 *it=fn(*it);   
            }
        }
        return std::move(array);
    }
    void for_each_parallel(const auto& array, auto&& fn){ //reuse array
        #pragma omp parallel
        {//multithread using openmp
            #pragma omp for //multithread using openmp
            for(auto it = array.begin(); it < array.end(); ++it){
                 fn(*it, it - array.begin());   
            }
        }
    }
    void for_each_parallel(auto begin, auto end, auto&& fn){ //reuse array
        #pragma omp parallel
        {//multithread using openmp
            #pragma omp for //multithread using openmp
            for(auto it = begin; it < end; ++it){
                 fn(it);   
            }
        }
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
    /*auto for_emplace_back(auto&& array, auto&& fn){

        return for_emplace_back(array, fn);
    }*/
    template<typename Number>
    std::vector<Number> for_emplace_back(const Number& init, const Number& end, int n, auto&& fn){
        std::vector<Number> myArray;
        Number dx=(end-init)/(double)(n-1);
        for(int i=0; i<n; ++i){
            myArray.emplace_back(fn(init+dx*i));  
        }
        return myArray;
    }
    auto accumulate(auto&& array, auto&& fn){
        
        for(auto it = array.begin(); it < array.end(); ++it){
            *it=fn(*it)+*std::prev(it);   
        }
        return std::move(array);
    }
    template<typename Number>
    Number sum(const std::vector<Number>& array, auto&& fn){
        auto it=array.begin();
        Number myNum=fn(*it);
        ++it;
        for(it; it < array.end(); ++it){
            myNum+=fn(*it);   
        }
        return myNum;
    }
    auto sum(auto begin, auto end, auto&& fn){
        auto myNum=fn(begin);
        for(int i=begin+1; i<end; ++i){
            myNum+=fn(i);   
        }
        return myNum;
    }
}
#endif