<?php

$ServerName = 'https://remotemysql.com/phpmyadmin/db_routines.php?db=mM3EsBqjfn';
$UserName = 'mM3EsBqjfn';
$Password = 'Tb10BZGuRS';
$DBName = 'mM3EsBqjfn';

$conn = new mysqli($ServerName, $UserName, $Password, $DBName);

if($conn->connect_error)
{
	echo(json_encode(aray('success'=>'false', 'error'=>'connection failed: '.$conn->connect_error)));
	die;
}

?>