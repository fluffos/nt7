// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("驴脸老诅[2;37;0m[2;37;0m", ({"goto"}));        
        set("gender", "女性");                
        set("long", "它就是一驴脸。[2;37;0m
它是阿草的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "hasty");
        set("owner_name", "阿草");
        set_temp("owner", "hasty");
        set_temp("owner_name", "阿草");
        ::setup();
}
