hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/78c03d5d35188d5bee6014276a92b6de670c8ae0.tar.gz
	SHA1 fb1f319a35c6eda53fd7dcb4c31fa0fb3f71e012
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/047f16c72c4419d253580babf3d2cd073cbbbc8a.tar.gz
	SHA1 d40d31b53c2d1b5ddd259c50fe9cfd9eb89c48cd
)

# Do not remove this
hunter_config(
    Boost
    VERSION ${HUNTER_Boost_VERSION}
    CMAKE_ARGS
    CONFIG_MACRO=BOOST_UUID_RANDOM_PROVIDER_FORCE_POSIX
)