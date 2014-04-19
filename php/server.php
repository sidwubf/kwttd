<?php

$host = '0.0.0.0';
//$host = '121.52.238.170';
$port = 50403;

$socket = socket_create(AF_INET, SOCK_DGRAM, SOL_UDP) or die("Could not create
socket\n");

$result = socket_bind($socket, $host, $port) or die("Could not bind to
socket\n");

$from = '';
$port = 0;
socket_recvfrom($socket, $buf, 12, 0, $from, $port);

echo "Received $buf from remote address $from and remote port $port";
