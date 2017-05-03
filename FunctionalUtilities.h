#ifndef FUTILITIES
#define FUTILITIES
#include <algorithm>
#include <vector>
namespace futilities{
    
    /**
        This function runs in parallel when compiled with openmp enabled
        @array std-style container
        @fn function to apply to every element in the array
        @returns new array with fn applied to original array
    */
    template<typename Array, typename Function>
    auto for_each_parallel(Array&& array, Function&& fn){ //reuse array
        #pragma omp parallel
        {//multithread using openmp
            #pragma omp for //multithread using openmp
            for(auto it = array.begin(); it < array.end(); ++it){
                 *it=fn(*it, it-array.begin());   
            }
        }
        return std::move(array);
    }
    /**
        This function runs in parallel when compiled with openmp enabled
        @array std-style container
        @fn function to apply to elements from "begin" to "fromEnd" in the array
        @returns new array with fn applied to original array
    */
    template<typename Array, typename Function>
    auto for_each_parallel_subset(Array&& array, int begin, int fromEnd, Function&& fn){ //reuse array
        #pragma omp parallel
        {//multithread using openmp
            #pragma omp for //multithread using openmp
            for(auto it = array.begin()+begin; it < array.end()-fromEnd; ++it){
                 *it=fn(*it, it-array.begin());   
            }
        }
        return std::move(array);
    }
    /**
        This function runs in parallel when compiled with openmp enabled
        @array std-style container
        @fn function to apply to every element in the array
        @returns new array with fn applied to original array
    */
    template<typename Array, typename Function>
    auto for_each_parallel_exclude_last(Array&& array, Function&& fn){ //reuse array
        #pragma omp parallel
        {//multithread using openmp
            #pragma omp for //multithread using openmp
            for(auto it = array.begin(); it < array.end()-1; ++it){
                 *it=fn(*it, it-array.begin());   
            }
        }
        array.pop_back();
        return std::move(array);
    }
    /**
        This function runs in parallel when compiled with openmp enabled
        @array std-style container
        @fn function to apply to every element in the array
        @returns new array with fn applied to original array
    */
    template<typename Array, typename Function>
    auto for_each_exclude_last(Array&& array, Function&& fn){ //reuse array
        for(auto it = array.begin(); it < array.end()-1; ++it){
            *it=fn(*it, *(it+1), it-array.begin());   
        }
        array.pop_back();
        return std::move(array);
    }
    /**
        This function runs in parallel when compiled with openmp enabled
        @array std-style container
        @fn function to apply to every element in the array
        @returns new array with fn applied to original array
    */
    template<typename Array, typename Function>
    auto for_each_parallel_copy(Array array, Function&& fn){ //reuse array
        //auto myArray=array;
        #pragma omp parallel
        {//multithread using openmp
            #pragma omp for //multithread using openmp
            for(auto it = array.begin(); it < array.end(); ++it){
                 *it=fn(*it, it-array.begin());   
            }
        }
        return array;
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
        @array std-style container
        @fn function to apply to every element in the array
        @returns new array with fn applied to original array
    */
    template<typename Array, typename Function>
    auto for_each(Array&& array, Function&& fn){ //reuse array
        for(auto it = array.begin(); it < array.end(); ++it){
            *it=fn(*it, it-array.begin());   
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
    template<typename Number, typename Function>
    std::vector<Number> for_emplace_back(const Number& init, const Number& end, int n, Function&& fn){
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
    template<typename Array, typename Function>
    auto cumulative_sum(Array&& array, Function&& fn){
        for(auto it = array.begin(); it < array.end(); ++it){
            *it=fn(*it, it-array.begin())+*std::prev(it);   
        }
        return std::move(array);
    }



    /**
        @array array to sum over
        @fn function to apply to each element
        @returns result of summing every element
    */
    template<typename Number, typename Function>
    auto sum(const std::vector<Number>& array, Function&& fn){
        auto it=array.begin();
        auto myNum=fn(*it, 0);
        ++it;
        for(it; it < array.end(); ++it){
            myNum+=fn(*it, it-array.begin());   
        }
        return myNum;
    }
    /**
        @array array to sum over
        @fn function to apply to each element
        @returns result of summing every element
    */
    template<typename Number, typename Function>
    auto sum_subset(const std::vector<Number>& array, int beginFrom, int endFrom, Function&& fn){
        auto it=array.begin()+beginFrom;
        auto myNum=fn(*it, 0);
        ++it;
        for(it; it < array.end()-endFrom; ++it){
            myNum+=fn(*it, it-array.begin());   
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
        for(incr i=begin+1; i<end; ++i){
            myNum+=fn(i);   
        }
        return myNum;
    }

    template<typename incr, typename init, typename fnToApply>
    auto recurse(const incr& n, const init& initValue, fnToApply&& fn)->decltype(fn(initValue, 0)){

        auto fnVal=fn(initValue, 0);
        for(incr i=0;i<n;++i){
            fnVal=fn(fnVal, i);
        }
        return fnVal;
    }


    template<typename incr, typename init, typename fnToApply, typename keepGoing>
    auto recurse(const incr& n, const init& initValue, fnToApply&& fn, keepGoing&& kpg)->decltype(fn(initValue, 0)){
        incr i=0;
        auto fnVal=fn(initValue, 0);
        while(i<n&&kpg(initValue, fnVal)){
            fnVal=fn(fnVal, i);
            ++i;
        }
        return fnVal;
    }

    template<typename incr, typename init, typename fnToApply, typename keepGoing>
    auto recurse_move(const incr& n, init&& initValue, fnToApply&& fn, keepGoing&& kpg){
        incr i=0;
        while(i<n&&kpg(initValue)){
            initValue=fn(initValue, i);
             ++i;
        }
        return std::move(initValue);
    }
    
}
#endif
