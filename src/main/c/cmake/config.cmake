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
    SHA1 555d8d920b8256f6c0129a2d67324d1c2618e212
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON ARCH_NATIVE=${ARCH_NATIVE} URL_BASE=${URL_BASE}
)

hunter_config(bcos-cpp-sdk
    VERSION 3.0.0-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/f975420d9b0dacc12824f043ee30df0da091127b.tar.gz
    SHA1 38efd08d0e270bd58e1211c2450b030307b7a347
)

hunter_config(bcos-c-sdk
    VERSION 3.0.0-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-c-sdk/archive/02ab604378c25e2fd7c6dbc1492277b56ca45de3.tar.gz
    SHA1 ee5c2a4db45a5d81cb3282b815db1686a1dc108e
)
