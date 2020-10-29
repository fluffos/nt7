#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short",HIY"虎山"NOR);
        set("long",@LONG
好多虎啊！
LONG);
        set("maze", 1);
        set("no_clean_up", 1);
        set("no_magic", 1);
        set("virtual_room",1);
        set("outdoors", "forest");  
        set("objects",([
                "/maze/forest/npc/tiger_king": 1,   
                "/maze/forest/npc/tiger_big": 5, 
                "/maze/forest/npc/tiger_baby": 5,   
                "/maze/forest/obj/box1": 1,       
        ]));
        setup();
}
