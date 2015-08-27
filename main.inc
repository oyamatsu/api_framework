<?


try{
	loadConfigFile();
	// フレームワーク処理
	$data = MainProc();

	$status = array('result' => 0);
	return json_encode(compact('status','data'));
}
catch (Exception $e){
	$status = array(
		'result'	=> $e->getCode(),
		'error'		=> array(
			'key'		=> $e->getMessage(),
			'msg'		=> $e->getMessage(),
		),
	);
	return json_encode(compact('status'));
}


function loadConfigFile()
{
	spl_autoload_register(
		function($name) {
			if (!$name){
				return;
			}

			$ret = @include_once($name . '.inc');
		}
	);
}