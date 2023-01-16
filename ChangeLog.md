### 3.2.0

(2023-01-16)

**更新**

- 更新bcos-boostssl、bcos-cpp-sdk、bcos-c-sdk

### 3.1.0

(2023-01-03)

**更新**

- 发送交易支持设置`extraData`字段

### 3.0.0

(2022-08-23)

**更新**

- 更新bcos-boostssl、bcos-cpp-sdk、bcos-c-sdk

### 3.0.0-rc4

(2022-06-30)

**更新**

- 更新bcos-c-sdk

### 3.0.0-rc3

(2022-03-31)

**新增**

- 添加交易编码接口
- 添加交易签名接口

**更新**

- 更新`bcos-boostssl`、`bcos-cpp-sdk`、`bcos-c-sdk`依赖

**修复**

- 修复windows平台下加载动态库失败的问题

### 3.0.0-rc2

(2022-02-22)

**新增**

- 添加区块高度通知注册接口
- 添加`windows ci`，支持通过`ci`上传动态库

**更新**

- 更新`bcos-boostssl`、`bcos-cpp-sdk`、`bcos-c-sdk`依赖

### 3.0.0-rc1

(2021-12-09)

**简介**

与区块链进行交互的`JNI`接口，通过封装`bcos-c-sdk`提供的c接口实现

**功能**

- `RPC`
- `AMOP`
- 合约事件订阅
