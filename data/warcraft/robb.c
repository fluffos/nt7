// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m史[1;35m塔[1;32m克[2;37;0m[2;37;0m", ({"stk"}));        
        set("gender", "女性");                
        set("long", "不知道啊不知道[2;37;0m
它是罗柏的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "robb");
        set("owner_name", "罗柏");
        set_temp("owner", "robb");
        set_temp("owner_name", "罗柏");
        ::setup();
}
