 hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/f65c4e07e57423b5e6005437ca562e2e7ccdbf6b.tar.gz
	SHA1 2fb1f7921316441a129cb780777e9c5f2cf0729a
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/f9edb77347d8f6556a0101287cc46540b2a7b993.tar.gz
	SHA1 468dc15fe60593509690e2c201665ce69bfe127a
)

# Do not remove this
hunter_config(
    Boost
    VERSION ${HUNTER_Boost_VERSION}
    CMAKE_ARGS
    CONFIG_MACRO=BOOST_UUID_RANDOM_PROVIDER_FORCE_POSIX
)