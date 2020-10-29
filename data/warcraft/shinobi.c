// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m毒狮[2;37;0m[2;37;0m", ({"lion"}));        
        set("gender", "男性");                
        set("long", "狮子，虎见之而伏，豹见之而瞑，熊见之而跃。[2;37;0m
它是病毒的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "shinobi");
        set("owner_name", "病毒");
        set_temp("owner", "shinobi");
        set_temp("owner_name", "病毒");
        ::setup();
}
