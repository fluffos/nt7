// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("好的[2;37;0m[2;37;0m", ({"xwdppd"}));        
        set("gender", "女性");                
        set("long", "好的[2;37;0m
它是武当师四的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wdppd");
        set("owner_name", "武当师四");
        set_temp("owner", "wdppd");
        set_temp("owner_name", "武当师四");
        ::setup();
}
