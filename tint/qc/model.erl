
-module(model).

-export(
   [% gen_fsm call-backs
    init/1, handle_sync_event/4, terminate/3, 

    % gen_fsm states
    sched_state/2, move_state/2, motor_state/2,

    % API
    sched/0, move/0, motor/0, write/2, read/1, start/0, stop/0]).

-behaviour(gen_fsm).

init([]) ->
%%% !!! eqc_c:start(main, [{c_src, "src/main.c"}, {cflags, "-DPC -Isrc -Llib -lmoto"}]). !!!`
    eqc_c:start(main, [verbose, {c_src, "src/main.c"}, {cflags, "-DPC -I../../moto/src -I../../proto/src -L../../moto/lib -L../../proto/lib -lmoto -lproto"}]),
%    eqc_c:start(main, [verbose, {c_src, "src/main.c"}, {additional_files, ["src/moto_driver_functions.c", "src/moto_interface.c", "src/moto_msg_handler.c", "src/moto_msg_manipulation.c"]}, {cflags, "-DPC -Isrc -Llib -lmoto"}]),

%, {additional_files, ["libmoto.a"]}]),
    %eqc_c:start(main),
    main:moto_init(),
%    Msg = qc_main:#msg{rear=1},
    {ok,sched_state,[]}.

terminate(_,_,_) ->
    ok.

%% Event handlers for each state

sched_state(move,S) ->
    
	New_value = hej_master:kg_to_pounds(1),
	if
	1==1 ->
		{next_state,move_state,S};
	true -> 
		io:format("Test passed: ~p\n",[New_value]),
		{next_state,sched_state,S}
	end;
   %% {next_state,move_state,S};
sched_state(motor,S) ->
   
	New_value = hej_master:kg_to_pounds(1),
      if
	1==1 ->
		{next_state,motor_state,S};
	true -> 
		io:format("Test passed: ~p\n",[New_value]),
		{next_state,sched_state,S}
	end.

move_state(sched,S) ->
    
	New_value = hej_master:kg_to_pounds(1),
      if
	1==1 ->
		{next_state,sched_state,S};
	true -> 
		io:format("Test passed: ~p\n",[New_value]),
		{next_state,move_state,S}
	end.


motor_state(sched,S) ->
	New_value = hej_master:kg_to_pounds(1),
      if
	1==1 ->
		{next_state,sched_state,S};
	true -> 
		io:format("Test passed: ~p\n",[New_value]),
		{next_state,motor_state,S}
	end.


%% Event handler for the stop event

handle_sync_event(stop,_,_,_) ->
    {stop,normal,ok,[]}.

%% User API

sched() ->
    gen_fsm:send_event(the_model,sched).

move() ->
    gen_fsm:send_event(the_model,move).

motor() ->
    gen_fsm:send_event(the_model,motor).
    	
write(Key,Val) ->
    gen_fsm:send_event(the_model,{write,Key,Val}).

read(Key) ->
    gen_fsm:sync_send_event(the_model,{read,Key}).

start() ->
    gen_fsm:start({local,the_model},?MODULE,[],[]).

stop() ->
    gen_fsm:sync_send_all_state_event(the_model,stop).
