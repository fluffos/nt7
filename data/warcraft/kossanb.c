// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m米贰兵散[2;37;0m[2;37;0m", ({"kossanbpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是散兵贰米的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kossanb");
        set("owner_name", "散兵贰米");
        set_temp("owner", "kossanb");
        set_temp("owner_name", "散兵贰米");
        ::setup();
}
