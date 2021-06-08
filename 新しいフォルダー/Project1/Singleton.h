#pragma once
class Singleton
{
public:
	static Singleton& GetInstance() {
		static Singleton sinstance_;
		return sinstance_;
	}
	void OutputLife();
private:
	Singleton();
	~Singleton();
	// �R�s�[�E����֎~
	Singleton(const Singleton&) = delete;
	void operator= (const Singleton&) = delete;

	int life_;
};

