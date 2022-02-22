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

hunter_config(bcos-boostssl
    VERSION 1.0.0-rc2-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/7fe9b9018914c5a1653822fd8e074b6c2a0d6488.tar.gz
    SHA1 19f596180e5d00a03227b42fbc80e788e3933090
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON URL_BASE=${URL_BASE}
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-rc2-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/89d57afc1a009911e10f65ff7cebf4ca58406e46.tar.gz
	SHA1 8ea4184225597afdb6844e97e005b50c01d9cebb
)

hunter_config(bcos-c-sdk
	VERSION 3.0.0-rc2-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-c-sdk/archive/91404d3ea6fc7dbd44cb39def0d82ca5a09e398a.tar.gz
	SHA1 e68d53bdbd5991205869bfab78d2304a2b474545
)