hunter_config(bcos-boostssl
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-boostssl/archive/87888f85eb34154166ea30c7b28974d0bfa849f2.tar.gz"
	SHA1 21567a7b4732d424983455e2ac97d5e199a1cf6e
)

hunter_config(bcos-cpp-sdk
	VERSION 3.0.0-local
	URL "https://${URL_BASE}/FISCO-BCOS/bcos-cpp-sdk/archive/1f74573512d741a1dbf084128413f177af726d22.tar.gz"
	SHA1 16d3158a77b58ab1b70c75c88f3f5ea40aa07ca5
)

hunter_config(bcos-framework VERSION 3.0.0-local
	URL https://${URL_BASE}/FISCO-BCOS/bcos-framework/archive/d4697aa6b984a18e2cab7f91c098480bf5e61ebd.tar.gz
	SHA1 ab2fa84f449aa90b108731734bfd28dc5e78da22
	CMAKE_ARGS HUNTER_PACKAGE_LOG_BUILD=ON HUNTER_PACKAGE_LOG_INSTALL=ON
)
