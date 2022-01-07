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

hunter_config(bcos-utilities VERSION 3.0.0-local
    URL https://${URL_BASE}/FISCO-BCOS/bcos-utilities/archive/fbe6d67de2e5d17f2ad35fd1730397239aa9373a.tar.gz
	SHA1 9cf973988b201d187e89aba69b2dd6d843a9612c
    CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)

hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/fcba29209cc15d84598e4aa172fcd823b85bf802.tar.gz
	SHA1 d156e59de6fa45f9577c764da38dc1b6ac0a114d
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/7710a57cb827b7b14547cedff32f3178597405dd.tar.gz
	SHA1 35d874773fb25376965a2b055ce837a5c4244a64
)

hunter_config(bcos-c-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-c-sdk/archive/51ebd29f1a8e36326d6dcde863448a12ed604db4.tar.gz
	SHA1 7f8f2685f25e08a99cda7baf21ca16ea5a625d38
)