// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m巨雕[2;37;0m[2;37;0m", ({"judiao"}));        
        set("gender", "女性");                
        set("long", "这是一只火红的巨雕，传说它身上有朱雀的灵魂。[2;37;0m
它是独孤醉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "duguzui");
        set("owner_name", "独孤醉");
        set_temp("owner", "duguzui");
        set_temp("owner_name", "独孤醉");
        ::setup();
}
