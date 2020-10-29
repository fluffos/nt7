// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("唠叨麒麟[2;37;0m[2;37;0m", ({"husayride"}));        
        set("gender", "男性");                
        set("long", "唠叨麒麟[2;37;0m
它是胡乱说的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "husay");
        set("owner_name", "胡乱说");
        set_temp("owner", "husay");
        set_temp("owner_name", "胡乱说");
        ::setup();
}
