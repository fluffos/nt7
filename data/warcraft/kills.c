// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("碧水晶晶兽[2;37;0m[2;37;0m", ({"superstart"}));        
        set("gender", "男性");                
        set("long", "懒洋洋，暖洋洋[2;37;0m
它是虾米的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kills");
        set("owner_name", "虾米");
        set_temp("owner", "kills");
        set_temp("owner_name", "虾米");
        ::setup();
}
