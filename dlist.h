#ifndef DLIST_H
#define DLIST_H

#include <stdexcept>
#include <initializer_list>
#include <memory>
#include <cmath>






template <typename T> class Dlist
{
private:
	struct node
	{
	T key;
	std::shared_ptr<node> prev;
	std::shared_ptr<node> next;
	};
	std::shared_ptr<node> head,tail;
public:
	using iter=std::shared_ptr<node>;
	using size_type=std::size_t;
	Dlist(){head=nullptr;tail=nullptr;size_count=0;}
	Dlist(std::initializer_list<T> il);
	Dlist(const Dlist&);
	Dlist& operator=(const Dlist&);
	~Dlist();
	iter search(const T& x);
	void push_back(const T& x);
	void insert(const T& x);//insert at front
	iter insert(const iter& p,const size_type& n,const T& x);
	iter insert(const iter& p,const T& x);
	iter insert(const iter& p,std::initializer_list<T> il);
	iter erase(const iter& p);
	iter erase(const T& x);
	char validate_b_e(const iter& b, const iter& e);
	iter erase(const iter& b, const iter& e);
	void clear();
	iter begin(){return head;}
	iter end(){return tail->next;}
	const iter cbegin() const {return head;}
	const iter cend() const {if(tail==nullptr) return nullptr; else return tail->next;}
	size_type size(){return size_count;}
	bool empty(){return true?false:size_count==0,size_count!=0;}
	void print();
	void printlink();
	void printstatus();
private:
	size_type size_count;
	double fpRound(const double & num, const unsigned int& dec);

};

template <typename T> double Dlist<T>::fpRound(const double& num, const unsigned int & dec)
{
	unsigned int digit=pow(10,dec);
	double ret=floor(num*digit+0.5)/digit;
	return ret;
}
template <typename T> Dlist<T>::Dlist(std::initializer_list<T> il)
{
	for(auto it=il.begin();it!=il.end();++it)
	{
		push_back(*it);
	}
}

template <typename T> Dlist<T>::Dlist(const Dlist& dlst)
{
	head=nullptr;tail=nullptr;size_count=0;
	std::shared_ptr<Dlist<T>::node> p=dlst.cbegin();
	while(p!=dlst.cend())
	{
		push_back(p->key);
		p=p->next;
	}

}

template <typename T> Dlist<T>& Dlist<T>::operator=(const Dlist& dlst)
{
	head=nullptr;tail=nullptr;size_count=0;
	auto p=dlst.cbegin();
	while(p!=dlst.cend())
	{
		push_back(p->key);
		p=p->next;
	}
	return *this;
}

template <typename T> Dlist<T>::~Dlist()
{
	clear();
}

template <typename T> typename Dlist<T>::iter Dlist<T>::search(const T& x)
{
	auto p=head;
	while(p!=nullptr&&p->key!=x)
		p=p->next;

	if(p==nullptr)//probably is double, the input x is not precise as p->key, so give another chance.
	{
	p=head;
	while(p!=nullptr&&fpRound(x,4)!=fpRound(p->key,4))
		p=p->next;
	}
	return p;
}

template <typename T> void Dlist<T>::insert(const T& x)
{
	if(head==nullptr)
		{
			head=std::make_shared<node> ();
			head->key=x;
			head->prev=nullptr;
			head->next=nullptr;
			tail=head;
		}
	else
		{
			auto p=std::make_shared<node>();
			p->key=x;
			p->prev=nullptr;
			p->next=head;
			p->next->prev=p;
			head=p;
		}
	++size_count;
}
template <typename T> void Dlist<T>::push_back(const T& x)
{
	
	if(head==nullptr)
		{
			head=std::make_shared<node> ();
			head->key=x;
			head->prev=nullptr;
			head->next=nullptr;
			tail=head;
		}
	else
		{
			tail->next=std::make_shared<node>();
			tail->next->key=x;
			tail->next->prev=tail;
			tail->next->next=nullptr;
			tail=tail->next;
		}
	++size_count;
}

template <typename T> typename Dlist<T>::iter Dlist<T>::insert(const iter& p,const T& x)
{
		iter ret=nullptr;
		if(head==nullptr)
			throw std::runtime_error("The list is empty!");
		else
		{
		auto it=head;
		while(it!=nullptr&&it!=p)
			it=it->next;
		if(it==nullptr)
			throw std::runtime_error("There is not such an iterator to insert!");
		else
			{
				auto n=std::make_shared<node>();
				n->key=x;
				n->prev=it->prev;
				n->next=it;
				it->prev=n;
				n->prev->next=n;
				ret=n;
				++size_count;
			}
		}
		return ret;
}


template <typename T> typename Dlist<T>::iter Dlist<T>::insert(const iter& p,const size_type& n,const T& x)
{
//	if(n==0)
//		return p;
//	else
//		{
			auto ret=p;
			for(auto i=0;i<n;++i)
				{
					ret=insert(ret,x);
				}
			return ret;
//		}
}

template <typename T> typename Dlist<T>::iter Dlist<T>::erase(const iter& p)
{
	iter ret=nullptr;
	if(head==nullptr)
		throw std::runtime_error("The list is empty!");
	else
		{
			if(p==head)
				{
					head=head->next;
					p->next=nullptr;//original head's next is null
					if(head!=nullptr)
						head->prev=nullptr;
					else//there is only one element in the list-->original head
						tail=nullptr;

					ret=head;
				}
			else if(p==tail)
				{
					tail=p->prev;
					tail->next=nullptr;
					p->prev=nullptr;
					ret=nullptr;
				}
			else
				{
					ret=p->next;
					p->prev->next=p->next;
					p->next->prev=p->prev;
					p->prev=nullptr;
					p->next=nullptr;
					
				}
		}
		--size_count;

		return ret;
}
template <typename T> typename Dlist<T>::iter Dlist<T>::erase(const T& x)
{
	auto p=search(x);
	if(p!=nullptr)
		return erase(p);
	else
		throw std::runtime_error("There is no such an element");
}
template <typename T> char Dlist<T>::validate_b_e(const iter& b, const iter& e)
{
	char ret;
	auto p=b;
	while(p!=e && p!=nullptr)
		p=p->next;
	if(p==nullptr)//e is not after b:maybe e is before b
	{
		p=b;
		while(p!=e && p!=nullptr)
			p=p->prev;
		if(p==nullptr)
			ret=0;//can't be deleted through b to e
		else
			ret=-1;//reverse order: e is starting, b is ending
	}
	else
		ret=1;//normal order: e is ending, b is beginning

	return ret;
}
template <typename T> typename Dlist<T>::iter Dlist<T>::erase(const iter& b, const iter& e)
{
	iter ret=nullptr;
	if(e!=nullptr)
	{
	//for(auto i=b;i!=e->next;i=i->next)
		auto i=b;
		auto saved_e_next=e->next;//e->next will be erased before loop termination condition: i==e->next
		while(i!=saved_e_next)
		{
			i=erase(i);
			//i=i->next;  i is erased so i->next=0x0
		}
		ret=i;
	}
	else
	{
	//for(auto i=b;i!=e;i=i->next)
		auto i=b;
		//auto saved_e=e;
		//while(i!=e)
		while(i!=nullptr)//e==nullptr in this condition
		{
			i=erase(i);
			//i=i->next;
		}
		ret=i;
	}
	return ret;
}
template <typename T> void Dlist<T>::clear()
{
	if(head!=nullptr)
	{
	auto p=head;
	while(p->next!=nullptr)
		{
		p=p->next;
		p->prev->prev=nullptr;
		p->prev->next=nullptr;
		p->prev=nullptr;
		}
		head=nullptr;
		tail=nullptr;
		size_count=0;
	}
	else//head==nullptr should be empty list, check this
	{
		if(tail!=nullptr||size_count!=0)
			throw std::runtime_error("The list head is NULL, but the list is not empty!");
	}
}
template <typename T> void Dlist<T>::print()
{
	auto p=head;
	while(p!=nullptr)
		{
		std::cout<<p->key<<" ";
		p=p->next;
		}
		std::cout<<std::endl;
}

template <typename T> void Dlist<T>::printlink()
{
	auto p=head;
	while(p!=nullptr)
		{
		std::cout<<p->prev<<"--"<<p->key<<"("<<p<<")"<<"--"<<p->next;
		if(p->next!=nullptr) std::cout<<"--->";
		p=p->next;
		}
		std::cout<<std::endl;
}

template <typename T> void Dlist<T>::printstatus()
{
		std::cout<<"There are "<<size()<<" element(s) in the this object."<<std::endl;
		std::cout<<"There are :";
		printlink();
}

#endif
