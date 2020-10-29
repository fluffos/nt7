#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIC"蛇洞"NOR);
        set("long",@LONG
好多蛇啊！
LONG);

        set("maze", 1);
        set("no_clean_up", 1);
        set("no_magic", 1);
        set("virtual_room",1);
        set("outdoors", "forest");  
        
        set("objects",([
                "/maze/forest/npc/snake_king": 1,   
                "/maze/forest/npc/snake_big": 5, 
                "/maze/forest/npc/snake_baby": 5,   
                "/maze/forest/obj/box1": 1,      
        ]));
        setup();
}
