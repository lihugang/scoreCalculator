#include <stdio.h>
#include <string.h>

#include "../3rd-party/cjson/cJSON.c"
#include "../3rd-party/cjson/cJSON.h"
#include "../3rd-party/curl/curl.h"
#include "../arguments.h"
#include "../debug/macro.h"
#include "../env/env.h"
#include "../globalVars.c"

#define DOWNLOAD_PATH _SERVER_REQUEST_PATH "/row/2024c6-seat-table"

extern const char* seat_table_save_path;

char responseBuffer[MAX_RESPONSE_BUFFER_SIZE] = {0};

static _OUT size_t response_receiver(_IN const void* receiveBuffer) {
  strcat(responseBuffer, receiveBuffer);
  return strlen(receiveBuffer);
};

void download_seat_table(_IN ARGUMENTS* args) {
  assert_not_null(args);
  ++(args->not_used_counters);
  CURL* requestHandle = curl_easy_init();
  char authorization_header[MAX_AUTHORIZATION_HEADER_SIZE] = {0};

  assert_not_null(requestHandle);

  strcpy(authorization_header, "Authorization: ");
  strcat(authorization_header, _SERVER_APP_KEY);
  // Authorization: ${appKey}

  curl_easy_setopt(requestHandle, CURLOPT_URL, DOWNLOAD_PATH);
  CURLcode responseStatus;
  struct curl_slist* requestHeaders = NULL;

  requestHeaders = curl_slist_append(requestHeaders, authorization_header);
  curl_easy_setopt(requestHandle, CURLOPT_HTTPHEADER, requestHeaders);
  curl_easy_setopt(requestHandle, CURLOPT_TIMEOUT, 5);
  curl_easy_setopt(requestHandle, CURLOPT_WRITEFUNCTION, response_receiver);
  curl_easy_setopt(requestHandle, CURLOPT_WRITEDATA, responseBuffer);

  responseStatus = curl_easy_perform(requestHandle);
  if (responseStatus != CURLE_OK) {
    throw_err("Request failed: %s\n", curl_easy_strerror(responseStatus));
  };

  cJSON* parsedResponseRoot = cJSON_Parse(responseBuffer);
  assert_not_null(parsedResponseRoot);

  cJSON* json_obj_responseStatus;
  cJSON* json_obj_responseData;
  // eg. {"status":"ok", "data":{"key":"xxx", "value":"xxx"}}
  json_obj_responseStatus = cJSON_GetObjectItem(parsedResponseRoot, "status");
  assert_not_null(json_obj_responseStatus);
  assert_not_null(json_obj_responseStatus->valuestring);

  json_obj_responseData = cJSON_GetObjectItem(parsedResponseRoot, "data");
  assert_not_null(json_obj_responseData);

  if (strcmp(json_obj_responseStatus->valuestring, "error") == 0) {
    // has error
    assert_not_null(json_obj_responseData->valuestring);
    throw_err("Server responded with an error: %s",
              json_obj_responseData->valuestring);
  };

  cJSON* json_obj_parsedData =
      cJSON_GetObjectItem(json_obj_responseData, "data");
  assert_not_null(json_obj_parsedData);
  assert_not_null(json_obj_parsedData->valuestring);

  FILE* write_fp = fopen(seat_table_save_path, "w");
  assert_not_null(write_fp);
  fwrite(json_obj_parsedData->valuestring, 1,
         strlen(json_obj_parsedData->valuestring), write_fp);
  fclose(write_fp);

  curl_easy_cleanup(requestHandle);

  cJSON_free(parsedResponseRoot);
};