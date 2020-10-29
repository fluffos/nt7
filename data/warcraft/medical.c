// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m九花玉露丸[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "$HIG$九花玉露丸[2;37;0m
它是丹丹的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "medical");
        set("owner_name", "丹丹");
        set_temp("owner", "medical");
        set_temp("owner_name", "丹丹");
        ::setup();
}
