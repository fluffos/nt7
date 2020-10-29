// Room: /d/xingxiu/job2.h
// Last Modified by Lonely on Apr. 25 2001

int valid_leave(object me, string dir)
{
        object ob;
        if( query_temp("wait_target", me) && 
                objectp(present("anran zi", environment(me))))
                return notify_fail("黯然子闪身拦在你面前，喝道：临阵想溜？给我滚回来！\n");
        if( query_temp("xx_rob", me) && 
                objectp(ob = present("hubiao biaoshi", environment(me))) &&
                query("target", ob) == me )
                return notify_fail("护镖镖师闪身拦住你的去路，看来是想把你给废了！\n");  
        if( query_temp("xx_rob", me) && objectp(present("shangdui",environment(me))) )
                return notify_fail("商队在这里呢，快抢(qiang)啊！\n");  
        return ::valid_leave(me, dir);
} 