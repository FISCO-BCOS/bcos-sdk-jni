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
    URL https://${URL_BASE}/FISCO-BCOS/bcos-utilities/archive/f6a20a05548da98bf99da68d1ee6413d5186156c.tar.gz
    SHA1 59c6cb92aee7ca6685a4c96528193519c373da0c
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)

hunter_config(bcos-crypto VERSION 1.0.0-rc3-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-crypto/archive/beaeb3d909d1e660fd359f6662bad2c6c73e20a1.tar.gz
    SHA1 cd93fad31ed599c95e7196ed5abe7de1ad2a7930
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)

hunter_config(wedpr-crypto VERSION 1.0.0
    URL https://${URL_BASE}/WeBankBlockchain/WeDPR-Lab-Crypto/archive/caeea48d7fa6c879fef52063cf107873744629b2.tar.gz
    SHA1 03e76f0759a0da0f55cad5d49af510657bb6f343
)

hunter_config(range-v3 VERSION 1.0.0
    URL https://${URL_BASE}/ericniebler/range-v3/archive/a81477931a8aa2ad025c6bda0609f38e09e4d7ec.tar.gz
    SHA1 2d84b639bfd42bb1cbe2fd88f85ff0d1cca25952
)

hunter_config(bcos-boostssl
    VERSION 1.0.0-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/e8e912b15dc7ea769427a761362f285e9a6611e7.tar.gz
    SHA1 91638e350b922d10a8d573b5b9a214ac447dfbb1
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON ARCH_NATIVE=${ARCH_NATIVE} URL_BASE=${URL_BASE}
)

hunter_config(bcos-cpp-sdk
    VERSION 3.3.0-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/005d3d86654ffcb21a9dd78bff41cb13803ac7a7.tar.gz
    SHA1 6b0754fac0128b2d34e4992ce5fe60f3a619d07f
)

hunter_config(bcos-c-sdk
    VERSION 3.3.0-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-c-sdk/archive/d61c7acb52353b77ebf49c6b2be530a0240a06dd.tar.gz
    SHA1 b59fc80d1edc95914ce88866263ebd15590fd827
)
