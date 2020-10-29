// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("不死之凰[2;37;0m[2;37;0m", ({"skky"}));        
        set("gender", "男性");                
        set("long", "这是一只普通的朱雀。[2;37;0m
它是虹剑的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "sixkiss");
        set("owner_name", "虹剑");
        set_temp("owner", "sixkiss");
        set_temp("owner_name", "虹剑");
        ::setup();
}
