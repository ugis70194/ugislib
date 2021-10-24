# Dockerによる競技プログラミング用環境構築

## Requirements
- Docker
- docker-compose
- VScode

## Install 
### Docker
1. [dockerをinstallする](https://docs.docker.com/engine/install/)
2. [userをdocker groupに追加する](https://qiita.com/tifa2chan/items/9dc28a56efcfb50c7fbe)

### docker-compose
1. [docker-composeをinstallする](https://docs.docker.jp/compose/install.html#linux)

### VScode
1. [VScodeをinstallする](https://code.visualstudio.com/download)
2. [拡張機能 Remote - Containers をinstallする](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

## Usage
1. 開きたいフォルダの直下に、このリポジトリの`.devcontainer`をコピーしてVScodeで開く
2. 開くとポップアップが出てくるので`Reopen in Container`を選択
3. リモートが開く(初回のビルドは10分くらいかかるので注意)

## Note
proxy環境下でうまく動くかわからないけど、proxy通せば多分動くと思う。  
[プロキシのある環境でDockerを動かす方法](https://qiita.com/dkoide/items/ca1f4549dc426eaf3735)

