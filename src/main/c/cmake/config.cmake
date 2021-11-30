hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/78c03d5d35188d5bee6014276a92b6de670c8ae0.tar.gz
	SHA1 fb1f319a35c6eda53fd7dcb4c31fa0fb3f71e012
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/005f2efac1e9865fb8075f36f43532a572b686ba.tar.gz
	SHA1 d2d186a31b902327d92c64ff87937395fdf4a2a8
)

# Do not remove this
hunter_config(
    Boost
    VERSION ${HUNTER_Boost_VERSION}
    CMAKE_ARGS
    CONFIG_MACRO=BOOST_UUID_RANDOM_PROVIDER_FORCE_POSIX
)