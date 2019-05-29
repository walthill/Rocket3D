#ifndef RK_LOG_H
#define RK_LOG_H

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

class RK_Log
{
	public:
		#pragma region Static Class Functions
		static void initInstance()
		{
			mpLog = new RK_Log;
		}

		static void cleanInstance()
		{
			if (mpLog != nullptr)
			{
				delete mpLog;
				mpLog = nullptr;
			}
		}

		static RK_Log* getInstance()
		{
			assert(mpLog != nullptr);
			return mpLog;
		}
		#pragma endregion
		
		static void initialize();

		inline static std::shared_ptr<spdlog::logger>& getConsoleCoreLogger() { return console_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger>& getConsoleClientLogger() { return console_ClientLogger; };
		inline static std::shared_ptr<spdlog::logger>& getFileCoreLogger() { return file_CoreLogger; };
		inline static std::shared_ptr<spdlog::logger>& getFileClientLogger() { return file_ClientLogger; };

	private:	
		static std::shared_ptr<spdlog::logger> console_CoreLogger, console_ClientLogger;
		static std::shared_ptr<spdlog::logger> file_CoreLogger, file_ClientLogger;
		static RK_Log *mpLog;

		static std::string mAppFilename, mCoreFilename;

		RK_Log();
		~RK_Log();
};

//Init/clean macro
#define RK_LOGGER_INIT()	:: RK_Log::initInstance(); RK_Log::getInstance()->initialize();
#define RK_LOGGER_CLEAN()		::RK_Log::getInstance()->cleanup();RK_Log::cleanInstance();

//Core console macros
#define RK_CORE_LOG_C(...)		::RK_Log::getInstance()->getConsoleCoreLogger()->trace(__VA_ARGS__)
#define RK_CORE_INFO_C(...)		::RK_Log::getInstance()->getConsoleCoreLogger()->info(__VA_ARGS__)
#define RK_CORE_WARN_C(...)		::RK_Log::getInstance()->getConsoleCoreLogger()->warn(__VA_ARGS__)
#define RK_CORE_ERROR_C(...)	::RK_Log::getInstance()->getConsoleCoreLogger()->error(__VA_ARGS__)
#define RK_CORE_FATAL_C(...)	::RK_Log::getInstance()->getConsoleCoreLogger()->fatal(__VA_ARGS__)

//Client console Macros
#define RK_LOG_C(...)			::RK_Log::getInstance()->getConsoleClientLogger()->trace(__VA_ARGS__)
#define RK_INFO_C(...)			::RK_Log::getInstance()->getConsoleClientLogger()->info(__VA_ARGS__)
#define RK_WARN_C(...)			::RK_Log::getInstance()->getConsoleClientLogger()->warn(__VA_ARGS__)
#define RK_ERROR_C(...)			::RK_Log::getInstance()->getConsoleClientLogger()->error(__VA_ARGS__)
#define RK_FATAL_C(...)			::RK_Log::getInstance()->getConsoleClientLogger()->fatal(__VA_ARGS__)

//Core file and console macros
#define RK_CORE_LOG_ALL(...) ::RK_Log::getInstance()->getFileCoreLogger()->trace(__VA_ARGS__);RK_Log::getInstance()->getConsoleCoreLogger()->trace(__VA_ARGS__)
#define RK_CORE_INFO_ALL(...) ::RK_Log::getInstance()->getFileCoreLogger()->info(__VA_ARGS__);RK_Log::getInstance()->getConsoleCoreLogger()->info(__VA_ARGS__)
#define RK_CORE_WARN_ALL(...) ::RK_Log::getInstance()->getFileCoreLogger()->warn(__VA_ARGS__);RK_Log::getInstance()->getConsoleCoreLogger()->warn(__VA_ARGS__)
#define RK_CORE_ERROR_ALL(...) ::RK_Log::getInstance()->getFileCoreLogger()->error(__VA_ARGS__);RK_Log::getInstance()->getConsoleCoreLogger()->error(__VA_ARGS__)
#define RK_CORE_FATAL_ALL(...) ::RK_Log::getInstance()->getFileCoreLogger()->fatal(__VA_ARGS__);RK_Log::getInstance()->getConsoleCoreLogger()->fatal(__VA_ARGS__)


//Core file macros
#define RK_CORE_LOG_F(...)		::RK_Log::getInstance()->getFileCoreLogger()->trace(__VA_ARGS__)
#define RK_CORE_INFO_F(...)		::RK_Log::getInstance()->getFileCoreLogger()->info(__VA_ARGS__)
#define RK_CORE_WARN_F(...)		::RK_Log::getInstance()->getFileCoreLogger()->warn(__VA_ARGS__)
#define RK_CORE_ERROR_F(...)	::RK_Log::getInstance()->getFileCoreLogger()->error(__VA_ARGS__)
#define RK_CORE_FATAL_F(...)	::RK_Log::getInstance()->getFileCoreLogger()->fatal(__VA_ARGS__)

//Client file Macros
#define RK_LOG_F(...)			::RK_Log::getInstance()->getFileClientLogger()->trace(__VA_ARGS__)
#define RK_INFO_F(...)			::RK_Log::getInstance()->getFileClientLogger()->info(__VA_ARGS__)
#define RK_WARN_F(...)			::RK_Log::getInstance()->getFileClientLogger()->warn(__VA_ARGS__)
#define RK_ERROR_F(...)			::RK_Log::getInstance()->getFileClientLogger()->error(__VA_ARGS__)
#define RK_FATAL_F(...)			::RK_Log::getInstance()->getFileClientLogger()->fatal(__VA_ARGS__)

//Client file and console macros
#define RK_LOG_ALL(...) ::RK_Log::getInstance()->getFileClientLogger()->trace(__VA_ARGS__);RK_Log::getInstance()->getConsoleClientLogger()->trace(__VA_ARGS__)
#define RK_INFO_ALL(...) ::RK_Log::getInstance()->getFileClientLogger()->info(__VA_ARGS__);RK_Log::getInstance()->getConsoleClientLogger()->info(__VA_ARGS__)
#define RK_WARN_ALL(...) ::RK_Log::getInstance()->getFileClientLogger()->warn(__VA_ARGS__);RK_Log::getInstance()->getConsoleClientLogger()->warn(__VA_ARGS__)
#define RK_ERROR_ALL(...) ::RK_Log::getInstance()->getFileClientLogger()->error(__VA_ARGS__);RK_Log::getInstance()->getConsoleClientLogger()->error(__VA_ARGS__)
#define RK_FATAL_ALL(...) ::RK_Log::getInstance()->getFileClientLogger()->fatal(__VA_ARGS__);RK_Log::getInstance()->getConsoleClientLogger()->fatal(__VA_ARGS__)

#endif // !RK_Log
