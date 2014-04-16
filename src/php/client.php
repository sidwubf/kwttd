<?php

$ip = '121.52.238.170';
$port = 21151;
//$ip = '218.83.32.240';
//$port = 30865;

$sock = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
if (!$sock) {
    echo 111;exit;
}

socket_bind($sock, '10.100.0.115', '21152');

$buf = 'hello';
socket_sendto($sock, $buf, strlen($buf), 0, $ip, $port);
socket_getsockname($sock, $from_ip, $from_port);
echo $from_ip . ':' . $from_port;
socket_close($sock);
