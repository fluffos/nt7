//Edited by fandog, 02/18/2000

inherit ROOM;
void create()
{
        set("short", "黄土路");
        set("long", @LONG
这是一条黄土路，不时可见江湖中人背着包袱，别着刀剑往北走去。
地上有许多马车碾过的痕迹。
LONG );
        set("exits", ([
                "north"      : __DIR__"tulu1",
                "west"       : __DIR__"tulu3",
                "southeast"  : "/d/yueyang/beimen",
                "southwest"  : "/d/kunming/yunnan1",
        ]));
        set("outdoors", "jingzhou");
        set("no_clean_up", 0);
        set("coor/x", -7100);
	set("coor/y", -2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}