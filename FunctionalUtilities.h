#ifndef FUTILITIES
#define FUTILITIES

#include <algorithm>
#include <vector>

namespace futilities{
    
    
    
    /**Utility function for integer powers.  
     * Recursively creates powers at compile time.  
     * Should be extremely fast.*/
    template<typename T>
    constexpr T const_power(const T& number, int N ){
        return (N == 1) ?             // terminal condition
            number:                   // and terminal value
            number*const_power(number, N-1); // recursive definition
    }


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
        This function runs in parallel when compiled with openmp enabled.  Be careful!  It is expected that fn induces side effects.
        @fnInit  function to get initial index
        @fnEnd function to get end index
        @array generic array...eg, an Eigen matrix
        @fn function to apply to array.  It is expected that fn induces side effects.
        @returns new array with fn applied to original array
    */
    template<typename GetInit, typename GetEnd, typename Array, typename Function>
    auto for_each_parallel_generic(const GetInit& fnInit, const GetEnd& fnEnd, Array&& array, Function&& fn){ //reuse array
        auto init=fnInit(array);
        auto end=fnEnd(array);
        #pragma omp parallel
        {//multithread using openmp
            #pragma omp for //multithread using openmp
            for(auto it = init; it < end; ++it){
                 fn(it, array);   
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
        @fn function to apply to elements from "begin" to "fromEnd" in the array
        @returns new array with fn applied to original array
    */
    template<typename Array, typename Function>
    auto for_each_subset(Array&& array, int begin, int fromEnd, Function&& fn){ //reuse array
        for(auto it = array.begin()+begin; it < array.end()-fromEnd; ++it){
            *it=fn(*it, it-array.begin());   
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
    auto for_each_parallel_copy(const Array& array, Function&& fn){
        auto myVal=fn(array.front(), 0);
        auto arrayLength=array.size();
        std::vector<decltype(myVal)> myVector(arrayLength); 

        #pragma omp parallel
        {//multithread using openmp
            #pragma omp for //multithread using openmp
            for(auto it = 0; it < arrayLength; ++it){
                myVector[it]=fn(array[it], it);   
            }
        }
        return myVector;
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
    Careful!  this function provides a mutated array (not the original array)
        @array std-style container
        @fn function to apply to every element in the array
        @returns new array with fn applied to original array
    */
    template<typename Array, typename Function>
    auto for_each_provide_array(Array&& array, Function&& fn){ //reuse array
        for(auto it = array.begin(); it < array.end(); ++it){
            *it=fn(*it, it-array.begin(), array);   
        }
        return std::move(array);
    }
    /**
        @array std-style container
        @fn function to apply to every element in the array
        @returns new array with fn applied to original array
    */
    template<typename Array, typename Function>
    auto for_each_copy(const Array& array, Function&& fn){ 
        Array tmpArr=array;
        for(auto it = tmpArr.begin(); it < tmpArr.end(); ++it){
            *it=fn(*it, it-tmpArr.begin(), array);   
        }
        return std::move(tmpArr);
    }

    template<typename incr, typename fnToApply>
    auto for_each(incr begin, incr end, fnToApply&& fn)->std::vector<decltype(fn(begin))>{
        auto myVal=fn(begin);
        std::vector<decltype(myVal)> myVector(end-begin); 
        myVector[0]=myVal;
        for(auto it = begin+1; it < end; ++it){
            myVector[it-begin]=fn(it);   
        }
        return myVector;
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
        @returns single value of results of applying fn to sequence and reducing
    */
    template<typename Array, typename Function, typename OptionalFirstItem>
    auto reduce_to_single(const Array& array, Function&& fn,  OptionalFirstItem&& item){
        auto curr=fn(item, array.front(), 0); 
        auto n=array.size();
        for(int i=1;i<n; ++i){
            curr=fn(std::move(curr), array[i],  i);   
        }
        return curr;
    }
    template<typename Array, typename Function>
    auto reduce_to_single(const Array& array, Function&& fn){
        return reduce_to_single(array, fn, array.front());
    }
    /**
        @array array to cumulate
        @fn function to apply to each element
        @returns new array of results of applying fn to sequence and cumulative summing
    */
    template<typename Array, typename Function, typename OptionalFirstItem>
    auto reduce(Array&& array, Function&& fn, const OptionalFirstItem& item){
        auto initIt=array.begin();
        *initIt=fn(item, *initIt, 0); 
        initIt++;
        for(auto it = initIt; it < array.end(); ++it){
            *it=fn(*std::prev(it), *it,  it-array.begin());   
        }
        return std::move(array);
    }
    /**
        @array array to cumulate
        @fn function to apply to each element
        @returns new array of results of applying fn to sequence and cumulative summing
    */
    template<typename Array, typename Function>
    auto reduce(Array&& array, Function&& fn){
        return reduce(std::move(array), fn, array.front());
    }
    /**
        @array array to cumulate
        @fn function to apply to each element
        @returns new array of results of applying fn to sequence and cumulative summing
    */
    template<typename Array, typename Function, typename OptionalFirstItem>
    auto reduce_reverse(Array&& array, Function&& fn, const OptionalFirstItem& item){
        auto initIt=array.rbegin();
        *initIt=fn(item, *initIt, 0); 
        initIt++;
        for(auto it = initIt; it < array.rend(); ++it){
            *it=fn(*std::prev(it), *it,  it-array.rbegin());   
        }
        return std::move(array);
    }
    /**
        @array array to cumulate
        @fn function to apply to each element
        @returns new array of results of applying fn to sequence and cumulative summing
    */
    template<typename Array, typename Function>
    auto reduce_reverse(Array&& array, Function&& fn){
        return reduce_reverse(std::move(array), fn, array.front());
    }
    /**
        @array array to cumulate
        @fn function to apply to each element
        @returns new array of results of applying fn to sequence and cumulative summing
    */
    template<typename Array, typename Function, typename OptionalFirstItem>
    auto reduce_copy(const Array& array, Function&& fn, const OptionalFirstItem& item){
        auto initIt=fn(item, *array.begin(), 0); 
        std::vector<decltype(initIt)> myVector(array.size());
        myVector[0]=initIt; 
        for(auto it = 1; it < array.size(); ++it){
            myVector[it]=fn(myVector[it-1], array[it],  it);   
        }
        return myVector;
    }
    /**
        @array array to cumulate
        @fn function to apply to each element
        @returns new array of results of applying fn to sequence and cumulative summing
    */
    template<typename Array, typename Function>
    auto reduce_copy(const Array& array, Function&& fn){
        return reduce_copy(array, std::move(fn), array.front());
    }
    /**
        @array array to cumulate
        @fn function to apply to each element
        @returns new array of results of applying fn to sequence and cumulative summing
    */
    template<typename Array, typename Function, typename OptionalFirstItem>
    auto reduce_reverse_copy(const Array& array, Function&& fn, const OptionalFirstItem& item){
        auto initIt=fn(item, *array.rbegin(), 0); 
        auto arrayLength=array.size();
        std::vector<decltype(initIt)> myVector(arrayLength);
        myVector[arrayLength-1]=initIt; 
        for(auto it = arrayLength-1; it > 0; --it){
            myVector[it-1]=fn(myVector[it], array[it-1],  arrayLength-it);   
        }
        return myVector;
    }
    /**
        @array array to cumulate
        @fn function to apply to each element
        @returns new array of results of applying fn to sequence and cumulative summing
    */
    template<typename Array, typename Function>
    auto reduce_reverse_copy(const Array& array, Function&& fn){
        return reduce_reverse_copy(array, std::move(fn), array.front());
    }

    /**
        @array array to cumulate
        @fn function to apply to each element
        @returns new array of results of applying fn to sequence and cumulative summing
    */
    template<typename Array, typename Function>
    auto cumulative_sum(Array&& array, Function&& fn){
        return reduce(std::move(array), [&](const auto& prev, const auto& curr, const auto& index){
            if(index==0){
                return fn(curr, index);
            }
            else{
                return prev+fn(curr, index);
            }
            
        });
    }
    /**
        @array array to cumulate
        @fn function to apply to each element
        @returns new array of results of applying fn to sequence and cumulative summing
    */
    template<typename Array, typename Function>
    auto cumulative_sum_copy(const Array& array, Function&& fn){
        return reduce_copy(array, [&](const auto& prev, const auto& curr, const auto& index){
            if(index==0){
                return fn(curr, index);
            }
            else{
                return prev+fn(curr, index);
            }
        });
    }


    /**
        @array array to sum over
        @fn function to apply to each element
        @returns result of summing every element
    */
    template<typename Array, typename Function>
    auto sum(const Array& array, Function&& fn){
        auto it=array.begin();
        auto myNum=fn(*it, 0);
        ++it;
        for(;it < array.end(); ++it){
            myNum+=fn(*it, it-array.begin());   
        }
        return myNum;
    }
    
    /**
        @array array to sum over
        @fn function to apply to each element
        @returns result of summing every element
    */
    template<typename Array, typename Function>
    auto sum_subset(const Array& array, int beginFrom, int endFrom, Function&& fn){
        auto it=array.begin()+beginFrom;
        auto myNum=fn(*it, beginFrom);
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
        for(incr i=1;i<n;++i){
            fnVal=fn(fnVal, i);
        }
        return fnVal;
    }

    template<typename incr, typename init, typename fnToApply, typename keepGoing>
    auto recurse(const incr& n, const init& initValue, fnToApply&& fn, keepGoing&& kpg)->decltype(fn(initValue, 0)){
        incr i=0;
        auto fnVal=fn(initValue, i);
        while(i<(n-1)&&kpg(fnVal)){
            ++i;
            fnVal=fn(fnVal, i);
        }
        return fnVal;
    }
    template<typename incr, typename init, typename fnToApply, typename keepGoing>
    auto recurse_move(const incr& n, init&& initValue, fnToApply&& fn, keepGoing&& kpg){
        incr i=0;
        while(i<n&&kpg(initValue)){
            initValue=fn(std::move(initValue), i);
             ++i;
        }
        return std::move(initValue);
    }
    template<typename incr, typename init, typename fnToApply>
    auto recurse_move(const incr& n, init&& initValue, fnToApply&& fn){
        for(incr i=0;i<n;++i){
            initValue=fn(std::move(initValue), i);
        }
        return std::move(initValue);
    }
    /*
    template<typename init, typename fnToApply, typename keepGoing>
    auto recurse_move(init&& initValue, fnToApply&& fn, keepGoing&& kpg){
        while(kpg(initValue)){
            initValue=fn(std::move(initValue));
        }
        return std::move(initValue);
    }*/
    
}
#endif
