#include <assert.h>
#include <stdlib.h>
#include <node_api.h>
#include "./backend/http.h"
#include "./backend/server.h"

napi_ref js_handler_ref = NULL;
napi_env env;

void setup_req_object(napi_env env, napi_value req_value, request req) {
    char url_buffer[256];
    strncpy(url_buffer, req.url, sizeof(url_buffer) - 1);
    url_buffer[sizeof(url_buffer) - 1] = '\0';

    napi_value url_value;
    napi_create_string_utf8(env, url_buffer, NAPI_AUTO_LENGTH, &url_value);
    napi_set_named_property(env, req_value, "url", url_value);
}

napi_value ResWriteHead(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 1;
    napi_value args[1];
    napi_value this_arg;

    status = napi_get_cb_info(env, info, &argc, args, &this_arg, NULL);
    if (status != napi_ok || argc < 1) {
        napi_throw_type_error(env, NULL, "Expected 1 argument");
        return NULL;
    }

    response *res;
    status = napi_unwrap(env, this_arg, (void**)&res);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Failed to unwrap response");
        return NULL;
    }

    int32_t status_code;
    status = napi_get_value_int32(env, args[0], &status_code);
    if (status != napi_ok) {
        napi_throw_type_error(env, NULL, "Invalid status code");
        return NULL;
    }

    (res->write_head)(res, status_code);

    return NULL;
}


void setup_res_object(napi_env env, napi_value res_value, response res) {
    napi_property_descriptor desc = { 
        "write_head", 0, ResWriteHead, 0, 0, 0, napi_default, 0 
    };
    napi_define_properties(env, res_value, 1, &desc);
}


void c_handler_bridge(request req, response res) {
    napi_handle_scope scope;
    napi_open_handle_scope(env, &scope);

    napi_value js_handler;
    napi_get_reference_value(env, js_handler_ref, &js_handler);

    napi_value global;
    napi_get_global(env, &global);

    napi_value req_value;
    napi_create_object(env, &req_value);

    napi_value res_value;
    napi_create_object(env, &res_value);

    setup_req_object(env, req_value, req);
    setup_res_object(env, res_value, res);

    napi_value argv[2] = { req_value, res_value };

    napi_call_function(env, global, js_handler, 2, argv, NULL);

    napi_close_handle_scope(env, scope);
}

napi_value SListen(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 2;
    napi_value args[2];
    napi_value this_arg;

    status = napi_get_cb_info(env, info, &argc, args, &this_arg, NULL);
    if (status != napi_ok || argc < 2) {
        napi_throw_type_error(env, NULL, "Expected 2 arguments");
        return NULL;
    }

    server *http_server; 
    status = napi_unwrap(env, this_arg, (void**)&http_server);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Failed to unwrap native object");
        return NULL;
    }

    int32_t port;
    status = napi_get_value_int32(env, args[0], &port);
    if (status != napi_ok) {
        napi_throw_type_error(env, NULL, "Invalid port");
        return NULL;
    }

    napi_valuetype valuetype;
    status = napi_typeof(env, args[1], &valuetype);
    if (status != napi_ok || valuetype != napi_function) {
        napi_throw_type_error(env, NULL, "Handler must be a function");
        return NULL;
    }

    if (js_handler_ref) {
        napi_delete_reference(env, js_handler_ref);
    }
    status = napi_create_reference(env, args[1], 1, &js_handler_ref);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Failed to create reference to handler");
        return NULL;
    }

    env = env;

    (http_server->listen)(http_server, port, (handler)c_handler_bridge);

    return NULL;
}

napi_value CreateServer(napi_env env, napi_callback_info info) {
    napi_status status;

    server *http_server = (server*)malloc(sizeof(server));
    if (http_server == NULL) {
        napi_throw_error(env, NULL, "Memory allocation failed");
        return NULL;
    }

    *http_server = create_server();

    napi_value server_obj;
    status = napi_create_object(env, &server_obj);
    if (status != napi_ok) {
        free(http_server);
        return NULL;
    }

    status = napi_wrap(env,
      server_obj,
      http_server,
      NULL,
      NULL,
      NULL
    );
    if (status != napi_ok) {
        free(http_server);
        return NULL;
    }

    napi_property_descriptor desc = { 
        "listen", 0, SListen, 0, 0, 0, napi_default, 0 
    };
    status = napi_define_properties(env, server_obj, 1, &desc);
    if (status != napi_ok) {
        free(http_server);
        return NULL;
    }

    return server_obj;
}

// Module init
napi_value Init(napi_env env, napi_value exports) {
    napi_property_descriptor desc = { 
        "create_server", 0, CreateServer, 0, 0, 0, napi_default, 0 
    };
    napi_define_properties(env, exports, 1, &desc);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
