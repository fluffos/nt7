// This program is a part of NITAN MudLIB

inherit ROOM;
#include <room.h> 
void create()
{
        set("short", "山隙中");
        set("long", @LONG
这是山壁间一条一尺多宽的山隙，被附生在壁上的蔓草藤萝遮掩，
不加仔细探查很难发现。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "east" : __DIR__"shandong",
                "westdown" : __DIR__"dong1",
 
        ]));
         
        set("coor/x",150);
        set("coor/y",0);
        set("coor/z",20);
        setup();
        replace_program(ROOM); 
} 
