// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m火麒麟[31m[2;37;0m[2;37;0m", ({"firebarry"}));        
        set("gender", "男性");                
        set("long", "磷甲刀枪不入，能散发极高温的火焰，自古以来曾四处为害[2;37;0m
它是老啤的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "barry");
        set("owner_name", "老啤");
        set_temp("owner", "barry");
        set_temp("owner_name", "老啤");
        ::setup();
}
