// This program is a part of NITAN MudLIB 
// redl 2013/4
#include <ansi.h> 
#include <room.h> 
inherit ROOM; 

void create() 
{ 
                set("short", "山脊小道"); 
                        set("long", @LONG
这是条山脊上的迂回盘折的小道，云蒸霞蔚中蜿蜒而上，两旁却
是深不见底的绝壁峡谷。路边的石缝林间，不经意地盛开着一丛丛艳
丽而凄绝的高山杜鹃花。
LONG );
                                

                set("exits", ([ /* sizeof() == */ 
                        "eastdown" : __DIR__"suiroad2",
                        "northup" : __DIR__"suistone",
                ])); 

                set("no_rideto", 1);
                set("no_flyto", 1);
                setup(); 
} 


