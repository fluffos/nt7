inherit ROOM;

void create()
{
        set("short", "厢房");
        set("long", @LONG
这里是苗家正厅旁的一个厢房，是供给远来的客人和苗家弟子所
居住的。厢房中央摆着几张大床，几张桌子。室中光线柔和，使人更
增睡意。
LONG );
        set("exits", ([
                "south" : __DIR__"miaojia_zhengting",
        ]));
        set("no_fight",1);
        set("no_steal",1);
        set("sleep_room",1);
        set("no_clean_up", 0);
        set("coor/x", -9010);
	set("coor/y", -950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}