<?php
class BaseJSONPage
{
	public function accessControlAllowOrigin()
	{
		return false;
	}

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
			if($this->accessControlAllowOrigin()){
				header('Access-Control-Allow-Origin: *');
			}

			if($this->isHttpsOnly()){
				if($_SERVER["HTTPS"] != "on")
					$this->throwException(403, array('Forbidden'=>'SSLでの通信のみ許可されます。'));
			}
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

