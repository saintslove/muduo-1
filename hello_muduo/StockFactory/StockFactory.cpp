#include <iostream>
#include "boost/noncopyable.hpp"
#include "boost/thread/mutex.hpp"
#include "boost/thread/lock_guard.hpp"
#include "boost/shared_ptr.hpp"
#include "boost/weak_ptr.hpp"
#include "boost/bind.hpp"
#include "boost/enable_shared_from_this.hpp"
#include <map>
#include <vector>

using namespace std;

class stock

{
public:
	stock(const char* key);
	~stock();
	const char* key()
	{
		return mKey.c_str();
	}
private:
	std::string mKey;
};

stock::stock(const char* key)
	:mKey(key)
{

}

stock::~stock()
{

}

class stockFactory : public boost::enable_shared_from_this<stockFactory>,
					boost::noncopyable
{
public:
	boost::shared_ptr<stock> get(const char* key);
private:
	void deleteStock(stock* stock_);
	static void weakDelete(boost::weak_ptr<stockFactory>& wkFactory, stock* stock_);
private:
	boost::mutex lock;
	std::map<std::string, boost::weak_ptr<stock>> stock_;
};

void stockFactory::weakDelete(boost::weak_ptr<stockFactory>& wkFactory, stock* stock_)
{
	boost::shared_ptr<stockFactory>factory(wkFactory.lock());
	if (factory) {
		factory->deleteStock(stock_);
	}
}


void stockFactory::deleteStock(stock* mStock)
{
	if (mStock) {
		boost::lock_guard<boost::mutex> guard(lock);
		stock_.erase(mStock->key());
	}
	delete mStock;
}

boost::shared_ptr<stock> stockFactory::get(const char* key)
{
	boost::lock_guard<boost::mutex> guard(lock);
	boost::weak_ptr<stock>& wkstock = stock_[key];
	boost::shared_ptr<stock> pstock = wkstock.lock();
	if (!pstock) {
		//可能存在stockFactory寿命比stock短，调用回调造成this（stockFactory）指针无效，core dump
		//pstock.reset(new stock(key),boost::bind(&stockFactory::deleteStock,this,_1));

		//shared_from_this造成stockFactory寿命延长，保证回调时，stockFactory对象肯定有效
		//pstock.reset(new stock(key), boost::bind(&stockFactory::deleteStock, shared_from_this(), _1));
		
		//采用弱引用，bind对象,尝试提升stockFactory，失败说明stockFactory已经销毁
		pstock.reset(new stock(key), boost::bind(&stockFactory::weakDelete, boost::weak_ptr<stockFactory>(shared_from_this()), _1));
		
		wkstock = pstock;
	}
	return pstock;
}


void testLongFactory()
{
	boost::shared_ptr<stockFactory> factory(new stockFactory);
	{
		boost::shared_ptr<stock> stock1 = factory->get("NYSE:IBM");
		boost::shared_ptr<stock> stock2 = factory->get("NYSE:IBM");
		assert(stock1 == stock2);
	}
}

void testShortFactory()
{
	boost::shared_ptr<stock> stock1;
	{
		boost::shared_ptr<stockFactory> factory(new stockFactory);
		stock1 = factory->get("NYSE:IBM");
		boost::shared_ptr<stock> stock2 = factory->get("NYSE:IBM");
		assert(stock1 == stock2);
	}
}


class X : public boost::enable_shared_from_this<X>, boost::noncopyable
{
public:
	~X()
	{
		std::cout << this << std::endl;
		std::cout << "delete X" << std::endl;
	}
	/*void add()
	{
		x = shared_from_this();
		count();
		xSet.push_back(shared_from_this());
		count();
	}
	void deleteX()
	{
		count();
		xSet.pop_back();
		count();
	}
	void count()
	{
		std::cout << x.use_count() << std::endl;
	}*/
private:
	boost::shared_ptr<X> x;
	std::vector<boost::shared_ptr<X>> xSet;
};


int main(int argc, char *argv[])
{
	/*boost::shared_ptr<int> a(new int(1));
	boost::shared_ptr<int> b(a);
	std::cout << b.use_count() << std::endl;*/
	//testLongFactory();
	//testShortFactory();
	/*std::map<std::string, std::string> maps;
	std::cout << "maps[\"1\"] = " << maps["1"].length() << std::endl;*/
	boost::shared_ptr<X> x(new X);
	std::cout << x.use_count() << std::endl;
	std::cout << x->shared_from_this().use_count() << std::endl;
	boost::shared_ptr<X> y = x->shared_from_this();
	std::cout << y.use_count() << std::endl;
	std::cout << x.use_count() << std::endl;
	std::cout << "x = " << x << std::endl;
	std::cout << "y = " << y << std::endl;
	/*x->count();
	x->add();
	x->deleteX();
	x->count();*/
	return 0;
}