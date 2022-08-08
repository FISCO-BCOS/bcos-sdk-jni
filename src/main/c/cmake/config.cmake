hunter_config(
    Boost VERSION "1.76.0-local"
    URL
    "https://osp-1257653870.cos.ap-guangzhou.myqcloud.com/FISCO-BCOS/FISCO-BCOS/deps/boost_1_76_0.tar.bz2
    https://downloads.sourceforge.net/project/boost/boost/1.76.0/source/boost_1_76_0.tar.bz2
    https://nchc.dl.sourceforge.net/project/boost/boost/1.76.0/boost_1_76_0.tar.bz2"
    SHA1
    8064156508312dde1d834fec3dca9b11006555b6
    CMAKE_ARGS
    CONFIG_MACRO=BOOST_UUID_RANDOM_PROVIDER_FORCE_POSIX
)

hunter_config(OpenSSL VERSION tassl_1.1.1b_v1.4-local
    URL https://${URL_BASE}/FISCO-BCOS/TASSL-1.1.1b/archive/f9d60fa510e5fbe24413b4abdf1ea3a48f9ee6aa.tar.gz
    SHA1 e56121278bf07587d58d154b4615f96575957d6f
)

hunter_config(bcos-utilities VERSION 1.0.0-rc3-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-utilities/archive/632cbeb0412d6ffa3c5217630fe6039f4092f3a4.tar.gz
    SHA1 37b46cd3174ec1b66e28f19e6e8f31f209b61e4b
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)

hunter_config(bcos-crypto VERSION 1.0.0-rc3-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-crypto/archive/34ca9b28f3d2f31948c118a70523df6fa4695e23.tar.gz
    SHA1 64e7b64652ccad212a497d9247fd238fea75578a
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)

hunter_config(bcos-boostssl
    VERSION 1.0.0-rc4-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/f628800173796df5eaab3366fd75d929a08eaa5b.tar.gz
    SHA1 22d28dcacfc01fd11573fc3f68b203707b56692a
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON ARCH_NATIVE=${ARCH_NATIVE} URL_BASE=${URL_BASE}
)

hunter_config(bcos-cpp-sdk
    VERSION 3.0.0-rc4-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/c46cef4c278cff2c0412f14f5ff6a6d2724c3886.tar.gz
    SHA1 0010ee407c804063a5d8c269624cb432998836b5
)

hunter_config(bcos-c-sdk
    VERSION 3.0.0-rc4-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-c-sdk/archive/e98369a9360e10285bbb1ae3efacdfc13e8f76ff.tar.gz
    SHA1 412ca97ff9e548664f373ad65b86536b153f3648
)
