<?php

function MainProc($file){
	include_once dirname(__FILE__).DIRECTORY_SEPARATOR.'scr'.DIRECTORY_SEPARATOR.$file.'.inc';
	$main = new $file();
	return $main->run();
}

try{
	// フレームワーク処理
	$data = MainProc(basename($_SERVER['SCRIPT_NAME'],'.php'));
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
