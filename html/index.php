<!DOCTYPE html>
<html lang="en-US">
<head>
	<meta charset="utf-8">
	<link href="style.css" type="text/css" rel="stylesheet" />
	<title>Online Teeworlds-Server Information</title>
</head>

<body>
	<div id="main_content">
		<h1 style="margin-top:125px;">Online Teeworlds-Server Information</h1><br />
		<form method="get">
			<div style="text-align:right;margin:auto;width:325px;">
				<?php
					echo 'IP/Hostname:&ensp;<input name="ip" type="text" size="20" value="' . $_GET["ip"] . '"><br />';
					echo 'Port:&ensp;<input name="port" type="number" size="20" maxlength="5" value="' . $_GET["port"] . '"><br />';
				?>
				<div style="width:94px;margin:auto;"><input type="submit" value="Get Info!"></div>
			</div>
		</form><br /><br />
		
		<div style="margin:auto;width:700px;text-align:left;font-size:8.5pt;">
			Programmed in C++/PHP by Malek | Sourcecode on <a target="_blank" href="https://github.com/Malekblubb/tw_online_server_info">GitHub</a>
		</div>

		<div id="main_info_table">
			<?php
				if($_GET["ip"] && $_GET["port"])
				{
					echo '<h2>' . $_GET["ip"] . ":" . $_GET["port"] . '</h2>';
					$cmd = "exec/tw_online_server_info " . $_GET["ip"] . ":" . $_GET["port"];
					$out = shell_exec($cmd);
					echo $out;
				}
				else
					echo "Enter an address of a teeworlds server";
			?>
		</div>
	</div>
</body>
</html>
