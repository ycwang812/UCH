<?php
	$database_dblink = "demo";
	$username_dblink = "root";

	$db_link = mysql_connect("localhost", $username_dblink);
	
	mysql_query("SET NAMES utf8", $db_link);
	mysql_query("SET CHARACTER_SET_CLIENT=utf8", $db_link);
	mysql_query("SET CHARACTER_SET_RESULTS=utf8", $db_link);
	
	mysql_select_db($database_dblink, $db_link);
	
	$name = $_POST["name"];
	$number = $_POST["number"];
	
	$insertSQL = sprintf(
		"INSERT INTO `class`(`name`, `number`) VALUES ('%s', '%s')", $name, $number);
	
	mysql_query($insertSQL, $db_link) or die(mysql_error());
	mysql_close($db_link);
?>