#ifndef FUTILITIES
#define FUTILITIES
#include <algorithm>
#include <vector>
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
        @begin first index
        @end last index
        @fn function to apply to every element in the array
        @returns vector of results
    */
    template<typename incr, typename fnToApply>
    auto for_each_parallel(incr begin, incr end, fnToApply&& fn)->std::vector<decltype(fn(begin))>{
        auto myVal=fn(begin);
        std::vector<decltype(myVal)> myVector(end-begin); 
        myVector[0]=myVal;
        #pragma omp parallel
        {//multithread using openmp
            #pragma omp for //multithread using openmp
            for(auto it = begin+1; it < end; ++it){
                 myVector[it-begin]=fn(it);   
            }
        }
        return myVector;
    }
    /**
        @begin first index
        @end last index
        @fn function to apply to every element in the array
    */
    void for_each(auto begin, auto end, auto&& fn){
        for(auto it = begin; it < end; ++it){
            fn(it);   
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
    /**
        @init first number in sequence
        @end last number in sequence
        @n total in sequence
        @fn function to apply to number in sequence
        @returns new array of results of applying fn to sequence
    */
    template<typename Number>
    std::vector<Number> for_emplace_back(const Number& init, const Number& end, int n, auto&& fn){
        std::vector<Number> myArray;
        Number dx=(end-init)/(double)(n-1);
        for(int i=0; i<n; ++i){
            myArray.emplace_back(fn(init+dx*i));  
        }
        return myArray;
    }
    /**
        @array array to cumulate
        @fn function to apply to each element
        @returns new array of results of applying fn to sequence and cumulative summing
    */
    auto cumulative_sum(auto&& array, auto&& fn){
        for(auto it = array.begin(); it < array.end(); ++it){
            *it=fn(*it)+*std::prev(it);   
        }
        return std::move(array);
    }
    /**
        @array array to sum over
        @fn function to apply to each element
        @returns result of summing every element
    */
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
    /**
        @begin first index
        @end last index
        @fn function to apply to each index
        @returns result of summing every function of index
    */
    template<typename incr, typename fnToApply>
    auto sum(incr begin, incr end, fnToApply&& fn)->decltype(fn(begin)){
        auto myNum=fn(begin);
        for(int i=begin+1; i<end; ++i){
            myNum+=fn(i);   
        }
        return myNum;
    }
}
#endif