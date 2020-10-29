// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("相无可厚非[2;37;0m[2;37;0m", ({"qilina"}));        
        set("gender", "男性");                
        set("long", "  [2;37;0m
它是雪甲的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "xueshana");
        set("owner_name", "雪甲");
        set_temp("owner", "xueshana");
        set_temp("owner_name", "雪甲");
        ::setup();
}
