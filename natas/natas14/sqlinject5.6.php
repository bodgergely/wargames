<?php
$conn = mysql_connect("localhost", "natas", "natas");
mysql_select_db('natas14', $conn);

function ask($conn, $use, $pass) { 
    $query = "SELECT * from users where username=\"".$use."\" and password=\"".$pass."\"";
    //$query = "SELECT * from users where username=\"natas15\"; -- and password=\"*/\"";
    echo "query: " . $query . "\n";
    $res = mysql_query($query, $conn);
    return $res;
}

// SELECT * from users where username="natas15" and password="kartya"

$username = "natas15\"; -- ";
$password = "*/\\";
//$password = "; SELECT * from users where username=\"natas15";

$res = ask($conn, $username, $password);

echo "res: ";
var_dump($res);

if(mysql_num_rows($res) > 0) {
    echo "Got at least one row!\n";
} else {
    echo "Now rows.\n";
}

//while ($row = $res->fetch_assoc()) {
//    echo "username: ".$row["username"]."\npassword: ".$row["password"]; echo "\n";
//}

mysql_close($conn);

?>
