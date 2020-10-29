#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", HIW"枯骨坑"NOR);
        set("long", @LONG
枯骨坑！
LONG);
        
        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room",1);
        set("no_clean_up", 1);
        set("outdoors", "necropolis");
        
        set("objects",([
                "/maze/necropolis/npc/skeleton": 8,   
                "/maze/necropolis/npc/skeleton_fighter": 3,    
                "/maze/necropolis/npc/skeleton_mage": 3,  
                "/maze/necropolis/npc/skeleton_lich": 1, 
        ]));
        setup();
        // replace_program(ROOM);
}
