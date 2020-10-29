// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m钢铁装甲[2;37;0m[2;37;0m", ({"tank"}));        
        set("gender", "男性");                
        set("long", "钢铁装甲[2;37;0m
它是武当制药的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "medic");
        set("owner_name", "武当制药");
        set_temp("owner", "medic");
        set_temp("owner_name", "武当制药");
        ::setup();
}
