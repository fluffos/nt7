// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m抱月乌锥马[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "$HIM$抱月乌锥马[2;37;0m
它是米芾的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "penm");
        set("owner_name", "米芾");
        set_temp("owner", "penm");
        set_temp("owner_name", "米芾");
        ::setup();
}
