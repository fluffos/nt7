inherit ROOM;

void create()
{
        set("short", "御街");
        set("long", @LONG
御街是横贯开封的主要街道，也是皇上出巡的要道。街道两边店
铺亭台不断，小贩叫卖，行人来往，车马喧哗，一派繁华，东面一座
高的铁塔就是有名的开封铁塔。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"jieying",
                  "south" : __DIR__"road5",
                  "north" : __DIR__"xuandemen",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}