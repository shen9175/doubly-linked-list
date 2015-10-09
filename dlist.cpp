#include <iostream>
#include <random>
#include "dlist.h"

using namespace std;

template <typename T> void test(Dlist<T> testobj);
int main()
{
	Dlist<int> a;
	Dlist<double> b;
	test(a);
	test(b);

	cout<<"Now testing initialization list initialiazation"<<endl;
	Dlist<int> c={23,45,23,123,56,23};
	Dlist<double> d={32.23,324.2334,876.323456,3213.0983,998.9645};
	c.print();
	d.print();
	return 0;
}



template <typename T> void test(Dlist<T> testobj)
{
	
	default_random_engine e;
	uniform_real_distribution<double> u(0,9);


	try{
		cout<<"Now testing default initialization:"<<endl;
		cout<<"There are "<<testobj.size()<<" element(s) in the default initialization object."<<endl;
		cout<<"There are :";
		testobj.printlink();
		testobj.print();
		cout<<"Default initialiazation test passed!"<<endl<<endl;

		cout<<"Now testing push_back() function:"<<endl;
		T temp;
		for(unsigned char i=0;i<10;++i)
			{
			temp=u(e);
			testobj.push_back(temp);
			cout<<"Generated random number: "<<temp<<". Put it into the list."<<endl;
			cout<<"Now the list is:"<<endl;
			testobj.printlink();
			testobj.print();
			}

		cout<<"Now testing clear() function:"<<endl;
		testobj.clear();
		testobj.printstatus();
		cout<<"clear() function testing passed!"<<endl;
		

		cout<<"Now testing push front insert(T x) function:"<<endl;
		for(unsigned char i=0;i<10;++i)
		{
			temp=u(e);
			testobj.insert(temp);
			cout<<"Generated random number: "<<temp<<". Put it into the list."<<endl;
			cout<<"Now the list is:"<<endl;
			testobj.printlink();
			testobj.print();
		}

		cout<<"Now testing insert an element at specific location:"<<endl;
		cout<<"Please input an element which the generated number will be put before this input element:"<<endl;
		cin>>temp;
		do 
		{
			if(temp<0) break;
			typename Dlist<T>::iter tempiter=testobj.search(temp);
			if(tempiter==nullptr)
				throw runtime_error("Not found the location in the list, try again!");
			else
				{
				temp=u(e);
				cout<<"Generated random number: "<<temp<<". Put it before "<<tempiter->key<<endl;
				testobj.insert(tempiter,temp);
				cout<<"Now the list is:"<<endl;
				testobj.printlink();
				testobj.print();
				}

			cout<<"Please input an element which the generated number will be put before this input element:"<<endl;
		}while(cin>>temp);


		cout<<"Now testing insert n same elements at specific location:"<<endl;
		cout<<"Please input an element which the generated numbers will be put before this input element:"<<endl;
		cin>>temp;
		cout<<"Please input how many duplicated numbers do you want to put into:"<<endl;
		typename Dlist<T>::size_type number;
		cin>>number;
		do
		{
			if(temp<0||number<0) break;
			typename Dlist<T>::iter tempiter=testobj.search(temp);
			if(tempiter==nullptr)
				throw runtime_error("Not found the location in the list, try again!");
			else
				{
					if(number<0)
						throw runtime_error("The number of insert element should not be negative,try again!");
					else
					{
					temp=u(e);
					cout<<"Generated random number: "<<temp<<". Put "<<number<<" of them before "<<tempiter->key<<endl;
					testobj.insert(tempiter,number,temp);
					cout<<"Now the list is:"<<endl;
					testobj.printlink();
					testobj.print();
					}
				}
		cout<<"Please input an element which the generated numbers will be put before this input element and how many duplicated number do you want to put into:"<<endl;
		}while(cin>>temp>>number);



		T starting,ending;
		cout<<"Now testing erase(b,e) function:"<<endl;
		cout<<"Please input the starting element and ending element to be erased in the list:"<<endl;
		cin>>starting>>ending;

		do
		{
			if(starting<0||ending<0) break;
			typename Dlist<T>::iter b,e;
			b=testobj.search(starting);
			e=testobj.search(ending);
			if(b==nullptr||e==nullptr)
				throw runtime_error("Starting or ending element not found,try again!");
			else
				{
				switch(testobj.validate_b_e(b,e))
				{
					case 1:
						cout<<"Now erasing..."<<endl;
						testobj.erase(b,e);
						break;
					case -1:
						cout<<"Starting and Ending are reversed but it's ok: Now erasing..."<<endl;
						testobj.erase(e,b);
						break;
					case 0:
						throw runtime_error("Starting or ending element not found,try again!");
						break;
					default:
						throw runtime_error("Should not be here in default case!");
						break;
				}
				cout<<"Finish erasing list, now the list is:"<<endl;
				testobj.printlink();
				testobj.print();
				}
			cout<<"Please input the starting element and ending element to be erased in the list:"<<endl;
		}while(cin>>starting>>ending);


		
	   }
	catch(runtime_error err)
		{
		cerr<<err.what()<<endl;
		}


	Dlist<T> l2(testobj);
	Dlist<T> l3;
	l3=l2;
	cout<<"Now testing the copy assignement and assignment operator!"<<endl;
	cout<<"The copy constructor assigned l2 from l, the l2 is:"<<endl;
	l2.print();
	cout<<"The assignment operator: l3=l2. the l3 is:"<<endl;
	l3.print();

} 
