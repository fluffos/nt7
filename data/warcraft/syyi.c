// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("七哈哈[2;37;0m[2;37;0m", ({"qihaha"}));        
        set("gender", "男性");                
        set("long", "七哈哈[2;37;0m
它是欧子的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "syyi");
        set("owner_name", "欧子");
        set_temp("owner", "syyi");
        set_temp("owner_name", "欧子");
        ::setup();
}
