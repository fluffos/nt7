// Room: /d/shaolin/chufang.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "厨房");
        set("long", @LONG
炊烟缭绕，蒸汽腾腾，香味扑鼻而来。靠墙是一排数丈长的灶台，
支着十来口大锅，最大的一口饭锅上方竟有人从梁上悬空而下，手持
木棍在搅拌。除了烧饭的僧人外，几位火工头陀忙着劈柴运薪，灶下
炉火熊熊。一位中年僧人正来回催促着。
LONG );
        set("exits", ([
                "south" : __DIR__"fanting1",
        ]));
        set("objects",([
                __DIR__"npc/shaofan-seng" : 2,
        ]));
        set("resource/water", 1);
        setup();
        replace_program(ROOM);
}
