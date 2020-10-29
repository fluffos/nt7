// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火[1;36m麒麟[2;37;0m[2;37;0m", ({"lol"}));        
        set("gender", "男性");                
        set("long", "麒，仁兽也，麋身牛尾一角；□（麟），牝麒也。[2;37;0m
它是夙岚的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "ohm");
        set("owner_name", "夙岚");
        set_temp("owner", "ohm");
        set_temp("owner_name", "夙岚");
        ::setup();
}
