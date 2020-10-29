#include <ansi.h> 
inherit ROOM;

void create()
{
        set("short", HIY "秦皇墓室" NOR);
        set("long", @LONG
你来到了秦始皇陵墓的中心，面前有具汉白玉的石棺(coffin)，里面
躺着曾经不可一世的人物--秦始皇。
LONG);
        
        set("maze", 1);
        set("no_magic", 1);
        set("virtual_room", 1);
        set("no_clean_up", 1);       
        set("objects",([
                "/maze/mausoleum/unique_room/obj/coffin" : 1,
                "/maze/mausoleum/npc/goldman": 3,  
                "/maze/mausoleum/npc/goldman2": 2,  
        ]));
        setup();
}
