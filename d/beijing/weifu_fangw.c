inherit ROOM;

void create()
{
        set("short", "西厢房");
        set("long", @LONG
这里是鹿鼎公府的西边的一个厢房，是供给王府的客人所居住的。
厢房中央摆着几张大床，几张桌子。室中光线柔和，使人更增睡意。
LONG );
        set("exits", ([
                "east" : "/d/beijing/weifu_dating",
        ]));

       set("no_fight",1);
       set("no_steal",1);
       set("sleep_room",1);
        set("no_clean_up", 0);
	set("coor/x", -2810);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}