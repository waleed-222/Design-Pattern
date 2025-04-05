#include<iostream>
#include <string>
class HttpRequest{
public:
    HttpRequest(const std::string &method,const std::string &url,
                const std::string &headers,const std::string &body)
                :method(method),url(url),headers(headers),body(body){}
    void send()const{
        std::cout<<"Sending HTTP Request:\n"
                 <<"Method:"<<method<<"\n"
                 <<"URL:"<<url<<"\n"
                 <<"Headers"<<headers<<"\n"
                 <<"Body"<<body<<"\n";
    }

private:
std::string method;
std::string url;
std::string headers;
std::string body;

friend class HttpRequestBuilder;
};
class HttpRequestBuilder{
public:
HttpRequestBuilder &setMethod(const std::string& method){
    this->method=method;
    return *this;
}
HttpRequestBuilder &setUrl(const std::string& url){
    this->url=url;
    return *this;
}
HttpRequestBuilder &setHeaders(const std::string& headers){
    this->headers=headers;
    return *this;
}
HttpRequestBuilder &setBody(const std::string& body){
    this->body=body;
    return *this;
}
HttpRequest build()const{return HttpRequest(method,url,headers,body);}
private:
std::string method= "GET";
std::string url="/";
std::string headers="";
std::string body="";
};

int main(){
    HttpRequest request=HttpRequestBuilder()
                        .setMethod("Post")
                        .setUrl("http://example.com/api")
                        .setHeaders("Content-Type:application/json")
                        .setBody(R"({"key":"value"})")
                        .build();
    return 0;
}