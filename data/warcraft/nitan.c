// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[33m泥马[2;37;0m[2;37;0m", ({"nima"}));        
        set("gender", "女性");                
        set("long", "哈哈[2;37;0m
它是泥潭的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "nitan");
        set("owner_name", "泥潭");
        set_temp("owner", "nitan");
        set_temp("owner_name", "泥潭");
        ::setup();
}
