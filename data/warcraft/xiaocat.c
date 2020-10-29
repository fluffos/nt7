// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("强化神兽[2;37;0m[2;37;0m", ({"jinhu"}));        
        set("gender", "男性");                
        set("long", "强化神兽[2;37;0m
它是胡乱飞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xiaocat");
        set("owner_name", "胡乱飞");
        set_temp("owner", "xiaocat");
        set_temp("owner_name", "胡乱飞");
        ::setup();
}
