#pragma once
#ifndef _SEND_MAIL_H_
#define _SEND_MAIL_H_
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <windows.h>
//#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)
using namespace std;

class Mail {
public:
	//int num = 100;
	string username = "*************@163.com";
	string password = "*************";
	string EmailTo = "*************@163.com";
	string subject = "Hello";
	string content = "test sending variable";
	string EmailContents =
		string("From: \"Yuor N\"<") + username + (">\r\n")
		+ string("To: \"dasiy\"<") + EmailTo + std::string(">\r\n")
		+ string("Subject: ") + subject + string("\r\n\r\n")
		+ content
		//+ to_string(num) + "\r\n"
		+ "\r\n.\r\n";
	string sendHost = "smtp.163.com";
	string recHost = "pop3.163.com";
	string sendHostAddr = "***.***.***.***";
	string recHostAddr = "***.***.***.***";
	int mailNum = 1;
	int mailCount = 0;
	string recContent;

public:
	void GetSmtpAddr(); //const char* service
	void GetPop3Addr();
	void Login();
	void SendMail(); //const char* email, const char* body
	void GetMail();
	void ReadMail(int mailNum);

public:
	string SendMsg(SOCKET s, const char rbuf[]);
	string SendMsg(SOCKET s, string rbuf);
	char ConvertToBase64(char uc);
	void EncodeBase64(char* dbuf, char* buf128, int len);
	//void ConnectMailServer(const char*, const char*, SOCKET& s);
	void errexit(const char*, ...);
	SOCKET connectTCP(const char*, const char*);
	SOCKET connectsock(const char* host, const char* service, const char* transport);
	void GetmailCount();
};


#endif
