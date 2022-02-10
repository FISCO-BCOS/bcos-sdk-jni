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

hunter_config(bcos-utilities VERSION 3.0.0-rc2-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-utilities/archive/1a1c28d2b87dc6dd9c02d9737d9cb3c434abc664.tar.gz
	SHA1 b8cd65db849be95bf37b3ab3fba0953fd0f59675
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)

hunter_config(bcos-crypto VERSION 3.0.0-rc3-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-crypto/archive/e2d2af7195a725eeab31da679f12d20c4838e0a1.tar.gz
	SHA1 e7ed758bfbcbd6db3a9d6dd99ba5aca022eab7c5
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON SM2_OPTIMIZE=ON
)

hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/16ce8a9f1125b86b18e888bcc1267d0ec6bf2d38.tar.gz
	SHA1 e887ef537a387dcb122f5fc30ac91b5889dac412
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/bd8a0059d742bfdc112a1b0ef41db158903db71c.tar.gz
	SHA1 412fc661af95ad37d4b5f6627b483595effa76e1
)

hunter_config(bcos-c-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-c-sdk/archive/1735a5faf2927c3baa934c5c09fc5022ce669ff1.tar.gz
	SHA1 1f43b6841ee21a10b4bdfb2e2b3968289f9caf6a
)