/********
	=========================
			 ROCKET ENGINE
	=========================
	File Created By: Walter Hill

	Rocket3D is an open source 3D game engine written using C++ & OpenGL.

	This class makes use of the spdlog logging library
	(https://github.com/gabime/spdlog)

	This code is open source under the Apache 2.0 license.
	(https://github.com/walthill/Rocket3D/blob/master/LICENSE)

	=========================
			 RK_Log.h
	=========================
	This class is utlized as a static class. It incorporates spdlog
	in order to output info and errors to the console and to log files.

********/

#ifndef RK_LOG_H
#define RK_LOG_H

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <DeanLib/Trackable.h>

class RK_Log : public Trackable
{
	public:
		#pragma region Static Class Functions
		/***
			* Initializes the global static instance of the RK_Log class
		***/
		static void initInstance()
		{
			mpLog = new RK_Log;
		}

		/***
			* Destroys the global static instance of the RK_Log class
		***/
		static void cleanInstance()
		{
			if (mpLog != nullptr)
			{
				delete mpLog;
				mpLog = nullptr;
			}
		}

		/***
			* Access the global static instance of the RK_Log class 
			  in order to call functions from across the engine
		***/
		static RK_Log* getInstance()
		{
			assert(mpLog != nullptr);
			return mpLog;
		}
		#pragma endregion
		
		/***
			* Initializes loggers for console and file outputs
		***/
		static void initialize();

		/***
			* Cleanup console and file loggers
		***
		void cleanup();*/

		/***
			* Access console logger for engine core
		***/
		inline static std::shared_ptr<spdlog::logger>& getConsoleCoreLogger() { return console_CoreLogger; };
		/***
			* Access console logger for game app
		***/
		inline static std::shared_ptr<spdlog::logger>& getConsoleClientLogger() { return console_ClientLogger; };
		/***
			* Access file logger for engine core
		***/
		inline static std::shared_ptr<spdlog::logger>& getFileCoreLogger() { return file_CoreLogger; };
		/***
			* Access file logger for game app
		***/
		inline static std::shared_ptr<spdlog::logger>& getFileClientLogger() { return file_ClientLogger; };

	private:	
		static std::shared_ptr<spdlog::logger> console_CoreLogger, console_ClientLogger;
		static std::shared_ptr<spdlog::logger> file_CoreLogger, file_ClientLogger;
		static RK_Log *mpLog;

		static std::string mAppFilename, mCoreFilename;

		RK_Log();
		~RK_Log();
};

//Init macro
#define RK_LOGGER_INIT()		::RK_Log::initInstance(); RK_Log::getInstance()->initialize();
//Destroy macro
#define RK_LOGGER_CLEAN()		::RK_Log::cleanInstance();


/* Core console macros
============================================================= */

//Output an engine log message to the console
#define RK_CORE_LOG_C(...)		::RK_Log::getInstance()->getConsoleCoreLogger()->trace(__VA_ARGS__)
//Output an engine info message to the console
#define RK_CORE_INFO_C(...)		::RK_Log::getInstance()->getConsoleCoreLogger()->info(__VA_ARGS__)
//Output an engine warning to the console
#define RK_CORE_WARN_C(...)		::RK_Log::getInstance()->getConsoleCoreLogger()->warn(__VA_ARGS__)
//Output an engine error message to the console
#define RK_CORE_ERROR_C(...)	::RK_Log::getInstance()->getConsoleCoreLogger()->error(__VA_ARGS__)
//Output an engine fatal error message to the console
#define RK_CORE_FATAL_C(...)	::RK_Log::getInstance()->getConsoleCoreLogger()->critical(__VA_ARGS__)


/* Client console macros
============================================================= */

//Output an app log message to the console 
#define RK_LOG_C(...)			::RK_Log::getInstance()->getConsoleClientLogger()->trace(__VA_ARGS__)
//Output an app info message to the console 
#define RK_INFO_C(...)			::RK_Log::getInstance()->getConsoleClientLogger()->info(__VA_ARGS__)
//Output an app warning to the console 
#define RK_WARN_C(...)			::RK_Log::getInstance()->getConsoleClientLogger()->warn(__VA_ARGS__)
//Output an app error message to the console 
#define RK_ERROR_C(...)			::RK_Log::getInstance()->getConsoleClientLogger()->error(__VA_ARGS__)
//Output an app fatal error message to the console 
#define RK_FATAL_C(...)			::RK_Log::getInstance()->getConsoleClientLogger()->critical(__VA_ARGS__)


/* Core file and console macros
============================================================= */

//Outut an engine log message to both the console and log file
#define RK_CORE_LOG_ALL(...)	::RK_Log::getInstance()->getFileCoreLogger()->trace(__VA_ARGS__);RK_Log::getInstance()->getConsoleCoreLogger()->trace(__VA_ARGS__)
//Outut an engine info message to both the console and log file
#define RK_CORE_INFO_ALL(...)	::RK_Log::getInstance()->getFileCoreLogger()->info(__VA_ARGS__);RK_Log::getInstance()->getConsoleCoreLogger()->info(__VA_ARGS__)
//Outut an engine warning message to both the console and log file
#define RK_CORE_WARN_ALL(...)	::RK_Log::getInstance()->getFileCoreLogger()->warn(__VA_ARGS__);RK_Log::getInstance()->getConsoleCoreLogger()->warn(__VA_ARGS__)
//Outut an engine error message to both the console and log file
#define RK_CORE_ERROR_ALL(...)	::RK_Log::getInstance()->getFileCoreLogger()->error(__VA_ARGS__);RK_Log::getInstance()->getConsoleCoreLogger()->error(__VA_ARGS__)
//Outut an engine fatal error message to both the console and log file
#define RK_CORE_FATAL_ALL(...)	::RK_Log::getInstance()->getFileCoreLogger()->critical(__VA_ARGS__);RK_Log::getInstance()->getConsoleCoreLogger()->critical(__VA_ARGS__)


/* Core file macros
============================================================= */ 

//Outut an engine log message to the log file
#define RK_CORE_LOG_F(...)		::RK_Log::getInstance()->getFileCoreLogger()->trace(__VA_ARGS__)
//Outut an engine info message to the log file
#define RK_CORE_INFO_F(...)		::RK_Log::getInstance()->getFileCoreLogger()->info(__VA_ARGS__)
//Outut an engine warning to the log file
#define RK_CORE_WARN_F(...)		::RK_Log::getInstance()->getFileCoreLogger()->warn(__VA_ARGS__)
//Outut an engine error message to the log file
#define RK_CORE_ERROR_F(...)	::RK_Log::getInstance()->getFileCoreLogger()->error(__VA_ARGS__)
//Outut an engine fatal error message to the log file
#define RK_CORE_FATAL_F(...)	::RK_Log::getInstance()->getFileCoreLogger()->critical(__VA_ARGS__)


/* Client file macros
============================================================= */

//Outut an app log message to the log file
#define RK_LOG_F(...)			::RK_Log::getInstance()->getFileClientLogger()->trace(__VA_ARGS__)
//Outut an app info message to the log file
#define RK_INFO_F(...)			::RK_Log::getInstance()->getFileClientLogger()->info(__VA_ARGS__)
//Outut an app warning to the log file
#define RK_WARN_F(...)			::RK_Log::getInstance()->getFileClientLogger()->warn(__VA_ARGS__)
//Outut an app error message to the log file
#define RK_ERROR_F(...)			::RK_Log::getInstance()->getFileClientLogger()->error(__VA_ARGS__)
//Outut an app fatal error message to the log file
#define RK_FATAL_F(...)			::RK_Log::getInstance()->getFileClientLogger()->critical(__VA_ARGS__)


/* Client file and console macros
============================================================= */

//Outut an app log message to both the console and log file
#define RK_LOG_ALL(...)			::RK_Log::getInstance()->getFileClientLogger()->trace(__VA_ARGS__);RK_Log::getInstance()->getConsoleClientLogger()->trace(__VA_ARGS__)
//Outut an app info message to both the console and log file
#define RK_INFO_ALL(...)		::RK_Log::getInstance()->getFileClientLogger()->info(__VA_ARGS__);RK_Log::getInstance()->getConsoleClientLogger()->info(__VA_ARGS__)
//Outut an app warning to both the console and log file
#define RK_WARN_ALL(...)		::RK_Log::getInstance()->getFileClientLogger()->warn(__VA_ARGS__);RK_Log::getInstance()->getConsoleClientLogger()->warn(__VA_ARGS__)
//Outut an app error message to both the console and log file
#define RK_ERROR_ALL(...)		::RK_Log::getInstance()->getFileClientLogger()->error(__VA_ARGS__);RK_Log::getInstance()->getConsoleClientLogger()->error(__VA_ARGS__)
//Outut an app fatal error message to both the console and log file
#define RK_FATAL_ALL(...)		::RK_Log::getInstance()->getFileClientLogger()->critical(__VA_ARGS__);RK_Log::getInstance()->getConsoleClientLogger()->critical(__VA_ARGS__)

#endif // !RK_Log
