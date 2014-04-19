<?php

$ip = '121.52.238.170';
$port = 21151;

$sock = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP);
if (!$sock) {
   echo 111;exit;
}

$buf = 'hello';
socket_sendto($sock, $buf, strlen($buf), 0, $ip, $port);
socket_getsockname($sock, $from_ip, $from_port);
echo $from_ip . ':' . $from_port;
socket_recvfrom($sock, $buf2, 12, 0, $ip, $port);
echo $buf2;
socket_close($sock);
