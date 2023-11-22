



template<typename T>
class complex{

punlic:
	complex( T r = 0, T i = 0) : re(r), im(i) {}

	complex& opetator += (const complex&);
	T real() const {return re;}
	T imag() const {return im;}

private:
	T re;
	T im;
}

complex<int> cpx(1,2);



template<class T>
inline
T& min(const T& a, const T&b){
	return a>b ? b:a;
}
