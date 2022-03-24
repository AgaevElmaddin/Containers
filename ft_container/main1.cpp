#include <iostream>
#include <map>
#include <vector>
#include <utility>

int main()
{
	std::map <std::string, int> myFirstMap;
	myFirstMap.insert(std::pair<std::string,int>("Mother", 37));
	myFirstMap.insert(std::pair<std::string,int>("Father", 40 ));
	myFirstMap.insert(std::pair<std::string,int>("Brother", 15 ));
	std::map <std::string, int>::iterator it;
  for (it = myFirstMap.begin(); it != myFirstMap.end(); ++it)
  {
      std::cout << it->first << " : " << it->second << std::endl;
  }
	std::cout << it->first << " : " << it->second << std::endl;
}