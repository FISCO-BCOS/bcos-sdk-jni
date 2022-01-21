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
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/685288e31c45ab983fc68b789ba81838948e2991.tar.gz
	SHA1 ba076ca3770b5a59e58dcc1772c99718d29f3854
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/f81727f912280d3d6814fde44c21116fc04982d4.tar.gz
	SHA1 96c003fec575fe4f6b66997e99b9dd9c34a24c62
)

hunter_config(bcos-c-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-c-sdk/archive/4e9ea73bc09aebcd20edf5c103dec0bc1385686c.tar.gz
	SHA1 5136bdfc33c645dda9490211bffce5c2395b7a05
)