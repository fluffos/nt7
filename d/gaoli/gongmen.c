// /d/gaoli/donggongmen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "宫门");
        set("long", @LONG
这是高丽皇宫的正门，北面朱红的宫门只有在百官早朝时才开启，
现在大门紧紧的关着，一队士兵英姿勃勃的站在宫门前，气氛宁静而压
抑，使人尽快离开。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south":__DIR__"yudao1", 
        ]));
set("objects",([
    __DIR__"npc/weishi":1,
    ]));
       setup();
        replace_program(ROOM);
}        
