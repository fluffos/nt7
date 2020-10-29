// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "树林");
        set("long", @LONG
你走在一片树林之中。这里树木茂盛，参天蔽日，非常凉快。西边
就是高丽的朝阳门了。有很多人从你身旁擦肩而过。看来高丽的繁华远
胜过处在战乱中的中原。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southwest" : __DIR__"baihumen",
                "northeast":__DIR__"shulin2",
        ]));
       setup();
        replace_program(ROOM);
}        
