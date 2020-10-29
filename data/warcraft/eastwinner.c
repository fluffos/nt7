// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小青龙[2;37;0m[2;37;0m", ({"qinglonga"}));        
        set("gender", "男性");                
        set("long", "我是一只小青龙，小青龙，我有许多小秘密，小秘密。[2;37;0m
它是东方常胜的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "eastwinner");
        set("owner_name", "东方常胜");
        set_temp("owner", "eastwinner");
        set_temp("owner_name", "东方常胜");
        ::setup();
}
