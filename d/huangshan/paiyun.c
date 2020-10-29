// Room: /d/huangshan/paiyun.c
// Last Modified by Lonely on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "排云亭");
        set("long", @LONG
观西海云的最佳处。黄山云海历来五分，东西南北海加天海，其中
西海云多为层状，好似排涛叠浪，排云亭是为观云而建，也因云而名，
在这里可以尽览黄山四奇之云海的妙处。
LONG
        );
        set("exits", ([ 
                "northup" : __DIR__"shizi",
                "south"   : __DIR__"feilai",
                "east"    : __DIR__"sanhua",
        ]));
        set("outdoors", "huangshan");
        set("no_clean_up", 0);
        set("coor/x", -605);
        set("coor/y", -1020);
        set("coor/z", -10);
        setup();
        replace_program(ROOM);
}