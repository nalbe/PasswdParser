#include "Parser.h"
#include "WMemStat.h"



Parser& Parser::getInstance()
{
	static Parser ps;
	return ps;
}




int Parser::parse(const char* filePath)
{
	std::string currStr;
	std::size_t delim[2];
	std::size_t substrLen;
	std::ifstream infile(filePath, std::ios::in);	///close via dtor
	WMemStat ms;


	if (!infile.is_open()) {
		appLog(std::string("Unable to read file: ") + filePath);
		return LastError = READ_ERROR__;
	}


	while (std::getline(infile, currStr)) {

		if (CancellationPending()) {
			return LastError = ABORT__;
		}


		if (ms.CurrProc_Used_Physical_Memory() >= bufferMax) {
			if (flush() != SUCCESS__) {
				return LastError;
			}
		}


		switch (stringFormat)
		{

		case 0:	//@mail<delimeter>password
			delim[0] = currStr.find('@');
			if (delim[0] == std::string::npos) {	//handle unknown string format
				inputBuffer[4].insert(currStr);
				continue;
			}

			delim[1] = currStr.find_first_of(delimSet, delim[0] + 1);
			if (delim[1] == std::string::npos) {	//handle unknown string format
				inputBuffer[4].insert(currStr);
				continue;
			}

			substrLen = delim[0];
			if (substrLen < 8) {
				inputBuffer[0].insert(currStr.substr(0, delim[0]));
			}
			else {
				inputBuffer[1].insert(currStr.substr(0, delim[0]));
			}

			substrLen = currStr.size() - (++delim[1]);
			if (substrLen < 8) {
				inputBuffer[2].insert(currStr.substr(delim[1], std::string::npos));
			}
			else {
				inputBuffer[3].insert(currStr.substr(delim[1], std::string::npos));
			}

			break;


		case 1:	//login<delimeter>password
			delim[0] = currStr.find_first_of(delimSet, 0);
			if (delim[0] == std::string::npos) {	//handle unknown string format
				inputBuffer[4].insert(currStr);
				continue;
			}

			substrLen = delim[0];
			if (substrLen < 8) {
				inputBuffer[0].insert(currStr.substr(0, delim[0]));
			}
			else {
				inputBuffer[1].insert(currStr.substr(0, delim[0]));
			}

			substrLen = currStr.size() - (++delim[0]);
			if (substrLen < 8) {
				inputBuffer[2].insert(currStr.substr(delim[0], std::string::npos));
			}
			else {
				inputBuffer[3].insert(currStr.substr(delim[0], std::string::npos));
			}

			break;


		default:
			appLog(std::string("Bad string format."));
			return LastError = UNEXPECTED_ERROR__;
		}
	}
	totalFilesCnt++;

	return LastError = SUCCESS__;
}




int Parser::flush()
{
	std::ofstream ostr_;

	for (short i = 0; i < 5; ++i) {
		ostr_.open(basePath + '\\' + std::to_string(i) + std::to_string(flushCounter) + ".tmp", std::ios::out);

		if (!ostr_.is_open()) {
			appLog(std::string("Unable to write file: ") + std::to_string(i) + std::to_string(flushCounter) + ".tmp");
			return LastError = WRITE_ERROR__;
		}

		if (inputBuffer[i].size()) {
			for (std::set<std::string>::iterator it = inputBuffer[i].begin(); it != inputBuffer[i].end(); ++it) {
				ostr_ << *it << '\n';
				++linesReadTotalCnt;
			}
		}

		ostr_.close();
		inputBuffer[i].clear();
	}
	++flushCounter;

	return LastError = SUCCESS__;
}




int Parser::merge()
{
	istr_ = new std::ifstream[flushCounter + 1];	//include (.lst) if exists
	std::ofstream ostr_;
	std::map<std::string, int> map_sort_uniq;		//hold string + source index
	std::string currStr;
	int minHeapIndex;
	int32_t currProgressPercentage;
	int32_t percentUntilReport = 50 + percentReportStep;
	size_t estimatedLinesToWriteCnt = linesReadTotalCnt;


	for (int i = 0; i < 5; ++i) {

		for (int j = 0; j <= flushCounter; ++j) {
		///get one line from each *.tmp | *.lst
			if (j != flushCounter) {
				istr_[j].open(basePath + '\\' + std::to_string(i) + std::to_string(j) + ".tmp", std::ios::in);
			}
			else {
				istr_[j].open(basePath + '\\' + outFilename[i] + ".lst", std::ios::in);
			}

			if (istr_[j].is_open()) {
				bool result = false;

				while (!result) {
					if (!std::getline(istr_[j], currStr)) {
						istr_[j].close();
						break;
					}
					result = (map_sort_uniq.emplace(currStr, j)).second;
					if (!result && j != flushCounter) {
						--linesReadTotalCnt;
						--estimatedLinesToWriteCnt;
					}
					else if (result && j == flushCounter) {
						++linesReadTotalCnt;
						++estimatedLinesToWriteCnt;
					}
				}
			}
			else if (j != flushCounter) {
				appLog(std::string("Unable to read file: ") + std::to_string(i) + std::to_string(j) + ".tmp");
				return LastError = READ_ERROR__;
			}
		}
		///
		///
		ostr_.open(basePath + '\\' + outFilename[i] + ".tmp", std::ios_base::out | std::ios_base::app);
		if (!ostr_.is_open()) {
			appLog(std::string("Unable to write file: ") + outFilename[i] + ".tmp");
			return LastError = WRITE_ERROR__;
		}
		///

		while (map_sort_uniq.size()) {

			if (CancellationPending()) {
				return LastError = ABORT__;
			}

			minHeapIndex = (map_sort_uniq.begin())->second;
			ostr_ << ((map_sort_uniq.begin())->first) << '\n';
			--estimatedLinesToWriteCnt;
			++lstLinesCnt[i];	//for statistic
			map_sort_uniq.erase(map_sort_uniq.begin());

			///progress report
			currProgressPercentage = 100 - (int32_t)((estimatedLinesToWriteCnt * 50) / (linesReadTotalCnt > 0 ? linesReadTotalCnt : 1));
			if (currProgressPercentage >= percentUntilReport) {
				ReportProgress(currProgressPercentage);
				percentUntilReport += percentReportStep;
			}
			///

			if (istr_[minHeapIndex].is_open()) {
				bool result = false;

				while (!result) {
					if (!std::getline(istr_[minHeapIndex], currStr)) {
						istr_[minHeapIndex].close();
						break;
					}
					result = (map_sort_uniq.emplace(currStr, minHeapIndex)).second;
					if (result && minHeapIndex == flushCounter) {
						++linesReadTotalCnt;
						++estimatedLinesToWriteCnt;
					}
					else if (!result && minHeapIndex != flushCounter) {
						--linesReadTotalCnt;
						--estimatedLinesToWriteCnt;
					}
				}
			}
		}
		ostr_.close();	///all istr_[] should be already closed

	}

	return LastError = SUCCESS__;
}




void Parser::cleanupFiles()
{
	if (istr_ != nullptr) {
		delete[] istr_;
		istr_ = nullptr;
	}

	for (int i = 0; i < 5; ++i) {

		///pop possible huge amount of data from memory
		inputBuffer[i].clear();


		for (int j = 0; j < flushCounter; ++j) {
			std::remove((basePath + '\\' + std::to_string(i) + std::to_string(j) + ".tmp").c_str());
		}

		if (LastError == SUCCESS__) {
			///remove old collection if exists
			std::remove((basePath + '\\' + outFilename[i] + ".lst").c_str());
			std::rename((basePath + '\\' + outFilename[i] + ".tmp").c_str(), (basePath + '\\' + outFilename[i] + ".lst").c_str());
		}
		else {
			std::remove((basePath + '\\' + outFilename[i] + ".tmp").c_str());
		}
	}

	return;
}




void Parser::clearData() {
	begin_time = 0;
	basePath.clear();
	bufferMax = 0;
	delimSet.clear();
	stringFormat = -1;
	totalFilesCnt = 0;
	for (int i = 0; i < 5; ++i) {
		lstLinesCnt[i] = 0;
	}
	linesReadTotalCnt = 0;
	flushCounter = 0;
	LastError = -1;
	log.clear();

	return;
}




void Parser::appLog(std::string msg)
{
	log += GetDateTime() + msg + "\n";
}

std::string Parser::getLog() {
	return log;
}

void Parser::writeLog() {
	std::ofstream oslog(basePath + '\\' + "PasswdParser.log", std::ios::out | std::ios::app);
	oslog << log << "\n\n";
	return;
}




std::string Parser::getElapsedTime()
{
	int seconds = (int)(float(clock() - begin_time) / CLOCKS_PER_SEC);
	int minutes = seconds / 60;
	int hours = minutes / 60;
	return std::to_string(hours) + "h:" + std::to_string((int)(minutes % 60)) + "m:" + std::to_string((int)(seconds % 60)) + "s";
}