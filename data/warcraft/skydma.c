// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("麒麟[2;37;0m[2;37;0m", ({"skql"}));        
        set("gender", "男性");                
        set("long", "麒麟[2;37;0m
它是事无绝对的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "skydma");
        set("owner_name", "事无绝对");
        set_temp("owner", "skydma");
        set_temp("owner_name", "事无绝对");
        ::setup();
}
