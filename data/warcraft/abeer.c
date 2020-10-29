// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大狼狗[2;37;0m[2;37;0m", ({"langou"}));        
        set("gender", "女性");                
        set("long", "大[2;37;0m
它是杯酒的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "abeer");
        set("owner_name", "杯酒");
        set_temp("owner", "abeer");
        set_temp("owner_name", "杯酒");
        ::setup();
}
