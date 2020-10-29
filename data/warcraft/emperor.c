// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[44;1m[1;34m太古[1;31m始祖[1;33m麒麟[2;37;0m[2;37;0m", ({"warsoul"}));        
        set("gender", "男性");                
        set("long", "天地初开时孕育的麒麟一族始祖。它全身霹雳金光闪耀威风凛凛。[2;37;0m
它是秦始皇的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "emperor");
        set("owner_name", "秦始皇");
        set_temp("owner", "emperor");
        set_temp("owner_name", "秦始皇");
        ::setup();
}
