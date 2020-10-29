#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", HIM "残破灵堂" NOR);
        set("long", @LONG
残破灵堂！
LONG);
        
        set("maze", 1);
        set("no_clean_up", 1);
        set("no_magic", 1);
        set("virtual_room",1);
        set("outdoors", "necropolis");
        
        set("objects",([
                "/maze/necropolis/npc/ghost": 8,   
                "/maze/necropolis/npc/ghost_fire": 3,    
                "/maze/necropolis/npc/ghost_eye": 3,
                "/maze/necropolis/npc/ghost_devil": 1,  
        ]));
        setup();
        // replace_program(ROOM);
}
