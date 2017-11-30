#include "Cboard.h"

class AIengine {
public:
	AIengine(){};
	Cboard gboard;
	int start_flag;
	void Api_init(int size);
	void Api_mymove(int x, int y);
	void Api_oppomove(int x, int y);
	void Api_makemove(int &x, int &y);
	void Api_inputmodify(int &x, int &y);
	void Api_outputmodify(int &x, int &y);
	void Api_set_turntime(int timeml);
	void Api_printboard();
	void Api_takeback();
	void Api_debug();
};