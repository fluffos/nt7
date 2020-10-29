inherit ROOM;

void create ()
{
        set ("short","东门");
        set ("long", @LONG
这里是东门了。有很多行人都在往城内走。在战乱的年代，武汉竟
然出奇地热闹。有几个官兵正耀武扬威地站在这里，检查着来往的行人。
LONG);

        set("exits", ([
                "west":__DIR__"zhongxin",
        ]));
        set("objects",([
                "/d/city/npc/bing":2,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5080);
	set("coor/y", -1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}