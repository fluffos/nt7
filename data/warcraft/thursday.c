// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m一[1;31m日[5m[1;36m四天[2;37;0m[2;37;0m[2;37;0m", ({"thu"}));        
        set("gender", "女性");                
        set("long", "$HIG$一$HIR$日$BLINK$$HIC$四天$NOR$[2;37;0m
它是星期四的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "thursday");
        set("owner_name", "星期四");
        set_temp("owner", "thursday");
        set_temp("owner_name", "星期四");
        ::setup();
}
