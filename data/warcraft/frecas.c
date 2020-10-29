// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m间条小猫[2;37;0m[2;37;0m", ({"ttiger"}));        
        set("gender", "女性");                
        set("long", "HAHAHA[2;37;0m
它是影月的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "frecas");
        set("owner_name", "影月");
        set_temp("owner", "frecas");
        set_temp("owner_name", "影月");
        ::setup();
}
