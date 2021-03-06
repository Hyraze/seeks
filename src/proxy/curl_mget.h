/**
 * The Seeks proxy and plugin framework are part of the SEEKS project.
 * Copyright (C) 2009-2011 Emmanuel Benazera <ebenazer@seeks-project.info>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef CURL_MGET_H
#define CURL_MGET_H

#include <string>
#include <vector>
#include <list>

#include <curl/curl.h>

namespace sp
{
  typedef struct _cbget
  {
    _cbget()
      :_url(NULL),_output(NULL),_proxy_port(0),_headers(NULL),_status(0),_handler(NULL),
       _content(NULL),_content_size(-1)
    {};

    ~_cbget()
    {};

    const char *_url;
    std::string *_output;

    long _connect_timeout_sec;
    long _transfer_timeout_sec;
    std::string _proxy_addr;
    short _proxy_port;
    const std::list<const char*> *_headers; // forced http headers
    int _status;
    CURL *_handler; // optional
    std::string _cookies; // optional
    std::string _http_method; // optional
    std::string *_content; // optional
    int _content_size; // optional
    std::string _content_type; // optional.
  } cbget;

  void* pull_one_url(void *arg_cbget);

  class curl_mget
  {
    public:
      curl_mget(const int &nrequests,
                const long &connect_timeout_sec,
                const long &connect_timeout_ms,
                const long &transfer_timeout_sec,
                const long &transfer_timeout_ms);

      ~curl_mget();

      // direct connection.
      std::string** www_mget(const std::vector<std::string> &urls, const int &nrequests,
                             const std::vector<std::list<const char*>*> *headers,
                             const std::string &proxy_addr, const short &proxy_port,
                             std::vector<int> &status,
                             std::vector<CURL*> *chandlers=NULL,
                             std::vector<std::string> *cookies=NULL,
                             const std::string &http_method="GET",
                             std::string *content=NULL,
                             const int &content_size=-1,
                             const std::string &content_type="");

      std::string* www_simple(const std::string &url,
                              std::list<const char*> *headers,
                              int &status,
                              const std::string &http_method="GET",
                              std::string *content=NULL,
                              const int &content_size=-1,
                              const std::string &content_type="",
                              const std::string &proxy_addr="",
                              const short &proxy_port=0);
    public:
      int _nrequests;
      long _connect_timeout_sec;
      long _connect_timeout_ms;
      long _transfer_timeout_sec;
      long _transfer_timeout_ms;
      std::string _lang;
      const std::list<const char*> *_headers; // forced http headers.

      std::string **_outputs;
      cbget **_cbgets;
  };
} /* end of namespace */

#endif
