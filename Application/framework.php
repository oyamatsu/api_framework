<?php

function compat_pathinfo($path, $opt=null)
{
	if (is_null($opt))
	{
		return pathinfo($path);
	}

	if (version_compare(phpversion(), '5.2.0', '>='))
	{
		return pathinfo($path, $opt);
	}

	if ($opt === PATHINFO_FILENAME)
	{
		return pathinfo_filename($path);
	}
	else
	{
		return pathinfo($path, $opt);
	}
}

// configファイルのロード
function RequireAllFiles($arg)
{
	if (! $arg)
	{
		return;
	}

	$autoload = rtrim($arg, DIRECTORY_SEPARATOR) . DIRECTORY_SEPARATOR;
	if (! is_dir($autoload))
	{
		return;
	}
	
	$files = array();
	$d = dir($autoload);
	while (false !== ($entry = $d->read()))
	{
		$path = $autoload . $entry;
		if (! is_file($path)) 
		{
			continue;
		}
		$ext = compat_pathinfo($path, PATHINFO_EXTENSION);
		if (strcasecmp($ext, 'inc') !== 0)
		{
			continue;
		}
		$files[] = $path;
	}
	$d->close();

	natsort($files);
	foreach ($files as $file)
	{
		require_once $file;
	}
}

RequireAllFiles(dirname(__FILE__).DIRECTORY_SEPARATOR.'sys');
RequireAllFiles(dirname(__FILE__).DIRECTORY_SEPARATOR.'config');

// セッションの開始
session_start();

require_once 'main.inc';
