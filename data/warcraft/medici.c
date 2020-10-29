// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m钢铁装甲[2;37;0m[2;37;0m", ({"tank"}));        
        set("gender", "男性");                
        set("long", "钢铁装甲[2;37;0m
它是制药一号的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "medici");
        set("owner_name", "制药一号");
        set_temp("owner", "medici");
        set_temp("owner_name", "制药一号");
        ::setup();
}
