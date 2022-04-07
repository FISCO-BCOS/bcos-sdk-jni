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
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/9b61e6ef1dd88468bfe7984800f4efc264b8ef47.tar.gz
	SHA1 5aed5b0e685332741c06cbce897fb5d6e0932762
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-rc3-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/06eb1411a98cb35ea5afb62dec76c533d6fe0f3c.tar.gz
	SHA1 62affa670f9bcbb2cdb8097b0b13dd09d13d130d
)

hunter_config(bcos-c-sdk
	VERSION 3.0.0-rc3-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-c-sdk/archive/fae949a09e479966696f91abdd8e0ebf630d19a8.tar.gz
	SHA1 bef3d457cea1a8b021835dd5c41c69914261904b
)
