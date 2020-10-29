inherit ROOM;

void create()
{
        set("short", "中院");
        set("long", @LONG
中院分为前后两部分，院子的正中有座铁制浮屠，高七层。雕刻
精美花纹。前边部分除中间的行道外，两边是花圃，各种一棵高大的
菩提树。后边铺着青石，通向大雄宝殿。南边是天王殿，东边是素斋
厨，西面是浴室。
LONG );
        set("objects", ([
                  __DIR__"npc/obj/tiefutu" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"tianwang",
                  "north" : __DIR__"daxiong",
                  "east" : __DIR__"chufang",
                  "west" : __DIR__"yushi",
        ]));
        set("outdoors", "xiangguosi");

	set("coor/x", -5040);
	set("coor/y", 2200);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}
