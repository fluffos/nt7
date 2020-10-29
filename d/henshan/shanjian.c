inherit ROOM;
void create()
{
        set("short", "山涧");
        set("long", @LONG
顺山涧漂流而下，沿溪遍布珍稀树木，泉石，林木，花草及峰峦
均极宜人。涧流至崖折叠飞泄而下，声震山谷。
LONG );
        set("exits", ([
               "down"     : __DIR__"heishatan",
               "northup"  : __DIR__"fangguangsi",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6990);
	set("coor/y", -5560);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}