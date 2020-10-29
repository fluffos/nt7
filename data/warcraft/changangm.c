// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "神武[2;37;0m
它是长七安的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "changangm");
        set("owner_name", "长七安");
        set_temp("owner", "changangm");
        set_temp("owner_name", "长七安");
        ::setup();
}
