// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小鸟鸟[2;37;0m[2;37;0m", ({"xiaoniao"}));        
        set("gender", "男性");                
        set("long", "其实我很大[2;37;0m
它是鸟米的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "gaokeyua");
        set("owner_name", "鸟米");
        set_temp("owner", "gaokeyua");
        set_temp("owner_name", "鸟米");
        ::setup();
}
