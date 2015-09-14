<?php
class hoge_fuga extends BaseJSONPage
{
	public function isPostOnly(){
		return true;
	}
	
	public function delegate()
	{
		//$pdo = Database::get()->handle();

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
