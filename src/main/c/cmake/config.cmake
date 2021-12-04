hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/78c03d5d35188d5bee6014276a92b6de670c8ae0.tar.gz
	SHA1 fb1f319a35c6eda53fd7dcb4c31fa0fb3f71e012
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/10044d89d9086102432da1009fb5c443139d5ffc.tar.gz
	SHA1 7c80061e5e7091c36bdbca7c54784b012864dcf0
)

# Do not remove this
hunter_config(
    Boost
    VERSION ${HUNTER_Boost_VERSION}
    CMAKE_ARGS
    CONFIG_MACRO=BOOST_UUID_RANDOM_PROVIDER_FORCE_POSIX
)