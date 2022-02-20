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

hunter_config(bcos-crypto VERSION 3.0.0-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-crypto/archive/52cf6db2c082ec723f5d150abaae312c8dd293d0.tar.gz
	SHA1 531f31424c3377a9bc8b68a739cfa9ce95f5e8e0
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON SM2_OPTIMIZE=ON
)

hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/70e65dd7855880730c7a826b91a7c6792e98cb64.tar.gz
	SHA1 e266701968fcff1546daaa04586076a4364fee21
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/fb263d1c877fae9dd617a21758b9dad6a2cfd733.tar.gz
	SHA1 902d037a88995d04d4f42695c9253b2bc8afdbb2
)

hunter_config(bcos-c-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-c-sdk/archive/a5ca8792bf4cff54d8d00a2893b72f53491b6e52.tar.gz
	SHA1 5492f249ae6ef84c60ae8dd2ba7d53231815171a
)