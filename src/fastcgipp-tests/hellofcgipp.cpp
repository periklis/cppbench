#include <fastcgi++/request.hpp>

class HelloFastcgi: public Fastcgipp::Request<wchar_t>
{
  bool response()
  {
    out << L"Content-Type: text/html; charset=utf-8\r\n\r\n";

    out <<
      L"<!DOCTYPE html>\n"
      L"<html>"
      L"<head>"
      L"<meta charset='utf-8' />"
      L"<title>fastcgi++: Hello World</title>"
      L"</head>"
      L"<body>"
      L"<p>"
      L"English: Hello World<br>"
      L"Russian: Привет мир<br>"
      L"Greek: Γεια σας κόσμε<br>"
      L"Chinese: 世界您好<br>"
      L"Japanese: 今日は世界<br>"
      L"Runic English?: ᚺᛖᛚᛟ ᚹᛟᛉᛚᛞ<br>"
      L"</p>"
      L"</body>"
      L"</html>";

    return true;
  }
};

#include <fastcgi++/manager.hpp>

int main()
{
  Fastcgipp::Manager<HelloFastcgi> manager;

  manager.setupSignals();
  manager.listen("127.0.0.1", "9000");
  manager.start();
  manager.join();

  return 0;
}
