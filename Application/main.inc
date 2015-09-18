<?php

function MainProc($p){
	$filepath = explode('.', $p);
	$class = $filepath[count($filepath)-1];
	include_once dirname(__FILE__).DIRECTORY_SEPARATOR.'scr'.DIRECTORY_SEPARATOR.join(DIRECTORY_SEPARATOR, $filepath).'.inc';
	$main = new $class();
	return $main->run();
}

try{
	// フレームワーク処理
	if(true===empty($_REQUEST['p'])){
		throw new Exception('Not Found', 404);
	}
	$data = MainProc($_REQUEST['p']);
	$status = array('result' => 200);
	echo json_encode(compact('status','data'));
}
catch (Exception $e){
	$status = array(
		'result'	=> method_exists($e,'getErrorCode') ? $e->getErrorCode() : $e->getCode(),
		'error'		=> array(
			'key'		=> method_exists($e,'getErrorKey') ? $e->getErrorKey() : '',
			'msg'		=> method_exists($e,'getErrorMessage') ? $e->getErrorMessage() : $e->getMessage(),
		),
	);
	echo json_encode(compact('status'));
}
