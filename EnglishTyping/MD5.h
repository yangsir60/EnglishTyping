#include <iostream>
#include <windows.h>
using namespace std;
typedef unsigned char uchar;
typedef unsigned long ulong;

//步函数
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
//循环左移
#define ROL(x, n) (((x) << (n)) | ((x) >> (32-(n))))
//  四轮操作
#define FF(a, b, c, d, mj, s, ti) { (a) += F ((b), (c), (d)) + (mj) + ti; (a) = ROL ((a), (s)); (a) += (b);}
#define GG(a, b, c, d, mj, s, ti) { (a) += G ((b), (c), (d)) + (mj) + ti; (a) = ROL ((a), (s)); (a) += (b);}
#define HH(a, b, c, d, mj, s, ti) { (a) += H ((b), (c), (d)) + (mj) + ti; (a) = ROL ((a), (s)); (a) += (b);}
#define II(a, b, c, d, mj, s, ti) { (a) += I ((b), (c), (d)) + (mj) + ti; (a) = ROL ((a), (s)); (a) += (b);}

class MD5 {
public:
	MD5(const string& str);
	const uchar* getDigest();	// 获取生成的摘要
	string outstr(int);			// 返回字符串
private:
	void generate(const uchar* input, int length);
	void change(const uchar block[64]);							// 四轮操作
	void encode(const ulong* input, uchar* output, int length);	// uchar to ulong
	void decode(const uchar* input, ulong* output, int length); // ulong to uchar

	ulong reg[4];		// ABCD
	ulong count[2];	    // 长度扩充
	uchar buffer[64];	// 输入buffer
	uchar digest[16];	// 生成的摘要
	bool end_flag;		// 结束标志
	static const uchar padding[64];
	static const char hex[16];
};
