hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/552ca82f8b9c68603ce76db276f2e6348018d639.tar.gz
	SHA1 a9db53b0b3ee397b9a96e449429d118996a1823f
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/f4278ed0077ab3507aa072717aa852c2dc972a06.tar.gz
	SHA1 ba2fd768ff6223e3323e8e580886bfa59ac26167
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