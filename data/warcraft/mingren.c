// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m文太[2;37;0m[2;37;0m", ({"toad"}));        
        set("gender", "男性");                
        set("long", "这就是火影忍者中的蛤蟆老大。[2;37;0m
它是欧阳鸣人的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mingren");
        set("owner_name", "欧阳鸣人");
        set_temp("owner", "mingren");
        set_temp("owner_name", "欧阳鸣人");
        ::setup();
}
