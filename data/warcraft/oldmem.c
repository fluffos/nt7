// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m地狱[1;31m火[2;37;0m[2;37;0m", ({"hellfire"}));        
        set("gender", "女性");                
        set("long", "地狱火[2;37;0m
它是忆当年的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "oldmem");
        set("owner_name", "忆当年");
        set_temp("owner", "oldmem");
        set_temp("owner_name", "忆当年");
        ::setup();
}
