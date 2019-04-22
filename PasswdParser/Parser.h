#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <time.h>
#include <iterator>
#include "DateTime.h"


#define	SUCCESS__ 0
#define READ_ERROR__ 1
#define WRITE_ERROR__ 2
#define ABORT__ 3
#define UNEXPECTED_ERROR__ 4




class Parser
{

public:
	clock_t begin_time;
	std::string basePath;
	size_t bufferMax = 0;
	std::string delimSet;
	int32_t stringFormat = -1;

	size_t totalFilesCnt = 0;					//input files counter
	size_t lstLinesCnt[5] = { 0 };				//for statistic only
	bool(*CancellationPending)();				//callback
	void(*ReportProgress)(int);					//callback
	int LastError = -1;


private:
	uint32_t percentReportStep = 1;
	size_t flushCounter = 0;
	size_t linesReadTotalCnt = 0;				//for progress report
	std::set<std::string> inputBuffer[5];		//using for sort
	std::string outFilename[5] = {
		"logins_short",
		"logins_long",
		"passwd_short",
		"passwd_long",
		"unknown_data"
	};

	std::ifstream* istr_ = nullptr;
	std::string log;


public:
	static Parser& getInstance();

	int parse(const char*);
	int flush();
	int merge();
	void cleanupFiles();
	void clearData();

	std::string getElapsedTime();
	void appLog(std::string);
	std::string getLog();
	void writeLog();


private:

	Parser() = default;
	~Parser() = default;
};






/*
#include <sys\stat.h>

struct stat fs = { 0 };
for (int i = 0; i < 5; ++i) {
///sum .lst filesize if exists
if (stat((basePath + '\\' + outFilename[i] + ".lst").c_str(), &fs) == 0)
{
bytesReadTotalCnt += fs.st_size;
}
///
}
*/

