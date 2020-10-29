// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("瑞兽自在麒麟[2;37;0m[2;37;0m", ({"xiaoyaoqilin"}));        
        set("gender", "男性");                
        set("long", "瑞兽自在麒麟[2;37;0m
它是张郁闷的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "renxiaoyao");
        set("owner_name", "张郁闷");
        set_temp("owner", "renxiaoyao");
        set_temp("owner_name", "张郁闷");
        ::setup();
}
