// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("升龙拳[2;37;0m[2;37;0m", ({"ryo"}));        
        set("gender", "男性");                
        set("long", "后有跟[2;37;0m
它是毁容的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "huirong");
        set("owner_name", "毁容");
        set_temp("owner", "huirong");
        set_temp("owner_name", "毁容");
        ::setup();
}
