// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m输出文字中[2;37;0m[2;37;0m", ({"bmw"}));        
        set("gender", "男性");                
        set("long", "bmw[2;37;0m
它是菜楚楚的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "caicc");
        set("owner_name", "菜楚楚");
        set_temp("owner", "caicc");
        set_temp("owner_name", "菜楚楚");
        ::setup();
}
