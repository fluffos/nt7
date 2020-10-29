// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("飞飞飞飞[2;37;0m[2;37;0m", ({"fly_b"}));        
        set("gender", "女性");                
        set("long", "飞飞飞飞[2;37;0m
它是丐帮号一的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wucb");
        set("owner_name", "丐帮号一");
        set_temp("owner", "wucb");
        set_temp("owner_name", "丐帮号一");
        ::setup();
}
