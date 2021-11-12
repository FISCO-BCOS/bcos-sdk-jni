hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/9b0092385a8271d566bd6d0c392722e031946dba.tar.gz"
	SHA1 9c2f6f6a1fd06c9c1a74ee4e04507c95bd5122d8
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/60fec51ae6b1572389b91f40d0519879a9fcb9b1.tar.gz"
	SHA1 fdc08b966c900632bfae8fe4db952a84c0264dba
)

hunter_config(bcos-framework VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-framework/archive/1f7c7de6e0b18486f1dc25de74bf0db148c2e429.tar.gz
    SHA1 f18a5c0c5c4e2c2e12451a0d02a90a446122fb1a
	CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)

# Do not remove this
hunter_config(
    Boost
    VERSION ${HUNTER_Boost_VERSION}
    CMAKE_ARGS
    CONFIG_MACRO=BOOST_UUID_RANDOM_PROVIDER_FORCE_POSIX
)