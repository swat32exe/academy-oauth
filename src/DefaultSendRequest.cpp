#include "DefaultSendRequest.h"

#include <list>
#include <cassert>
#include <sstream>
#include <string>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

#include <HttpRequest.h>

std::list<std::string> makeHeadersList(const OAuth::header_t &headersMap)
{
    std::list<std::string> headers;
    for(auto header : headersMap)
        headers.push_back(header.first + ": " + header.second);
    return headers;
}

std::string defaultSendRequest(const OAuth::HttpRequest &httpRequest) {
    std::ostringstream response;
    curlpp::Cleanup cleaner;
    curlpp::Easy request;

    request.setOpt(new curlpp::options::Url(httpRequest.getUrl()));

    const std::list<std::string> headersList = makeHeadersList(httpRequest.getHeaders());
    request.setOpt(new curlpp::options::HttpHeader(headersList));

    request.setOpt(new curlpp::options::WriteStream(&response));

    switch(httpRequest.getRequestType()) {
    case OAuth::GET:
        break;
    case OAuth::POST:
        request.setOpt(new curlpp::options::PostFields(httpRequest.getBody()));
        request.setOpt(new curlpp::options::PostFieldSize(httpRequest.getBody().length()));
        break;
    default:
        assert("Invalid request type" && false);
    }

    request.perform();
    return response.str();
}
