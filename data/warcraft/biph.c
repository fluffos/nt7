// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("猪宝宝[2;37;0m[2;37;0m", ({"zhu"}));        
        set("gender", "男性");                
        set("long", "一头狂吃不饱的猪[2;37;0m
它是玄空飞羽的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "biph");
        set("owner_name", "玄空飞羽");
        set_temp("owner", "biph");
        set_temp("owner_name", "玄空飞羽");
        ::setup();
}
