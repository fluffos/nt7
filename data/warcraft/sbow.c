// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m避水金睛兽[2;37;0m[2;37;0m", ({"bishui"}));        
        set("gender", "女性");                
        set("long", "老牛的坐骑[2;37;0m
它是旁观者的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "sbow");
        set("owner_name", "旁观者");
        set_temp("owner", "sbow");
        set_temp("owner_name", "旁观者");
        ::setup();
}
