-module(udp_server).
-export([start/0]).

start() ->
	spawn(fun() -> server(21151) end).
	
server(Port) ->
	{ok, Socket} = gen_udp:open(Port, [binary, {active, false}]),
	io:format("socket:~p~n", [Socket]),
	loop(Socket).
	
loop(Socket) ->
	inet:setopts(Socket, [{active, once}]),
	receive
		{udp, Socket, Host, Port, Bin} ->
			io:format("received:~p~p~p~n", [Bin, Host, Port]),
			gen_udp:send(Socket, Host, Port, Bin),
			loop(Socket)
	end.