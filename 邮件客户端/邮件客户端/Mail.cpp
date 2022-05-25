#include "pch.h"
#include "Mail.h"
#include <thread>

#define LINELEN 1500
#define WAVERS MAKEWORD(2, 0)

void Mail::SendMail() { //const char* emailTo, const char* bodyint main(int argc, char *argv[])
	//char host[20] = "smtp.dlmu.edu.cn"; //163.com//客户端和服务器端都运行到同一个主机上
	char service[20] = "smtp"; //默认的服务名smtp
	SOCKET s; //TCP套接字
	char buf[1500] = { };
	//memset(buf, 0, 1500);
	WSADATA wsadata;
	//switch (argc) {
	//case 1:
	//	strcpy_s(host, 20, "smtp.dlmu.edu.cn");
	//	break;
	//case 3:
	//	strcpy_s(service, 20, argv[2]);
	//	//service = argv[2];
	//case 2:
	//	strcpy_s(host, 20, argv[1]);
	//	//host = argv[1];
	//	break;
	//default:
	//	fprintf(stderr, "usage: TCPdaytime [host [port]]\n");
	//	exit(1);
	//}
	if (WSAStartup(WAVERS, &wsadata) != 0)
		errexit("WSAStartup failed\n");

	//ConnectMailServer(host, service, s);
	int cc;
	s = connectTCP(sendHost.c_str(), service);
	// 连接邮件服务器，如果连接后没有响应，则2 毫秒后重新连接
	cc = recv(s, buf, LINELEN, 0); //没有错误，就是获取不到
	while (cc < 0) //不能小于等于0
	{
		std::cout << "reconnect..." << std::endl;
		Sleep(500);
		s = connectTCP(sendHost.c_str(), service);
		memset(buf, 0, sizeof(buf));
		cc = recv(s, buf, LINELEN, 0);
	}
	std::cout << buf << std::endl;
	//while (cc != SOCKET_ERROR && cc > 0) {
	//	//字节流传输协议
	//	buf[cc] = '\0';
	//	(void)fputs(buf, stdout);
	//	cc = recv(s, buf, LINELEN, 0);
	//}

	// EHLO
	//memset(buf, 0, sizeof(buf));
	//sprintf_s(buf, sizeof(buf), "EHLO HYL-PC\r\n");
	//send(s, buf, strlen(buf), 0);
	//memset(buf, 0, sizeof(buf));
	//recv(s, buf, sizeof(buf), 0);
	//std::cout << "EHLO REceive: " << buf << std::endl;

	//HELO
	char helo[] = "HELO DLMU\r\n";
	SendMsg(s, helo);

	//AUTH　LOGIN
	char authLogin[] = "AUTH LOGIN\r\n";
	SendMsg(s, authLogin);

	//USER 
	memset(buf, 0, sizeof(buf));
	char tempusername[128] = {};
	//memcpy(tempusername, username.c_str(), username.size());
	sprintf_s(tempusername, sizeof(tempusername), username.c_str());//你的邮箱账号
	//char tempusername[] = "yangjiyin@dlmu.edu.cn"; 
	char usernameLogin[1500] = {};
	EncodeBase64(buf, tempusername, strlen(tempusername));
	sprintf_s(usernameLogin, sizeof(usernameLogin), "%s\r\n", buf);
	SendMsg(s, usernameLogin);

	//PASSWORD
	memset(buf, 0, sizeof(buf));
	char temppassword[128] = {};
	sprintf_s(temppassword, sizeof(temppassword), password.c_str());//你的邮箱账号
	//char temppassword[] = "12345@Yjy";
	char passwordLogin[1500] = {};
	EncodeBase64(buf, temppassword, strlen(temppassword));
	sprintf_s(passwordLogin, sizeof(passwordLogin), "%s\r\n", buf);
	SendMsg(s, passwordLogin);

	//MAI FROM
	char maiFrom[1500] = {}; // "MAIL FROM: <yangjiyin@dlmu.edu.cn>\r\n";
	sprintf_s(maiFrom, sizeof(maiFrom), "MAIL FROM:<%s>\r\n", username.c_str());
	SendMsg(s, maiFrom);

	//RCPT TO
	char rcptTo[1500] = {}; // = "RCPT TO: <wy13149746632@163.com>\r\n";
	sprintf_s(rcptTo, sizeof(rcptTo), "RCPT TO:<%s>\r\n", EmailTo.c_str());
	SendMsg(s, rcptTo);


	//DATA
	char data[] = "DATA\r\n";
	SendMsg(s, data);

	EmailContents =
		string("From: \"Your N\"<") + username + (">\r\n")
		+ string("To: \"dasiy\"<") + EmailTo + std::string(">\r\n")
		+ string("Subject: ") + subject + string("\r\n\r\n")
		+ content
		//+ to_string(num) + "\r\n"
		+ "\r\n.\r\n";
	//BODY
	memset(buf, 0, sizeof(buf));
	sprintf_s(buf, sizeof(buf), "%s\r\n", EmailContents.c_str());
	string temp = SendMsg(s, buf);
	AfxMessageBox((CString)temp.c_str());

	//QUIT
	char quit[] = "QUIT\r\n";
	SendMsg(s, quit);

	closesocket(s);
	WSACleanup();
}

void Mail::GetMail()
{
	//char host[20] = "pop3.dlmu.edu.cn"; //客户端和服务器端都运行到同一个主机上
	char service[20] = "pop3"; //默认的服务名smtp
	SOCKET s; //TCP套接字
	char buf[1500] = { };
	WSADATA wsadata;
	if (WSAStartup(WAVERS, &wsadata) != 0)
		errexit("WSAStartup failed\n");
		//AfxMessageBox(L"WSAStartup failed\n");

	int cc;
	s = connectTCP(recHost.c_str(), service);
	cc = recv(s, buf, LINELEN, 0);
	while (cc < 0) //不能小于等于0
	{
		std::cout << "reconnect..." << std::endl;
		Sleep(500);
		s = connectTCP(recHost.c_str(), service);
		memset(buf, 0, sizeof(buf));
		cc = recv(s, buf, LINELEN, 0);
	}
	std::cout << buf << std::endl;

	string user = string("user ") + username + string("\r\n");
	SendMsg(s, user);
	string pass = string("pass ") + password + string("\r\n");
	SendMsg(s, pass);
	//SendMsg(s, string("list\r\n"));
	SendMsg(s, string("retr " + to_string(mailNum) + "\r\n"));
	//char end[LINELEN + 1] = {};
	//sprintf_s(end, sizeof(end), ) ;
	SendMsg(s, "quit\r\n");
}

void Mail::GetSmtpAddr() //const char* service
{
	//char host[] = {"smtp.dlmu.edu.cn" }; //163.com//客户端和服务器端都运行到同一个主机上
	char service[] = { "smtp" };//默认的服务名smtp
	char transport[] = "tcp"; //邮件一定是TCP协议
	//SOCKET s; //TCP套接字
	char buf[1500] = {  };

	WSADATA wsadata;
	if (WSAStartup(WAVERS, &wsadata) != 0)
		//AfxMessageBox(L"WSAStartup failed\n");
		errexit("WSAStartup failed\n");
	struct hostent* phe;
	//实现域名到 32位IP地址 的转换
	if (phe = gethostbyname(sendHost.c_str())) {
		//for (int j = 0; j < phe->h_length; j++) {
		//	if (!inet_ntoa(*(struct in_addr*)phe->h_addr_list[j])) {
		//		printf("%s ip addr %d: %s\n", service, j + 1, inet_ntoa(*(struct in_addr*)phe->h_addr_list[j]));
		//	}
		//}
		sendHostAddr = inet_ntoa(*(struct in_addr*)phe->h_addr_list[0]);
		//string temp = service + string(" ip addr: ") + inet_ntoa(*(struct in_addr*)phe->h_addr_list[0]);
		//AfxMessageBox((CString)(temp.c_str()));
		//temp.Format(_T("%s ip addr %d: %s\n"), service, 1, inet_ntoa(*(struct in_addr*)phe->h_addr_list[0]));

		printf("%s ip addr %d: %s\n", service, 1, inet_ntoa(*(struct in_addr*)phe->h_addr_list[0]));
	}
	else if ((inet_addr(sendHost.c_str())) == INADDR_NONE) {
		//string temp = "can't get \"" + string(sendHost.c_str()) + "\" host entry\n";
		//AfxMessageBox((CString)temp.c_str());
		errexit("can't get \"%s\" host entry\n", sendHost.c_str());

	}
	//closesocket(s);
	WSACleanup();
}

void Mail::GetPop3Addr()
{
	//char host[] = { "pop3.dlmu.edu.cn" }; //163.com//客户端和服务器端都运行到同一个主机上
	char service[] = "pop3";//默认的服务名
	char transport[] = "tcp"; //邮件一定是TCP协议
	//SOCKET s; //TCP套接字
	char buf[1500] = {  };
	WSADATA wsadata;
	if (WSAStartup(WAVERS, &wsadata) != 0)
		//AfxMessageBox(L"WSAStartup failed\n");
		errexit("WSAStartup failed\n");
	struct hostent* phe;
	//实现域名到 32位IP地址 的转换
	if (phe = gethostbyname(recHost.c_str())) {
		recHostAddr = inet_ntoa(*(struct in_addr*)phe->h_addr_list[0]);
		//string temp = service + string(" ip addr: ") + inet_ntoa(*(struct in_addr*)phe->h_addr_list[0]);
		//AfxMessageBox((CString)(temp.c_str()));
		//printf("%s ip addr %d: %s\n", service, 1, inet_ntoa(*(struct in_addr*)phe->h_addr_list[0]));
	}
	else if ((inet_addr(recHost.c_str())) == INADDR_NONE) {
		//string temp = "can't get \"" + string(recHost.c_str()) + "\" host entry\n";
		//AfxMessageBox((CString)temp.c_str());
		errexit("can't get \"%s\" host entry\n", recHost.c_str());

	}
	//closesocket(s);
	WSACleanup();
}

//Mail AfxMail;
//void AfxGetMail() {
//	for (int i = 0; i < 5; i++) {
//		AfxMail.mailNum = i + 1;
//		AfxMail.GetMail();
//		
//		string tempMailFileName = "邮件-" + to_string(AfxMail.mailNum) + ".txt";
//		ofstream outfile;
//		outfile.open(tempMailFileName.c_str(), ios::out | ios::trunc);
//		outfile << AfxMail.recContent;
//		outfile.close();
//	}
//	AfxMessageBox(L"5封邮件已经准备就绪");
//
//}


void Mail::ReadMail(int mailNum) {
	string tempMailFileName = "邮件-" + to_string(mailNum) + ".txt";
	ifstream infile;
	infile.open(tempMailFileName.c_str(), ios::in);
	if (!infile)
	{
		string message = tempMailFileName + "还没有没有下载";
		AfxMessageBox((CString)message.c_str());
	}
	recContent = "";
	infile >> recContent;
	infile.close();
}

void Mail::Login()
{
	char service[20] = "smtp"; //默认的服务名smtp
	SOCKET s; //TCP套接字
	char buf[1500] = { };
	//memset(buf, 0, 1500);
	WSADATA wsadata;

	if (WSAStartup(WAVERS, &wsadata) != 0) {
		//string tempMsg = "WSAStartup failed\n";
		//MessageBox(_T("这是一个最简单的消息框！"));
		errexit("WSAStartup failed\n");
	}

	//ConnectMailServer(host, service, s);
	int cc;
	s = connectTCP(sendHost.c_str(), service);
	// 连接邮件服务器，如果连接后没有响应，则2 毫秒后重新连接
	cc = recv(s, buf, LINELEN, 0); //没有错误，就是获取不到
	while (cc < 0) //不能小于等于0
	{
		std::cout << "reconnect..." << std::endl;
		Sleep(500);
		s = connectTCP(sendHost.c_str(), service);
		memset(buf, 0, sizeof(buf));
		cc = recv(s, buf, LINELEN, 0);
	}
	std::cout << buf << std::endl;


	//HELO
	char helo[] = "HELO DLMU\r\n";
	SendMsg(s, helo);

	//AUTH　LOGIN
	char authLogin[] = "AUTH LOGIN\r\n";
	SendMsg(s, authLogin);

	//USER 
	memset(buf, 0, sizeof(buf));
	char tempusername[128] = {};
	//memcpy(tempusername, username.c_str(), username.size());
	sprintf_s(tempusername, sizeof(tempusername), username.c_str());//你的邮箱账号
	//char tempusername[] = "yangjiyin@dlmu.edu.cn"; 
	char usernameLogin[1500] = {};
	EncodeBase64(buf, tempusername, strlen(tempusername));
	sprintf_s(usernameLogin, sizeof(usernameLogin), "%s\r\n", buf);
	SendMsg(s, usernameLogin);

	//PASSWORD
	memset(buf, 0, sizeof(buf));
	char temppassword[128] = {};
	sprintf_s(temppassword, sizeof(temppassword), password.c_str());//你的邮箱账号
	//char temppassword[] = "12345@Yjy";
	char passwordLogin[1500] = {};
	EncodeBase64(buf, temppassword, strlen(temppassword));
	sprintf_s(passwordLogin, sizeof(passwordLogin), "%s\r\n", buf);
	string temp = SendMsg(s, passwordLogin);
	//MessageBox(L"修改成功");
	AfxMessageBox((CString)temp.c_str());
	SendMsg(s, "quit\r\n");

	//GetMail();
	//AfxMail.username = username;
	//AfxMail.password = password;
	//AfxMail.sendHostAddr = sendHostAddr;
	//AfxMail.recHostAddr = recHostAddr;
	//thread t(AfxGetMail);
	//t.join();
	GetmailCount();
}


//void ConnectMailServer(const char* host, const char* service, SOCKET &s) {
//	char buf[LINELEN + 1];
//	int cc;
//	s = connectTCP(host, service);
//	// 连接邮件服务器，如果连接后没有响应，则2 秒后重新连接
//	cc = recv(s, buf, LINELEN, 0); //没有错误，就是获取不到
//	while (cc = recv(s, buf, LINELEN, 0) <= 0)
//	{
//		std::cout << "reconnect..." << std::endl;
//		Sleep(2);
//		s = connectTCP(host, service);
//		memset(buf, 0, sizeof(buf));
//	}
//	while (cc != SOCKET_ERROR && cc > 0) { 
//		//字节流传输协议
//		buf[cc] = '\0';
//		(void)fputs(buf, stdout);
//		cc = recv(s, buf, LINELEN, 0);
//	}
//	std::cout << buf << std::endl;
//
//	closesocket(s);
//}

void Mail::errexit(const char* format, ...) { //
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	WSACleanup();
	exit(1);
}

SOCKET Mail::connectTCP(const char* host, const char* service)
{
	return	connectsock(host, service, "tcp");//SOCKET();
}

SOCKET Mail::connectsock(const char* host, const char* service, const char* transport)
{
	struct hostent* phe;
	struct servent* pse;
	struct protoent* ppe;
	struct sockaddr_in sin;
	int s, type;

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;

	if (pse = getservbyname(service, transport)) {
		sin.sin_port = pse->s_port; //6400
		//printf("%s %d/%s  \n", pse->s_name, ntohs(pse->s_port), pse->s_proto);
	}

	else if ((sin.sin_port = htons((u_short)atoi(service))) == 0) {
		//string tempMsg = "can't get \"" + (string)service + "service entry\n"; 
		//AfxMessageBox((CString)tempMsg.c_str());
		errexit("can't get \"%s\" service entry\n", service);
	}


	if (phe = gethostbyname(host)) {
		//sin.sin_addr.s_addr = inet_addr("127.0.0.1");
		//设置域名的目的是为了获取IP地址
		memcpy(&sin.sin_addr, phe->h_addr_list[0], phe->h_length);
		//printf("IP addr %d: %s\n", 1, inet_ntoa(*(struct in_addr*)phe->h_addr_list[0]));	

	}
	else if ((sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE) {
		//string tempMsg = "can't get \"" + (string)host + "host entry\n";
		//AfxMessageBox((CString)tempMsg.c_str());
		errexit("can't get \"%s\" host entry\n", host);
	}

	if (!strcmp(host, sendHost.c_str())) {
		sin.sin_addr.s_addr = inet_addr(sendHostAddr.c_str());
	}
	else {
		sin.sin_addr.s_addr = inet_addr(recHostAddr.c_str());
	}


	if ((ppe = getprotobyname(transport)) == 0)
	{
		//string tempMsg = "can't get \"" + (string)transport + "protocal entry\n";
		//AfxMessageBox((CString)tempMsg.c_str());
		errexit("can't get \"%s\" protocal entry\n", transport);
	}
		

	if (strcmp(transport, "udp") == 0)
		type = SOCK_DGRAM;
	else type = SOCK_STREAM;

	s = socket(PF_INET, type, ppe->p_proto);
	//sin.sin_port = 25;
	//s = socket(PF_INET, SOCK_STREAM, 0);
	if (s == INVALID_SOCKET) {
		//string tempMsg = "can't creat socket: "; // +(string)protocal + "protocal entry\n";
		//AfxMessageBox((CString)tempMsg.c_str());

		errexit("can't creat socket: %d\n", host, service, GetLastError());
	}
	if (connect(s, (struct sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR) {
		//string tempMsg = "can't connect to " + (string)host + "."  + (string)service+ to_string(GetLastError()) + "\n";
		//AfxMessageBox((CString)tempMsg.c_str());

		errexit("can't connect to %s.%s: %d\n", host, service, GetLastError());

	}
	return s;

}

void Mail::GetmailCount()
{
	char service[20] = "pop3"; //默认的服务名smtp
	SOCKET s; //TCP套接字
	char buf[1500] = { };
	WSADATA wsadata;
	if (WSAStartup(WAVERS, &wsadata) != 0) {
		//AfxMessageBox(L"WSAStartup failed\n");
		errexit("WSAStartup failed\n");
	}


	int cc;
	s = connectTCP(recHost.c_str(), service);
	cc = recv(s, buf, LINELEN, 0);
	while (cc < 0) //不能小于等于0
	{
		std::cout << "reconnect..." << std::endl;
		Sleep(500);
		s = connectTCP(recHost.c_str(), service);
		memset(buf, 0, sizeof(buf));
		cc = recv(s, buf, LINELEN, 0);
	}
	std::cout << buf << std::endl;

	string user = string("user ") + username + string("\r\n");
	SendMsg(s, user);
	string pass = string("pass ") + password + string("\r\n");
	SendMsg(s, pass);
	SendMsg(s, string("list\r\n"));

	SendMsg(s, "quit\r\n");
}




char Mail::ConvertToBase64(char uc)
{
	if (uc < 26)
	{
		return 'A' + uc;
	}
	if (uc < 52)
	{
		return 'a' + (uc - 26);
	}
	if (uc < 62)
	{
		return '0' + (uc - 52);
	}
	if (uc == 62)
	{
		return '+';
	}
	return '/';
}

// base64的实现
void Mail::EncodeBase64(char* dbuf, char* buf128, int len)
{
	struct Base64Date6
	{
		unsigned int d4 : 6;
		unsigned int d3 : 6;
		unsigned int d2 : 6;
		unsigned int d1 : 6;
	};

	struct Base64Date6* ddd = NULL;
	int           i = 0;
	char          buf[256] = { 0 };
	char* tmp = NULL;
	char          cc = '\0';

	memset(buf, 0, 256);
	strcpy_s(buf, 256, buf128);
	for (i = 1; i <= len / 3; i++)
	{
		tmp = buf + (i - 1) * 3;
		cc = tmp[2];
		tmp[2] = tmp[0];
		tmp[0] = cc;
		ddd = (struct Base64Date6*)tmp;
		dbuf[(i - 1) * 4 + 0] = ConvertToBase64((unsigned int)ddd->d1);
		dbuf[(i - 1) * 4 + 1] = ConvertToBase64((unsigned int)ddd->d2);
		dbuf[(i - 1) * 4 + 2] = ConvertToBase64((unsigned int)ddd->d3);
		dbuf[(i - 1) * 4 + 3] = ConvertToBase64((unsigned int)ddd->d4);
	}
	if (len % 3 == 1)
	{
		tmp = buf + (i - 1) * 3;
		cc = tmp[2];
		tmp[2] = tmp[0];
		tmp[0] = cc;
		ddd = (struct Base64Date6*)tmp;
		dbuf[(i - 1) * 4 + 0] = ConvertToBase64((unsigned int)ddd->d1);
		dbuf[(i - 1) * 4 + 1] = ConvertToBase64((unsigned int)ddd->d2);
		dbuf[(i - 1) * 4 + 2] = '=';
		dbuf[(i - 1) * 4 + 3] = '=';
	}
	if (len % 3 == 2)
	{
		tmp = buf + (i - 1) * 3;
		cc = tmp[2];
		tmp[2] = tmp[0];
		tmp[0] = cc;
		ddd = (struct Base64Date6*)tmp;
		dbuf[(i - 1) * 4 + 0] = ConvertToBase64((unsigned int)ddd->d1);
		dbuf[(i - 1) * 4 + 1] = ConvertToBase64((unsigned int)ddd->d2);
		dbuf[(i - 1) * 4 + 2] = ConvertToBase64((unsigned int)ddd->d3);
		dbuf[(i - 1) * 4 + 3] = '=';
	}
	return;
}

string Mail::SendMsg(SOCKET s, const char rbuf[]) {
	char buf[1500];
	memset(buf, 0, sizeof(buf));
	sprintf_s(buf, sizeof(buf), rbuf);
	send(s, buf, strlen(buf), 0);
	memset(buf, 0, sizeof(buf));
	recv(s, buf, sizeof(buf), 0);
	//if (!memcmp(rbuf, "quit", strlen("quit"))) {
	//	AfxMessageBox((CString)buf);
	//}
	printf("%sReceive: %s", rbuf, buf);
	return (string)(buf);
}

string Mail::SendMsg(SOCKET s, string rbuf) {
	char buf[LINELEN + 1];
	memset(buf, 0, sizeof(buf));
	sprintf_s(buf, sizeof(buf), rbuf.c_str());
	send(s, buf, strlen(buf), 0);
	memset(buf, 0, sizeof(buf));
	if (!memcmp(rbuf.c_str(), "list", strlen("list"))) {

		int cc = -1; //没有错误，就是获取不到
		cc = recv(s, buf, LINELEN, 0);
		ofstream outfile;
		outfile.open("mailCount.txt", ios::out | ios::trunc);

		while (cc != SOCKET_ERROR && cc > 0) {
			buf[cc] = '\0'; //形成一个字符
			(void)fputs(buf, stdout);
			//利用最后四个字符判断邮件接收结束，并不严谨，万一分开？
			// 接收的
			//数据每1500传输一次
			outfile << buf;
			if (buf[cc - 4] == '\n' && buf[cc - 3] == '.' && buf[cc - 2] == '\r' && buf[cc - 1] == '\n') { //!memcmp(buf + cc  - 2, ".\n", 2)"\n\0.\0\n"  
				break;
			}
			cc = recv(s, buf, LINELEN, 0); //会阻塞
		}
		outfile.close();
		ifstream infile;
		infile.open("mailCount.txt");
		mailCount = -2;
		for (string buf; getline(infile, buf); ) {
			mailCount++;
		}
		//AfxMessageBox((CString)to_string(mailCount).c_str());
	}
	else if (!memcmp(rbuf.c_str(), "retr", strlen("retr"))) {
		//for (int i = 0; i < 5; i++) {
			string tempMailFileName = "邮件-" + to_string(mailNum) + ".txt";
			ofstream outfile;
			outfile.open(tempMailFileName.c_str(), ios::out | ios::trunc);

			//recContent = "";
			int cc = -1; //没有错误，就是获取不到
			cc = recv(s, buf, LINELEN, 0);
			while (cc != SOCKET_ERROR && cc > 0) {
				//recContent += buf;
				//字节流传输协议
				buf[cc] = '\0'; //形成一个字符
				(void)fputs(buf, stdout);
				//利用最后四个字符判断邮件接收结束，并不严谨，万一分开？
				//数据每1500传输一次
				if (buf[cc - 4] == '\n' && buf[cc - 3] == '.' && buf[cc - 2] == '\r' && buf[cc - 1] == '\n') { //!memcmp(buf + cc  - 2, ".\n", 2)"\n\0.\0\n"  
					break;
				}
				outfile << buf;
				
				cc = recv(s, buf, LINELEN, 0); //会阻塞
			}
			outfile.close();
		//}

	}
	else {
		recv(s, buf, sizeof(buf), 0);
		printf("%sReceive: %s", rbuf.c_str(), buf);
	}
	return (string)buf;
}


