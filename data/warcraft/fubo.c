// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("镇魂麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "男性");                
        set("long", "一股悠远宁静的气息将你包围[2;37;0m
它是伏波的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "fubo");
        set("owner_name", "伏波");
        set_temp("owner", "fubo");
        set_temp("owner_name", "伏波");
        ::setup();
}
