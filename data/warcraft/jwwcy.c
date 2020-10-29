// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火麒麟[2;37;0m[2;37;0m", ({"hql"}));        
        set("gender", "男性");                
        set("long", "火麒麟[2;37;0m
它是叶隐的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jwwcy");
        set("owner_name", "叶隐");
        set_temp("owner", "jwwcy");
        set_temp("owner_name", "叶隐");
        ::setup();
}
