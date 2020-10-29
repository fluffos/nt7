inherit ROOM;

void create ()
{
        set ("short","南门");
        set ("long", @LONG
这里是九江的南门。这里的行人很多。虽是战乱年代，但九江还是
很繁华。不时有行人在这里出出进进，几个官兵耀武扬威地站在这里，
检查着来往的行人。
LONG);

        set("exits", ([
                "north":__DIR__"hzjie5",
        ]));
        set("objects",([
                "/d/city/npc/bing":2,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5090);
	set("coor/y", -1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}