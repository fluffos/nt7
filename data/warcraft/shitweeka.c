// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("异形[2;37;0m[2;37;0m", ({"queen"}));        
        set("gender", "女性");                
        set("long", "皇后[2;37;0m
它是一长的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "shitweeka");
        set("owner_name", "一长");
        set_temp("owner", "shitweeka");
        set_temp("owner_name", "一长");
        ::setup();
}
