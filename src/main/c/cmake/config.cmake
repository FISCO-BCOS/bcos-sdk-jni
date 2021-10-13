hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/1b972a6734ef49ac4ca56184d31fe54a08a97e82.tar.gz"
	SHA1 6d35d940eacb7f41db779fb8182cbebf50535574
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/ywy2090/bcos-cpp-sdk/archive/57571f8528397e4f254f94e20c6fc3792394034d.tar.gz"
	SHA1 553ee655b96dab60280694a2dd606b17708c5565
)

hunter_config(bcos-framework VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-framework/archive/d4697aa6b984a18e2cab7f91c098480bf5e61ebd.tar.gz
	SHA1 ab2fa84f449aa90b108731734bfd28dc5e78da22
	CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)