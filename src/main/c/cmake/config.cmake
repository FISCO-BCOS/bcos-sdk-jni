hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/176dbb74c41a0efaf38bd8725908929b708bdf14.tar.gz"
	SHA1 ab851a11610fab6df520730a3bcbf8bd08a87065
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/a272dc16750291a70771bfd253362d8a971b4636.tar.gz"
	SHA1 168e8a401bd8b64c54bc1b62d5c87a437e66e890
)

hunter_config(bcos-framework VERSION 3.0.0-33486b94
	URL https://${URL_BASE}/FISCO-BCOS/bcos-framework/archive/24bda7fa38040767ef5e6b42baf25e7253952017.tar.gz
	SHA1 0cbf768520833c04d5b93e4ea6c8a884a0f089d5
	CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)