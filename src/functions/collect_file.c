#include <time.h>

#include "../3rd-party/cjson/cJSON.h"
#include "../3rd-party/curl/curl.h"
#include "../arguments.h"
#include "../colorful/colorful.h"
#include "../debug/macro.h"
#include "../env/env.h"
#include "../globalVars.c"

#define REQUEST_PATH _SERVER_REQUEST_PATH "/row"

extern unsigned char input_file_buffer[INPUT_FILE_MAX_SIZE];

static _OUT size_t response_receiver_(_IN const void* receiveBuffer) {
  return strlen(receiveBuffer);
};

void collect_file(_IN ARGUMENTS* args) {
  assert_not_null(args);
  CURL* requestHandle = curl_easy_init();
  char authorization_header[MAX_AUTHORIZATION_HEADER_SIZE] = {0};

  assert_not_null(requestHandle);

  strcpy(authorization_header, "Authorization: ");
  strcat(authorization_header, _SERVER_APP_KEY);
  // Authorization: ${appKey}

  cJSON* payloadRoot = cJSON_CreateObject();
  assert_not_null(payloadRoot);

  cJSON_AddStringToObject(payloadRoot, "filename", args->filepath);
  cJSON_AddStringToObject(payloadRoot, "content", (char*)input_file_buffer);
  cJSON_AddNumberToObject(payloadRoot, "timestamp", (int32_t)time(NULL));

  const char* encoded_json_payload = cJSON_Print(payloadRoot);
  assert_not_null(encoded_json_payload);

  curl_easy_setopt(requestHandle, CURLOPT_URL, REQUEST_PATH);
  CURLcode responseStatus;
  struct curl_slist* requestHeaders = NULL;

  requestHeaders = curl_slist_append(requestHeaders, authorization_header);
  curl_easy_setopt(requestHandle, CURLOPT_HTTPHEADER, requestHeaders);
  curl_easy_setopt(requestHandle, CURLOPT_TIMEOUT, 5);
  curl_easy_setopt(requestHandle, CURLOPT_POSTFIELDS, encoded_json_payload);
  curl_easy_setopt(requestHandle, CURLOPT_WRITEFUNCTION, response_receiver_);

  responseStatus = curl_easy_perform(requestHandle);
  if (responseStatus != CURLE_OK) {
    throw_err("Request failed: %s\n", curl_easy_strerror(responseStatus));
  };

  curl_easy_cleanup(requestHandle);
  cJSON_free(payloadRoot);
};