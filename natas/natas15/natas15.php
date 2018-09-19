<?php
$conn = mysqli_connect('localhost', 'natas', 'natas', 'natas15');

function ask($conn, $use) { 
    $query = "SELECT * from users where username=\"".$use;
    echo "query: " . $query . "\n";
    $res = $conn->query($query);
    return $res;
}

$username = "natas16\"; SELECT * FROM users;";
//$username = "natas16\" and password=\"kartya";

$res = ask($conn, $username);

if($res) {
    if($res->num_rows > 0) {
        echo "This user exists.<br>";
    } else {
        echo "This user doesn't exist.<br>";
    }
} else {
    echo "Error in query.<br>";
}

$conn->close();
?>



