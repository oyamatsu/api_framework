<?php
class BaseJSONPage
{
	public function delegate()
	{
	}

	public function validate()
	{
	}

	public function run()
	{
		try{
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

