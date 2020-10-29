// Room: /d/suzhou/lingyanta.c
// Last Modified by Lonely on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "灵岩塔");
        set("long",@long
灵岩塔，又名永多宝佛塔，始建于梁代。高约三十多米，为七级八
面塔。塔身上刻写着“灵岩塔”三个大字。
long);
        set("outdoors", "suzhou");
        set("exits",([
                "west"   : __DIR__"lingyansi",
//                "westup" : __DIR__"sdhyuan",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1130);
	set("coor/y", -1160);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}