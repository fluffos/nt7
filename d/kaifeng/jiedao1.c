inherit ROOM;

void create()
{
        set("short", "御街");
        set("long", @LONG
这条道横贯南北，北到宣德门，南至南盈门，是以前皇上出巡时
常走的道，所以修得是格外平整。道两边店铺不断。西面就是开封府
的大堂，再向南一点就可以出城了。
LONG );
        set("outdoors", "kaifeng");
        set("exits", ([
                  "west" : __DIR__"kaifeng",
                  "north" : __DIR__"jiedao",
                  "south" : __DIR__"jiedao2",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -5040);
	set("coor/y", 2150);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}