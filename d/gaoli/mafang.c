// /d/gaoli/maji
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "马房");
        set("long", @LONG
高丽马虽然不如突厥马那么高大，但却善走长途，这个马房，各式
各样的马应有尽有，突厥马，高丽马，甚至连岭南马都有。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
               "south":__DIR__"qinglong-1", 
        ]));
set("objects", ([
                "/d/gaoli/npc/ma" : 1,
        ]));
       setup();
        replace_program(ROOM);
}        
