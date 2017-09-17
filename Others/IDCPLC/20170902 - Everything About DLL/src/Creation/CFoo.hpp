/**
Declaring a class
This class will be exported to DLL
*/

#ifdef  __EXPORT_CLASS_
#define DECLARE __declspec( dllexport )
#else
#define DECLARE __declspec( dllexport )
#endif

class DECLARE CFoo
{
private:
	char m_internal[64];
public:
	CFoo();
	
	int add(int i, int j);
	int sub(int i, int j);
	char * last_function();
};