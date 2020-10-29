// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[41;1m[1;33m睡袋[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "alias m whistle sleepbag[2;37;0m
它是老汉的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "laohanf");
        set("owner_name", "老汉");
        set_temp("owner", "laohanf");
        set_temp("owner_name", "老汉");
        ::setup();
}
