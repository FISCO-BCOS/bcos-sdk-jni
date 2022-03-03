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

hunter_config(bcos-utilities VERSION 1.0.0-rc1-f12788a1 CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON)
hunter_config(OpenSSL VERSION tassl_1.1.1b_v1.4-63b60292)

hunter_config(bcos-crypto VERSION 3.0.0-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-crypto/archive/eb042091bb6aef907aecfe84dfe365da006b2952.tar.gz
    SHA1 dbfe8d9f79311fd62c8f69e0f870b1150077f4ed
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON SM2_OPTIMIZE=ON
)

hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/8778a68a247d442ae6f4721271ba80fdd0164413.tar.gz
	SHA1 a46a65ac84c009177bd50a9c1f2bb0e2ba58023e
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/b50e0cfb36d1cdbd5f6a618d4d96c5cd9a510270.tar.gz
	SHA1 4121ffe834b48c29f1227db1f3212831ff2c7d4b
)

hunter_config(bcos-c-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-c-sdk/archive/fb6338eea3bfcea2884d7603f440a56a1dd71fb0.tar.gz
	SHA1 9a8d5f0a7ddc81b7fad87a0f1482ac40e9765c57
)