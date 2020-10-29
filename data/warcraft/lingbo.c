// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m微步[2;37;0m[2;37;0m", ({"lingbopet"}));        
        set("gender", "男性");                
        set("long", "哈哈[2;37;0m
它是凌波的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "lingbo");
        set("owner_name", "凌波");
        set_temp("owner", "lingbo");
        set_temp("owner_name", "凌波");
        ::setup();
}
