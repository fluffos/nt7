// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("大狗[2;37;0m[2;37;0m", ({"zbz"}));        
        set("gender", "男性");                
        set("long", "大狗[2;37;0m
它是故人难忘的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "qianmb");
        set("owner_name", "故人难忘");
        set_temp("owner", "qianmb");
        set_temp("owner_name", "故人难忘");
        ::setup();
}
