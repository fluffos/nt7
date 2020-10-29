// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小麒麒[2;37;0m[2;37;0m", ({"sleepbag"}));        
        set("gender", "女性");                
        set("long", "我的么幻兽我的魔幻兽[2;37;0m
它是司马不平的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "monzan");
        set("owner_name", "司马不平");
        set_temp("owner", "monzan");
        set_temp("owner_name", "司马不平");
        ::setup();
}
