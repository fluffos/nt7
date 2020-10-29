// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m幽冥[1;31m血河[1;36m虎[2;37;0m[2;37;0m", ({"pkm"}));        
        set("gender", "男性");                
        set("long", "一头来之冥界的白虎[2;37;0m
它是沉舟的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "sunrain");
        set("owner_name", "沉舟");
        set_temp("owner", "sunrain");
        set_temp("owner_name", "沉舟");
        ::setup();
}
