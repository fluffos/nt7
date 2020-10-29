// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("爱骑[2;37;0m[2;37;0m", ({"ilovelong"}));        
        set("gender", "女性");                
        set("long", "我爱我的龙龙[2;37;0m
它是赵晶的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "zhaojing");
        set("owner_name", "赵晶");
        set_temp("owner", "zhaojing");
        set_temp("owner_name", "赵晶");
        ::setup();
}
