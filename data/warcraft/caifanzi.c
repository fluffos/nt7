// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"yuetee"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是菜贩子的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "caifanzi");
        set("owner_name", "菜贩子");
        set_temp("owner", "caifanzi");
        set_temp("owner_name", "菜贩子");
        ::setup();
}
