// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小鸟啊[2;37;0m[2;37;0m", ({"wwqqaa"}));        
        set("gender", "男性");                
        set("long", "这不是一只小鸟[2;37;0m
它是东方布败的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dongfang");
        set("owner_name", "东方布败");
        set_temp("owner", "dongfang");
        set_temp("owner_name", "东方布败");
        ::setup();
}
