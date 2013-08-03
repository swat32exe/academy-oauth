#ifndef _SIMPLEREQUESTSENDER_H
#define _SIMPLEREQUESTSENDER_H

#include <string>

#include <HttpRequest.h>

std::string sendRequest(const OAuth::HttpRequest &httpRequest);

#endif
