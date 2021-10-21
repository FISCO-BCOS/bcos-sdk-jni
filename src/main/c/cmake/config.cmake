hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/c9a0dae2700db66c2ed3f002c381fb2ed5f576f3.tar.gz"
	SHA1 4c8c082874697796ae82064a42b7d702de556162
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/98f767f4e01f9f6e87a8b17470a8d63988c46a84.tar.gz"
	SHA1 1516eb7bacdbcff5faf030d964cb2e66229ee5d2
)

hunter_config(bcos-framework VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-framework/archive/d4697aa6b984a18e2cab7f91c098480bf5e61ebd.tar.gz
	SHA1 ab2fa84f449aa90b108731734bfd28dc5e78da22
	CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)