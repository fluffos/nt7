// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("唠叨的麒麟[2;37;0m[2;37;0m", ({"duanziride"}));        
        set("gender", "男性");                
        set("long", "唠叨的麒麟[2;37;0m
它是段子的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "duanzi");
        set("owner_name", "段子");
        set_temp("owner", "duanzi");
        set_temp("owner_name", "段子");
        ::setup();
}
