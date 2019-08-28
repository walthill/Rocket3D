/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 RK_Log.cpp
	=========================

********/


#include "RK_Log.h"
#include <iostream>

RK_Log* RK_Log::mpLog = nullptr;
std::string RK_Log::mAppFilename = "log/applog.txt", RK_Log::mCoreFilename = "log/enginelog.txt";
std::shared_ptr<spdlog::logger> RK_Log::console_CoreLogger;
std::shared_ptr<spdlog::logger> RK_Log::console_ClientLogger;
std::shared_ptr<spdlog::logger> RK_Log::file_CoreLogger;
std::shared_ptr<spdlog::logger> RK_Log::file_ClientLogger;

RK_Log::RK_Log()
{
}

RK_Log::~RK_Log()
{
}

void RK_Log::initialize()
{
	std::string file_engineId = "(ENGINE)";
	std::string console_engineId = "[ENGINE]";
	std::string file_appId = "(APP)";
	std::string console_appId = "[APP]";

	std::string coutPattern = "%^[%T] %n >>> %v%$";
	std::string foutPattern = "%^[%T] %n {%l} >>> %v%$";

	/*************************
		Init console loggers
	***************************/

	console_CoreLogger = spdlog::stdout_color_mt(console_engineId);
	console_CoreLogger->set_pattern(coutPattern);
	console_CoreLogger->set_level(spdlog::level::trace);

	console_ClientLogger = spdlog::stdout_color_mt(console_appId);
	console_ClientLogger->set_pattern(coutPattern);
	console_ClientLogger->set_level(spdlog::level::trace);
	
	/*************************
		Init file loggers
	***************************/

	try
	{
		file_CoreLogger = spdlog::basic_logger_mt(file_engineId, mCoreFilename, true);
		file_CoreLogger->set_pattern(foutPattern);
		file_CoreLogger->set_level(spdlog::level::trace);
		file_CoreLogger->flush();
	}
	catch (const spdlog::spdlog_ex &ex)
	{
		std::cout << "Log init failed: " << ex.what() << std::endl;
	}

	try
	{
		file_ClientLogger = spdlog::basic_logger_mt(file_appId, mAppFilename, true);
		file_ClientLogger->set_pattern(foutPattern);
		file_ClientLogger->set_level(spdlog::level::trace);
		file_ClientLogger->flush();
	}
	catch (const spdlog::spdlog_ex &ex)
	{
		std::cout << "Log init failed: " << ex.what() << std::endl;
	}
}