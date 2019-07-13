Interesting functions
=====================
ngx_worker_process_cycle - main worker loop
ngx_process_events_and_timers - main event processing cycle
ngx_epoll_process_events - main event loop
ngx_event_accept
ngx_http_init_connection
ngx_handle_read_event

To handle the incoming connection:
ngx_http_wait_request_handler

Handle http request: these functions are prefixed with ngx_http_
--------------------
create_request - ngx_http_request.c
process_request_line
parse_request_line - ngx_http_parse.c
process_request_uri
process_request_headers - to parse the key-value headers
process_request
handler
rewrite_handler(request_t* r)

http core phases (ngx_http_core_module.c)
----------------
ngx_http_core_run_phases - for writing the response
ngx_http_core_rewrite_phase



ngx_epoll_process_events - main event loop
-------------------------------------------
ngx_epoll_module.c

queries the number of events from the event_list

Line 836: for loop to process the events we have

retrieves the ngx_connection_t object from the event.

We call the connection's read method which is most likely: ngx_http_wait_request_handler

ngx_http_wait_request_handler
-----------------------------
ngx_http_request.c

ngx_http_connection_t - represents the http connection type

We need to allocate a buffer(ngx_buf.c) for the client's http header - can be specified in the nginx.conf
Let's say the header buff size is 1024 bytes - will be allocated (ngx_palloced)

Now can call ngx_unix_recv(ngx_recv.c) to read buff size (ie 1024) the bytes from the connection.

We read the header: "GET / HTTP/1.1\r\nHost: 127.0.0.1:8090\r\nUser-Agent: curl/7.64.0\r\nAccept: */*\r\n\r\n" 

The above header read was just 78 bytes.

What happens if the header is of enourmous size? Attacker can exploit this?? Or headers after the buff size will be dropped?

ngx_http_create_request is called. This first creates a new pool with size 4096. It uses this pool
to allocate a ngx_http_request_t object.

**ngx_http_request_t** is very important data structure!!!! And is quite big! 1392 bytes!
This represents the current request we are processing.

Sets the read event handler to be ngx_http_block_reading.

Pulls in the http configurations. (ngx_http_core_main_conf_t)

Once we have allocated the http_request_t associated with the connection
we can start processing it.

ngx_http_process_request_line
-----------------------------
ngx_http_request.c

Line 964 start an infinite processing loop.

- read_request_header(http_request_t*)
    The header we have read before is now considered. Since we read it we just return from this func.

- parse_request_line(header data pointer) - request line is the "GET / HTTP/1.1\r\n"
    http/ngx_http_parse
    (gdb) p b->pos
$118 = (u_char *) 0x5578cf188b50 "GET / HTTP/1.1\r\nHost: 127.0.0.1:8090\r\nUser-Agent: curl/7.64.0\r\nAccept: */*\r\n\r\n"

    Reads each character one by one...
    - Parses the http method type. (GET, POST etc.)
    - Parses the URI
    - Parses the http protocol type and the major and minor digit

- process_request_uri - ngx_http_request.c

- process_request_headers - parse the headers (key: value)

   Load the configs based on the host header.
   Start parsing the header's key, values and call a handler function associated with a well known
   header field. Liek Host, User-Agent etc 

   - parse_header_line
        "Host: 127.0.0.1:8090\r\nUser-Agent: curl/7.64.0\r\nAccept: */*\r\n\r\n"
        Parses the key("Host") and value("127.0.0.1:8090")
   
   - process_host
        This function processes the Host value
            In our case "127.0.0.1:8090"

        - validate_host("127.0.0.1:8090")
            Parses the value of the host by iterating over its chars.
    
    - process_user_agent (after parsing the User-Agent field) 
        ngx_http_process_user_agent is handler function to deal with it
        Processing the user agent is weird. We try to look for well known agents as substrings
        inside the header value(curl/7.64.0). We do this with ngx_strstrn(s1, s2, n).
        #security, can we exploit this brute force string search?

    The key(Accept) does not have a handler function associated with it.

    Now are done with parsing the headers.

    - process_request_header()
    - process_request(http_request r)

        Sets up handlers on the connection:
            - request_handler
            - block_reading
    - ngx_http_hander()
        Sets up the write handler:
            ngx_http_core_run_phases

    - ngx_http_core_run_phases(request_t* r) - IMPORTANT!
       
run_phases(request_t* r) - IMPORTANT!!!!
========================
ngx_http_core_module.c

We grab the core_main_conf_t for our http config.
This config coontains a `phase_engine` member that contains the handlers for the phases.
ngx_http_phase_handler_t -> we have these defined to handle the write phases.
    - rewrite_phase, etc

- ngx_http_core_rewrite_phase(request_t*, phase_handler_t*)
  ---------------------------
    - coolkit stuff (if applicable) - comes with OpenResty
    - rewrite_handler(request_t*)

        Loads the rewrite_loc_conf_t data.

- find_config_phase(request_t*, phase_handler_t*)

- post_rewrite_phase(request_t*, phase_handler_t*)

- generic_phase(request_t*, phase_handler_t*)
    - limit_req_handler(request*)
    - limit_conn_handler(request*)

- access_phase(request_t*, phase_handler_t*)
    - access_handler(request*) - ngx_http_access_module.c

    - auth_basic_handler(request*) - ngx_http_auth_basic_module.c

- post_access_phase

- generic_phase

    - try_files_handler(request_t* r)

    - mirror_handler(request_t* r)

- content_phase
    - index_handler(request_t* r) - ngx_http_index_module.c
        - to load the index.html
        
        - map_uri_to_path() - gets the absolute file path for the index
        
        - ngx_open_cached_file

        - ngx_http_internal_redirect(request, uri, args)

        - autoindex_handler

        - static_handler(request*)
            - discard_request_body(request)
            - action: "sending response to client"
            
            - send_header(request)
                
                - headers_filter - ngx_http_header_filter_module.c - THIS CREATES THE HEADER!!!
                - next_header_filter
                    - charset_header_filter
                        - destintation_charset
                    - Sets header like: "Accept-Ranges" (https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Accept-Ranges)
                - Sets the Status line: "200 OK"
                - "ETag"
                - "Content-Type"
                - "Content-Length"
                - "Connection: keep-alive"
               
            Finally writes out the header:
                "200 OK\r\nServer: openresty/1.13.6.2\r\nDate: Fri, 05 Jul 2019 22:53:43 GMT\r\nContent-Type: text/html\r\nContent-Length: 4490\r\nLast-Modified: Wed, 03 Jul 2019 21:45:09 GMT\r\nConnection: keep-alive\r\nETag: \"5d1d21e5-118a\"\r\nAccept-Ranges: bytes\r\n\r\n"
                Header size: 246

            - Calls the ngx_http_write_filter 
            
Call the **send_chain** which sends the header/body!! Most likely we just set up the send_chain with
the header values and later we set up the same with the body and do the actual send at once.
                
Once we wrote the header we go back to ngx_http_static_handler.

    - ngx_http_output_filter

    - body_filter
        - next_body_filter
        - copy_filter
        - ngx_output_chain()
    - trailers_filter
    - chunked_body_filter - to prepare the body for sending - needs to allocate buffer for it
    - write_filter - puts the HEADER buffer and the BODY buffer into a unified buffer
        - ngx_linux_sendfile_chain - to actualyl send now
            - uses iovec to send the buffers
            - ngx_output_chain_to_iovec
                

ngx_output_chain_to_iovec
-------------------------
Sends the data. 
Data to be sent can be in file or memory.
ngx_chain_t contains a linked list of buffers (header, body, '\r\n\', '\r\n')
We iovec those buffers to send.

ngx_linux_send_file_chain -- THIS IS THE NETWORK SEND routine
-------------------------

Sets up the iovec with the buffers as described above. 
There are all sorts of TCP optimizations that could be done like tcp_nodelay, tcp_nopush
If the buffers are in memory, like with lua output and not in file we can just write.
Otherwise if static file we call ngx_linux_sendfile, if in memory ngx_writev

ngx_writev_chain.c - ngx_writev




Lua content delivery
====================
ngx_lua-0.10.13/src/ngx_http_lua_contentby.c
ngx_http_lua_util.h
lua_common.h
ngx_http_lua_output.c - to grab the output produced by ngx_echo

ngx_http_lua_ctx_t is the main data structure.

Functions (prefixed with ngx_http_lua_):
---------
content_handler
content_by_chunk
create_ctx(request*)
ngx_http_lua_cache_loadbuffer
send_header_if_needed
send_chain_link
new_thread
run_thread
ngx_say 
ngx_echo
pcre_malloc
pcre_free

capture_filter -> THIS ONE will be called when we are about to send the body - grabs the computed lua string


LuaJIT:
lj_BC_FUNCC
lua_resume
lj_vm_resume



Memory Allocation
=================

nginx uses pools. core/ngx_palloc.c

ngx_memalign - ngx_alloc.c -> to create a pool

ngx_create_pool(size_t size, ngx_log_t *log); - creates a pool with 'size'

Small object allocation vs big happens differently.
A given pool has blocks linked together. 

Memory alignment is also considered. Alignment: sizeof(unsigned long) - 8 bytes on x64


Utility data structures
=======================

ngx_rbtree - for logn lookup

ngx_array_t - ngx_array.h
-----------
    - contigous memory area with known size and memory pool
    - each array has a pool associated with. The number of elements it has. Size of each element. The pointer to the elements. The size.

ngx_str_t
---------
    - size_t length
    - uchar* data




