// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m吉普[1;37m牧马人[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这是JEEP最新推出撒哈拉2.8T柴油,四门加高，号称越野之王[2;37;0m
它是古龙的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "gulong");
        set("owner_name", "古龙");
        set_temp("owner", "gulong");
        set_temp("owner_name", "古龙");
        ::setup();
}
