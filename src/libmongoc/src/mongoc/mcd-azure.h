/**
 * Copyright 2022 MongoDB, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MCD_AZURE_H_INCLUDED
#define MCD_AZURE_H_INCLUDED

#include "mongoc-prelude.h"

#include <mongoc/mongoc.h>

#include <mongoc/mongoc-http-private.h>

#include <mcd-time.h>

/**
 * @brief An Azure OAuth2 access token obtained from the Azure API
 */
typedef struct mcd_azure_access_token {
   /// The access token string
   char *access_token;
   /// The resource of the token (the Azure resource for which it is valid)
   char *resource;
   /// The HTTP type of the token
   char *token_type;
   /// The duration after which it will the token will expires. This is relative
   /// to the "issue time" of the token.
   mcd_duration expires_in;
} mcd_azure_access_token;

/**
 * @brief Try to parse an Azure access token from an IMDS metadata JSON response
 *
 * @param out The token to initialize. Should be uninitialized. Must later be
 * destroyed by the caller.
 * @param json The JSON string body
 * @param len The length of 'body'
 * @param error An output parameter for errors
 * @retval true If 'out' was successfully initialized to a token.
 * @retval false Otherwise
 *
 * @note The 'out' token must later be given to @ref
 * mcd_azure_access_token_destroy
 */
bool
mcd_azure_access_token_try_init_from_json_str (mcd_azure_access_token *out,
                                               const char *json,
                                               int len,
                                               bson_error_t *error)
   BSON_GNUC_WARN_UNUSED_RESULT;

/**
 * @brief Destroy and zero-fill an access token object
 *
 * @param token The access token to destroy
 */
void
mcd_azure_access_token_destroy (mcd_azure_access_token *token);

/**
 * @brief An Azure IMDS HTTP request
 */
typedef struct mcd_azure_imds_request {
   /// The underlying HTTP request object to be sent
   mongoc_http_request_t req;
} mcd_azure_imds_request;

/**
 * @brief Initialize a new IMDS HTTP request
 *
 * @param out The object to initialize
 *
 * @note the request must later be destroyed with mcd_azure_imds_request_destroy
 */
void
mcd_azure_imds_request_init (mcd_azure_imds_request *out);

/**
 * @brief Destroy an IMDS request created with mcd_azure_imds_request_init()
 *
 * @param req
 */
void
mcd_azure_imds_request_destroy (mcd_azure_imds_request *req);

#endif // MCD_AZURE_H_INCLUDED