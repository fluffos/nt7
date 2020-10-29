// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小猪猪[2;37;0m[2;37;0m", ({"littlemouse"}));        
        set("gender", "女性");                
        set("long", "一头傻乎乎的小乳猪。[2;37;0m
它是小耗子的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "mice");
        set("owner_name", "小耗子");
        set_temp("owner", "mice");
        set_temp("owner_name", "小耗子");
        ::setup();
}
