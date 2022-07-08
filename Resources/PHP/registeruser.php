<?php

include_once 'BDConnect.php';
$MyData = json_decode(file_get_contents('php://input'));

$UserLogin = $MyData->UserLogin;
$UserPassword = $MyData->UserPassword;

$stmt = $conn->prepare("SELECT id FROM users WHERE login = ?");
$stmt->bind_param("s", $UserLogin);
$stmt->execute();
if($stmt->fetch())
{
	echo json_encode(array('Success'=>false, 'Error'=>'User '.$UserLogin.' already exist'));
}
else
{
	$stmt->close();
	$stmt = $conn->prepare("INSERT INTO users (login, password) VALUES(?,?)");
	$stmt->bind_param("ss", $UserLogin, $UserPassword);
	$stmt->execute();
	$last_id = $stmt->insert_id;
	
	$stmt->close();
	
	$stmt = $conn->prepare("SELECT name, address FROM servers");
	$stmt->execute();
	$stmt->bind_result($name, $address);
	
	$ServerNames = array();
	$ServerAddresses = array();
	
	while($stmt->fetch())
	{
		$ServerNames[] = $name;
		$ServerAddresses[] = $address;
	}
	
	echo json_encode(array('Success'=>true, 'ServerNames'=>$ServerNames, 'ServerAddresses'=>$ServerAddresses));
}

?>