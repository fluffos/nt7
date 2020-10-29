// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m墨鱼[2;37;0m[2;37;0m", ({"mql"}));        
        set("gender", "男性");                
        set("long", "墨鱼再临[2;37;0m
它是铁头丁的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "uliank");
        set("owner_name", "铁头丁");
        set_temp("owner", "uliank");
        set_temp("owner_name", "铁头丁");
        ::setup();
}
