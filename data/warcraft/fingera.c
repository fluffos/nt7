// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("挖火[2;37;0m[2;37;0m", ({"along"}));        
        set("gender", "男性");                
        set("long", "燸国[2;37;0m
它是加藤鹰的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "fingera");
        set("owner_name", "加藤鹰");
        set_temp("owner", "fingera");
        set_temp("owner_name", "加藤鹰");
        ::setup();
}
