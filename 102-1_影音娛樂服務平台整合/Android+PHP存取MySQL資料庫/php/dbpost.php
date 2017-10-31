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

	$result = mysql_query("SELECT * FROM `class`", $db_link);
	
	echo "<!DOCTYPE html><html><head><meta http-equiv='Content-Type' content='text/html; chartset=UTF-8'></head><body><table board='1'><tr><th>Name</th><th>Number</th></tr>";
	
	while ($row = mysql_fetch_array($result)) {
		echo "<tr><td>" . $row['name'] . "</td><td>" . $row['number'] . "</td></tr>";
	}
	
	echo "</table></body></html>";
	
	mysql_close($db_link);
?>