// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("赤链蛇[2;37;0m[2;37;0m", ({"pla"}));        
        set("gender", "女性");                
        set("long", "不解释。[2;37;0m
它是挖宝一的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "wbga");
        set("owner_name", "挖宝一");
        set_temp("owner", "wbga");
        set_temp("owner_name", "挖宝一");
        ::setup();
}
