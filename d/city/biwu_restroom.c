#include <room.h>
#include <ansi.h>
inherit ROOM;

int do_look(string arg);

void create()
{
    set("short", HIY"休息室"NOR);
        set("long", @LONG
这是一个简单但是色彩柔和的小房间，四周随意放着一些沙发，
另外中间还有几张小床，给打下擂台的挑战者们时不时给抬到这里来。
这里最好请保持安静。
LONG );

    set("no_fight",1);
    set("no_beg",1);
    set("no_steal",1);
    set("biwu_room",1);

    set("exits", ([
        "east"  : "/d/city/biwu_road",
    ]));

    set("no_clean_up", 0);
	set("coor/x", -70);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
}

void init()
{
    add_action("do_get","get");
    add_action("do_put","put");
    add_action("do_drop","drop");
}

int do_get()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在这里你想干什么？\n");
    return 1;
}

int do_drop()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在这里你想干什么？\n");
    return 1;
}

int do_put()
{
    object me;
    me = this_player();
    if (wizardp(me)) return 0;

    tell_object(me,"在这里你想干什么？\n");
    return 1;
}