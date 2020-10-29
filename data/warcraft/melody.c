// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是叶断尘的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "melody");
        set("owner_name", "叶断尘");
        set_temp("owner", "melody");
        set_temp("owner_name", "叶断尘");
        ::setup();
}
