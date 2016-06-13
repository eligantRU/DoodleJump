#include "stdafx.h"
#include "sheet.h"

int main()
{
/*	FuckingJSONParser parser;

	sf::Http http;
	http.setHost("127.0.0.1");
	sf::Http::Request request("web_backend/DoodleJump/api/index.php/records/10", sf::Http::Request::Get);
	sf::Http::Response response = http.sendRequest(request);
	sf::Http::Response::Status status = response.getStatus();

	if (status == sf::Http::Response::Ok)
	{
		std::vector<Record> records;
		records.reserve(10);
		//std::string str = "{\"nickname\":\"user1\",\"score\":\"1\"},{\"nickname\":\"user2\",\"score\":\"2\"},{\"nickname\":\"user3\",\"score\":\"3\"} ";
		std::string str = parser.getArray(response.getBody());
		for (int i = 0; i < 10; ++i)
		{
			std::string strJSON = parser.getJSON(str);
			std::string result1 = parser.getCoupleKeyValue(strJSON);
			std::string result2 = parser.getCoupleKeyValue(strJSON);
			std::map<std::string, std::string> result1mod = parser.getMap(result1);
			std::map<std::string, std::string> result2mod = parser.getMap(result2);
			records.push_back(Record(result1mod["nickname"], std::stoull(result2mod["score"].c_str())));
		}
	}
	else
	{
		std::cout << "Error: " << status << std::endl;
	}*/

	srand(unsigned(time(nullptr)));
	Game game;
	game.launch();
	return 0;
}
