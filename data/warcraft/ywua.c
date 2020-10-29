// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[30m驴子他爹[2;37;0m[2;37;0m", ({"lvzia"}));        
        set("gender", "男性");                
        set("long", "驴子他爹[2;37;0m
它是邪月秃贼的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ywua");
        set("owner_name", "邪月秃贼");
        set_temp("owner", "ywua");
        set_temp("owner_name", "邪月秃贼");
        ::setup();
}
