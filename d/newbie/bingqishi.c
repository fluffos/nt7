inherit ROOM;
#include <ansi.h>

string show_jia();

void create()
{
        set("short", "兵器室");
        set("long", @LONG
这是乃是古村的兵器室，四周是几个兵器架，上面摆满了各种各
样的兵器，（输入指令 look jia） 可以看到有什么兵器，需要的话
可以拿（输入指令 qu 兵器ID from jia）。
LONG);
        set("exits", ([
                "south" : __DIR__"lianwuchang",
        ]));

        set("item_desc", ([
                "jia"   :  (: show_jia :),
        ]));
        set("xinshoucun", 1);
        set("no_fight", 1);

        set("no_pk", 1);
	setup();
}

string show_jia()
{
        string msg;

        msg =  HIC "兵器架上摆有以下兵器：\n\n" NOR;
        msg += HIY "长鞭（chang bian）\n" NOR;
        msg += HIY "钢刀（gang dao）\n" NOR;
        msg += HIY "长剑（chang jian）\n" NOR;
        msg += HIY "齐眉棍（qimei gun）\n" NOR;
        msg += HIY "钢杖（gang zhang）\n" NOR;
        msg += HIY "竹棒（zhu bang）\n\n" NOR;
        msg += HIR "输入指令 " HIY "qu <兵器的英文名> from jia" HIR " 来取兵器。\n\n" NOR;

        return msg;
}

void init()
{
        add_action("do_get", "qu");
}

int do_get(string arg)
{
        mapping ids = ([
                "chang bian" : "bian",
                "gang dao"   : "blade",
                "chang jian" : "changjian",
                "qimei gun"  : "qimeigun",
                "gang zhang" : "gangzhang",
                "zhu bang"   : "zhubang",
        ]);
        
        string wid;
        object weapon;

        if (! arg)return notify_fail("你要取什么兵器？qu <兵器ＩＤ> from jia。\n");

        if (sscanf(arg, "%s from jia", wid) != 1)return notify_fail("你要取什么兵器？qu <兵器ＩＤ> from jia。\n");

        if (! ids[wid])
                return notify_fail("你输入的兵器不存在，请输入指令 look jia 来查看可拿取的兵器。\n");

        if( query_temp("qu_in_newbie", this_player()) )
                return notify_fail("你已经取过兵器了，如果想再次取兵器可退出游戏（输入exit）后重新进入。\n");

        weapon = new(__DIR__"obj/" + ids[wid]);

        if (! objectp(weapon))
                return notify_fail("clone " + wid + " error!\n");

        tell_object(this_player(),HIG"你从兵器架上拿了一"+query("unit", weapon)+weapon->name()+"。\n"NOR);

        weapon->move(this_player(), 1);

        tell_object(this_player(),HIC"请输入指令look "+query("id", weapon)+"查看该兵器的使用方法。\n"NOR);

        set_temp("qu_in_newbie", 1, this_player());

        return 1;
        
}
