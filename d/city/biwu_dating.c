#include <room.h>
#include <ansi.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"演武大厅"NOR);
        set("long", @LONG
这是一个宽敞的大房间，靠北墙搭着一个巨大的擂台(leitai)，
擂台后被一块布帘遮挡的密密实实，但是一股浓厚的杀气仍然从布帘
后散发出来，弥漫在空气里，直钻入你内心。在东面墙上，悬挂着偌
大的一个大匾(dabian)。
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);
    set("biwu_room",1);

    set("item_desc",([
            "leitai" : "一个四四方方的大擂台，你可以跳(jump)上去。\n",
    ]));

    set("exits", ([
        "south"  : "/d/city/biwu_road",
    ]));

    set("no_clean_up", 0);
	set("coor/x", -60);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
}

void init()
{
    add_action("do_no","get");
    add_action("do_no","put");
    add_action("do_no","drop");
    add_action("do_no","summon");
    add_action("do_no","eat");
    add_action("do_no","drink");
    add_action("do_no","guard");
    add_action("do_jump","jump");
    add_action("do_look","look");
}

int do_no()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在这里你想干什么？\n");
    return 1;
}

int do_look(string arg)
{
    string msg;
    int i;
    mapping paiming;

    if (arg != "dabian") return 0;
    paiming = COMPETE_D->query_tops();
    msg = HIC "      *          雄       霸       天       下          *\n"NOR;
    msg += HIC "-------------------------------------------------------------\n";
    msg += "\n";
    for (i = 0;i < sizeof(paiming);i++)
{
            msg += HIY + "   【天下第" + chinese_number(i+1) + "】 " + NOR + paiming[i]["title"] + "\n";
            msg += "\n";
}
    msg += HIC "-------------------------------------------------------------\n";
    write(msg);
    return 1;
}

int do_jump(string arg)
{
    object me;

    me = this_player();

    if (arg != "leitai")
    {
            tell_object(me,"你要往哪里跳啊？\n");
            return 1;
    }

    if (wizardp(me))
    {
            tell_object(me,"你是巫师啊，就别来跟玩家争什么第一第二了！\n");
            return 1;
    }

    if (COMPETE_D->join_competition(me)) 
            return 1;
}