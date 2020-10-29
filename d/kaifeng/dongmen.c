inherit ROOM;

void create()
{
        set("short", "东门");
        set("long", @LONG
开封府内东面的主要交通要道，街道两边店铺林立，行人车马如
梭。小商贩们挑着担子来回吆喝。出门向东北就是华北了，向东南是
扬州城。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"eroad",
                "east" : __DIR__"guandao1",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5020);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}