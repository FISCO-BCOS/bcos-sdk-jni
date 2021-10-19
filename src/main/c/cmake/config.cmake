hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/92b11cf12706a09c2f19e29cb92d2ad9daeece40.tar.gz"
	SHA1 eed0064cbde342a10e10ea8936bed973e33424ec
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/77c4318dacf58858e9727d36c65f2b31e4fcf609.tar.gz"
	SHA1 7d45da95496c51c7acc24b7213eef515dc1ffb03
)

hunter_config(bcos-framework VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-framework/archive/d4697aa6b984a18e2cab7f91c098480bf5e61ebd.tar.gz
	SHA1 ab2fa84f449aa90b108731734bfd28dc5e78da22
	CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)
