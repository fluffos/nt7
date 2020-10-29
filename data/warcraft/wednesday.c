// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m一[1;31m日[5m[1;36m三天[2;37;0m[2;37;0m[2;37;0m", ({"wed"}));        
        set("gender", "女性");                
        set("long", "$HIG$一$HIR$日$BLINK$$HIC$三天$NOR$[2;37;0m
它是星期三的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wednesday");
        set("owner_name", "星期三");
        set_temp("owner", "wednesday");
        set_temp("owner_name", "星期三");
        ::setup();
}
