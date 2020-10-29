#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", HIC"乱坟岗"NOR);
        set("long", @LONG
乱坟岗！
LONG);
        
        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room",1);
        set("no_clean_up", 1);
        set("outdoors", "necropolis");
        
        set("objects",([
                "/maze/necropolis/npc/zombie": 8,   
                "/maze/necropolis/npc/zombie_blood": 3,    
                "/maze/necropolis/npc/zombie_power": 3,  
                "/maze/necropolis/npc/zombie_lord": 1,  
        ]));
        setup();
        // replace_program(ROOM);
}
