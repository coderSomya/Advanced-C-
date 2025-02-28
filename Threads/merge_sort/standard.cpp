#include <iostream>
#include <vector>
#include <random>
#include <chrono>

class StandardMergeSort{
  private:
    std::vector<int> &nums;
    
    void standard_sort(int start, int end){
        if(start>=end){
            return;
        }
        
        int mid = (start+end)/2;
        
        standard_sort(start,mid);
        standard_sort(mid+1, end);
        
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
    StandardMergeSort(std::vector<int> &arr): nums(arr){
    }
    
    ~StandardMergeSort(){   
    }
    
    void sort(){
        standard_sort(0, nums.size()-1);
    }
};

int main(){
    srand(time(NULL));
    
    std::vector<int> nums;
    for(int i=0; i<100000; i++){
        nums.push_back((rand())%100);
    }
    StandardMergeSort smr(nums);
    
    auto START=std::chrono::high_resolution_clock::now();
    smr.sort();
    auto END=std::chrono::high_resolution_clock::now();
    
    auto time=duration_cast<std::chrono::microseconds>(END-START);
    
    for(int i=10; i<100; i++){
        std::cout<<nums[i]<<" ";
    }
    
    std::cout<<"\n";
    std::cout<<"Time taken: "<<time.count()<<" microseconds"<<std::endl;  
    return 0;
}