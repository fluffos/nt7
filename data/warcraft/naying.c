// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m好声音转椅[2;37;0m[2;37;0m", ({"baima"}));        
        set("gender", "男性");                
        set("long", "这个是从英国空运来的豪华转椅，由犀牛皮做成，价值80多万。[2;37;0m
它是那英的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "naying");
        set("owner_name", "那英");
        set_temp("owner", "naying");
        set_temp("owner_name", "那英");
        ::setup();
}
