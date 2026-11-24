#include "PlateRecognizer.h"
#include <iostream>
#include "dotenvparse.h"

using namespace std;


// repliactes this curl command: curl -X POST -F "upload=@/tmp/car.jpg" 
// -H "Authorization: Token YOUR_API_TOKEN" 
// https://api.platerecognizer.com/v1/plate-reader/
// Example curl command from https://api.platerecognizer.com/v1/api-reference/#tag/Snapshot-Cloud
string PlateRecognizer::ReadPlate(const string& imagePath) {
    // Load the .env file to get the API token
    DotenvParse::LoadEnvFile(".env");
    string apiToken = DotenvParse::envVariables["PLATE_API_KEY"];

    CURL* curl = curl_easy_init();
    if (!curl) {
        return "Failed to initialize curl";
    }

    string response;
    // -H "Authorization: Token ..."
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, ("Authorization: Token " + apiToken).c_str());

    // -F "upload=@/tmp/car.jpg"
    curl_mime* form = curl_mime_init(curl);
    curl_mimepart* field = curl_mime_addpart(form);
    curl_mime_name(field, "upload");
    curl_mime_filedata(field, imagePath.c_str());

    curl_easy_setopt(curl, CURLOPT_URL, PLATE_READER_URL.c_str());
    curl_easy_setopt(curl, CURLOPT_MIMEPOST, form);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cout << "curl error: " << curl_easy_strerror(res) << endl;
    } else {
        long status = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status);
        cout << "HTTP status: " << status << endl;
    }

    // Clean up, free from memory to be used again
    curl_mime_free(form);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    return response; // return the response from the API, which is a JSON string
}

// used to handle the data once it's recieved already, doesn't actually fetch any data
// callback functions must have this signature: size_t function(char* ptr, size_t size, size_t nmemb, void* userdata)
// is called multiple times, once for each chunk of data that arrives, so we need to append it to a string instead of just returning it
size_t PlateRecognizer::writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata) {
    string* response = (string*) userdata;   // turn the void* back into a string pointer
    size_t bytes = size * nmemb;             // how many bytes arrived in this chunk

    for (size_t i = 0; i < bytes; i++) {
        response->push_back(ptr[i]);         // add each byte to the end of the string, -> is used instead of . for pointers to access members of the object
    }

    return bytes;                            // tell curl we handled all of them, needs it 
}
