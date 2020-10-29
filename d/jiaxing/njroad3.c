// Room: /d/jiaxing/njroad3.c
// Last Modified by Lonely on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "村中小路");
        set("long", @LONG
一条村中的小路。路边是一家民房，好象很久没有人住的样子。南
边有条小路通向江边。
LONG
        );
        set("outdoors","jiaxing");
        set("exits", ([
                "west" : __DIR__"njroad2",
                "east" : __DIR__"njeast",
                "north": __DIR__"qianyuan",
                "south": __DIR__"njroad4",
        ]) );

        set("no_clean_up", 0);
	set("coor/x", 1270);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}