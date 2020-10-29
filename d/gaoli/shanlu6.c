// /d/gaoli/xuanwumen
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "山路");
        set("long", @LONG
你走在一条山路上。南边就是高丽的玉龙门了。有很多行人从你的
身旁走过，说着你听不懂的高丽语。看来高丽的繁华要略胜过现在战乱
的中原。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southwest" : __DIR__"xuanwumen",
                "northeast":__DIR__"shanlu7",
        ]));
       setup();
        
}

