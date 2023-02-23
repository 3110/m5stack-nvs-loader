# NVS 設定ライブラリ

NVS の内容を JSON ファイルで設定するライブラリです。NVS の名前空間は`NVSLoader`のコンストラクタで指定します（最大 15 文字）。

設定ファイルは`data`ディレクトリ（`platformio.ini`の`data_dir`で指定したディレクトリ）に置き，`pio run --target uploadfs`を実行するとフォルダにあるファイルをすべて SPIFFS の`/`にアップロードします。

## 設定ファイル

値は文字列のみに対応している。

```json
{
    "キー1": "値1",
    "キー2": "値2",
    ...
    "キーn": "値n"
}
```

## サンプルプログラム

### `examples/wifi-connect`

`wifi.json`で SSID（キー`ssid`）とパスワード（キー`password`）を設定すると，その情報を使って WiFi に接続する。

```wifi.json
{
    "ssid": "SSID",
    "password": "パスワード"
}
```
