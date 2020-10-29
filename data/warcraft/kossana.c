// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("美丽中国梦[2;37;0m[2;37;0m", ({"kossanapet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是散兵壹米的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kossana");
        set("owner_name", "散兵壹米");
        set_temp("owner", "kossana");
        set_temp("owner_name", "散兵壹米");
        ::setup();
}
