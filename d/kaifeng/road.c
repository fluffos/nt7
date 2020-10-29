inherit ROOM;

void create()
{
        set("short", "御街");
        set("long", @LONG
这条道横贯南北，北到宣德门，南至南盈门，是以前皇上出巡时
常走的道所以修得也是格外平整。道两边店铺不断。向南再过去不远。
经过石拱门就是相国寺，北面是朱雀门。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"yaopu",
                  "southup" : __DIR__"gongmen",
                  "north" : __DIR__"zhuque",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5050);
	set("coor/y", 2230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}