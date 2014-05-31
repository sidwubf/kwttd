-module(udp_server).
-export([start/0]).

-define(ENDPOINT_LOG, "ep.log").

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
			io:format("received:~p Host:~p Port:~p~n", [Bin, Host, Port]),
			file:write_file(?ENDPOINT_LOG, io_lib:file("~p,~p,~p\n", [Bin, Host, Port])),
			gen_udp:send(Socket, Host, Port, Bin),
			loop(Socket)
	end.
	
