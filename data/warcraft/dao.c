// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("九把刀[2;37;0m[2;37;0m", ({"daoze"}));        
        set("gender", "男性");                
        set("long", "阿哈哈哈...[2;37;0m
它是刀九把的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dao");
        set("owner_name", "刀九把");
        set_temp("owner", "dao");
        set_temp("owner_name", "刀九把");
        ::setup();
}
