hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/a6394c8f1966a0a590f98cb26e4c6fddcd1755c8.tar.gz"
	SHA1 3d7ed0d250e7cd2f634fe717af5d3ec9591a6146
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/32b42ad1d6e8405fa76f04710c9cf380ab485c35.tar.gz"
	SHA1 c0e3bb215a0488057b6040869d80f49bd92a351c
)

hunter_config(bcos-framework VERSION 3.0.0-33486b94
	URL https://${URL_BASE}/FISCO-BCOS/bcos-framework/archive/24bda7fa38040767ef5e6b42baf25e7253952017.tar.gz
	SHA1 0cbf768520833c04d5b93e4ea6c8a884a0f089d5
	CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)