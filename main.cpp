#include <crow.h>
#include <opencv2/opencv.hpp>

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([]() {
        CROW_LOG_ERROR << "Tick Count = " << cv::getTickCount();
        return "Hello world";
    });

    CROW_ROUTE(app, "/binarize").methods(crow::HTTPMethod::Post)([](const crow::request &req) {
        auto request_json = crow::json::load(req.body);
        if (!request_json)
            return crow::response(400, "");
        auto image_base64 = request_json["image"].s();
        auto image = crow::utility::base64decode(image_base64);
        if (image.size() > std::numeric_limits<int>::max())
            return crow::response(400, "");

        // std::ostringstream os;
        // os << image;

        cv::Mat buffer(static_cast<int>(image.size()), 1, CV_8U, image.data());
        cv::Mat src = cv::imdecode(buffer, cv::IMREAD_GRAYSCALE);
        cv::Mat dst;

        cv::threshold(src, dst, 128, 255, CV_8UC1);

        std::vector<uchar> dst_png;
        cv::imencode(".png", dst, dst_png);

        /*
        auto dst_base64 = crow::utility::base64encode(dst_png.data(), dst.size());
        crow::json::wvalue response_json;
        response_json["image"] = dst_base64;
        auto response = crow::response(response_json.dump());
        // auto response = crow::response{os.str()};
        response.add_header("Content-Type", "application/json");
        */
        auto response = crow::response(std::string((const char *)dst_png.data(), dst_png.size()));
        return response;
    });

    app.port(80).multithreaded().run();
}