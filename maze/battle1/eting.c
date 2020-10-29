// This program is a part of NT MudLIB
// eting.c
// 演武厅


#include <ansi.h>
inherit ROOM;

string long_desc();
int do_withdraw(string arg);
int do_plant(string arg);


void create()
{
        set("short", HIW"演武厅"NOR);
        set("long", (: long_desc :));

        set("exits", ([
                "west" : __DIR__"etower2",
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

        if( !query("flag") )
                desc  = HIW"
                   /I____________I\\
                 //||||||||||||||||\\\\
             T\\//IIIIIIIIIIIIIIIIIIII\\\\/T
            ^^^^"+HIG"||"NOR+HIY"^^^"+HIW"[ 演武厅 ]"NOR+HIY"^^^"+HIG"||"+HIY"^^^^         "+HIY"
                "+HIG"||"NOR+HIY"________________"+HIG"||"NOR+HIY"             "+HIC"
         []__|[]___[]___||___[]___[]|__[]___[]
         |_________|_|________|_|____________|"+HIB"
               ||                  ||
               ||                  ||
               ||                  ||
               ||                  ||
               ||                  ||
               ||__________________||\n
               "+HIC"正前方竖着一排兵器架\n"NOR;
        else
                desc  = HIW"
                   /I____________I\\         "+HIR"★"+HIW"
                 //||||||||||||||||\\\\       "+HIY"||"+HIR"~~~~~~~~/"+HIW"
             T\\//IIIIIIIIIIIIIIIIIIII\\\\/T   "+HIY"||   武   "+HIR"{"+HIW"
            ^^^^"+HIG"||"NOR+HIY"^^^"+HIW"[ 演武厅 ]"NOR+HIY"^^^"+HIG"||"+HIY"^^^^    "+HIY"||         "+HIR"\\"+HIY"
                "+HIG"||"NOR+HIY"________________"+HIG"||"NOR+HIY"        ||"+HIR"~~~~~~~~~~~"+HIC"
         []__|[]___[]___||___[]___[]|__[]___[]
         |_________|_|________|_|____________|"+HIB"
               ||                  ||
               ||                  ||
               ||                  ||
               ||                  ||
               ||                  ||
               ||__________________||\n
               "+HIC"正前方竖着一排兵器架\n"NOR;

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
                flag->set_name(query("flag_name"), ({ "flag" }) );
                if( flag->move(me) ) {
                        message_vision(HIG"$N一把扯下了大旗，高高举起。\n"NOR, me);
                        set("flag",0);
                } else {
                        destruct(flag);
                }
                CHANNEL_D->do_channel(this_object(), "war",
                        "听说"+me->name()+"夺走了"+query("flag_name")+HIR"！"NOR );
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

        if( query_temp("battle/team_name", me) == query("team_name") )
                return notify_fail("这可不是你的地盘。\n");

        flag = present("flag",me );
        if( !flag ) return notify_fail("你手中没旗可以插。\n");

        if( query("name", flag) == query("team_name")+"大旗" )
                return notify_fail("自己的队旗应该插在大本营才是。\n");

        message_vision(HIY"$N把大旗哗啦啦展开，插上了旗杆。\n"NOR, me);

        set("flag",1);

        CHANNEL_D->do_channel(this_object(), "war",
                "听说"+me->name()+"将"+query("name", flag)+HIR"插到了演武厅！"NOR);
        set("flag_name",query("name", flag));

        destruct(flag);

        BATTLEFIELD_D->add_bonus_score(me, 20);
        BATTLEFIELD_D->win_battle(query_temp("battle/team_name", me)); 
        return 1;
}
