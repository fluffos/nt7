// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qiling"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是运镖甲的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "atyubiao");
        set("owner_name", "运镖甲");
        set_temp("owner", "atyubiao");
        set_temp("owner_name", "运镖甲");
        ::setup();
}
