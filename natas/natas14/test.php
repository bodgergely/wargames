<?php
$_REQUEST = array("username"=>"natas15", "password"=>"kartya");
$conn = mysqli_connect('localhost', 'natas', 'natas', 'natas14');

if ($conn->connect_errno) {
    echo "Failed to connect to MySQL: ( " . $conn->connect_errno . ")" . $conn->connect_error;
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
?>
