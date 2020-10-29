// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;33m七[1;36m色[1;37m蝙[1;31m蝠[2;37;0m[2;37;0m", ({"qcbfx"}));        
        set("gender", "女性");                
        set("long", "神龙教的一只可爱的小动物。[2;37;0m
它是洪不安通的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "hbat");
        set("owner_name", "洪不安通");
        set_temp("owner", "hbat");
        set_temp("owner_name", "洪不安通");
        ::setup();
}
