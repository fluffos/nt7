// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("看什么[2;37;0m[2;37;0m", ({"xcmmtt"}));        
        set("gender", "女性");                
        set("long", "看什么[2;37;0m
它是不悔的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xcmm");
        set("owner_name", "不悔");
        set_temp("owner", "xcmm");
        set_temp("owner_name", "不悔");
        ::setup();
}
