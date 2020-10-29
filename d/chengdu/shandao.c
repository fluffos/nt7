//Edited by fandog, 02/18/2000

inherit ROOM;
void create()
{
        set("short", "山道");
        set("long", @LONG
这是一条樵夫乡农践踏出来的山道，偶而可见一两个江湖中人背着
包袱，别着刀剑走过。北面是一片蓊郁的山林，南边就是有名的白帝城
了。
LONG );
        set("exits", ([
                "south" : __DIR__"baidicheng",
                "north" : __DIR__"shennongjia",
        ]));
        set("outdoors", "jiangling");
        set("no_clean_up", 0);
        set("coor/x", -15070);
	set("coor/y", -1820);
	set("coor/z", -40);
	setup();
        replace_program(ROOM);
}