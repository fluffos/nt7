// for this dir "hj_npc_tarder.lpc", "hj_npc_zhujian.lpc", "hj_npc_lianmo.lpc"
// #include .  by naihe 2:16 03-11-5

int me_ok( object me )
{ 
    if( !me || query_temp("huanjing", me) != "start"
      || query_temp("hj_hp", me)<1
      || !query_temp("this_time_mark", me )
      || !environment(me) || !query("room_mark", environment(me)) )
        return 0;
    return 1;
}

int ob_ok()
{
    object ob = this_object(), env;

    if( !living(ob) ) return 0;
    env = environment(ob);
    if( !env || query("room_mark", env) != MY_ROOM_MARK )
        return 0;
    return 1;
}
