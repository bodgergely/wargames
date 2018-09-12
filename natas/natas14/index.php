<html>
<head>
</head>
<body>
<h1>natas14</h1>
<div id="content">
<?php

if(array_key_exists("username", $_REQUEST)) {
    $conn = mysqli_connect('localhost', 'natas', 'natas', 'natas14');
    if ($conn->connect_errno) {
        echo "Failed to connect to MySQL: ( " . $conn->connect_errno . ")" . $conn->connect_error;
        return;
    }

    $query = "SELECT * from users where username=\"".$_REQUEST["username"]."\" and password=\"".$_REQUEST["password"]."\"";
    if(array_key_exists("debug", $_GET)) {
        echo "Executing query: $query<br>";
    }
    $res = $conn->query($query);
    if($res->num_rows > 0) {
            echo "Successful login! The password for natas15 is kartya<br>";
    } else {
            echo "Access denied!<br>";
    }
    $conn->close();
} else {
?>

<form action="index.php" method="POST">
Username: <input name="username"><br>
Password: <input name="password"><br>
<input type="submit" value="Login" />
</form>
<?php } ?>
<div id="viewsource"><a href="index-source.html">View sourcecode</a></div>
</div>
</body> 
</html> 
