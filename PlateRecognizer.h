#ifndef PLATERECOGNIZER
#define PLATERECOGNIZER

#include <string>

using namespace std;

class PlateRecognizer {
    public:
        static void Init();
        static void Shutdown();
        static string ReadPlate(const string& imagePath);
    private:
        inline static const string PLATE_READER_URL = "https://api.platerecognizer.com/v1/plate-reader/";
        static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata);
};

#endif