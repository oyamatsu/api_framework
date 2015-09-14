<?php
class BaseJSONPage
{
	public function delegate()
	{
	}

	public function validate()
	{
	}

	public function isPostOnly()
	{
		return false;
	}

	public function run()
	{
		try{
			if($this->isPostOnly()){
				if($_SERVER['REQUEST_METHOD']!='POST')
					$this->throwException(405,'Method Not Allowed');
			}

			$this->validate();
			$ret = $this->delegate();
		}
		catch(Exception $e){
			throw $e;
		}
		return $ret;
	}

	public function throwException($code,$error)
	{
		$e = new HttpResponseSend($code,$error);
		throw $e;
	}
}

