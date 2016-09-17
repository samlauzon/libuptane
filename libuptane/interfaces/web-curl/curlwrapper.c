
#include <curl/curl.h> 
#include <stdlib.h> 
#include "curlwrapper.h" 

CURL *curl = NULL;       // Handle to curl instance
uint8_t is_running = 0;  // 1: Fetch active; 0: Fetch inactive; 

#define debug_output(fmt, ...) fprintf(stderr, fmt, ##__VA_ARGS__)   // Debug output     

void *data_callback = NULL; // Data callback hook into the main application

static size_t fetch_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
   debug_output("%s", contents);
   ((void (*)(void)) data_callback)(); // Call the callback in main application

   is_running = 0; 
   return ( size * nmemb ); 
}

void curl_init( void *callback )  
{ 
   curl = curl_easy_init(); 
   data_callback = callback; 
} 

void curl_setcallback( void *fn ) 
{
   data_callback = fn; 
}

void *curl_getcallback( void ) 
{
   return data_callback; 
}

uint8_t curl_fetch( const char *url ) 
{
    if(!curl) 
       return -1; 

    if(is_running)
       return -2; // "Is running"  // TODO: Fix with enum? 

    CURLcode result; 
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, fetch_callback);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0); // Bad - but works without a cert.
    //curl_easy_setopt(curl, CURLOPT_CAPATH, ".");     // Better - but it doesn't like my bundle.

    result = curl_easy_perform(curl); 
    
    if( result != CURLE_OK ) 
    {
       switch(result) 
       {
          case CURLE_SSL_CACERT:
             debug_output(" [cURL] Error with SSL Certificate\n");
             break;
          default: 
             debug_output("Error: %d\n", result);
       } 
       return -1; 
    } 

    // Query is running, Do not allow a second until this one clears.
    is_running = 1; 
    return 0; 
}

void curl_fini( void ) 
{
    curl_easy_cleanup(curl); 
}

