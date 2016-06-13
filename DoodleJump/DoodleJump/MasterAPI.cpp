#pragma once

#include "stdafx.h"
#include "sheet.h"

MasterAPI::MasterAPI()
{

}

MasterAPI::MasterAPI(std::string host)
{
	setHost(host);
}

MasterAPI::~MasterAPI()
{

}

void MasterAPI::setHost(std::string host)
{
	m_http.setHost(host);
}

sf::Http::Request::Method MasterAPI::selectMethod(std::string method) const
{
	if (method == "GET")
	{
		return sf::Http::Request::Method::Get;
	}
	else if (method == "POST")
	{
		return sf::Http::Request::Method::Post;
	}
	else if (method == "PUT")
	{
		return sf::Http::Request::Method::Put;
	}
	else if (method == "DELETE")
	{
		return sf::Http::Request::Method::Delete;
	}
	else if (method == "HEAD")
	{
		return sf::Http::Request::Method::Head;
	}
	else
	{
		assert(0);
		return sf::Http::Request::Method::Get; // For no warning
	}
}

sf::Http::Response::Status MasterAPI::sendRequest(std::string body, std::string method)
{
	sf::Http::Request request(body, selectMethod(method));
	m_response = m_http.sendRequest(request);
	return m_response.getStatus();
}

std::string MasterAPI::getResponseBody() const
{
	return m_response.getBody();
}
