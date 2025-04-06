
#include <stdlib.h>
#include <stdio.h>

#define __USE_INLINE__

#include <proto/exec.h>

int tls_size = 0;

#define align_size 4

#define max(a,b) ((a)>(b)?(a):(b))

template <typename T> struct tls 
{
	int offset;

	tls()
	{
		offset = tls_size;
		tls_size += max(sizeof(T),align_size);
	}

	// Implicit convertion to T
	operator T() const
	{
		struct Task *me = FindTask(NULL);
		T *var = (T *) ((char *) me -> tc_UserData + offset) ;
		return *var;
	}

	// Also useful: regernce acccess.
	int &operator()()
	{
		struct Task *me = FindTask(NULL);
		T *var = (T *) ((char *) me -> tc_UserData + offset) ;
		return *var;
	}

	T *operator&()
	{
		struct Task *me = FindTask(NULL);
		T *var = (T *) ((char *) me -> tc_UserData + offset) ;
		return var;
	}

	bool operator==(T &other)
	{
		struct Task *me = FindTask(NULL);
		T *var = (T *) ((char *) me -> tc_UserData + offset) ;
		return (*var == other);
	}

	void operator=(T value)
	{
		struct Task *me = FindTask(NULL);
		T *var = (T *) ((char *) me -> tc_UserData + offset) ;
		*var = value;

		printf("value is %ld\n",value);
	}

	void operator+=(T value)
	{
		struct Task *me = FindTask(NULL);
		T *var = (T *) ((char *) me -> tc_UserData + offset) ;
		*var += value;	
	}

	void operator*=(T value)
	{
		struct Task *me = FindTask(NULL);
		T *var = (T *) ((char *) me -> tc_UserData + offset) ;
		*var *= value;	
	}

	void operator<<=(T value)
	{
		struct Task *me = FindTask(NULL);
		T *var = (T *) ((char *) me -> tc_UserData + offset) ;
		*var <<= value;	
	}

	void operator>>=(T value)
	{
		struct Task *me = FindTask(NULL);
		T *var = (T *) ((char *) me -> tc_UserData + offset) ;
		*var >>= value;	
	}

	void operator/=(T value)
	{
		struct Task *me = FindTask(NULL);
		T *var = (T *) ((char *) me -> tc_UserData + offset) ;
		*var /= value;	
	}

	void operator-=(T value)
	{
		struct Task *me = FindTask(NULL);
		T *var = (T *) ((char *) me -> tc_UserData + offset) ;
		*var -= value;	
	}
};

tls<int> hello ;
tls<char> dick;

void assert_value( const char *description, int output, int expected )
{
	printf( "%s: %s\n",description,  (output == expected) ? "Success" : "Failed");
}

int main()
{
	struct Task *me;

	printf("size of tls buffer: %ld\n", tls_size);

	me = FindTask(NULL);

	me -> tc_UserData = malloc(tls_size);	// make thread local space.

	dick = 2;
	hello = 4;
	hello += 2;

	assert_value( "objcet should return a integer value", hello, 6 );
	assert_value( "reference of object should return a correct address, and give expected value", *((int *) &hello), 6);

	printf("%ld\n", *((char *) &dick));

	free( me -> tc_UserData );

	return 0;
}

