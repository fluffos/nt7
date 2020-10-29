// /d/gaoli/chaguan
// Room in 高丽
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "茶馆");
        set("long", @LONG
各地的名茶这里都有的卖。这里冲茶的水也是从城外专程运来的。
这里冲茶的壶更是名贵的紫砂壶。这里冲茶的方法也是最讲究的。每壶
茶的第一杯是用来养壶的。所以这里冲出的茶都有一种纯厚的香气。
LONG
        );
set("exits", ([
               "north":__DIR__"baihu-2", 
        ]));
     set("objects", ([
                "/d/gaoli/npc/chaer" : 1,
               //"/d/gaoli/npc/chake" : 2,
        ]));
     set("resource/water",1);
       setup();
        replace_program(ROOM);
}        
