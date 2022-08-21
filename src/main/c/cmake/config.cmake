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
    URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/67960fac4b94b34477b34df5edcc11d91311c5b1.tar.gz
    SHA1 73944cd84e0e1baf40ab88924ad84923718a81de
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON ARCH_NATIVE=${ARCH_NATIVE} URL_BASE=${URL_BASE}
)

hunter_config(bcos-cpp-sdk
    VERSION 3.0.0-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/ab596cf08f2d1185e7fa3fe0426bd0a3c52d5d24.tar.gz
    SHA1 92434af15462ee096c4d869a09ec450f1ff6a6b8
)

hunter_config(bcos-c-sdk
    VERSION 3.0.0-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-c-sdk/archive/8069f7e91a485f90a437816d6bc0c25b23316ab2.tar.gz
    SHA1 50cbb2b9984c6da98f018739afe9d460a7dd49c8
)
