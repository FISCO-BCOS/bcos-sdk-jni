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

hunter_config(OpenSSL VERSION tassl_1.1.1b_v1.4-63b60292)

hunter_config(bcos-utilities VERSION 1.0.0-rc2-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-utilities/archive/55d6bf357719aa030e3898b060b4a3ff2476434b.tar.gz
	SHA1 d0aeb11cf064a5e9793c50dd7bb8487e2d251f02
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)

hunter_config(bcos-crypto VERSION 1.0.0-rc2-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-crypto/archive/86fdc960741bd26cea3c9f04e61f138f508c7add.tar.gz
    SHA1 53dcac50016f5e1bd517ae8d595b586e358ad118
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON SM2_OPTIMIZE=ON
)

hunter_config(bcos-boostssl VERSION 1.0.0-rc3-local
	URL https://github.com/LucasLi1024/bcos-boostssl/archive/b7dfe34bab17f405d033072e1880065b8efbc8f8.tar.gz
	SHA1 76152c6664de5616fd3951a5d3296996cf32e8d7
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-rc4-local
	URL https://github.com/LucasLi1024/bcos-cpp-sdk/archive/88735f813c1fa3119a4705a84f4aee6b2bc9581f.tar.gz
	SHA1 f5a91e8cbb21eb2dac4ce4f30c6e622ec8163fc8
)

hunter_config(bcos-c-sdk
	VERSION 3.0.0-rc4-local
	URL https://github.com/LucasLi1024/bcos-c-sdk/archive/2b2995c235179df09fdaf8a2bcf0e2debb167db2.tar.gz
	SHA1 1bf2d84331c89634912756b5c88e744588f8dafd
)