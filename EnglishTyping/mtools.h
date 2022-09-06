#pragma once
#include <QString>

class mtools {
public:
	mtools();
	~mtools();

	static bool IsEnglish(QString str)
	{
		QByteArray ba = str.toLatin1();
		const char *ch = ba.data();
		while (*ch) {
			if ((*ch >= 'A' && *ch <= 'Z') || (*ch >= 'a' && *ch <= 'z')){

			}
			else {
				return false;
			}

			ch++;
		}

		return true;

	}
};

