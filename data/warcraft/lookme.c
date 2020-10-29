// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m龙猫[2;37;0m[2;37;0m", ({"longlong"}));        
        set("gender", "女性");                
        set("long", "说说[2;37;0m
它是乱舞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "lookme");
        set("owner_name", "乱舞");
        set_temp("owner", "lookme");
        set_temp("owner_name", "乱舞");
        ::setup();
}
