// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m专杀鬼子[2;37;0m[2;37;0m", ({"leguia"}));        
        set("gender", "男性");                
        set("long", "$HIC$专杀鬼子[2;37;0m
它是踏平东京的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "legui");
        set("owner_name", "踏平东京");
        set_temp("owner", "legui");
        set_temp("owner_name", "踏平东京");
        ::setup();
}
