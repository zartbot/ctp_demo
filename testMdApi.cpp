// testTraderApi.cpp : 定义控制台应用程序的入口点。
//

#include "./ctpapi/ThostFtdcMdApi.h"
#include "MdSpi.h"
#include <iostream>
#include <fstream>
#include <cstring>

// UserApi对象
CThostFtdcMdApi* pUserApi;
#define MAXSIZE 10000

char  FRONT_ADDR[] = "tcp://180.168.146.187:10031";		// 前置地址
TThostFtdcBrokerIDType	BROKER_ID = "9999";				// 经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID = "";			// 注意这里输入你自己的投资者代码
TThostFtdcPasswordType  PASSWORD = "";			// 注意这里输入你自己的用户密码

char *ppInstrumentID[MAXSIZE];			// 行情订阅列表
int iInstrumentID = 0;									// 行情订阅数量


// 请求编号
int iRequestID = 0;

int main()
{
        std::string symbol;
        std::ifstream is("symbol.cfg");
        while ( is >> symbol)
        {
             std::cout << symbol << std::endl;
             const char *csymbol = symbol.c_str();
             ppInstrumentID[iInstrumentID] = new char[strlen(csymbol)+1];
             strcpy( ppInstrumentID[iInstrumentID] , csymbol);
             ++iInstrumentID;
        }
	// 初始化UserApi
	pUserApi = CThostFtdcMdApi::CreateFtdcMdApi();			// 创建UserApi
	CThostFtdcMdSpi* pUserSpi = new CMdSpi();
	pUserApi->RegisterSpi(pUserSpi);						// 注册事件类
	pUserApi->RegisterFront(FRONT_ADDR);					// connect
	pUserApi->Init();

	pUserApi->Join();
//	pUserApi->Release();
return 0;
}
