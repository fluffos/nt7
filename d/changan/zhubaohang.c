//Room: zubaohang.c

inherit ROOM;

void create ()
{
        set ("short", "珠宝行");
        set("long", @LONG
珠宝行中珠光宝气四射，眩的人有些睁不开眼睛。精致的长柜中
陈设着各类首饰珠宝玉器，几个老行家正陪着客人挑选所需珠宝。一
个雕花木架上摆着颗三尺多高的玉树，珍贵之外又透着淡雅秀丽，曲
折含蓄之气。
LONG );
        set("exits", ([
                "south" : "/d/changan/yongtai-beikou",
        ]));
        set("objects", ([
                "/d/changan/npc/jinfuhuan"  : 1,
        ]));

        set("coor/x", -10760);
	set("coor/y", 1970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}