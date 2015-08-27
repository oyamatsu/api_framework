<?
/** DBコントローラクラス
 * $pdo = Database::get()->handle(); でPDOオブジェクトを取得できる
 */
class Database
{
	private $_handle = null;
	private $DB_CONNECT = true; // DB接続するか否か
	
	private function __construct()
	{
		// MySQLDB接続情報
		switch ($SERVER_NAME)
		{
			#
			# ローカル環境
			#
			case 'localhost':
			{
				$DB_CONN_HOST = 'dev-hoge.fuga.jp';
				$DB_CONN_NAME = 'test';
				$DB_CONN_USER = '*******';
				$DB_CONN_PASS = '*******';
				$DB_CONN_PERSIST = true;

				break;
			}

			#
			# 開発環境
			#
			case 'dev-hoge.fuga.jp':
			{
				$DB_CONN_HOST = 'localhost';
				$DB_CONN_NAME = 'test';
				$DB_CONN_USER = '*******';
				$DB_CONN_PASS = '*******';
				$DB_CONN_PERSIST = false;

				break;
			}

			#
			# ステージング
			#
			case 'stg-hoge.fuga.jp':
			{
				$DB_CONN_HOST = 'localhost';
				$DB_CONN_NAME = 'test';
				$DB_CONN_USER = '*******';
				$DB_CONN_PASS = '*******';
				$DB_CONN_PERSIST = true;

				break;
			}

			#
			# 本番ドメイン
			#
			case 'hoge.fuga.jp':
			{
				$DB_CONN_HOST = 'localhost';
				$DB_CONN_NAME = 'test';
				$DB_CONN_USER = '*******';
				$DB_CONN_PASS = '*******';
				$DB_CONN_PERSIST = true;

				break;
			}

			#
			# 利用していない
			#
			default:
			{
				break;
			}
		}

		if($this->DB_CONNECT){
			$_DB = array(
				'dsn'			=> 'mysql:dbname=' . $DB_CONN_NAME . ';host=' . $DB_CONN_HOST,
				'username'		=> $DB_CONN_USER,
				'password'		=> $DB_CONN_PASS,
				'persist'		=> $DB_CONN_PERSIST,
			);
			try{
				$this->_hundle =& new PDO($_DB['dsn'], $_DB['username'], $_DB['password'], array(PDO::ATTR_PERSISTENT => $_DB['$DB_CONN_PERSIST']));
			}
			catch(PDOException $e){
				throw new Exception($e->getMessage(), $e->getCode());
			}
		}
	}

	public static function get() {
		static $db = null;
		if ($db==null || $this->DB_CONNECT) $db = new Database();
		return $db;
	}

	public function handle() {
		return $this->_handle;
	}
}


