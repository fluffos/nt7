// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[34m渊鱼丛雀[2;37;0m[2;37;0m", ({"woo"}));        
        set("gender", "男性");                
        set("long", "渊鱼丛雀!!![2;37;0m
它是夜无道的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wowo");
        set("owner_name", "夜无道");
        set_temp("owner", "wowo");
        set_temp("owner_name", "夜无道");
        ::setup();
}
