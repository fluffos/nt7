// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火麒麟[2;37;0m[2;37;0m", ({"yxq"}));        
        set("gender", "男性");                
        set("long", "火麒麟[2;37;0m
它是药小邪的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fengyao");
        set("owner_name", "药小邪");
        set_temp("owner", "fengyao");
        set_temp("owner_name", "药小邪");
        ::setup();
}
