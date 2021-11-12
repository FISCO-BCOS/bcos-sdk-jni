hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/9e5df568b9e35465cd7e47231f5df629b6fa1083.tar.gz"
	SHA1 8d0e46116f1c4ad5a316903a4662538e7eaab305
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/48e75b0b9f4d084305b384eedf288c7a7fca95d8.tar.gz"
	SHA1 28cb7cd40242ae955db0d5aeafe32444e7082fec
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