// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m极品玄武[2;37;0m[2;37;0m", ({"xuanwu"}));        
        set("gender", "男性");                
        set("long", "$HIW$极品玄武[2;37;0m
它是黄鹤楼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hhl");
        set("owner_name", "黄鹤楼");
        set_temp("owner", "hhl");
        set_temp("owner_name", "黄鹤楼");
        ::setup();
}
