<?php
class HttpResponseSend extends Exception
{
	public $http_code;
	public $http_mess;
	public $key;
	
	function __get($name)
	{
		if ($name === 'desc_text')
		{
			if ($this->key)
			{
				if (is_scalar($this->key))
				{
					return $this->key;
				}
				
				return print_r($this->key, true);
			}
		}
	}

	public function getErrorCode(){ return $this->http_code; }
	public function getErrorKey(){ return $this->key; }
	public function getErrorMessage(){ return $this->http_mess; }

	function __construct($code, $desc=null, $mess=null)
	{
		$this->http_code = $code;
		if(true===is_array($desc)){
			$this->key = key(array_slice($desc, 0, 1));
			$mess = @$desc[$this->key];
		}
		else{
			$this->key = $desc;
		}
		if (! $mess)
		{
			$mess = self::get_http_error_message($code) or $mess = 'UnKnown Code';
		}
		$this->http_mess = $mess;
		parent::__construct();
	}

	static function get_http_error_message($code)
	{
		//
		// http://www.saturn.dti.ne.jp/~jpug/doc/web/httpstatus.html
		//
		$HTTP_ERRORMESS_MAP = array
		(
		# 100 - 199
			100 => 'Continue',
			101 => 'Switching Protocols',
			102 => 'Processing',

		# 200 - 299
			200 => 'OK',
			201 => 'Created',
			202 => 'Accepted',
			203 => 'Non-Authoritative Information',
			204 => 'No Content',
			205 => 'Reset Content',
			206 => 'Partial Content',
			207 => 'Multi-Status',
			226 => 'IM Used',

		# 300 - 399
			300 => 'Multiple Choices',
			301 => 'Moved Permanently',
			302 => 'Found',
			303 => 'See Other',
			304 => 'Not Modified',
			305 => 'Use Proxy',
			307 => 'Temporary Redirect',

		# 400 - 499
			400 => 'Bad Request',
			401 => 'Unauthorized',
			402 => 'Payment Required',
			403 => 'Forbidden',
			404 => 'Not Found',
			405 => 'Method Not Allowed',
			406 => 'Not Acceptable',
			407 => 'Proxy Authentication Required',
			408 => 'Request Timeout',
			409 => 'Conflict',
			410 => 'Gone',
			411 => 'Length Required',
			412 => 'Precondition Failed',
			413 => 'Request Entity Too Large',
			414 => 'Request-URI Too Long',
			415 => 'Unsupported Media Type',
			416 => 'Requested Range Not Satisfiable',
			417 => 'Expectation Failed',
			418 => "I'm a teapot",
			422 => 'Unprocessable Entity',
			423 => 'Locked',
			424 => 'Failed Dependency',
			426 => 'Upgrade Required',

		# 500 - 599
			500 => 'Internal Server Error',
			501 => 'Not Implemented',
			502 => 'Bad Gateway',
			503 => 'Service Unavailable',
			504 => 'Gateway Timeout',
			505 => 'HTTP Version Not Supported',
			506 => 'Variant Also Negotiates',
			507 => 'Insufficient Storage',
			510 => 'Not Extended',
		);
		if (! isset($HTTP_ERRORMESS_MAP[$code]))
		{
			$code = 500;
		}
		return $HTTP_ERRORMESS_MAP[$code];
	}
}
