#include <iostream>
#include <vector>
using std::vector;
/**
 * 思路
 * 排序数组中找最小：优先考虑二分搜索，先找可以折半的判断条件：
 * {3,4,5,1,2}，中间值比左边界大，则最小值在右边，中间比左边界小，则最小值在左边
 * 通过上面的思考可以细化思路：
 * 中间值>=左边界，则left=mid，否则right=mid，终止条件是left+1>=right，此时返回right
 * 正常情况下是left+1==right，只有一个元素时会left+1>right
 * 特例：（1）输入数组大小为0 （2）旋转了0个元素，即全排序数组（3）在判断相等时跳过最小值，{1,0,1,1,1}
 */
class Solution
{
  public:
    int minNumberInRotateArray(vector<int> &rotateArray)
    {
        if (rotateArray.empty()) //空数组
            return 0;
        size_t left = 0, right = rotateArray.size() - 1;
        if (rotateArray[left] < rotateArray[right]) //旋转0个元素
            return rotateArray[left];
        size_t mid;
        while (left + 1 < right)
        {
            mid = (left + right) >> 1;
            if (rotateArray[left] == rotateArray[mid] && rotateArray[mid] == rotateArray[right])
                return FindMinInOrder(rotateArray, left, right);
            if (rotateArray[mid] >= rotateArray[left])
                left = mid;
            else
                right = mid;
        }
        return rotateArray[right];
    }
    //特例：在判断相等时跳过最小值；只能按顺序判断
    int FindMinInOrder(vector<int> &rotateArray, int left, int right)
    {
        int nMin = rotateArray[left];
        for (int i = left; i <= right; ++i)
            if (nMin > rotateArray[i])
                nMin = rotateArray[i];
        return nMin;
    }
};
int main(int argc, char *argv[])
{
    Solution s;
    vector<int> input1{3, 4, 5, 1, 2}; //1.旋转数组
    std::cout << s.minNumberInRotateArray(input1) << std::endl;
    vector<int> input2; //2.空数组
    std::cout << s.minNumberInRotateArray(input2) << std::endl;
    vector<int> input3{3, 3, 3, 1, 1, 1, 1, 1}; //3.旋转数组，有相等的值
    std::cout << s.minNumberInRotateArray(input3) << std::endl;
    vector<int> input4{1, 2, 3, 4, 5}; //4.旋转0个，全排序数组
    std::cout << s.minNumberInRotateArray(input4) << std::endl;
    vector<int> input5{2, 1, 2, 2, 2}; //5.在判断相等时跳过最小值
    std::cout << s.minNumberInRotateArray(input5) << std::endl;
    vector<int> input6{2}; //6.只有一个元素
    std::cout << s.minNumberInRotateArray(input6) << std::endl;
    return 0;
}