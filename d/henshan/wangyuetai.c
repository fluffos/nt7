#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "望月台");
        set("long", @LONG
望月台是祝融殿后一高耸巨石。每当夜籁，皓月当空，犹如玉盘
冰轮，漫洒万里清辉，清冷月色，辉映低昂的群峰。此时浩然万里，
举七十二峰，峰峰贮冰壶中，始信下方无此月也。前人因此有诗句言
人间朗魄已皆尽，此地清光犹未低。
LONG );
        set("exits", ([
               "southup"    : __DIR__"zhurongdian",
               "up"    : "/d/reborn/jitan3",
        ]));

        set("objects", ([
                __DIR__"npc/youke"    : 3,
        ]));    

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6930);
	set("coor/y", -5480);
	set("coor/z", 30);
	setup();
}