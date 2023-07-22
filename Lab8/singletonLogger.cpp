#include <fstream>

const auto logFile = "log.txt";

class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }
    void report(std::string message) {
        std::ofstream fout;
        fout.open(logFile, std::fstream::out | std::fstream::app);
        fout << message << std::endl;
        fout.close();
    }
private:
    Logger() {}
    Logger(Logger const&);
    void operator=(Logger const&);
};

void subroutine() {
    Logger::getInstance().report("logging in subroutine()");
}

int main () {
    Logger::getInstance().report("logging in main()");
    subroutine();
    return 0;
}
