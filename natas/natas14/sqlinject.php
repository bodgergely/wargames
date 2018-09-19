<?php
$conn = mysqli_connect("localhost", "natas", "natas", "natas14");


function ask($conn, $use, $pass) { 
    $query = "SELECT * from users where username=\"".$use."\" and password=\"".$pass."\"";
    echo "query: " . $query . "\n";
    $res = $conn->query($query);
    return $res;
}

$username = "natas15\"; -- ";
$password = "*/\\";

$res = ask($conn, $username, $password);

if($res->num_rows > 0) {
    echo "Got at least one row!\n";
} else {
    echo "Now rows.\n";
}

//while ($row = $res->fetch_assoc()) {
//    echo "username: ".$row["username"]."\npassword: ".$row["password"]; echo "\n";
//}

$conn->close();

?>
