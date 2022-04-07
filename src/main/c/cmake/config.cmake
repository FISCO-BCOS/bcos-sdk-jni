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
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/1c9cecf7ec9ed59d0bdaa9f390c618c8f4208cf2.tar.gz
	SHA1 95774f3638b4bcb27a6708fca0a28389a7cfa9c3
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-rc3-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/8a6f3e0d122dc83c0166b9ac6020db28ede8950c.tar.gz
	SHA1 c4d50f4f3cf9f88520a3c45718d4044bfcad4b93
)

hunter_config(bcos-c-sdk
	VERSION 3.0.0-rc3-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-c-sdk/archive/f2af9e090d2b4078c50c7f0087d0108e338b03af.tar.gz
	SHA1 534b534d595aa41d13a7b9fd38680340f80be53f
)