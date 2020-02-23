#include <string>
#include <iostream>
using namespace std;

struct Pingable
{
	virtual ~Pingable() = default;
	virtual wstring ping(const wstring& message) = 0;
};

struct Pong : Pingable
{
	wstring ping(const wstring& message) override
	{
		return message + L" pong";
	}
};

#include <cpprest/http_client.h>
using namespace web;                        // Common features like URIs.
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::client;          // HTTP client features

struct RemotePong : Pingable
{
    wstring ping(const wstring& message) override
    {
        //wstring result;
        http_client client(U("http://localhost:9149/"));
        uri_builder builder(U("/api/pingpong/"));
        builder.append(message);
        pplx::task<wstring> task = client.request(methods::GET, builder.to_string())
            .then([=](http_response r)
        {
            return r.extract_string();
        });
        task.wait();
        return task.get();
    }
};

void try_it(Pingable& p)
{
	wcout << p.ping(L"ping") << "\t";
}

int main()
{
	//Pong pp;
    RemotePong pp;
	for (size_t i = 0; i != 10; i++)
	{
		try_it(pp);
	}

	return 0;
}