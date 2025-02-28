#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>


class ParallelMergeSort{
  private:
    std::vector<int> &nums;
    const int THRESHOLD = 1000; // size below which we will use normal sort to save on resources
    
    void parallel_sort(int start, int end){
        if(start>=end){
            return;
        }
        
        int mid = (start+end)/2;
        
        if (end - start > THRESHOLD) {
            std::thread left_thread(&ParallelMergeSort::parallel_sort, this, start, mid);
            std::thread right_thread(&ParallelMergeSort::parallel_sort, this, mid + 1, end);
            
            left_thread.join();
            right_thread.join();
        } else {
            // Sequential execution for smaller chunks
            parallel_sort(start, mid);
            parallel_sort(mid + 1, end);
        }
        
        int i = start;
        int j = mid+1;
        int k = 0;
        
        std::vector<int> _nums(end-start+1);
        while(i<=mid && j<=end){
            if(nums[i]<nums[j]){
                _nums[k]=nums[i];
                i++;
            }
            else{
                _nums[k]=nums[j];
                j++;
            }
            k++;
        }
        
        while(i<=mid){
            _nums[k++]=nums[i++];
        }
        
        while(j<=end){
            _nums[k++]=nums[j++];
        }
        
        for(int r=0; r<_nums.size(); r++){
            nums[start + r] = _nums[r];
        }
    }
  public:
    ParallelMergeSort(std::vector<int> &arr): nums(arr){
    }
    
    ~ParallelMergeSort(){   
    }
    
    void sort(){
        parallel_sort(0, nums.size()-1);
    }
};

int main(){
    srand(time(NULL));
    
    std::vector<int> nums;
    for(int i=0; i<10000000; i++){
        nums.push_back((rand())%100);
    }
    ParallelMergeSort pmr(nums);
    
    auto START=std::chrono::high_resolution_clock::now();
    pmr.sort();
    auto END=std::chrono::high_resolution_clock::now();
    
    auto time=duration_cast<std::chrono::microseconds>(END-START);
    
    for(int i=10; i<100; i++){
        std::cout<<nums[i]<<" ";
    }
    
    std::cout<<"\n";
    std::cout<<"Time taken: "<<time.count()<<" microseconds"<<std::endl;  
    return 0;
}