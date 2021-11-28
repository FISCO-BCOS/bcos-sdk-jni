 hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/f65c4e07e57423b5e6005437ca562e2e7ccdbf6b.tar.gz
	SHA1 2fb1f7921316441a129cb780777e9c5f2cf0729a
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/dad9a72d24cccc6c8438caf4a5782b19ba5b6abf.tar.gz
	SHA1 f2739100f30d45353b95741613d4325232f11a0b
)

# Do not remove this
hunter_config(
    Boost
    VERSION ${HUNTER_Boost_VERSION}
    CMAKE_ARGS
    CONFIG_MACRO=BOOST_UUID_RANDOM_PROVIDER_FORCE_POSIX
)