// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("无敌[2;37;0m[2;37;0m", ({"jinhu"}));        
        set("gender", "男性");                
        set("long", "无敌[2;37;0m
它是胡一乱飞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "mcat");
        set("owner_name", "胡一乱飞");
        set_temp("owner", "mcat");
        set_temp("owner_name", "胡一乱飞");
        ::setup();
}
