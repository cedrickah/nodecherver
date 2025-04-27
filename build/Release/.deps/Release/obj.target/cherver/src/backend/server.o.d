cmd_Release/obj.target/cherver/src/backend/server.o := cc -o Release/obj.target/cherver/src/backend/server.o ../src/backend/server.c '-DNODE_GYP_MODULE_NAME=cherver' '-DUSING_UV_SHARED=1' '-DUSING_V8_SHARED=1' '-DV8_DEPRECATION_WARNINGS=1' '-D_GLIBCXX_USE_CXX11_ABI=1' '-D_LARGEFILE_SOURCE' '-D_FILE_OFFSET_BITS=64' '-D__STDC_FORMAT_MACROS' '-DOPENSSL_NO_PINSHARED' '-DOPENSSL_THREADS' '-DBUILDING_NODE_EXTENSION' -I/home/zotcha/.cache/node-gyp/20.18.2/include/node -I/home/zotcha/.cache/node-gyp/20.18.2/src -I/home/zotcha/.cache/node-gyp/20.18.2/deps/openssl/config -I/home/zotcha/.cache/node-gyp/20.18.2/deps/openssl/openssl/include -I/home/zotcha/.cache/node-gyp/20.18.2/deps/uv/include -I/home/zotcha/.cache/node-gyp/20.18.2/deps/zlib -I/home/zotcha/.cache/node-gyp/20.18.2/deps/v8/include  -fPIC -pthread -Wall -Wextra -Wno-unused-parameter -m64 -O3 -fno-omit-frame-pointer  -MMD -MF ./Release/.deps/Release/obj.target/cherver/src/backend/server.o.d.raw   -c
Release/obj.target/cherver/src/backend/server.o: ../src/backend/server.c \
 ../src/backend/socket.h ../src/backend/request.h \
 ../src/backend/response.h ../src/backend/server.h
../src/backend/server.c:
../src/backend/socket.h:
../src/backend/request.h:
../src/backend/response.h:
../src/backend/server.h:
