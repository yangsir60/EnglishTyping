#include <iostream>
#include <windows.h>
using namespace std;
typedef unsigned char uchar;
typedef unsigned long ulong;

//������
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))
//ѭ������
#define ROL(x, n) (((x) << (n)) | ((x) >> (32-(n))))
//  ���ֲ���
#define FF(a, b, c, d, mj, s, ti) { (a) += F ((b), (c), (d)) + (mj) + ti; (a) = ROL ((a), (s)); (a) += (b);}
#define GG(a, b, c, d, mj, s, ti) { (a) += G ((b), (c), (d)) + (mj) + ti; (a) = ROL ((a), (s)); (a) += (b);}
#define HH(a, b, c, d, mj, s, ti) { (a) += H ((b), (c), (d)) + (mj) + ti; (a) = ROL ((a), (s)); (a) += (b);}
#define II(a, b, c, d, mj, s, ti) { (a) += I ((b), (c), (d)) + (mj) + ti; (a) = ROL ((a), (s)); (a) += (b);}

class MD5 {
public:
	MD5(const string& str);
	const uchar* getDigest();	// ��ȡ���ɵ�ժҪ
	string outstr(int);			// �����ַ���
private:
	void generate(const uchar* input, int length);
	void change(const uchar block[64]);							// ���ֲ���
	void encode(const ulong* input, uchar* output, int length);	// uchar to ulong
	void decode(const uchar* input, ulong* output, int length); // ulong to uchar

	ulong reg[4];		// ABCD
	ulong count[2];	    // ��������
	uchar buffer[64];	// ����buffer
	uchar digest[16];	// ���ɵ�ժҪ
	bool end_flag;		// ������־
	static const uchar padding[64];
	static const char hex[16];
};
