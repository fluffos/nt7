// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("可爱[2;37;0m[2;37;0m", ({"keai"}));        
        set("gender", "女性");                
        set("long", "可爱动人的人[2;37;0m
它是小盐的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaoyan");
        set("owner_name", "小盐");
        set_temp("owner", "xiaoyan");
        set_temp("owner_name", "小盐");
        ::setup();
}
