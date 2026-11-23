/* -----
This code was written by Opus 5.5;
when prompted 'How do you set up cURL to work in cpp?'
the generated text helped me write the PlateRecognizer.cpp file, which is used to read license plates from images using the Plate Recognizer API.:
accessed: November 2026
 -------- */

#include <curl/curl.h>
#include <iostream>
#include <string>

// libcurl calls this as data arrives and always follow this signature: size_t function(char* ptr, size_t size, size_t nmemb, void* userdata)
// this function is called multiple times, once for each chunk of data that arrives, so we need to append it to a string instead of just returning it
// ptr is the data that was received, size is the size of each chunk, nmemb is the number of chunks, userdata is a pointer to a string that we passed in to store the data
static size_t writeCallback(char* ptr, size_t size, size_t nmemb, void* userdata) { 
    auto* out = static_cast<std::string*>(userdata); // auto makes cpp figure out the type automatically
    out->append(ptr, size * nmemb); // since out is pointer -> dereference it to append the data to the string, appends starts at ptr for size * nmemb bytes
    return size * nmemb;
}

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);  // needs to be called once per program
    CURL* curl = curl_easy_init(); // what actaully does the curl request, needs to be called once per request and cleaned up after          
    if (!curl) return 1; // check to see if curl was initialized properly

    std::string response;
    curl_easy_setopt(curl, CURLOPT_URL, "https://example.com"); // set the URL to send the request to
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // follow redirects if the server responds with a redirect
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback); // set the callback function to handle the data that is received, this is called multiple times as data arrives
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response); // set the pointer to the string that will store the data, this is passed to the callback function as userdata

    CURLcode res = curl_easy_perform(curl); // perform the request, this is a blocking call that will wait until the request is complete
    // CURLcode is an enum that contains all the possible error codes that can be returned by curl_easy_perform
    // check to see if the request was successful, if not print the error message
    if (res != CURLE_OK) 
        std::cerr << "curl error: " << curl_easy_strerror(res) << "\n"; // curl_easy_strerror returns a string that describes the error code instead of just the number
    else
        std::cout << response.substr(0, 200) << "...\n";

    // clean up, free from memory to be used again
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}