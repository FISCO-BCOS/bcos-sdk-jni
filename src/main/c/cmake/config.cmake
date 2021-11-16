hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/f75a921483fc15a6d63cf04fea799d8522e731d4.tar.gz
	SHA1 9879730f164af093f86dbf3f88d44871048df130
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/9844e20ce7e286cf84dc184b0fe6a6b702069ed5.tar.gz
	SHA1 00d9c233a34deba8bea71f9cebaf3786c173fc37
)

hunter_config(bcos-framework VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-framework/archive/403509babb28e648390dcc5f77576f35e7ba0b7a.tar.gz
    SHA1 f34447aba04532cee17b519a8ce47f3c0e6d1ec1
	CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)

# Do not remove this
hunter_config(
    Boost
    VERSION ${HUNTER_Boost_VERSION}
    CMAKE_ARGS
    CONFIG_MACRO=BOOST_UUID_RANDOM_PROVIDER_FORCE_POSIX
)