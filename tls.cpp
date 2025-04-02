
#include <stdlib.h>
#include <stdio.h>

#define __USE_INLINE__

#include <proto/exec.h>

int tls_size = 0;

template <typename T> struct tls 
{
	int offset;

	tls()
	{
		offset = tls_size;
		tls_size += sizeof(T);
	}

	T Equals()
	{
		struct Task *me = FindTask(NULL);
		T *var = (T *) ((char *) me -> tc_UserData + offset) ;
		return *var;
	}

	T operator() () // This one is not working...
	{
		printf("get\n");
		return 10;
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

	T *operator&()
	{
		struct Task *me = FindTask(NULL);
		T *var = (T *) ((char *) me -> tc_UserData + offset) ;
		return var;
	}
};

tls<int> hello ;
tls<char> dick;

int main()
{
	struct Task *me;

	printf("count tls: %ld\n", tls_size);

	me = FindTask(NULL);

	me -> tc_UserData = malloc(tls_size);	// make thread local space.

	dick = 2;
	hello = 4;

	hello += 2;

	printf("Has value: %ld\n", hello);

	printf("%ld\n", *((int *) &hello));

	printf("%ld\n", *((char *) &dick));

	free( me -> tc_UserData );

	return 0;
}

