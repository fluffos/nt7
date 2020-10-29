#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", HIY"聚灵法阵"NOR);
        set("long", @LONG
聚灵法阵！
LONG);
        
        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room",1);
        set("no_clean_up", 1);
        set("outdoors", "necropolis");
        
        set("objects",([
                "/maze/necropolis/npc/skeleton_lich_special": 1,  
                "/maze/necropolis/npc/zombie_lord_special": 1,  
                "/maze/necropolis/npc/ghost_devil_special": 1,  
        ]));
        setup();
        // replace_program(ROOM);
}
