// /d/gaoli/shanghang
// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "商行");
        set("long", @LONG
这是高丽最负胜名的商行--广义隆，这个商行的货物远到碎叶。岭
南域内外都有它的分店，据说这里的老板喜好收藏，藏品丰厚，其中有
不少稀奇古怪的奇珍异宝，只是谁也没见过。
LONG
        );
set("exits", ([
               "north":__DIR__"baihu-1", 
        ]));
set("objects", ([
                "/d/gaoli/npc/cui" : 1,
        ]));

       setup();
        replace_program(ROOM);
}        
