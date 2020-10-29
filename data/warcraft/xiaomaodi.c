// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m狂蟒[2;37;0m[2;37;0m", ({"boa"}));        
        set("gender", "男性");                
        set("long", "一条疯狂的巨蛇，它正在狠狠地盯着你，仿佛可以看穿你的一切。[2;37;0m
它是小猫弟的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xiaomaodi");
        set("owner_name", "小猫弟");
        set_temp("owner", "xiaomaodi");
        set_temp("owner_name", "小猫弟");
        ::setup();
}
