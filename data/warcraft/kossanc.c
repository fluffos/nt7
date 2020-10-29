// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m米叁兵散[2;37;0m[2;37;0m", ({"kossancpet"}));        
        set("gender", "男性");                
        set("long", "美丽中国梦[2;37;0m
它是散兵叁米的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "kossanc");
        set("owner_name", "散兵叁米");
        set_temp("owner", "kossanc");
        set_temp("owner_name", "散兵叁米");
        ::setup();
}
