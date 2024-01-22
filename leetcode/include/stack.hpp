#ifndef LEETCODE_STACK_HPP
#define LEETCODE_STACK_HPP

#define STACKSIZE 5000

struct Stack
{
private:
	char backingArr[STACKSIZE] = { 0 };
	int _i = -1;
public:
	void Push(const char ch)
	{
		if (_i > STACKSIZE - 2)
			return;
		backingArr[++_i] = ch;
	}

	char Pop(void)
	{
		if (_i < 0)
			return 0;
		else
			return backingArr[_i--];
	}

	bool IsEmpty()
	{
		return _i < 0;
	}
};

#endif