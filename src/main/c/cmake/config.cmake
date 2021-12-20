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

hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/4f60c9b070242b91731e239f8e30a0fce76da1a8.tar.gz
	SHA1 e095c2f6544f5b0c06ec6314bc95772a6d3a2fc4
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/1757093f9444e4abb6cd7f12fb1e48d744fe596e.tar.gz
	SHA1 21fd65eb808bf5c286e55d94eb36ab09c0702699
)

hunter_config(bcos-c-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-c-sdk/archive/9201db19d6184c28ef3be037eca3df9befc31699.tar.gz
	SHA1 0c6339d722b2d4258b734101fcef21ee77f4d130
)