inherit ROOM;

void create()
{
        set("short", "御街");
        set("long", @LONG
这条道横贯南北，北到宣德门，南至南盈门，是以前皇上出巡时
常走的道，所以修得是格外平整。街道两边的店铺不断。北边过去不
远，就是大相国寺。东面是繁塔。
LONG );
        set("outdoors", "kaifeng");
        set("exits", ([
        "east":__DIR__"fanta",
                  "north" : __DIR__"jiedao1",
                  "south" : __DIR__"nanying",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -5040);
	set("coor/y", 2140);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}