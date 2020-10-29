// jingzuo.c
// Dec.11 1997 by Venus

void wakeup(object me, object where);
void del_jingzuoed(object me);

int main(object me, string arg)
{
        mapping fam;
        object where = environment(me);

        seteuid(getuid());

        if( query("family/family_name", me) != "峨嵋派" )
                return notify_fail("只有峨嵋派弟子才会才能静坐！\n");

        if( query("no_fight", environment(me)) && 
            (query("doing", me) != "scheme" || this_player(1)) )
                return notify_fail("这里太纷杂，你没法安心静坐。\n");

        if( query("eff_jing", me)<50 )
                return notify_fail("你受伤太重，无法定心静坐。\n");

        if (me->is_busy())
                return notify_fail("你正忙着呢！\n");

        if (me->is_fighting())
                return notify_fail("战斗中想静坐？你不要命啦！\n");

        if( time()-query("jingzuo_time", me)<120 )
                return notify_fail("你刚才静坐过，现在头脑一片空白。\n");

        if (me->query_skill("mahayana", 1) < 40)
                return notify_fail("你的大乘般涅磐功还太浅薄了，没法静心静坐。\n");

        write("你盘膝坐下，开始入定。\n");
        write("不一会儿，你神游天外，物我两忘。\n");
        set_temp("block_msg/all", 1, me);
        message_vision("$N一躬身，坐了下来，闭目端念，静心打坐。\n",me);

        set("no_get", 1, me);
        set("no_get_from", 1, me);
        me->disable_player(" <静坐中>");
        me->start_call_out(bind((: call_other, __FILE__, "wakeup", me, where :), me),
                           random(45) + 1 , me, where);

        return 1;
}

void wakeup(object me, object where)
{
        int skillslvl, addp, addc, exppot, intpot;

        skillslvl = (int) me->query_skill("mahayana", 1);
        exppot=(query("combat_exp", me)/100000);
        intpot = (int) (me->query_int() / 10);

        if (skillslvl > 100) skillslvl = (skillslvl - 100) / 2 + 100;
        if (exppot > 150) exppot = (exppot - 150) / 4 + 100; else
        if (exppot > 50)  exppot = (exppot - 50) / 2 + 50;

        addp = (int) (random(skillslvl) / 5 + intpot);
        addc = (int) (random(skillslvl) / 3 + exppot);

        if( query("combat_exp", me) >= 1500000 )
                addc /= 2;

        if( query("combat_exp", me) >= 3000000 )
                addc /= 2;

        if( query("combat_exp", me) >= 5000000 )
                addc /= 2;

        me->receive_damage("jing", 15);
        me->receive_wound("jing", 3);
        if( objectp(where) && query("no_fight", where) )
                me->receive_wound("jing", 5);
        me->improve_potential(addp);
        addn("combat_exp", addc, me);
        me->enable_player();
        message_vision("$N静坐完毕，缓缓睁眼，长长吐了一口气。\n",me);
        set_temp("block_msg/all", 0, me);
        set("jingzuo_time", time(), me);
        write("你静坐完毕，感觉到好累。\n");

        delete("no_get", me);
        delete("no_get_from", me);
        me->write_prompt();
        return;
}

int help(object me)
{
        write(@HELP
指令格式 : jingzuo

这个指令是峨嵋派弟子用以静坐修道的命令.

HELP );
        return 1;
}