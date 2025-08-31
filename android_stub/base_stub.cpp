// base_stub.cpp
#include <ostream>
#include <sstream>

namespace android {
namespace base {

enum class LogSeverity {
    VERBOSE, DEBUG, INFO, WARNING, ERROR, FATAL, FATAL_WITHOUT_ABORT
};

enum class LogId {
    MAIN, RADIO, EVENTS, SYSTEM, CRASH, STATS, SECURITY, DEFAULT
};

class LogMessage {
public:
    LogMessage(const char* file,
               unsigned int line,
               LogSeverity severity,
               const char* tag,
               int errno_value);

    LogMessage(const char* file,
               unsigned int line,
               LogId id,
               LogSeverity severity,
               const char* tag,
               int errno_value);

    ~LogMessage();

    std::ostream& stream();

    static void LogLine(const char* file,
                        unsigned int line,
                        LogSeverity severity,
                        const char* tag,
                        const char* message);
};

// Definitions — no asm(), just match the signature
LogMessage::LogMessage(const char*, unsigned int, LogSeverity, const char*, int) {}
LogMessage::LogMessage(const char*, unsigned int, LogId, LogSeverity, const char*, int) {}
LogMessage::~LogMessage() {}
std::ostream& LogMessage::stream() {
    static std::ostringstream oss;
    return oss;
}
void LogMessage::LogLine(const char*, unsigned int, LogSeverity, const char*, const char*) {}

} // namespace base
} // namespace android
