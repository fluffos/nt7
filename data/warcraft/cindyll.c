// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小耗子[2;37;0m[2;37;0m", ({"mouse"}));        
        set("gender", "女性");                
        set("long", "小耗子[2;37;0m
它是糖醋鲤鱼的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cindyll");
        set("owner_name", "糖醋鲤鱼");
        set_temp("owner", "cindyll");
        set_temp("owner_name", "糖醋鲤鱼");
        ::setup();
}
