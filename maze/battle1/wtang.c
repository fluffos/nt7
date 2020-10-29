// This program is a part of NT MudLIB
// 赤火龙坛

#include <ansi.h>
inherit ROOM;

string long_desc();
int do_withdraw(string arg);
int do_plant(string arg);

void create()
{
        set("short", HIR"赤火龙坛"NOR);

        set( "long", (: long_desc :) );

        set("exits", ([
                "south" : __DIR__"wtower5",
                "down"  : __DIR__"wting",
        ]));
        
        set("outdoors", "battle");
        setup();
}


void init()
{
        add_action("do_withdraw", "ba");
        add_action("do_withdraw", "withdraw");
        add_action("do_plant", "plant");
}


string long_desc()
{
        string desc,temp;
        int nRank,i,j;

        if( query("flag") >0 )
                desc  = HIY"

                           /I______________I\\               "+HIC"|"+HIR"=====|"+HIY"
                         //||||||||||||||||||\\\\             "+HIC"|"+HIR" 武   |"+HIY"
                     T\\//IIIIIIIIIIIIIIIIIIIIII\\\\/T         "+HIC"|"+HIR"=====|"+HIY"
                     ^^^^"+HIG"||"NOR+HIY"^^^"+HIR"【赤火龙坛】"NOR+HIY"^^^"+HIG"||"+HIY"^^^^         "+HIC"|"+HIY"
                         "+HIG"||"NOR+HIY"__________________"+HIG"||"NOR+HIY"             "+HIC"|"+HIY"
                        /||||||||||||||||||||||\\            "+HIC"|"+HIY"
                    T\\//IIIIIIIIIIIIIIIIIIIIIIII\\\\/T        "+HIC"|"+HIY"
                    ^^^^"+HIG"||"+HIY"^^^^^^^^^^^^^^^^^^^^"+HIG"||"+HIY"^^^^        "+HIC"|"+HIG"
                        ||                    ||            "+HIC"|"+HIW"
          []___[]___[]__|[]___[]___||___[]___[]|__[]___[]___[]
          |__________________|_|________|_|__________________|"+HIR"
             ||                                          ||
\n"NOR;
        else
                desc  = HIY"

                           /I______________I\\
                         //||||||||||||||||||\\\\
                     T\\//IIIIIIIIIIIIIIIIIIIIII\\\\/T
                     ^^^^"+HIG"||"NOR+HIY"^^^"+HIR"【赤火龙坛】"NOR+HIY"^^^"+HIG"||"+HIY"^^^^
                         "+HIG"||"NOR+HIY"__________________"+HIG"||"NOR+HIY"
                        /||||||||||||||||||||||\\
                    T\\//IIIIIIIIIIIIIIIIIIIIIIII\\\\/T
                    ^^^^"+HIG"||"+HIY"^^^^^^^^^^^^^^^^^^^^"+HIG"||"+HIY"^^^^
                        ||                    ||
          []___[]___[]__|[]___[]___||___[]___[]|__[]___[]___[]
          |__________________|_|________|_|__________________|"+HIR"
             ||                                          ||
\n"NOR;

        return desc;
}

int do_withdraw(string arg)
{
        object flag, me=this_player(), *obj;
        int i, bGuarded = 0;

        if( !arg || arg != "flag" && arg != "qi" )
                return notify_fail("你想要拔什么？\n");

        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( query("flag") <= 0 )
                return notify_fail("没旗可拔。\n");

        if( query_temp("battle/team_name", me) == query("team_name") )
                return notify_fail("偷自己的旗？\n");

        message_vision(HIY"$N向旗杆跃起，想一把拔下旗子。\n"NOR, me);

        obj = all_inventory(environment(me));
        for( i=0; i<sizeof(obj); i++ ) {
                if( living(obj[i]) &&
                    query_temp("battle/team_name", obj[i]) != query_temp("battle/team_name", me) && 
                    obj[i]->visible(me) ) {
                        obj[i]->kill_ob(me);
                        message_vision(HIR"$N急对$n喝道：“$n竟敢偷旗，看招！”\n"NOR, obj[i],me,me);
                        me->kill_ob(obj[i]);
                        bGuarded = 1;
                }
        }

        if( !bGuarded )
        {
                flag = new(__DIR__"obj/flag");
                flag->set_name(query("team_name")+"大旗", ({ "flag" }) );
                if( flag->move(me) ) {
                        message_vision(HIG"$N一把扯下了大旗，高高举起。\n"NOR, me);
                        set("flag",0);
                } else {
                        destruct(flag);
                }
                CHANNEL_D->do_channel(this_object(), "war",
                        "听说"+me->name()+"夺走了"+query("team_name")+HIR"的大旗！"NOR );

        }
        return 1;
}

int do_plant(string arg)
{
        object flag, me = this_player();

        if( !BATTLEFIELD_D->in_battle(me) )
                return notify_fail("现在没有比赛。\n");

        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE);

        if( !arg || arg != "flag" && arg != "qi" )
                return notify_fail("你想要插什么？\n");

        if( query("flag") > 0 )
                return notify_fail("旗杆上已有旗了。\n");

        if( query_temp("battle/team_name", me) != query("team_name") )
                return notify_fail("这可不是你的大本营。\n");

        flag = present("flag",me );
        if( !flag ) return notify_fail("你手中没旗可以插。\n");

        if( query("name", flag) != query("team_name")+"大旗" )
                return notify_fail("自己的大本营怎么能插人家的旗？\n");

        message_vision(HIY"$N把大旗哗啦啦展开，插上了旗杆。\n"NOR, me);

        destruct(flag);

        set("flag",1);

        CHANNEL_D->do_channel(this_object(), "war",
                "听说"+me->name()+"将大旗插回了大本营！" );

        BATTLEFIELD_D->add_bonus_score(me, 20);
        return 1;
}
