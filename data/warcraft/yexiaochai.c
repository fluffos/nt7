// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("刀狂剑痴[2;37;0m[2;37;0m", ({"daokuang"}));        
        set("gender", "男性");                
        set("long", "刀狂剑痴[2;37;0m
它是叶小钗的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yexiaochai");
        set("owner_name", "叶小钗");
        set_temp("owner", "yexiaochai");
        set_temp("owner_name", "叶小钗");
        ::setup();
}
