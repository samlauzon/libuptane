
#include <curl/curl.h> 
#include "curlwrapper.h" 


static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
   fprintf(stderr, "%s", contents);
   return ( size * nmemb ); 
}

void curl_init( void )  
{ 
   CURL *curl = curl_easy_init(); 
    if(curl) 
    { 
       CURLcode result; 
       curl_easy_setopt(curl, CURLOPT_URL, "http://google.com");
       curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
       result = curl_easy_perform(curl); 
       if( result == CURLE_OK ) 
       {
          fprintf(stderr, "Success!\n");    
       }
       else
       {
          switch(result) 
          {
             case CURLE_SSL_CACERT:
                fprintf(stderr, " [cURL] Error with SSL Certificate\n");
                break;
             default: 
                fprintf(stderr, "Error: %d\n", result);
          } 
       } 
       curl_easy_cleanup(curl); 
    } 
}


