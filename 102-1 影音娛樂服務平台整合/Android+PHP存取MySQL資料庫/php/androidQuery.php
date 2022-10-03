<?php
	$database_dblink = "demo";
	$username_dblink = "root";

	$db_link = mysql_connect("localhost", $username_dblink);
	
	mysql_query("SET NAMES utf8", $db_link);
	mysql_query("SET CHARACTER_SET_CLIENT=utf8", $db_link);
	mysql_query("SET CHARACTER_SET_RESULTS=utf8", $db_link);
	
	mysql_select_db($database_dblink, $db_link);
	
	$result = mysql_query("SELECT * FROM `class`", $db_link);
	$json = array();
	
	while ($row = mysql_fetch_array($result)) {
		$json["class"][] = array("name" => $row['name'], "number" => $row['number']);
	}
	
	echo json_encode($json);
	
	mysql_close($db_link);
?>