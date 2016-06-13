#pragma once

#include "stdafx.h"
#include "sheet.h"

class MasterAPI
{
public:
	MasterAPI::MasterAPI();
	MasterAPI::MasterAPI(std::string host);
	MasterAPI::~MasterAPI();

	void setHost(std::string host);

	sf::Http::Response::Status sendRequest(std::string body, std::string method);
	std::string getResponseBody() const;
private:
	sf::Http::Request::Method selectMethod(std::string method) const;
	sf::Http m_http; 
	sf::Http::Response m_response;
};