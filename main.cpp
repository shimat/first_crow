#include <crow.h>
#include <opencv2/opencv.hpp>

/*
class CustomLogger : public crow::ILogHandler
{
  public:
    CustomLogger()
    {
    }

    void log(std::string message, crow::LogLevel level)
    {
        // "message" doesn't contain the timestamp and loglevel
        // prefix the default logger does and it doesn't end
        // in a newline.
        std::cerr << message << std::endl;
    }
};
//*/

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([]() {
        CROW_LOG_ERROR << "Tick Count = " << cv::getTickCount();
        return "Hello world";
    });

    CROW_ROUTE(app, "/test").methods(crow::HTTPMethod::Post)([](const crow::request &req) {
        auto x = crow::json::load(req.body);
        if (!x)
            return crow::response(400);
        auto sum = x["a"].i() + x["b"].i();
        std::ostringstream os;
        os << sum;
        return crow::response{os.str()};
    });

    app.port(80).multithreaded().run();
}