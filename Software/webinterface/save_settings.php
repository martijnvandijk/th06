<?php
	// Open and write to the usersettings.json file
	$f = @fopen("js/usersettings.json", "w");
	fwrite($f, $_POST['data']);
	var_dump($_POST);
	fclose($f);
?>