hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/9b0092385a8271d566bd6d0c392722e031946dba.tar.gz"
	SHA1 9c2f6f6a1fd06c9c1a74ee4e04507c95bd5122d8
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/42add22b27b166b51c414a588ed2ab0487e7f7f2.tar.gz"
	SHA1 5689c4b3335415e20ff5eb30b633ed251e4357de
)

hunter_config(bcos-framework VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-framework/archive/1f7c7de6e0b18486f1dc25de74bf0db148c2e429.tar.gz
    SHA1 f18a5c0c5c4e2c2e12451a0d02a90a446122fb1a
	CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)