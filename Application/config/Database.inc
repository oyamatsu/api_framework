<?php
/** DBコントローラクラス
 * $pdo = Database::get()->handle(); でPDOオブジェクトを取得できる
 */
class Database
{
	private $_handle = null;
	
	private function __construct()
	{
		// MySQLDB接続情報
		switch ($_SERVER['SERVER_NAME'])
		{
			#
			# ローカル環境
			#
			case 'localhost':
			{
				$DB_CONN_HOST = 'dev-hoge.fuga.jp';
				$DB_CONN_NAME = 'test';
				$DB_CONN_USER = '********';
				$DB_CONN_PASS = '********';
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
				$DB_CONN_USER = '********';
				$DB_CONN_PASS = '********';
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

		$_DB = array(
			'dsn'			=> 'mysql:host=' . $DB_CONN_HOST . ';dbname=' . $DB_CONN_NAME.';charset=utf8;',
			'username'		=> $DB_CONN_USER,
			'password'		=> $DB_CONN_PASS,
			'persist'		=> $DB_CONN_PERSIST,
		);
		try{
			$pdo = new PDO($_DB['dsn'], $_DB['username'], $_DB['password'], array(PDO::ATTR_PERSISTENT => $_DB['persist']));
			$this->_handle =& $pdo;
		}
		catch(PDOException $e){
			throw new Exception($e->getCode(), $e->getMessage());
		}
	}

	public static function get() {
		static $db;
		return $db ?: $db = new self;
	}

	public function handle() {
		if (false===empty($db)) $this->_handle = $db;
		return $this->_handle;
	}
}


