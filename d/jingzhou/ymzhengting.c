// This program is a part of NT MudLIB

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "衙门正厅");
        set("long", @LONG
这里是江陵知府的衙门大堂。两边是“肃静”、“回避”的牌子，
十几个衙役齐刷刷地站着，手拿水火棍，虎视耽耽的。知府大人坐在案
台后，冷冷地逼视着你。大堂上方挂一巨匾，上写“明镜高悬”四个大
字。一个师爷打扮的人站在知府大人身后，不时俯身对大人耳语几句。
LONG );
        set("region", "jingzhou");
        set("exits", ([
                "north" : __DIR__"jzyamen",
                "south" : __DIR__"houyuan",
                "east"  : __DIR__"laofang",
        ]));
        set("objects", ([
                "/d/city/npc/yayi" : 4,
                __DIR__"npc/shiye" : 1,
                __DIR__"npc/ling"  : 1,
        ]));

        create_door("east", "铁门", "west", DOOR_CLOSED);
        set("coor/x", -7110);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if (! wizardp(me) && objectp(present("ling tuisi", environment(me))) &&
                dir == "east")
                return notify_fail("凌翰林挡住了你：请勿入牢房。\n");
        return ::valid_leave(me, dir);
}