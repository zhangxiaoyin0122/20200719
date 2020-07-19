#include <iostream>
#include <vector>
using namespace std;

class BitMap {
	BitMap(size_t range) {
		_bit.resize(range / 32+1);
	}
	//查找:查看对应比特位是否为1
	bool Test(size_t n) {
		int idx = n / 32;
		int BitIdx = n % 32;
		if ((_bit[idx] >> BitIdx)&1)
			return true;
		else 
			return false;
	}
	//插入:对应比特位 置为1,其它位不变
	void Set(size_t n) {
		int idx = n / 32;
		int BitIdx = n % 32;
		_bit[idx] |= (1 << BitIdx);
	}
	//删除:对应比特位置为0,其它位不变
	void Reset(size_t n) {
		int idx = n / 32;
		int BitIdx = n % 32;
		_bit[idx] &= ~(1 << BitIdx);
	}


private:
	vector<int> _bit;
};


template<class T,class HF1,class HF2,class HF3>
class BloomFilter {
	BloomFilter(size_t num)
		:_bit(5 * num)
		,BitCount(5 * num) 
	{}
	//查找:
	bool Test(const T& value) {
		HF1 hf1;
		HF2 hf2;
		HF3 hf3;
		//计算哈希值
		size_t hashCode1 = hf1(value);
		size_t hashCode2 = hf2(value);
		size_t hashCode3 = hf3(value);

		_bit.Set(hashCode1 % _bitCount);
		_bit.Set(hashCode2 % _bitCount);
		_bit.Set(hashCode3 % _bitCount);
	}
	//插入:
	void Set(const T& value) {
		HF1 hf1;
		size_t hashCode1 = hf1(value);
		if (!_bit.Test(hashCode1 % _bitCount))
			return false;
		HF2 hf2;
		size_t hashCode2 = hf2(value);
		if (!_bit.Test(hashCode2 % _bitCount))
			return false;
		HF3 hf3;
		size_t hashCode3 = hf3(value);
		if (!_bit.Test(hashCode3 % _bitCount))
			return false;

		//返回true: 不一定正确
		return true;
	}
	

private:
	BitMap _bit;
	size_T BitCount;
};