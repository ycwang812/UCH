<?php
	$db_link = mysql_connect("localhost", "root");
	
	if (!$db_link) {
		echo "MySQL Server conncet fail...";
	} else {
		echo "MySQL Server conncet successful...";
	}
	
	mysql_close($db_link);
?>