// Room: /d/quanzhou/enyuanxiang.c
// Last Modified by Lonely on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "恩怨巷");
        set("long", @LONG
走进巷中，就感到一股肃杀之气弥漫四周。巷旁一碑耸立，上书「
恩怨分明」四个大字，仔细一看，乃用指力刻划而成！北面就是闻名天
下的擂台了。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"eastroad2",
        ]));
	set("coor/x", -880);
	set("coor/y", -7660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}