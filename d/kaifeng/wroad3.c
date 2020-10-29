inherit ROOM;

void create()
{
 set("short", "西大街");
        set("long", @LONG
开封府内西面的主要交通要道，街道两边店铺林立，行人车马如
梭商贩的吆喝，市民与小贩的讨价还价，喧闹无比。南边不远就是延
庆观。东面是龙亭园。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"wroad2",
                  "east" : __DIR__"tinyuan",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5070);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}