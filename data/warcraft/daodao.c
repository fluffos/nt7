// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"xing"}));        
        set("gender", "男性");                
        set("long", "叨叨的麒麟[2;37;0m
它是叨叨的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "daodao");
        set("owner_name", "叨叨");
        set_temp("owner", "daodao");
        set_temp("owner_name", "叨叨");
        ::setup();
}
