#include <iostream>
#include <vector>
#include <functional> //greater
#include <queue>      //priority_queue
#include <assert.h>
using namespace std;

/******************************** 插入排序 平均O(N^2) ********************************/
/**
 * 插入排序 insertion sort
 */
template <typename Comparable>
void InsertionSort(vector<Comparable> &v)
{
    int j;
    for (size_t i = 1; i < v.size(); ++i)
    {
        Comparable tmp = v[i];
        for (j = i; j > 0 && tmp < v[j - 1]; --j)
            v[j] = v[j - 1];
        v[j] = tmp;
    }
}
/**
 * 为了传递Object类型，辅助三参数STL接口而写的 Insertion Sort
 * begin,end:迭代器
 * cmp:比较器
 * obj:基本元素类型
 */
template <typename Iterator, typename Comparator, typename Object>
void InsertionSort(const Iterator &begin, const Iterator &end, Comparator cmp, const Object &obj)
{
    Iterator j;
    for (Iterator i = begin + 1; i != end; ++i)
    {
        Object tmp = *i;
        for (j = i; j != begin && cmp(tmp, *(j - 1)); --j)
            *j = *(j - 1);
        *j = tmp;
    }
}
/**
 * 三参数STL接口 Insertion Sort
 */
template <typename Iterator, typename Comparator>
void InsertionSort(const Iterator &begin, const Iterator &end, Comparator cmp)
{
    if (begin != end)
        InsertionSort(begin, end, cmp, *begin);
}

/******************************** 谢尔(Shell)排序 平均O(N^(5/4))********************************/
/**
 * 谢尔(Shell)排序,重点在于增量序列
 */
template <typename Comparable>
void ShellSort(vector<Comparable> &v)
{
    for (size_t gap = (v.size() >> 1); gap > 0; gap >>= 1)
        for (size_t i = gap; i < v.size(); ++i)
        {
            Comparable tmp = v[i];
            int j = i;
            for (; j >= gap && tmp < v[j - gap]; j -= gap)
                v[j] = v[j - gap];
            v[j] = tmp;
        }
}
/******************************** 堆(优先队列)排序 平均O(NlogN)********************************/
/**
 * STL priority_queue实现的堆排序
 */
template <typename Comparable>
void HeapSortSTL(vector<Comparable> &v)
{
    priority_queue<Comparable, vector<Comparable>, greater<Comparable>> minPQ(v.begin(), v.end());
    for (size_t i = 0; i < v.size(); ++i, minPQ.pop())
        v[i] = minPQ.top();
    assert(minPQ.empty());
}

/**
 * 在堆中，返回下标为i的结点的左儿子下标
 */
inline int LeftChild(int i) { return 2 * i + 1; }
/**
 * 最大堆的下滤操作,build/delete heap时必做的操作
 * v:堆所在vector
 * hole:空穴下标
 * curSize:堆当前的逻辑大小
 */
template <typename Comparable>
void percolateDown(vector<Comparable> &v, int hole, int curSize)
{
    Comparable tmp = v[hole];
    int child;
    for (; LeftChild(hole) < curSize; hole = child) //无左儿子就停止
    {
        child = LeftChild(hole);
        if (child + 1 < curSize && v[child] < v[child + 1]) //有右儿子且较大（找较大的儿子）
            ++child;
        if (tmp < v[child]) //判断是否还需要下滤
            v[hole] = v[child];
        else
            break;
    }
    v[hole] = tmp;
}
/**
 * 不另外申请空间，直接在v上建堆，每次deleteMax放到v的最后位置
 */
template <typename Comparable>
void HeapSort(vector<Comparable> &v)
{
    for (int i = v.size() >> 1; i >= 0; --i) //建堆
        percolateDown(v, i, v.size());
    for (int j = v.size() - 1; j > 0; --j)
    {
        swap(v[0], v[j]); //交换既是为了下滤，也正好算删除了堆顶，且无需再申请空间
        percolateDown(v, 0, j);
    }
}
/******************************** 归并排序 最坏O(NlogN)********************************/
template <typename Comparable>
void MergeCombine(vector<Comparable> &v, vector<Comparable> &vnTmp, int nLeft, int nMid, int nRight)
{
    int nLeftPos = nLeft, nRightPos = nMid + 1, nTmpPos = nLeft;
    while (nLeftPos <= nMid && nRightPos <= nRight) //两个数组合并到一个数组
        if (v[nLeftPos] < v[nRightPos])
            vnTmp[nTmpPos++] = v[nLeftPos++];
        else
            vnTmp[nTmpPos++] = v[nRightPos++];
    while (nLeftPos <= nMid) //剩余的复制完
        vnTmp[nTmpPos++] = v[nLeftPos++];
    while (nRightPos <= nRight)
        vnTmp[nTmpPos++] = v[nRightPos++];
    for (int i = nLeft; i <= nRight; ++i) //复制回原来的vector
        v[i] = vnTmp[i];
}
/**
 * 归并的分,递归
 */
template <typename Comparable>
void MergeDivide(vector<Comparable> &v, vector<Comparable> &vnTmp, int nLeft, int nRight)
{
    if (nLeft < nRight)
    {
        int nMid = (nLeft + nRight) >> 1;
        MergeDivide(v, vnTmp, nLeft, nMid);
        MergeDivide(v, vnTmp, nMid + 1, nRight);
        MergeCombine(v, vnTmp, nLeft, nMid, nRight);
    }
}
/**
 * 归并排序的驱动函数
 */
template <typename Comparable>
void MergeSort(vector<Comparable> &v)
{
    vector<Comparable> vnTmp(v.size());
    MergeDivide(v, vnTmp, 0, v.size() - 1);
}

/******************************** 快速排序 平均O(NlogN)********************************/
/**
 * 插入排序，当数组长度较小（5-20），用插入排序比用快排好，因为没必要递归
 */
template <typename Comparable>
void InsertionSort(vector<Comparable> &v, int nLeft, int nRight)
{
    int j;
    for (int i = nLeft + 1; i <= nRight; ++i)
    {
        Comparable tmp = v[i];
        for (j = i; j > nLeft && tmp < v[j - 1]; --j)
            v[j] = v[j - 1];
        v[j] = tmp;
    }
}
/**
 * 三数中值分割,取left，middle和right三个值的中值作为枢纽元(pivot)
 * 且这三个值按大小顺序依次放在left，right-1和right位置上
 * 好处：快排核心中无需担心越界问题
 */
template <typename Comparable>
const Comparable &median3(vector<Comparable> &v, int nLeft, int nRight)
{
    int nMid = (nLeft + nRight) >> 1;
    if (v[nMid] < v[nLeft])
        swap(v[nMid], v[nLeft]);
    if (v[nRight] < v[nLeft])
        swap(v[nRight], v[nLeft]);
    if (v[nRight] < v[nMid])
        swap(v[nRight], v[nMid]);
    swap(v[nMid], v[nRight - 1]);
    return v[nRight - 1];
}
/**
 * 快排核心
 * 1.等于pivot都停住，为了在有很多相等元素时，保持左右两个集合平衡
 * 2.while时无需判断i<j,因为median3的处理方式确保了i和j不会越界
 * 3.前置++和--，可以确保在v[i]==pivot或v[j]==pivot时，不会陷入死循环
 */
template <typename Comparable>
void QuickSort(vector<Comparable> &v, int nLeft, int nRight)
{
    if (nLeft + 10 <= nRight)
    {
        Comparable pivot = median3(v, nLeft, nRight);
        int i = nLeft, j = nRight - 1;
        for (;;)
        {
            while (v[++i] < pivot)
                ;
            while (v[--j] > pivot)
                ;
            if (i < j)
                swap(v[i], v[j]);
            else
                break;
        }
        swap(v[i], v[nRight - 1]); //枢纽元放到正确位置
        QuickSort(v, nLeft, i - 1);
        QuickSort(v, i + 1, nRight);
    }
    else
        InsertionSort(v, nLeft, nRight);
}
template <typename Comparable>
void QuickSort(vector<Comparable> &v)
{
    QuickSort(v, 0, v.size() - 1);
}

/******************************** 间接排序 ********************************/
/**
 * 大的Comparable对象复制操作耗时严重，声明一个指针数组进行排序,
 * 最后根据已排序的指针数组，对原数组进行重排。这种做法最大限度减
 * 少复制次数
 */
template <typename Comparable>
void SortLargeObj(vector<Comparable> &v)
{
    vector<Comparable *> p(v.size()); //对指针数组排序
    for (size_t i = 0; i < v.size(); ++i)
        p[i] = &v[i];
    sort(p.begin(), p.end(), [](const Comparable *lhs, const Comparable *rhs) {
        return *lhs < *rhs;
    });
    int j, nextj;
    //遍历已排序的数组p，依此顺序安放v元素
    for (int i = 0; i < v.size(); ++i)
    {
        if (p[i] != &v[i]) //如果位置不对应
        {
            Comparable tmp = v[i];
            //以指针索引与元素索引不对应而构成的循环遍历，把元素放到正确的位置
            for (j = i; p[j] != &v[i]; j = nextj)
            {
                nextj = p[j] - &v[0]; //p[j]所指对象的索引
                v[j] = *p[j];         //安放到正确位置
                p[j] = &v[j];         //安放正确后要更改p[j]，外循环遍历到的时候才知道是正确的了
            }
            v[j] = tmp;
            p[j] = &v[j];
        }
    }
}

template <typename Object>
void PrintVec(const vector<Object> &v)
{
    for (auto x : v)
        cout << x << " ";
    cout << endl;
}

int main(int argc, char *argv[])
{
    vector<int> input({34, 8, 64, 65, 32, 21, 15, 27, 12, 101, 54, 72, 88, 66, 17});
    PrintVec(input);

    // InsertionSort(input);
    // InsertionSort(input.begin(), input.end(), greater<int>());
    // InsertionSort(input.begin(), input.end(), less<int>());

    // ShellSort(input);

    // HeapSortSTL(input);
    // HeapSort(input);

    // MergeSort(input);

    // QuickSort(input);

    SortLargeObj(input);
    PrintVec(input);
}