// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("逗战剩佛[2;37;0m[2;37;0m", ({"cctv"}));        
        set("gender", "男性");                
        set("long", "星海云雨的一只幻兽而已。[2;37;0m
它是星海云雨的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "asmmah");
        set("owner_name", "星海云雨");
        set_temp("owner", "asmmah");
        set_temp("owner_name", "星海云雨");
        ::setup();
}
