// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大鸟[2;37;0m[2;37;0m", ({"qazxsw"}));        
        set("gender", "女性");                
        set("long", "  [2;37;0m
它是波波的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "davida");
        set("owner_name", "波波");
        set_temp("owner", "davida");
        set_temp("owner_name", "波波");
        ::setup();
}
