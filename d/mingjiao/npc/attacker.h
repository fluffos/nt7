void init()
{
        object ob, me = this_player();
        if ( interactive(me) 
           && query_temp("mj/xunluo", me )
           && query_temp("mj/attacker", me )
           && query("outer_times", random(this_object())) == 1
          ) {
                 ob = new("/d/mingjiao/npc/attacker");
                 message_vision("\n一个人影突然从旁跳了出来，拦住$N的去路！\n\n", me); 
                 ob->move(environment(me));
                 addn_temp("mj/attacker", 1, me);
                 addn_temp("mj/attacker1", 1, me);
                 ob->do_copy(me);
                 ob->kill_ob(me);
        }
}

int valid_leave(object me, string dir)
{
        object ob;
        if( query_temp("mj/xunluo", me )
          && objectp(ob=present("attacker", environment(me)))
           && query("victim", ob) == query("id", me )
          && !userp(ob))
            return notify_fail(ob->name()+"一言不发，闪身拦在你面前！\n");
            return ::valid_leave(me, dir);
} 
