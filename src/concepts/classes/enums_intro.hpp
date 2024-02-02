#pragma once

void using_enums();
void enums_concept_hub();

class Log {
public:
    // const int LogLevelError = 0;
    // const int LogLevelWarning = 1;
    // const int LogLevelInfo = 2;
    enum Level { LogLevelError = 0, LogLevelWarning = 1, LogLevelInfo = 2 };

private:
    Level m_LogLevel = LogLevelInfo;  // or Log::Level::LogLevelInfo

public:
    void SetLevel(Level);
    void Error(const char*);
    void Warn(const char*);
    void Info(const char*);
};
