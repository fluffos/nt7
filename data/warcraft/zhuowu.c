// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m小珊瑚虫[2;37;0m[2;37;0m", ({"coral"}));        
        set("gender", "男性");                
        set("long", "蹁跹浮游，梦幻空花！[2;37;0m
它是卓无航的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "zhuowu");
        set("owner_name", "卓无航");
        set_temp("owner", "zhuowu");
        set_temp("owner_name", "卓无航");
        ::setup();
}
