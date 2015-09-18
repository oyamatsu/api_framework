# APIレスポンスを作るためのフレームワーク
.htaccessを使わず、APIのレスポンスを生成する為だけの軽量フレームワークを目指した。
軽量という言葉が何を意味するかというと、スタートアップで作りこむのが面倒だっただけなので、必要に応じてフレームワークの改良を進めていく。

# 使い方
## Config
### DataBase
サーバー名によりDB接続先をそれぞれ設定。
`$pdo = Database::get()->handle();` でPDOオブジェクトを取得できる。クエリ実行前にPDOオブジェクトを取得し、PDOの記法でクエリをprepareして実行する。

## scr下に.incファイルを設置
既に設置されているhoge_fuga.incをコピーして実装を進める。
### 決まりごと
- ファイル名は下記アクセスURLの項に則り、 `class名.inc` とする
- class名はファイル名と同じとする
- BaseJSONPageをextendsする
- validate()メソッドにて入力パラメータのバリデーションを行う
- delegate()メソッドにてメインの処理を行う

以上を満たす為、クラス定義は下記の形式とする。
```
class hoge_fuga extends BaseJSONPage
{
	public function delegate()
	{
		return array(
			'hoge'	=> 'fuga',
		);
	}

	public function validate()
	{
		$error = array();

		if($error){
			$this->throwException(400, $error);
		}
	}
}
```

# アクセスURL
`index.php` に対し、パラメータ名'p'に起動するclass名（=ファイル名）を入力する。
既に設置されている `hoge_fuga.inc` の処理を実行するには、 `index.php?p=hoge_fuga` にアクセスする。

classファイルをフォルダにまとめて管理する場合、'.'でディレクトリ階層を表現する。
`?p=test.hoge_fuga` にアクセスした場合、 `Application/scr/test/hoge_fuga.inc` のファイルを実行する。


